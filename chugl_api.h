
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

#ifndef CHUGL_API
#define CHUGL_API

#include "chuck_dl.h"
#include "chuck_def.h"

CK_DLL_MFUN(chugl_color3);
CK_DLL_MFUN(chugl_color4);
CK_DLL_MFUN(chugl_translate2);
CK_DLL_MFUN(chugl_scale2);
CK_DLL_MFUN(chugl_rotateZ);
CK_DLL_MFUN(chugl_pushMatrix);
CK_DLL_MFUN(chugl_popMatrix);
CK_DLL_MFUN(chugl_rect);
CK_DLL_MFUN(chugl_line);
CK_DLL_MFUN(chugl_ellipse);
CK_DLL_MFUN(chugl_clear);

#endif // CHUGL_API

