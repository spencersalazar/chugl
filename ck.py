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

#include "chugl.h"
#include "chugl_opengl.h"

#include "chuck_dl.h"
#include "chuck_def.h"
#include "chuck_type.h"

#include "chugl_util.h"

#include "glplat.h"

// general includes
#include <stdio.h>
#include <limits.h>

t_CKINT Chuck_OpenGL_offset_chugl = 0;

CK_DLL_CTOR(Chuck_OpenGL_ctor)
{{
    OBJ_MEMBER_OBJECT(SELF, Chuck_OpenGL_offset_chugl) = NULL;
}}

{chugin_defines}

{chugin_query}
{{
    // hmm, don't change this...
    QUERY->setname(QUERY, "OpenGL");
    
    // begin the class definition
    // can change the second argument to extend a different ChucK class
    QUERY->begin_class(QUERY, "OpenGL", "Object");
    
    Chuck_OpenGL_offset_chugl = QUERY->add_mvar(QUERY, "int", "@chugl_data", FALSE);
    
    QUERY->add_ctor(QUERY, Chuck_OpenGL_ctor);
    
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
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good()) return;
    
    chgl->enter();
    
{mfun_getargs}
    {mfun_call_and_return}
}}

"""

int_arg_type = '    t_CKINT {arg_var} = GET_NEXT_INT(ARGS);\n'
float_arg_type = '    t_CKFLOAT {arg_var} = GET_NEXT_FLOAT(ARGS);\n'
int_array1_type = """    Chuck_Array4 *{arg_var}_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    {arr_type} *{arg_var} = new {arr_type}[{arg_var}_arr->size()];
    chgl->scheduleDataForCleanup({arg_var});
    copy_ckarray4_to_array({arg_var}, {arg_var}_arr);
"""
### TODO: fix for 32 bit (only correct for 64 bit)
float_array1_type = """    Chuck_Array8 *{arg_var}_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    {arr_type} *{arg_var} = new {arr_type}[{arg_var}_arr->size()];
    chgl->scheduleDataForCleanup({arg_var});
    copy_ckarray8_to_array({arg_var}, {arg_var}_arr);
"""
### TODO: fix for 32 bit (only correct for 64 bit)
double_array1_type = """    Chuck_Array8 *{arg_var}_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    {arg_var}_arr->add_ref();
    chgl->scheduleArrayForCleanup({arg_var}_arr);
    {arr_type} *{arg_var} = &({arg_var}_arr->m_vector.front());
"""
# void_array1_type = """    Chuck_Array *_{arg_var}_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
#     void *{arg_var};
#     if(_{arg_var}_arr->m_array_type == &t_int)
#     {{{{
#         Chuck_Array4 *{arg_var}_arr = (Chuck_Array4 *) _{arg_var}_arr;
#         GLubyte *{arg_var}_v = new GLubyte[{arg_var}_arr->size()];
#         chgl->scheduleArrayForCleanup({arg_var}_v);
#         copy_ckarray4_to_array({arg_var}_v, {arg_var}_arr);
#         {arg_var} = (void *) {arg_var}_v;
#     }}}}
#     else if(_{arg_var}_arr->m_array_type == &t_float)
#     {{{{
#         Chuck_Array8 *{arg_var}_arr = (Chuck_Array8 *) _{arg_var}_arr;
#         GLfloat *{arg_var}_v = new GLfloat[{arg_var}_arr->size()];
#         chgl->scheduleArrayForCleanup({arg_var}_v);
#         copy_ckarray8_to_array({arg_var}_v, {arg_var}_arr);
#         {arg_var} = (void *) {arg_var}_v;
#     }}}}
# """

### TODO: fix for 32 bit (only correct for 64 bit)
void_array1_type = """    Chuck_Array *_{arg_var}_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *{arg_var};
    if(_{arg_var}_arr->data_type_kind() == CHUCK_ARRAY4_DATAKIND)
    {{{{
        Chuck_Array4 *{arg_var}_arr = (Chuck_Array4 *) _{arg_var}_arr;
        GLubyte *{arg_var}_v = new GLubyte[{arg_var}_arr->size()];
        chgl->scheduleDataForCleanup({arg_var}_v);
        copy_ckarray4_to_array({arg_var}_v, {arg_var}_arr);
        {arg_var} = (void *) {arg_var}_v;
    }}}}
    else if(_{arg_var}_arr->data_type_kind() == CHUCK_ARRAY8_DATAKIND)
    {{{{
        Chuck_Array4 *{arg_var}_arr = (Chuck_Array4 *) _{arg_var}_arr;
        {arg_var}_arr->add_ref();
        chgl->scheduleArrayForCleanup({arg_var}_arr);
        {arg_var} = (void *) &({arg_var}_arr->m_vector.front());
    }}}}
    else
    {{{{
        assert(0);
    }}}}
"""

define_get_arg_type = {
    'GLenum': int_arg_type,
    'GLshort': int_arg_type,
    'GLushort': int_arg_type,
    'GLint': int_arg_type,
    'GLuint': int_arg_type,
    'GLsizei': int_arg_type,
    'GLbitfield': int_arg_type,
    'GLfloat': float_arg_type,
    'GLdouble': float_arg_type,
    'GLboolean': int_arg_type,
    'GLbyte': int_arg_type,
    'GLubyte': int_arg_type,
    
    'constGLushort*': int_array1_type.format(arr_type='GLushort', arg_var='{arg_var}'),
    'GLushort*': int_array1_type.format(arr_type='GLushort', arg_var='{arg_var}'),
    'constGLboolean*': int_array1_type.format(arr_type='GLboolean', arg_var='{arg_var}'),
    'GLboolean*': int_array1_type.format(arr_type='GLboolean', arg_var='{arg_var}'),
    'constGLbyte*': int_array1_type.format(arr_type='GLbyte', arg_var='{arg_var}'),
    'GLbyte*': int_array1_type.format(arr_type='GLbyte', arg_var='{arg_var}'),
    'constGLint*': int_array1_type.format(arr_type='GLint', arg_var='{arg_var}'),
    'GLint*': int_array1_type.format(arr_type='GLint', arg_var='{arg_var}'),
    'constGLsizei*': int_array1_type.format(arr_type='GLsizei', arg_var='{arg_var}'),
    'GLsizei*': int_array1_type.format(arr_type='GLsizei', arg_var='{arg_var}'),
    'constGLuint*': int_array1_type.format(arr_type='GLuint', arg_var='{arg_var}'),
    'GLuint*': int_array1_type.format(arr_type='GLuint', arg_var='{arg_var}'),
    'constGLenum*': int_array1_type.format(arr_type='GLenum', arg_var='{arg_var}'),
    'GLenum*': int_array1_type.format(arr_type='GLenum', arg_var='{arg_var}'),
    'constGLchar*': int_array1_type.format(arr_type='GLchar', arg_var='{arg_var}'),
    'GLchar*': int_array1_type.format(arr_type='GLchar', arg_var='{arg_var}'),
    'constGLubyte*': int_array1_type.format(arr_type='GLubyte', arg_var='{arg_var}'),
    'GLubyte*': int_array1_type.format(arr_type='GLubyte', arg_var='{arg_var}'),
    'constGLshort*': int_array1_type.format(arr_type='GLshort', arg_var='{arg_var}'),
    'GLshort*': int_array1_type.format(arr_type='GLshort', arg_var='{arg_var}'),
    
    'constGLdouble*': double_array1_type.format(arr_type='GLdouble', arg_var='{arg_var}'),
    'GLdouble*': double_array1_type.format(arr_type='GLdouble', arg_var='{arg_var}'),
    'constGLfloat*': float_array1_type.format(arr_type='GLfloat', arg_var='{arg_var}'),
    'GLfloat*': float_array1_type.format(arr_type='GLfloat', arg_var='{arg_var}'),
    
    'constvoid*': void_array1_type.format(arg_var='{arg_var}'),
    'void*': void_array1_type.format(arg_var='{arg_var}'),
}

void_call_and_return = '{func_call};'
int_call_and_return = 'RETURN->v_int = {func_call};'
float_call_and_return = 'RETURN->v_float = {func_call};'
int_array1_call_and_return = """    
"""

define_call_and_return = {
    'void': void_call_and_return,
    'GLvoid': void_call_and_return,
    'GLenum': int_call_and_return,
    'GLshort': int_call_and_return,
    'GLushort': int_call_and_return,
    'GLint': int_call_and_return,
    'GLuint': int_call_and_return,
    'GLsizei': int_call_and_return,
    'GLbitfield': int_call_and_return,
    'GLfloat': float_call_and_return,
    'GLdouble': float_call_and_return,
    'GLboolean': int_call_and_return,
    'GLbyte': int_call_and_return,
    'GLubyte': int_call_and_return,
}

import_mfun_template = """
    QUERY->add_mfun(QUERY, Chuck_OpenGL_{mfun_name}, "{return_type}", "{mfun_name}");
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
    'GLbyte': 'int',
    'GLubyte': 'int',
    
    'constGLushort*': 'int[]',
    'GLushort*': 'int[]',
    'constGLboolean*': 'int[]',
    'GLboolean*': 'int[]',
    'constGLubyte*': 'int[]',
    'GLubyte*': 'int[]',
    'constGLbyte*': 'int[]',
    'GLbyte*': 'int[]',
    'constGLint*': 'int[]',
    'GLint*': 'int[]',
    'constGLsizei*': 'int[]',
    'GLsizei*': 'int[]',
    'constGLuint*': 'int[]',
    'GLuint*': 'int[]',
    'constGLenum*': 'int[]',
    'GLenum*': 'int[]',
    'constGLchar*': 'int[]',
    'GLchar*': 'int[]',
    'constGLubyte*': 'int[]',
    'GLubyte*': 'int[]',
    'constGLshort*': 'int[]',
    'GLshort*': 'int[]',
    
    'constGLchar*const*': 'int[][]',
    'GLchar*const*': 'int[][]',
    
    'constGLdouble*': 'float[]',
    'GLdouble*': 'float[]',
    'constGLfloat*': 'float[]',
    'GLfloat*': 'float[]',
    
    'constvoid*': 'Object',
    'void*': 'Object',
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
        self.unknown_types = dict()
        self.skipped = []
        
    #
    def beginFile(self, genOpts):
        OutputGenerator.beginFile(self, genOpts)

    def endFile(self):
        code = chugin_template.format(chugin_defines=self.defines, chugin_query=chugin_query_static, chugin_imports=self.imports)
        self.outFile.write(code);
        # Finish processing in superclass
        OutputGenerator.endFile(self)
        
        print "skipped:"
        for c in self.skipped:
            # print "%s %s" % (t, self.unknown_types[t])
            print "%s" % c
        
        print "unknown types:"
        for t in self.unknown_types:
            # print "%s %s" % (t, self.unknown_types[t])
            print "%s" % t
    
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
        if proto is None and proto.text is None and len(proto) == 0:
            self.skipped.append(name)
            return
        rtype = ''
        proto_ptype = proto.find('ptype')
        if proto_ptype is not None:
            if proto_ptype.text is not None: rtype += proto_ptype.text
            if proto_ptype.tail is not None: rtype += proto_ptype.tail
        elif proto.text is not None: rtype += proto.text
        rtype = re.sub(r'\s', '', rtype)
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
        
        type_fail = False
        if rtype not in define_call_and_return:
            if rtype not in self.unknown_types: self.unknown_types[rtype] = []
            self.unknown_types[rtype].append(name)
            type_fail = True
        for param in params:
            if param['type'] not in define_get_arg_type:
                if param['type'] not in self.unknown_types: self.unknown_types[param['type']] = []
                self.unknown_types[param['type']].append(name)
                type_fail = True
        if type_fail:
            self.skipped.append(cfun_name)
            return
        
        getargs = ''
        callargs = []
        import_args = ''
        for param in params:
            ptype = param['type']
            cktype = gltype2cktype[ptype]
            arg_var = 'arg_' + param['name']
            getargs += define_get_arg_type[ptype].format(arg_var=arg_var)
            callargs.append(arg_var)
            import_args += import_arg.format(arg_type=cktype, arg_name=param['name'])
        
        call_and_return = define_call_and_return[rtype].format(func_call='%s(%s)' % (cfun_name, ', '.join(callargs)))
        
        self.defines += define_mfun_template.format(mfun_name=name, 
            mfun_getargs=getargs, mfun_call_and_return=call_and_return)
        self.imports += import_mfun_template.format(mfun_name=name, return_type=gltype2cktype[rtype], import_args=import_args)
        
