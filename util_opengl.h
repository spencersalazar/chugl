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

#ifndef UTIL_OPENGL
#define UTIL_OPENGL

#include "chuck_def.h"

#ifdef __APPLE__
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>
#else
#include <gl/gl.h>
#endif // __APPLE__

void gen2d_ellipse_fan(GLfloat *buf, GLint nVertex, float x, float y, float xRadius, float yRadius);
void HSVtoRGB( t_CKFLOAT *r, t_CKFLOAT *g, t_CKFLOAT *b, t_CKFLOAT h, t_CKFLOAT s, t_CKFLOAT v );

#endif // UTIL_OPENGL
