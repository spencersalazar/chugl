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

#include "util_shader.h"

#include <stdio.h>
#include <stdlib.h>

GLuint createProgramWithDefaultAttributes(const char *vertSrc, const char *fragSrc)
{
    GLuint vertShader, fragShader;
    GLuint _program = 0;
    
    // Create shader program.
    _program = glCreateProgram();
    
    // Create and compile vertex shader.
    if (!compileShader(&vertShader, GL_VERTEX_SHADER, vertSrc)) {
        fprintf(stderr, "Failed to compile vertex shader");
        glDeleteProgram(_program);
        return 0;
    }
    
    // Create and compile fragment shader.
    if (!compileShader(&fragShader, GL_FRAGMENT_SHADER, fragSrc)) {
        fprintf(stderr, "Failed to compile fragment shader");
        glDeleteProgram(_program);
        return 0;
    }
    
    // Attach vertex shader to program.
    glAttachShader(_program, vertShader);
    
    // Attach fragment shader to program.
    glAttachShader(_program, fragShader);
    
    // Bind attribute locations.
    // This needs to be done prior to linking.
    glBindAttribLocation(_program, CHUGL_SHADER_POSITION, "position");
    glBindAttribLocation(_program, CHUGL_SHADER_NORMAL, "normal");
    glBindAttribLocation(_program, CHUGL_SHADER_COLOR, "color");
    glBindAttribLocation(_program, CHUGL_SHADER_TEXCOORD0, "texcoord0");
    
    // Link program.
    if (!linkProgram(_program)) {
        fprintf(stderr, "Failed to link program: %d", _program);
        
        if (vertShader) {
            glDeleteShader(vertShader);
            vertShader = 0;
        }
        if (fragShader) {
            glDeleteShader(fragShader);
            fragShader = 0;
        }
        if (_program) {
            glDeleteProgram(_program);
            _program = 0;
        }
        
        return 0;
    }
    
    // Release vertex and fragment shaders.
    if (vertShader) {
        glDetachShader(_program, vertShader);
        glDeleteShader(vertShader);
    }
    if (fragShader) {
        glDetachShader(_program, fragShader);
        glDeleteShader(fragShader);
    }
    
    return _program;
}


bool compileShader(GLuint *shader, GLenum type, const char *src)
{
    GLint status;
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &src, NULL);
    glCompileShader(*shader);
    
#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        fprintf(stderr, "Shader compile log:\n%s", log);
        free(log);
    }
#endif
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        glDeleteShader(*shader);
        return false;
    }
    
    return true;
}

bool linkProgram(GLuint prog)
{
    GLint status;
    glLinkProgram(prog);
    
#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        fprintf(stderr, "Program link log:\n%s", log);
        free(log);
    }
#endif
    
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == 0) {
        return false;
    }
    
    return true;
}

bool validateProgram(GLuint prog)
{
    GLint logLength, status;
    
    glValidateProgram(prog);
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        fprintf(stderr, "Program validate log:\n%s", log);
        free(log);
    }
    
    glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
    if (status == 0) {
        return false;
    }
    
    return true;
}
