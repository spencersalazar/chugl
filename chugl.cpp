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
#include "chugl_opengl.h"
#include "chugl_api.h"

#include "chuck_type.h"
#include "chuck_instr.h"
#include "chuck_vm.h"

#ifdef __APPLE__
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>
#else
#include <gl/gl.h>
#endif // __APPLE__

// general includes
#include <stdio.h>
#include <limits.h>
#include <math.h>


/*----------------------------------------------------------------------------
  class: chuglHack
   desc: ChucK GL hack ugen
         Used to detect transition from code -> ugen processing in VM
-----------------------------------------------------------------------------*/

t_CKINT chuglHack_offset_chugl = 0;

CK_DLL_CTOR(chuglHack_ctor)
{
    OBJ_MEMBER_INT(SELF, chuglHack_offset_chugl) = 0;
}

CK_DLL_DTOR(chuglHack_dtor)
{
    OBJ_MEMBER_INT(SELF, chuglHack_offset_chugl) = 0;
}

CK_DLL_TICK(chuglHack_tick)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chuglHack_offset_chugl);
    
    chgl->exit();
    
    *out = 0;
    return TRUE;
}


/*----------------------------------------------------------------------------
  class: chugl
   desc: Primary high-level graphics interface for ChucK GL graphics. 
-----------------------------------------------------------------------------*/

chugl *chugl::s_mainChugl = NULL;

chugl *chugl::mainChugl() { return s_mainChugl; }

chugl::chugl()
{
    m_Chuck_UI_Manager_init = (void (*)()) dlsym(RTLD_DEFAULT, "Chuck_UI_Manager_init");
    if(m_Chuck_UI_Manager_init != NULL)
        m_Chuck_UI_Manager_init();
    
    m_Chuck_UI_Manager_start = (void (*)()) dlsym(RTLD_DEFAULT, "Chuck_UI_Manager_start");
    if(m_Chuck_UI_Manager_start != NULL)
        m_Chuck_UI_Manager_start();
    
    // else fuck it we'll do it live
    // TODO: check if in miniAudicle; otherwise log warning
    
    m_lock = 0;
    m_good = FALSE;
    m_enter = FALSE;
    m_windowWidth = m_windowHeight = 0;
    
    if(s_mainChugl == NULL)
        s_mainChugl = this;
}

chugl::~chugl()
{
}

void chugl::enter()
{
    if(!good())
    {
        EM_error3("chugl: warning! attempt to activate chugl when not fully initialized");
        while(!good()) ;
    }
    
    if(m_enterMainThread && !isMainThread())
        m_enter = FALSE; // force re-entry
    
    if(!m_enter)
    {
        platformEnter();
        
        if(isMainThread()) m_enterMainThread = TRUE;
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, windowWidth(), 0, windowHeight(), -0.1, 100);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_MULTISAMPLE);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        m_enter = TRUE;
    }
}

void chugl::exit()
{
    if(!good())
    {
        EM_error3("chugl: warning! attempt to deactivate chugl when not fully initialized");
        while(!good()) ;
    }
    
    if(m_enter)
    {
        if(m_enterMainThread)
            platformEnter(); // re-enter on this thread
        
        glFlush();
        
        cleanupArrayData();
        
        platformExit();
        
        m_enter = FALSE;
    }
}

void chugl::cleanupArrayData()
{
    for(list<chugl_array_data_base *>::iterator i = m_cleanupData.begin(); i != m_cleanupData.end(); i++)
        delete *i;
    m_cleanupData.clear();
    for(list<Chuck_Array *>::iterator i = m_cleanupArray.begin(); i != m_cleanupArray.end(); i++)
        (*i)->release();
    m_cleanupArray.clear();
}


t_CKINT chugl_offset_data = 0;
t_CKINT chugl_offset_gl = 0;
t_CKINT chugl_offset_hack = 0;


CK_DLL_CTOR(chugl_ctor)
{
    chugl *chgl = chugl::platformMake();
    OBJ_MEMBER_INT(SELF, chugl_offset_data) = (t_CKINT) chgl;
    
    Chuck_Env * env = Chuck_Env::instance();
    
    // create OpenGL object
    a_Id_List list = new_id_list( "OpenGL", 0 );
    
    Chuck_Type * type = type_engine_find_type( env, list );
    
    delete_id_list( list );
    
    Chuck_Object * gl = instantiate_and_initialize_object( type, NULL );
    
    OBJ_MEMBER_INT(gl, Chuck_OpenGL_offset_chugl) = (t_CKINT) chgl;
    OBJ_MEMBER_OBJECT(SELF, chugl_offset_gl) = gl;
    
    // create chuglHack object
    a_Id_List hackList = new_id_list( "chuglHack", 0 );
    
    Chuck_Type * hackType = type_engine_find_type( env, hackList );
    
    delete_id_list( hackList );
    
    Chuck_UGen *hack = (Chuck_UGen *) instantiate_and_initialize_object( hackType, NULL );
    
    OBJ_MEMBER_INT(hack, chuglHack_offset_chugl) = (t_CKINT) chgl;
    OBJ_MEMBER_INT(SELF, chugl_offset_hack) = (t_CKINT) hack;
    
    SHRED->vm_ref->m_bunghole->add(hack, FALSE);
}

CK_DLL_DTOR(chugl_dtor)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    SAFE_DELETE(chgl);
    OBJ_MEMBER_INT(SELF, chugl_offset_data) = 0;
}

// example of getter/setter
CK_DLL_MFUN(chugl_openWindow)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    
    t_CKFLOAT x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y = GET_NEXT_FLOAT(ARGS);
    
    chgl->openWindow(x, y);
}

// example of getter/setter
CK_DLL_MFUN(chugl_fullscreen)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    
    chgl->openFullscreen();
}

CK_DLL_MFUN(chugl_width)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    
    RETURN->v_float = chgl->windowWidth();
}

CK_DLL_MFUN(chugl_good)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    
    RETURN->v_int = chgl->good();
}

CK_DLL_MFUN(chugl_height)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    
    RETURN->v_float = chgl->windowHeight();
}


/*----------------------------------------------------------------------------
  class: chuglImage
   desc: ChucK GL image handling class
-----------------------------------------------------------------------------*/

chugl_image::chugl_image()
{
    m_tex = 0;
}

chugl_image::~chugl_image()
{
}

t_CKINT chuglImage_offset_data = 0;
t_CKINT chuglImage_offset_chugl = 0;

CK_DLL_CTOR(chuglImage_ctor)
{
    chugl *chgl = chugl::mainChugl();
    chugl_image *img = NULL;
    
    if(chgl && chgl->good())
    {
        chgl->enter(); // chgl->lock();
        
        img = chugl_image::platformMake();
        
        // chgl->unlock();
    }
    
    OBJ_MEMBER_INT(SELF, chuglImage_offset_data) = (t_CKINT) img;
    OBJ_MEMBER_INT(SELF, chuglImage_offset_chugl) = (t_CKINT) chgl;
}

CK_DLL_DTOR(chuglImage_dtor)
{
    chugl_image *img = (chugl_image *) OBJ_MEMBER_INT(SELF, chuglImage_offset_data);
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chuglImage_offset_chugl);
    
    if(chgl && chgl->good())
    {
        SAFE_DELETE(img);
    }
    // else just leak
    OBJ_MEMBER_INT(SELF, chugl_offset_data) = 0;
}

CK_DLL_MFUN(chuglImage_load)
{
    RETURN->v_int = 0;
    
    chugl_image *img = (chugl_image *) OBJ_MEMBER_INT(SELF, chuglImage_offset_data);
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chuglImage_offset_chugl);
    if(!img || !chgl || !chgl->good()) return;
    
    Chuck_String *str = GET_NEXT_STRING(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    RETURN->v_int = img->load(str->str);
    
    // chgl->unlock();
}

CK_DLL_MFUN(chuglImage_unload)
{
    chugl_image *img = (chugl_image *) OBJ_MEMBER_INT(SELF, chuglImage_offset_data);
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chuglImage_offset_chugl);
    if(!img || !chgl || !chgl->good()) return;
    
    chgl->enter(); // chgl->lock();
    
    img->unload();
    
    // chgl->unlock();
}

CK_DLL_MFUN(chuglImage_tex)
{
    RETURN->v_int = 0;
    
    chugl_image *img = (chugl_image *) OBJ_MEMBER_INT(SELF, chuglImage_offset_data);
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chuglImage_offset_chugl);
    if(!img || !chgl || !chgl->good()) return;
    
    RETURN->v_int = img->tex();
}


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




// query function: chuck calls this when loading the Chugin
// NOTE: developer will need to modify this function to
// add additional functions to this Chugin
CK_DLL_QUERY( chugl )
{
    // hmm, don't change this...
    QUERY->setname(QUERY, "chugl");
    
    
    /*** OpenGL ***/
    OpenGL_query(QUERY);
    
    
    /*** chuglImage ***/
    QUERY->begin_class(QUERY, "chuglImage", "Object");
    
    QUERY->add_ctor(QUERY, chuglImage_ctor);
    QUERY->add_dtor(QUERY, chuglImage_dtor);
    
    chuglImage_offset_data = QUERY->add_mvar(QUERY, "int", "@chuglImage_data", FALSE);
    chuglImage_offset_chugl = QUERY->add_mvar(QUERY, "int", "@chuglImage_chugl", FALSE);
    
    QUERY->add_mfun(QUERY, chuglImage_load, "int", "load");
    QUERY->add_arg(QUERY, "string", "file");
    
    QUERY->add_mfun(QUERY, chuglImage_unload, "void", "unload");
    
    QUERY->add_mfun(QUERY, chuglImage_tex, "int", "tex");
    
    QUERY->end_class(QUERY);
    
    
    /*** chugl ***/
    QUERY->begin_class(QUERY, "chugl", "Object");
    
    QUERY->add_ctor(QUERY, chugl_ctor);
    QUERY->add_dtor(QUERY, chugl_dtor);
    
    chugl_offset_data = QUERY->add_mvar(QUERY, "int", "@chugl_data", FALSE);
    chugl_offset_gl = QUERY->add_mvar(QUERY, "OpenGL", "gl", FALSE);
    chugl_offset_hack = QUERY->add_mvar(QUERY, "int", "@chugl_hack", FALSE);
    
    QUERY->add_mfun(QUERY, chugl_openWindow, "void", "openWindow");
    QUERY->add_arg(QUERY, "float", "width");
    QUERY->add_arg(QUERY, "float", "height");
    
    QUERY->add_mfun(QUERY, chugl_fullscreen, "void", "fullscreen");
    
    QUERY->add_mfun(QUERY, chugl_width, "float", "width");
    QUERY->add_mfun(QUERY, chugl_height, "float", "height");
    
    QUERY->add_mfun(QUERY, chugl_good, "int", "good");
    
    QUERY->add_mfun(QUERY, chugl_clear, "void", "clear");
    
    QUERY->add_mfun(QUERY, chugl_pushMatrix, "void", "pushMatrix");
    QUERY->add_mfun(QUERY, chugl_popMatrix, "void", "popMatrix");
    
    QUERY->add_mfun(QUERY, chugl_rotateZ, "void", "rotate");
    QUERY->add_arg(QUERY, "float", "z");
    
    QUERY->add_mfun(QUERY, chugl_translate2, "void", "translate");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    
    QUERY->add_mfun(QUERY, chugl_scale2, "void", "scale");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    
    QUERY->add_mfun(QUERY, chugl_color4, "void", "color");
    QUERY->add_arg(QUERY, "float", "r");
    QUERY->add_arg(QUERY, "float", "g");
    QUERY->add_arg(QUERY, "float", "b");
    QUERY->add_arg(QUERY, "float", "a");
    
    QUERY->add_mfun(QUERY, chugl_color3, "void", "color");
    QUERY->add_arg(QUERY, "float", "r");
    QUERY->add_arg(QUERY, "float", "g");
    QUERY->add_arg(QUERY, "float", "b");
    
    QUERY->add_mfun(QUERY, chugl_hsv4, "void", "hsv");
    QUERY->add_arg(QUERY, "float", "h");
    QUERY->add_arg(QUERY, "float", "s");
    QUERY->add_arg(QUERY, "float", "v");
    QUERY->add_arg(QUERY, "float", "a");
    
    QUERY->add_mfun(QUERY, chugl_hsv3, "void", "hsv");
    QUERY->add_arg(QUERY, "float", "h");
    QUERY->add_arg(QUERY, "float", "s");
    QUERY->add_arg(QUERY, "float", "v");
    
    QUERY->add_mfun(QUERY, chugl_rect, "void", "rect");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "width");
    QUERY->add_arg(QUERY, "float", "height");
    
    QUERY->add_mfun(QUERY, chugl_ellipse, "void", "ellipse");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "width");
    QUERY->add_arg(QUERY, "float", "height");
    
    QUERY->add_mfun(QUERY, chugl_line, "void", "line");
    QUERY->add_arg(QUERY, "float", "x1");
    QUERY->add_arg(QUERY, "float", "y1");
    QUERY->add_arg(QUERY, "float", "x2");
    QUERY->add_arg(QUERY, "float", "y2");
    
    // end the class definition
    // IMPORTANT: this MUST be called!
    QUERY->end_class(QUERY);
    
    
    /*** chuglHack ***/
    
    QUERY->begin_class(QUERY, "chuglHack", "UGen");
    
    chuglHack_offset_chugl = QUERY->add_mvar(QUERY, "int", "@chuglHack_chugl", FALSE);
    
    QUERY->add_ctor(QUERY, chuglHack_ctor);
    QUERY->add_dtor(QUERY, chuglHack_dtor);
    
    QUERY->add_ugen_func(QUERY, chuglHack_tick, NULL, 0, 1);
    
    QUERY->end_class(QUERY);
    
    
    /*** curve ***/
    
    QUERY->begin_class(QUERY, "curve", "Object");
    
    QUERY->add_ctor(QUERY, curve_ctor);
    QUERY->add_dtor(QUERY, curve_dtor);
    
    curve_offset_data = QUERY->add_mvar(QUERY, "int", "@curve_data", FALSE);
    
    QUERY->add_mfun(QUERY, curve_getTarget, "float", "target");
    
    QUERY->add_mfun(QUERY, curve_setTarget, "float", "target");
    QUERY->add_arg(QUERY, "float", "t");
    
    QUERY->add_mfun(QUERY, curve_setVal, "float", "val");
    QUERY->add_arg(QUERY, "float", "v");
    
    QUERY->add_mfun(QUERY, curve_getVal, "float", "val");
    
    QUERY->end_class(QUERY);
    
    
    /*** curveExp ***/
    
    QUERY->begin_class(QUERY, "curveExp", "curve");

    QUERY->add_ctor(QUERY, curveExp_ctor);
    QUERY->add_dtor(QUERY, curveExp_dtor);

    QUERY->end_class(QUERY);
    
    
    // wasn't that a breeze?
    return TRUE;
}

