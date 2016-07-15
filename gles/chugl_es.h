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

#ifndef CHUGL_ES_H
#define CHUGL_ES_H

#include "chugl.h"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include <list>


class chugl_es : public chugl
{
public:
    chugl_es();
    virtual ~chugl_es();

    glm::vec4 color;
    std::list<glm::mat4x4> proj;
    std::list<glm::mat4x4> modelview;
    
    /*
     * Draw specified 2d geometry with default color. 
     */
    void render2d(glm::vec2 *pos, GLuint num, GLenum mode);

protected:
    virtual void backendEnter();
    virtual void backendExit();
    
    void loadShader2d();
    
    GLint m_2dshader;
    GLint m_2dshader_uniform_modelviewproj;
    GLint m_2dshader_uniform_normal;
};

#endif // CHUGL_ES_H
