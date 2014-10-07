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

#include "chuck_type.h"
#include "chuck_instr.h"

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
    m_windowWidth = m_windowHeight = 0;
    
    if(s_mainChugl == NULL)
        s_mainChugl = this;
}

chugl::~chugl()
{
}

void chugl::cleanupArrayData()
{
    for(int i = 0; i < m_cleanupData.size(); i++)
        delete m_cleanupData[i];
    m_cleanupData.clear();
}


template<typename T>
T rad2deg(T rad)
{
    return rad/M_PI*180.0;
}


t_CKINT chugl_offset_data = 0;
t_CKINT chugl_offset_gl = 0;


CK_DLL_CTOR(chugl_ctor)
{
    chugl *chgl = chugl::platformMake();
    OBJ_MEMBER_INT(SELF, chugl_offset_data) = (t_CKINT) chgl;
    
    Chuck_Env * env = Chuck_Env::instance();
    a_Id_List list = new_id_list( "OpenGL", 0 ); // TODO: nested types
    
    Chuck_Type * type = type_engine_find_type( env, list );
    
    delete_id_list( list );
    
    Chuck_Object * gl = instantiate_and_initialize_object( type, NULL );
    
    OBJ_MEMBER_INT(gl, Chuck_OpenGL_offset_chugl) = (t_CKINT) chgl;
    OBJ_MEMBER_OBJECT(SELF, chugl_offset_gl) = gl;
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

CK_DLL_MFUN(chugl_lock)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    t_CKBOOL good = chgl->good();
    if(!good) return;
    
    chgl->lock();
}

CK_DLL_MFUN(chugl_unlock)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    chgl->unlock();
}

CK_DLL_MFUN(chugl_beginDraw)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    chgl->lock();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, chgl->windowWidth(), 0, chgl->windowHeight(), -0.1, 100);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glEnable(GL_LINE_SMOOTH);
    
    chgl->unlock();
}

CK_DLL_MFUN(chugl_endDraw)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    chgl->lock();
    
    glFlush();
    
    chgl->unlock();
}

CK_DLL_MFUN(chugl_color3)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT r = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT g = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT b = GET_NEXT_FLOAT(ARGS);
    
    chgl->lock();
    
    glColor4f(r, g, b, 1.0);
    
    chgl->unlock();
}

CK_DLL_MFUN(chugl_color4)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT r = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT g = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT b = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT a = GET_NEXT_FLOAT(ARGS);
    
    chgl->lock();
    
    glColor4f(r, g, b, a);
    
    chgl->unlock();
}

CK_DLL_MFUN(chugl_translate2)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y = GET_NEXT_FLOAT(ARGS);
    
    chgl->lock();
    
    glTranslatef(x, y, 0);
    
    chgl->unlock();
}

CK_DLL_MFUN(chugl_scale2)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y = GET_NEXT_FLOAT(ARGS);
    
    chgl->lock();
    
    glScalef(x, y, 1);
    
    chgl->unlock();
}

CK_DLL_MFUN(chugl_rotateZ)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT z = GET_NEXT_FLOAT(ARGS);
    
    chgl->lock();
    
    glRotatef(rad2deg(z), 0, 0, 1);
    
    chgl->unlock();
}

CK_DLL_MFUN(chugl_pushMatrix)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    chgl->lock();
    
    glPushMatrix();
    
    chgl->unlock();
}

CK_DLL_MFUN(chugl_popMatrix)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    chgl->lock();
    
    glPopMatrix();
    
    chgl->unlock();
}

CK_DLL_MFUN(chugl_rect)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT width = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT height = GET_NEXT_FLOAT(ARGS);
    
    chgl->lock();
    
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(x, y, 0);
    glVertex3f(x+width, y, 0);
    glVertex3f(x, y+height, 0);
    glVertex3f(x+width, y+height, 0);
    glEnd();
    
    chgl->unlock();
}

CK_DLL_MFUN(chugl_line)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT x1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT x2 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y2 = GET_NEXT_FLOAT(ARGS);
    
    chgl->lock();
    
    glBegin(GL_LINES);
    glVertex3f(x1, y1, 0);
    glVertex3f(x2, y2, 0);
    glEnd();
    
    chgl->unlock();
}

CK_DLL_MFUN(chugl_ellipse)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT width = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT height = GET_NEXT_FLOAT(ARGS);
    
    chgl->lock();
    
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(x, y, 0);
    glVertex3f(x+width, y, 0);
    glVertex3f(x, y+height, 0);
    glVertex3f(x+width, y+height, 0);
    glEnd();
    
    chgl->unlock();
}

CK_DLL_MFUN(chugl_clear)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    chgl->lock();
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    chgl->unlock();
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
        chgl->lock();
        
        img = chugl_image::platformMake();
        
        chgl->unlock();
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
    
    RETURN->v_int = img->load(str->str);
}

CK_DLL_MFUN(chuglImage_unload)
{
    chugl_image *img = (chugl_image *) OBJ_MEMBER_INT(SELF, chuglImage_offset_data);
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chuglImage_offset_chugl);
    if(!img || !chgl || !chgl->good()) return;
    
    img->unload();
}

CK_DLL_MFUN(chuglImage_tex)
{
    RETURN->v_int = 0;
    
    chugl_image *img = (chugl_image *) OBJ_MEMBER_INT(SELF, chuglImage_offset_data);
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chuglImage_offset_chugl);
    if(!img || !chgl || !chgl->good()) return;
    
    RETURN->v_int = img->tex();
}



// query function: chuck calls this when loading the Chugin
// NOTE: developer will need to modify this function to
// add additional functions to this Chugin
CK_DLL_QUERY( chugl )
{
    // hmm, don't change this...
    QUERY->setname(QUERY, "chugl");
    
    // add OpenGL
    OpenGL_query(QUERY);
    
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
    
    
    // begin the class definition
    // can change the second argument to extend a different ChucK class
    QUERY->begin_class(QUERY, "chugl", "Object");
    
    QUERY->add_ctor(QUERY, chugl_ctor);
    QUERY->add_dtor(QUERY, chugl_dtor);
    
    chugl_offset_data = QUERY->add_mvar(QUERY, "int", "@chugl_data", FALSE);
    chugl_offset_gl = QUERY->add_mvar(QUERY, "OpenGL", "gl", FALSE);
    
    QUERY->add_mfun(QUERY, chugl_openWindow, "void", "openWindow");
    QUERY->add_arg(QUERY, "float", "width");
    QUERY->add_arg(QUERY, "float", "height");
    
    QUERY->add_mfun(QUERY, chugl_fullscreen, "void", "fullscreen");
    
    QUERY->add_mfun(QUERY, chugl_width, "float", "width");
    QUERY->add_mfun(QUERY, chugl_height, "float", "height");
    
    QUERY->add_mfun(QUERY, chugl_good, "int", "good");
    
    QUERY->add_mfun(QUERY, chugl_lock, "void", "lock");
    QUERY->add_mfun(QUERY, chugl_unlock, "void", "unlock");    
    
    QUERY->add_mfun(QUERY, chugl_beginDraw, "void", "beginDraw");
    QUERY->add_mfun(QUERY, chugl_endDraw, "void", "endDraw");
    
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
    
    QUERY->add_mfun(QUERY, chugl_rect, "void", "rect");
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

    // wasn't that a breeze?
    return TRUE;
}

