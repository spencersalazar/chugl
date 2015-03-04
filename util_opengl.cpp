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

#include "util_opengl.h"

#include <stdlib.h>
#include <math.h>

template<typename V>
inline V &v2d_x(V *v, size_t i) { return v[i*2]; }
template<typename V>
inline V &v2d_y(V *v, size_t i) { return v[i*2+1]; }

void gen2d_ellipse_fan(GLfloat *buf, GLint nVertex, float x, float y, float xRadius, float yRadius)
{
    v2d_x(buf,0) = x; v2d_y(buf,0) = y;
    float two_pi = 2.0f*M_PI;
    for(int i = 1; i < nVertex; i++)
    {
        float fraction = ((float)(i-1))/(nVertex-2);
        v2d_x(buf, i) = xRadius*cos(fraction*two_pi);
        v2d_y(buf, i) = yRadius*sin(fraction*two_pi);
    }
}
