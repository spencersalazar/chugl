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
/*
 * OpenGL headers by platform
 */


#ifndef GLPLAT_H
#define GLPLAT_H



#ifdef __APPLE__
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#define CHUGL_ES2
#else
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>
#define CHUGL_GL
#endif
#else
#include <gl/gl.h>
#define CHUGL_GL
#endif // __APPLE__

#endif // GLPLAT_H
