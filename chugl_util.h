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

#include "chugl.h"

#include "chuck_dl.h"
#include "chuck_def.h"
#include "chuck_type.h"


template<typename T>
void copy_ckarray4_to_array(T *array, Chuck_Array4 *ckarray)
{
    t_CKUINT val;
    for(int i = 0; i < ckarray->size(); i++)
    {
        ckarray->get(i, &val);
        array[i] = val;
    }
}

template<typename T>
void copy_ckarray8_to_array(T *array, Chuck_Array8 *ckarray)
{
    t_CKFLOAT val;
    for(int i = 0; i < ckarray->size(); i++)
    {
        ckarray->get(i, &val);
        array[i] = val;
    }
}

template<typename T>
void copy_array_to_ckarray4(T *array, Chuck_Array4 *ckarray)
{
    t_CKINT val;
    for(int i = 0; i < ckarray->size(); i++)
    {
        val = array[i];
        ckarray->set(i, val);
    }
}


