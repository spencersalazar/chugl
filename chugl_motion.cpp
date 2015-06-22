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


#include "chugl_motion.h"

#include "chuck_type.h"
#include "chuck_instr.h"
#include "chuck_vm.h"

#include <math.h>

/*----------------------------------------------------------------------------
  class: curve
   desc: ChucK GL animation curves
-----------------------------------------------------------------------------*/

class curve
{
public:
    curve(t_CKFLOAT val, t_CKFLOAT t) :
    m_val(val), m_target(val), m_last_t(t) { }
    virtual ~curve() { }
    
    void interp(t_CKFLOAT t)
    {
        if(t > m_last_t)
        {
            internal_interp(t, t-m_last_t);
            m_last_t = t;
        }
    }
    
    inline t_CKFLOAT getVal() { return m_val; }
    inline void setVal(t_CKFLOAT val) { m_val = val; }
    
    inline t_CKFLOAT getTarget() { return m_target; }
    inline void setTarget(t_CKFLOAT target) { m_target = target; }
    
protected:
    
    virtual void internal_interp(t_CKFLOAT t, t_CKFLOAT dt) = 0;
    
    t_CKFLOAT m_val, m_target;
    t_CKDUR m_dur;
    
private:
    t_CKFLOAT m_last_t;
};

class curveExp : public curve
{
public:
    curveExp(t_CKFLOAT val, t_CKFLOAT t, t_CKFLOAT fs, t_CKFLOAT t40 = 1) :
    curve(val, t), m_fs(fs)
    {
        this->setT40(t40);
    }
    
    void setRate(t_CKFLOAT rate) { m_a1 = 1-rate; }
    
    void setT40(t_CKFLOAT t40)
    {
        t_CKFLOAT n40 = t40*m_fs;
        m_a1 = pow(0.01, 1.0/n40);
    }
    
protected:
    virtual void internal_interp(t_CKFLOAT t, t_CKFLOAT dt)
    {
        t_CKFLOAT n = dt*m_fs;
        t_CKFLOAT a1_n = pow(m_a1, n);
        m_val = a1_n*m_val + (1-a1_n)*m_target;
    }
    
    t_CKFLOAT m_fs, m_a1;
};


t_CKINT curve_offset_data = 0;

CK_DLL_CTOR(curve_ctor)
{
    OBJ_MEMBER_INT(SELF, curve_offset_data) = 0;
    
    if(SELF->type_ref->name == "curve")
    {
        t_CKFLOAT fs = SHRED->vm_ref->srate();
        t_CKFLOAT t = SHRED->vm_ref->shreduler()->now_system/fs;
        
        curve *c = new curveExp(0, t, fs);
        OBJ_MEMBER_INT(SELF, curve_offset_data) = (t_CKINT) c;
    }
}

CK_DLL_DTOR(curve_dtor)
{
    curve *c = (curve *) OBJ_MEMBER_INT(SELF, curve_offset_data);
    SAFE_DELETE(c);
    OBJ_MEMBER_INT(SELF, curve_offset_data) = 0;
}

CK_DLL_MFUN(curve_getTarget)
{
    curve *c = (curve *) OBJ_MEMBER_INT(SELF, curve_offset_data);
        
    RETURN->v_float = c->getTarget();
}

CK_DLL_MFUN(curve_setTarget)
{
    curve *c = (curve *) OBJ_MEMBER_INT(SELF, curve_offset_data);
    
    t_CKFLOAT target = GET_NEXT_FLOAT(ARGS);
    
    c->setTarget(target);
    
    RETURN->v_float = target;
}

CK_DLL_MFUN(curve_setVal)
{
    curve *c = (curve *) OBJ_MEMBER_INT(SELF, curve_offset_data);
    
    t_CKFLOAT val = GET_NEXT_FLOAT(ARGS);
    
    c->setVal(val);
    
    RETURN->v_float = val;
}

CK_DLL_MFUN(curve_getVal)
{
    t_CKFLOAT fs = SHRED->vm_ref->srate();
    t_CKFLOAT t = SHRED->vm_ref->shreduler()->now_system/fs;
    
    curve *c = (curve *) OBJ_MEMBER_INT(SELF, curve_offset_data);
    
    c->interp(t);
    
    RETURN->v_float = c->getVal();
}

CK_DLL_CTOR(curveExp_ctor)
{
    t_CKFLOAT fs = SHRED->vm_ref->srate();
    t_CKFLOAT t = SHRED->vm_ref->shreduler()->now_system/fs;
    
    curveExp *c = new curveExp(0, t, fs);
    OBJ_MEMBER_INT(SELF, curve_offset_data) = (t_CKINT) c;
}

CK_DLL_DTOR(curveExp_dtor)
{
    curveExp *c = (curveExp *) OBJ_MEMBER_INT(SELF, curve_offset_data);
    SAFE_DELETE(c);
    OBJ_MEMBER_INT(SELF, curve_offset_data) = 0;
}

CK_DLL_MFUN(curveExp_setT40)
{
    curveExp *c = (curveExp *) OBJ_MEMBER_INT(SELF, curve_offset_data);
    
    t_CKFLOAT t40 = GET_NEXT_FLOAT(ARGS);
    
    c->setT40(t40);
    
    RETURN->v_float = t40;
}

