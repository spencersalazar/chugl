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


#ifndef CHUGL_MOTION
#define CHUGL_MOTION

#include "chuck_dl.h"
#include "chuck_def.h"

/*----------------------------------------------------------------------------
  class: curve
   desc: ChucK GL animation curves
-----------------------------------------------------------------------------*/

extern t_CKINT curve_offset_data;

CK_DLL_CTOR(curve_ctor);
CK_DLL_DTOR(curve_dtor);
CK_DLL_MFUN(curve_getTarget);
CK_DLL_MFUN(curve_setTarget);
CK_DLL_MFUN(curve_setVal);
CK_DLL_MFUN(curve_getVal);

CK_DLL_CTOR(curveExp_ctor);
CK_DLL_DTOR(curveExp_dtor);
CK_DLL_MFUN(curveExp_setT40);

#endif // CHUGL_MOTION
