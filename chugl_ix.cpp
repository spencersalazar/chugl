
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


#include "chugl_ix.h"


t_CKINT Pointer_offset_x = 0;
t_CKINT Pointer_offset_y = 0;
t_CKINT Pointer_offset_state = 0;


CK_DLL_CTOR(Pointer_ctor)
{
	OBJ_MEMBER_FLOAT(SELF, Pointer_offset_x) = 0;
	OBJ_MEMBER_FLOAT(SELF, Pointer_offset_y) = 0;
	OBJ_MEMBER_INT(SELF, Pointer_offset_state) = 0;
}


CK_DLL_DTOR(Pointer_dtor)
{
}




