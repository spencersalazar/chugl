
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
#include "chuck_type.h"
#include "chuck_instr.h"


ixPointer::ixPointer(Chuck_Object *obj) : m_obj(obj)
{
}

void ixPointer::move(float x, float y)
{
    OBJ_MEMBER_FLOAT(m_obj, Pointer_offset_x) = x;
    OBJ_MEMBER_FLOAT(m_obj, Pointer_offset_y) = y;
    
    Chuck_Event *move_event = (Chuck_Event *) OBJ_MEMBER_OBJECT(m_obj, Pointer_offset_move);
    move_event->queue_broadcast();
}

void ixPointer::stateChange(int state)
{
    OBJ_MEMBER_FLOAT(m_obj, Pointer_offset_state) = state;
    
    Chuck_Event *state_change_event = (Chuck_Event *) OBJ_MEMBER_OBJECT(m_obj, Pointer_offset_stateChange);
    state_change_event->queue_broadcast();
}

int ixPointer::state()
{
    return OBJ_MEMBER_FLOAT(m_obj, Pointer_offset_state);
}



t_CKINT Pointer_offset_x = 0;
t_CKINT Pointer_offset_y = 0;
t_CKINT Pointer_offset_state = 0;
t_CKINT Pointer_offset_move = 0;
t_CKINT Pointer_offset_stateChange = 0;


CK_DLL_CTOR(Pointer_ctor)
{
	OBJ_MEMBER_FLOAT(SELF, Pointer_offset_x) = 0;
	OBJ_MEMBER_FLOAT(SELF, Pointer_offset_y) = 0;
	OBJ_MEMBER_INT(SELF, Pointer_offset_state) = 0;
    
    Chuck_DL_Api::Type eventType =  API->object->get_type(API, SHRED, "Event");    
    Chuck_Event *move_event = (Chuck_Event *) API->object->create(API, SHRED, eventType);
    move_event->add_ref();
    OBJ_MEMBER_OBJECT(SELF, Pointer_offset_move) = move_event;
    
    Chuck_Event *state_change_event = (Chuck_Event *) API->object->create(API, SHRED, eventType);
    state_change_event->add_ref();
    OBJ_MEMBER_OBJECT(SELF, Pointer_offset_stateChange) = state_change_event;
}


CK_DLL_DTOR(Pointer_dtor)
{
    Chuck_Event *move_event = (Chuck_Event *) OBJ_MEMBER_OBJECT(SELF, Pointer_offset_move);
    move_event->release();
    OBJ_MEMBER_OBJECT(SELF, Pointer_offset_move) = NULL;
    
    Chuck_Event *state_change_event = (Chuck_Event *) OBJ_MEMBER_OBJECT(SELF, Pointer_offset_stateChange);
    state_change_event->release();
    OBJ_MEMBER_OBJECT(SELF, Pointer_offset_stateChange) = NULL;
}




