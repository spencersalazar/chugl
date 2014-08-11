# ----------------------------------------------------------------------------
# chugl
# Chuck OpenGL library module
#
# Copyright (c) 2014 Spencer Salazar.  All rights reserved.
# https://ccrma.stanford.edu/~spencer/
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
# U.S.A.
# ----------------------------------------------------------------------------

import re

from reg import *

chugin_template = """
/*----------------------------------------------------------------------------
  chugl
  Chuck OpenGL library module

  Copyright (c) 2014 Spencer Salazar.  All rights reserved.
  https://ccrma.stanford.edu/~spencer/

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  U.S.A.
-----------------------------------------------------------------------------*/

#include "chuck_dl.h"
#include "chuck_def.h"

#ifdef __APPLE__
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>
#else
#include <gl/gl.h>
#endif // __APPLE__

// general includes
#include <stdio.h>
#include <limits.h>


{chugin_defines}

{chugin_query}
{{
    // hmm, don't change this...
    QUERY->setname(QUERY, "OpenGL");
    
    // begin the class definition
    // can change the second argument to extend a different ChucK class
    QUERY->begin_class(QUERY, "OpenGL", "Object");
    
{chugin_imports}
    
    QUERY->end_class(QUERY);
    
    return TRUE;
}}

"""

chugin_query_dynamic="CK_DLL_QUERY( OpenGL )"
chugin_query_static="t_CKBOOL OpenGL_query(Chuck_DL_Query *QUERY)"

define_mfun_template = """
CK_DLL_MFUN(Chuck_OpenGL_{mfun_name})
{{
{mfun_getargs}
    {mfun_return}{cfun_name}({mfun_args});
}}

""";

define_get_arg_type = {
    'int': '    t_CKINT {arg_var} = GET_NEXT_INT(ARGS);\n',
    'float': '    t_CKFLOAT {arg_var} = GET_NEXT_FLOAT(ARGS);\n',
}

define_return_type = {
    'void': '',
    'int': 'RETURN->v_int = ',
    'float': 'RETURN->v_float = ',
}

import_mfun_template = """    QUERY->add_mfun(QUERY, Chuck_OpenGL_{mfun_name}, "{return_type}", "{mfun_name}");
{import_args}

""";
import_arg = """    QUERY->add_arg(QUERY, \"{arg_type}\", \"{arg_name}\");
""";

define_svar_template = """static const t_CKINT Chuck_OpenGL_{svar_name} = {svar_constant_name};
"""
import_svar_template = """    QUERY->add_svar( QUERY, "int", "{svar_name}", TRUE, (void *)&Chuck_OpenGL_{svar_name} );
""";

gltype2cktype = {
    'void': 'void',
    'GLvoid': 'void',
    'GLenum': 'int',
    'GLshort': 'int',
    'GLushort': 'int',
    'GLint': 'int',
    'GLuint': 'int',
    'GLsizei': 'int',
    'GLbitfield': 'int',
    'GLfloat': 'float',
    'GLdouble': 'float',
    'GLboolean': 'int',
    'GLubyte': 'int',
}

class ChuginOutputGenerator(OutputGenerator):
    """Generate specified API interfaces for ChucK chugin"""
    def __init__(self,
                 errFile = sys.stderr,
                 warnFile = sys.stderr,
                 diagFile = sys.stdout):
        OutputGenerator.__init__(self, errFile, warnFile, diagFile)
        # Internal state - accumulators for different inner block text
        self.defines = ''
        self.imports = ''
        
    #
    def beginFile(self, genOpts):
        OutputGenerator.beginFile(self, genOpts)

    def endFile(self):
        code = chugin_template.format(chugin_defines=self.defines, chugin_query=chugin_query_static, chugin_imports=self.imports)
        self.outFile.write(code);
        # Finish processing in superclass
        OutputGenerator.endFile(self)
    
    def beginFeature(self, interface, emit):
        # Start processing in superclass
        OutputGenerator.beginFeature(self, interface, emit)

    def endFeature(self):
        # Finish processing in superclass
        OutputGenerator.endFeature(self)
    
    # Type generation
    def genType(self, typeinfo, name):
        OutputGenerator.genType(self, typeinfo, name)
    
    # Enumerant generation
    def genEnum(self, enuminfo, name):
        OutputGenerator.genEnum(self, enuminfo, name)
        
        svar_name = re.sub(r'^GL_', '', name)
        
        self.defines += define_svar_template.format(svar_name=svar_name, svar_constant_name=name)
        self.imports += import_svar_template.format(svar_name=svar_name)
    
    #
    # Command generation
    def genCmd(self, cmdinfo, name):
        OutputGenerator.genCmd(self, cmdinfo, name)
        
        proto = cmdinfo.elem.find('proto')
        if proto is None or proto.text is None:
            return
        rtype = re.sub(r'\s', '', proto.text)
        cfun_name = proto.find('name').text
        name = re.sub(r'^gl', '', cfun_name)
        
        xparams = cmdinfo.elem.findall('param')
        params = []
        for xparam in xparams:
            param = {}
            param['name'] = xparam.find('name').text
            ptype = xparam.find('ptype')
            if ptype is not None:
                typestr = ''
                if xparam.text is not None: typestr += xparam.text
                if ptype.text is not None: typestr += ptype.text
                if ptype.tail is not None: typestr += ptype.tail
                param['type'] = re.sub('\s', '', typestr)
            else:
                param['type'] = re.sub('\s', '', xparam.text)
            params.append(param)
        
        if rtype not in gltype2cktype:
            print 'rtype not found: %s' % rtype
            return
        for param in params:
            if param['type'] not in gltype2cktype:
                print 'param type not found: %s' % param['type']
                return
        
        getargs = ''
        callargs = []
        import_args = ''
        for param in params:
            cktype = gltype2cktype[param['type']]
            arg_var = 'arg_' + param['name']
            getargs += define_get_arg_type[cktype].format(arg_var=arg_var)
            callargs.append(arg_var)
            import_args += import_arg.format(arg_type=cktype, arg_name=param['name'])
        
        self.defines += define_mfun_template.format(mfun_name=name, 
            mfun_getargs=getargs, mfun_return=define_return_type[gltype2cktype[rtype]], 
            cfun_name=cfun_name, mfun_args=', '.join(callargs))
        self.imports += import_mfun_template.format(mfun_name=name, return_type=gltype2cktype[rtype], import_args=import_args)

