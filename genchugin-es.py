#!/usr/bin/env python
#
# Copyright (c) 2013-2014 The Khronos Group Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and/or associated documentation files (the
# "Materials"), to deal in the Materials without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Materials, and to
# permit persons to whom the Materials are furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Materials.
#
# THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.

import sys, time, pdb, string, cProfile
from reg import *
from ck import *

# debug - start header generation in debugger
# dump - dump registry after loading
# profile - enable Python profiling
# protect - whether to use #ifndef protections
# registry <filename> - use specified XML registry instead of gl.xml
# target - string name of target header, or all targets if None
# timeit - time length of registry loading & header generation
# validate - validate return & parameter group tags against <group>
debug   = False
dump    = False
profile = False
protect = True
target  = None
timeit  = False
validate= False
# Default input / log files
errFilename = None
diagFilename = 'OpenGL/diag.txt'
regFilename = 'OpenGL/gl.xml'

if __name__ == '__main__':
    i = 1
    while (i < len(sys.argv)):
        arg = sys.argv[i]
        i = i + 1
        if (arg == '-debug'):
            write('Enabling debug (-debug)', file=sys.stderr)
            debug = True
        elif (arg == '-dump'):
            write('Enabling dump (-dump)', file=sys.stderr)
            dump = True
        elif (arg == '-noprotect'):
            write('Disabling inclusion protection in output headers', file=sys.stderr)
            protect = False
        elif (arg == '-profile'):
            write('Enabling profiling (-profile)', file=sys.stderr)
            profile = True
        elif (arg == '-registry'):
            regFilename = sys.argv[i]
            i = i+1
            write('Using registry ', regFilename, file=sys.stderr)
        elif (arg == '-time'):
            write('Enabling timing (-time)', file=sys.stderr)
            timeit = True
        elif (arg == '-validate'):
            write('Enabling group validation (-validate)', file=sys.stderr)
            validate = True
        elif (arg[0:1] == '-'):
            write('Unrecognized argument:', arg, file=sys.stderr)
            exit(1)
        else:
            target = arg
            write('Using target', target, file=sys.stderr)

# Simple timer functions
startTime = None
def startTimer():
    global startTime
    startTime = time.clock()
def endTimer(msg):
    global startTime
    endTime = time.clock()
    if (timeit):
        write(msg, endTime - startTime)
        startTime = None

# Load & parse registry
reg = Registry()

startTimer()
tree = etree.parse(regFilename)
endTimer('Time to make ElementTree =')

startTimer()
reg.loadElementTree(tree)
endTimer('Time to parse ElementTree =')

if (validate):
    reg.validateGroups()

if (dump):
    write('***************************************')
    write('Performing Registry dump to regdump.txt')
    write('***************************************')
    reg.dumpReg(filehandle = open('regdump.txt','w'))

# Turn a list of strings into a regexp string matching exactly those strings
def makeREstring(list):
    return '^(' + '|'.join(list) + ')$'

# These are "mandatory" OpenGL ES 1 extensions, to
# be included in the core GLES/gl.h header.
es1CoreList = [
    'GL_OES_read_format',
    'GL_OES_compressed_paletted_texture',
    'GL_OES_point_size_array',
    'GL_OES_point_sprite'
]

# Descriptive names for various regexp patterns used to select
# versions and extensions

allVersions     = allExtensions = '.*'
noVersions      = noExtensions = None
gl12andLaterPat = '1\.[2-9]|[234]\.[0-9]'
belowgl3Pat = '(1|2)\.[0-9]'
gles2onlyPat    = '2\.[0-9]'
gles2and30Pat   = '2\.[0-9]|3.0'
gles2and30and31Pat    = '2.[0-9]|3.[01]'
es1CorePat      = makeREstring(es1CoreList)
# Extensions in old glcorearb.h but not yet tagged accordingly in gl.xml
glCoreARBPat    = None
glx13andLaterPat = '1\.[3-9]'

# Copyright text prefixing all headers (list of strings).
prefixStrings = [
    '/*',
    '** Copyright (c) 2013-2014 The Khronos Group Inc.',
    '**',
    '** Permission is hereby granted, free of charge, to any person obtaining a',
    '** copy of this software and/or associated documentation files (the',
    '** "Materials"), to deal in the Materials without restriction, including',
    '** without limitation the rights to use, copy, modify, merge, publish,',
    '** distribute, sublicense, and/or sell copies of the Materials, and to',
    '** permit persons to whom the Materials are furnished to do so, subject to',
    '** the following conditions:',
    '**',
    '** The above copyright notice and this permission notice shall be included',
    '** in all copies or substantial portions of the Materials.',
    '**',
    '** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,',
    '** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF',
    '** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.',
    '** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY',
    '** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,',
    '** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE',
    '** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.',
    '*/',
    '/*',
    '** This header is generated from the Khronos OpenGL / OpenGL ES XML',
    '** API Registry. The current version of the Registry, generator scripts',
    '** used to make the header, and the header can be found at',
    '**   http://www.opengl.org/registry/',
    '**',
    '** Khronos $' + 'Revision$ on $' + 'Date$',
    '*/',
    ''
]

# wglext.h needs Windows include
wglPlatformStrings = [
    '#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)',
    '#define WIN32_LEAN_AND_MEAN 1',
    '#include <windows.h>',
    '#endif',
    '',
]


# Insert generation date in a comment for headers not having *GLEXT_VERSION macros
genDateCommentString = [
    format("/* Generated on date %s */" % time.strftime("%Y%m%d")),
    ''
]


buildList = [
    # GLES 3.1 / 3.0 / 2.0 extensions - GLES2/gl2ext.h
    GeneratorOptions(
        filename          = 'chugl_opengles.cpp',
        apiname           = 'gles2',
        profile           = 'common',
        versions          = gles2onlyPat,
        emitversions      = allVersions,
        defaultExtensions = None,                # Default extensions for GLES 2
        addExtensions     = None,
        removeExtensions  = None,
        ),
    None
]

# create error/warning & diagnostic files
if (errFilename):
    errWarn = open(errFilename,'w')
else:
    errWarn = sys.stderr
diag = open(diagFilename, 'w')

def genHeaders():
    # Loop over targets, building each
    generated = 0
    for genOpts in buildList:
        if (genOpts == None):
            break
        if (target and target != genOpts.filename):
            # write('*** Skipping', genOpts.filename)
            continue
        write('*** Building', genOpts.filename)
        generated = generated + 1
        startTimer()
        gen = ChuginOutputGenerator(errFile=errWarn,
                                    warnFile=errWarn,
                                    diagFile=diag)
        reg.setGenerator(gen)
        reg.apiGen(genOpts)
        write('** Generated', genOpts.filename)
        endTimer('Time to generate ' + genOpts.filename + ' =')
    if (target and generated == 0):
        write('Failed to generate target:', target)

if (debug):
    pdb.run('genHeaders()')
elif (profile):
    import cProfile, pstats
    cProfile.run('genHeaders()', 'profile.txt')
    p = pstats.Stats('profile.txt')
    p.strip_dirs().sort_stats('time').print_stats(50)
else:
    genHeaders()
