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

#include "chugl_es.h"
#include "chugl_opengl.h"
#include "util_shader.h"

#include "chuck_errmsg.h"

#include "glplat.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

namespace {
    // put in anonymous namespace to hide from other files
    extern const char *g_vert2d_shader;
    extern const char *g_frag2d_shader;
}

chugl_es::chugl_es() : chugl()
{
    m_2dshader = 0;
    
    proj.push_back(glm::mat4x4());
    proj.front() = glm::ortho<float>(0, windowWidth(), 0, windowHeight(), -0.1, 100);
    
    modelview.push_back(glm::mat4x4());
}

chugl_es::~chugl_es()
{
    glDeleteProgram(m_2dshader);
    m_2dshader = 0;
}

void chugl_es::backendEnter()
{
    // clear matrix stacks
    proj.clear();
    modelview.clear();
    
    // set default color
    color = glm::vec4(1, 1, 1, 1);
    
    // push default projection matrix
    proj.push_back(glm::mat4x4());
    proj.front() = glm::ortho<float>(0, windowWidth(), 0, windowHeight(), -0.1, 100);
    
    // push default modelview matrix
    modelview.push_back(glm::mat4x4());
}

void chugl_es::backendExit()
{
    glFlush();
}

void chugl_es::loadShader2d()
{
    if(m_2dshader == 0)
    {
        m_2dshader = createProgramWithDefaultAttributes(g_vert2d_shader, g_frag2d_shader);
        m_2dshader_uniform_modelviewproj = glGetUniformLocation(m_2dshader, "uMatMvp");
        m_2dshader_uniform_normal = glGetUniformLocation(m_2dshader, "uMatNormal");
    }
}

void chugl_es::render2d(glm::vec2 *pos, GLuint num, GLenum mode)
{
    loadShader2d();
    
    glUseProgram(m_2dshader);
    
    glVertexAttrib4fv(CHUGL_SHADER_COLOR, &color[0]);
    glDisableVertexAttribArray(CHUGL_SHADER_COLOR);
    
    glVertexAttrib3f(CHUGL_SHADER_NORMAL, 0, 0, -1);
    glDisableVertexAttribArray(CHUGL_SHADER_NORMAL);
    
    glDisableVertexAttribArray(CHUGL_SHADER_TEXCOORD0);
    
    glVertexAttribPointer(CHUGL_SHADER_POSITION, 2, GL_FLOAT, GL_FALSE, 0, &pos[0]);
    glEnableVertexAttribArray(CHUGL_SHADER_POSITION);
    
    glm::mat4x4 mvp = proj.front()*modelview.front();
    glUniformMatrix4fv(m_2dshader_uniform_modelviewproj, 1, GL_FALSE, &mvp[0][0]);
    glm::mat3x3 normal = glm::mat3x3(glm::inverseTranspose(modelview.front()));
    glUniformMatrix3fv(m_2dshader_uniform_normal, 1, GL_FALSE, &normal[0][0]);
    
    glDrawArrays(mode, 0, num);
}

void chugl_es::render2d(GLfloat *pos, GLuint num, GLenum mode)
{
    loadShader2d();
    
    glUseProgram(m_2dshader);
    
    glVertexAttrib4fv(CHUGL_SHADER_COLOR, &color[0]);
    glDisableVertexAttribArray(CHUGL_SHADER_COLOR);
    
    glVertexAttrib3f(CHUGL_SHADER_NORMAL, 0, 0, -1);
    glDisableVertexAttribArray(CHUGL_SHADER_NORMAL);
    
    glDisableVertexAttribArray(CHUGL_SHADER_TEXCOORD0);
    
    glVertexAttribPointer(CHUGL_SHADER_POSITION, 2, GL_FLOAT, GL_FALSE, 0, pos);
    glEnableVertexAttribArray(CHUGL_SHADER_POSITION);
    
    glm::mat4x4 mvp = proj.front()*modelview.front();
    glUniformMatrix4fv(m_2dshader_uniform_modelviewproj, 1, GL_FALSE, &mvp[0][0]);
    glm::mat3x3 normal = glm::mat3x3(glm::inverseTranspose(modelview.front()));
    glUniformMatrix3fv(m_2dshader_uniform_normal, 1, GL_FALSE, &normal[0][0]);
    
    glDrawArrays(mode, 0, num);
}

namespace {
    const char *g_vert2d_shader = "\n\
attribute vec4 position;\n\
attribute vec3 normal;\n\
attribute vec4 color;\n\
attribute vec2 texcoord0;\n\
\n\
varying lowp vec4 vColor;\n\
\n\
uniform mat4 uMatMvp;\n\
uniform mat3 uMatNormal;\n\
\n\
void main()\n\
{\n\
    vec3 eyeNormal = normalize(uMatNormal * normal);\n\
    vec3 lightPosition = vec3(0.0, 0.0, -1.0);\n\
    vec4 diffuseColor = vec4(1.0, 1.0, 1.0, 1.0);\n\
    \n\
    float nDotVP = max(0.0, dot(eyeNormal, normalize(lightPosition)));\n\
    \n\
    vColor = diffuseColor * nDotVP * color;\n\
    //vColor = color;\n\
    \n\
    gl_Position = uMatMvp*position;\n\
}\n\
";
    
    const char *g_frag2d_shader = "\n\
varying lowp vec4 vColor;\n\
\n\
void main()\n\
{\n\
    gl_FragColor = vColor;\n\
    //gl_FragColor = vec4(1, 1, 1, 1);\n\
}\n\
";
}





