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

#if CHUGL_ENABLE_OPENGL_BINDINGS
#include "chugl_opengl.h"
#endif // CHUGL_ENABLE_OPENGL_BINDINGS

#include "chugl_api.h"
#include "chugl_ix.h"
#include "chugl_motion.h"

#include "chuck_type.h"
#include "chuck_instr.h"
#include "chuck_vm.h"

#include "glplat.h"

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

chugl::chugl() :
m_pointer(NULL)
{
    // first check if we are in miniAudicle
    const char **MA_VERSION = (const char **) dlsym(RTLD_DEFAULT, "MA_VERSION");
    if(MA_VERSION == NULL)
    {
        // find standalone UI hooks for MAUI.chug
        m_Chuck_UI_Manager_init = (void (*)()) dlsym(RTLD_DEFAULT, "Chuck_UI_Manager_init");
        if(m_Chuck_UI_Manager_init != NULL)
            m_Chuck_UI_Manager_init();
    
        m_Chuck_UI_Manager_start = (void (*)()) dlsym(RTLD_DEFAULT, "Chuck_UI_Manager_start");
        if(m_Chuck_UI_Manager_start != NULL)
            m_Chuck_UI_Manager_start();

        if(m_Chuck_UI_Manager_init == NULL || m_Chuck_UI_Manager_start == NULL)
        {
            EM_error3("chugl: erorr: unable to find MAUI");
        }
    }

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
        
        backendEnter();
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glClearColor(0.0, 0.0, 0.0, 1.0);
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
        
        backendExit();
        
        platformExit();
        
        cleanupArrayData();
        
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

void chugl::setPointer(ixPointer *pointer)
{
    // can only be set once
    assert(m_pointer == NULL);
    m_pointer = pointer;
}

ixPointer *chugl::pointer()
{
    return m_pointer;
}


t_CKINT chugl_offset_data = 0;
t_CKINT chugl_offset_gl = 0;
t_CKINT chugl_offset_hack = 0;
t_CKINT chugl_offset_pointer = 0;


CK_DLL_CTOR(chugl_ctor)
{
    chugl *chgl = chugl::platformMake();
    OBJ_MEMBER_INT(SELF, chugl_offset_data) = (t_CKINT) chgl;

#if CHUGL_ENABLE_OPENGL_BINDINGS
    // note: currently broken, update to latest object creation method
    /* create OpenGL object */
    a_Id_List list = new_id_list( "OpenGL", 0 );
    Chuck_Type * type = type_engine_find_type( env, list );    
    delete_id_list( list );
    
    Chuck_Object * gl = instantiate_and_initialize_object( type, NULL );
    gl->add_ref();

    OBJ_MEMBER_INT(gl, Chuck_OpenGL_offset_chugl) = (t_CKINT) chgl;
    OBJ_MEMBER_OBJECT(SELF, chugl_offset_gl) = gl;
#endif // CHUGL_ENABLE_OPENGL_BINDINGS
    
    /* create chuglHack object */
    
    Chuck_DL_Api::Type hackType = API->object->get_type(API, SHRED, "chuglHack");
    Chuck_UGen *hack = (Chuck_UGen *) API->object->create(API, SHRED, hackType);
    hack->add_ref();
    
    OBJ_MEMBER_INT(hack, chuglHack_offset_chugl) = (t_CKINT) chgl;
    OBJ_MEMBER_INT(SELF, chugl_offset_hack) = (t_CKINT) hack;
    
    SHRED->vm_ref->m_bunghole->add(hack, FALSE);
	
    /* create pointer object */
    Chuck_DL_Api::Type ptrType =  API->object->get_type(API, SHRED, "Pointer");    
    Chuck_Object * pointer = (Chuck_Object *) API->object->create(API, SHRED, ptrType);
    // TODO: why do i have to call ctor directly?
    Pointer_ctor(pointer, NULL, VM, SHRED, API);
    pointer->add_ref();
    
    OBJ_MEMBER_OBJECT(SELF, chugl_offset_pointer) = pointer;
    chgl->setPointer(new ixPointer(pointer));
}

CK_DLL_DTOR(chugl_dtor)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);

#if CHUGL_ENABLE_OPENGL_BINDINGS
    Chuck_Object * gl = OBJ_MEMBER_OBJECT(SELF, chugl_offset_gl);
    gl->release();
    OBJ_MEMBER_OBJECT(SELF, chugl_offset_gl) = 0;
#endif
    
    // disconnect hack tick object
    Chuck_UGen *hack = (Chuck_UGen *) OBJ_MEMBER_INT(SELF, chugl_offset_hack);
    hack->disconnect(0);
    hack->release();
    OBJ_MEMBER_INT(SELF, chugl_offset_hack) = 0;

    Chuck_Object * pointer = OBJ_MEMBER_OBJECT(SELF, chugl_offset_pointer);
    pointer->release();
    OBJ_MEMBER_OBJECT(SELF, chugl_offset_pointer) = 0;
    
    SAFE_DELETE(chgl);
    OBJ_MEMBER_INT(SELF, chugl_offset_data) = 0;
}


// query function: chuck calls this when loading the Chugin
// NOTE: developer will need to modify this function to
// add additional functions to this Chugin
CK_DLL_QUERY( chugl )
{
    // hmm, don't change this...
    QUERY->setname(QUERY, "chugl");
    
    
#if CHUGL_ENABLE_OPENGL_BINDINGS
    /*** OpenGL ***/
    OpenGL_query(QUERY);
#endif // CHUGL_ENABLE_OPENGL_BINDINGS
    
    
    /*** chuglImage ***/
    QUERY->begin_class(QUERY, "chuglImage", "Object");
    QUERY->doc_class(QUERY, "chuglImage handles loading image files into graphics memory as a texture. ");
    
    QUERY->add_ctor(QUERY, chuglImage_ctor);
    QUERY->add_dtor(QUERY, chuglImage_dtor);
    
    chuglImage_offset_data = QUERY->add_mvar(QUERY, "int", "@chuglImage_data", FALSE);
    chuglImage_offset_chugl = QUERY->add_mvar(QUERY, "int", "@chuglImage_chugl", FALSE);
    
    QUERY->add_mfun(QUERY, chuglImage_load, "int", "load");
    QUERY->add_arg(QUERY, "string", "file");
    QUERY->doc_func(QUERY, "Load the specified file path from disk into texture memory. ");
    
    QUERY->add_mfun(QUERY, chuglImage_unload, "void", "unload");
    QUERY->doc_func(QUERY, "Unload the texture. ");
    
    QUERY->add_mfun(QUERY, chuglImage_tex, "int", "tex");
    QUERY->doc_func(QUERY, "Get the OpenGL texture name (e.g. for use with gl.BindTexture). Returns 0 if no texture has been loaded.");
    
    QUERY->add_mfun(QUERY, chuglImage_draw, "void", "draw");
    QUERY->add_arg(QUERY, "float", "x");     QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "width"); QUERY->add_arg(QUERY, "float", "height");
    QUERY->doc_func(QUERY, "Draw the image into the rectangle specified by the given bottom-left corner position (x,y) and width and height.");
    
    QUERY->end_class(QUERY);
	
    /*** Pointer ***/
    
    QUERY->begin_class(QUERY, "Pointer", "Object");
    // QUERY->doc_class(QUERY, "");

    QUERY->add_ctor(QUERY, Pointer_ctor);
    QUERY->add_dtor(QUERY, Pointer_dtor);
	
    // Pointer_offset_data = QUERY->add_mvar(QUERY, "int", "@Pointer_data", FALSE);
    Pointer_offset_x = QUERY->add_mvar(QUERY, "float", "x", FALSE);
    QUERY->doc_var(QUERY, "Current x position of primary pointer.");
    Pointer_offset_y = QUERY->add_mvar(QUERY, "float", "y", FALSE);
    QUERY->doc_var(QUERY, "Current y position of primary pointer.");
    Pointer_offset_state = QUERY->add_mvar(QUERY, "int", "state", FALSE);
    QUERY->doc_var(QUERY, "Current state of primary pointer.");
    
    Pointer_offset_move = QUERY->add_mvar(QUERY, "Event", "move", FALSE);
    QUERY->doc_func(QUERY, "Returns an Event that signals when the pointer moves.");
    Pointer_offset_stateChange = QUERY->add_mvar(QUERY, "Event", "stateChange", FALSE);
    QUERY->doc_func(QUERY, "Returns an Event that signals when the pointer changes state (e.g. click or touch).");

    QUERY->end_class(QUERY);
    
    
    /*** chugl ***/
    QUERY->begin_class(QUERY, "chugl", "Object");
    QUERY->doc_class(QUERY, "The chugl class is the primary interface between ChucK code and the ChuGL graphics system. ");
    
    QUERY->add_ctor(QUERY, chugl_ctor);
    QUERY->add_dtor(QUERY, chugl_dtor);
    
    chugl_offset_data = QUERY->add_mvar(QUERY, "int", "@chugl_data", FALSE);
    chugl_offset_hack = QUERY->add_mvar(QUERY, "int", "@chugl_hack", FALSE);
    
#if CHUGL_ENABLE_OPENGL_BINDINGS
    chugl_offset_gl = QUERY->add_mvar(QUERY, "OpenGL", "gl", FALSE);
    QUERY->doc_var(QUERY, "An OpenGL object, for making direct OpenGL calls to the graphics state represented by this instance.");
#endif // CHUGL_ENABLE_OPENGL_BINDINGS
    
    chugl_offset_pointer = QUERY->add_mvar(QUERY, "Pointer", "pointer", FALSE);
    
    QUERY->add_mfun(QUERY, chugl_openWindow, "void", "openWindow");
    QUERY->add_arg(QUERY, "float", "width");
    QUERY->add_arg(QUERY, "float", "height");
    QUERY->doc_func(QUERY, "Open a window for drawing with specified width and height. ");
    
    QUERY->add_mfun(QUERY, chugl_fullscreen, "void", "fullscreen");
    QUERY->doc_func(QUERY, "Open a fullscreen window for drawing. ");
    
    QUERY->add_mfun(QUERY, chugl_isOpen, "int", "isOpen");
    QUERY->doc_func(QUERY, "Return 1 if the chugl window is currently open, or 0 if it has been closed. ");
    
    QUERY->add_mfun(QUERY, chugl_width, "float", "width");
    QUERY->doc_func(QUERY, "Width of the window, or of the screen if a fullscreen window is being used. ");
    QUERY->add_mfun(QUERY, chugl_height, "float", "height");
    QUERY->doc_func(QUERY, "Height of the window, or of the screen if a fullscreen window is being used. ");
    
    QUERY->add_mfun(QUERY, chugl_good, "int", "good");
    QUERY->doc_func(QUERY, "Returns true if the window or screen is ready to be drawn to, and the underlying OpenGL context is ready. ");
    
    QUERY->add_mfun(QUERY, chugl_hideCursor, "void", "hideCursor");
    QUERY->add_mfun(QUERY, chugl_showCursor, "void", "showCursor");
    
    QUERY->add_mfun(QUERY, chugl_clear, "void", "clear");
    QUERY->doc_func(QUERY, "Clear the screen.");
    
    QUERY->add_mfun(QUERY, chugl_pushMatrix, "void", "pushMatrix");
    QUERY->doc_func(QUERY, "Push the current transform matrix.");
    QUERY->add_mfun(QUERY, chugl_popMatrix, "void", "popMatrix");
    QUERY->doc_func(QUERY, "Pop the current transform matrix.");
    
    QUERY->add_mfun(QUERY, chugl_rotateZ, "void", "rotate");
    QUERY->add_arg(QUERY, "float", "angle");
    QUERY->doc_func(QUERY, "Rotate by the specified angle (in radians) around the z-axis (e..g 2-D rotation). ");
    
    QUERY->add_mfun(QUERY, chugl_translate2, "void", "translate");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->doc_func(QUERY, "Translate in 2-D by the specified x and y directions. ");
    
    QUERY->add_mfun(QUERY, chugl_scale2, "void", "scale");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->doc_func(QUERY, "Scale in 2-D by the specified factors in x and y. ");
    
    QUERY->add_mfun(QUERY, chugl_color4, "void", "color");
    QUERY->add_arg(QUERY, "float", "r");
    QUERY->add_arg(QUERY, "float", "g");
    QUERY->add_arg(QUERY, "float", "b");
    QUERY->add_arg(QUERY, "float", "a");
    QUERY->doc_func(QUERY, "Set the current drawing color to the specified RGBA color. ");
    
    QUERY->add_mfun(QUERY, chugl_color3, "void", "color");
    QUERY->add_arg(QUERY, "float", "r");
    QUERY->add_arg(QUERY, "float", "g");
    QUERY->add_arg(QUERY, "float", "b");
    QUERY->doc_func(QUERY, "Set the current drawing color to the specified RGB color. ");
    
    QUERY->add_mfun(QUERY, chugl_hsv4, "void", "hsv");
    QUERY->add_arg(QUERY, "float", "h");
    QUERY->add_arg(QUERY, "float", "s");
    QUERY->add_arg(QUERY, "float", "v");
    QUERY->add_arg(QUERY, "float", "a");
    QUERY->doc_func(QUERY, "Set the current drawing color to the specified HSVA color. ");
    
    QUERY->add_mfun(QUERY, chugl_hsv3, "void", "hsv");
    QUERY->add_arg(QUERY, "float", "h");
    QUERY->add_arg(QUERY, "float", "s");
    QUERY->add_arg(QUERY, "float", "v");
    QUERY->doc_func(QUERY, "Set the current drawing color to the specified HSV color. ");
    
    QUERY->add_mfun(QUERY, chugl_rect, "void", "rect");
    QUERY->add_arg(QUERY, "float", "x");     QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "width"); QUERY->add_arg(QUERY, "float", "height");
    QUERY->doc_func(QUERY, "Draw a rectangle with bottom-left corner at (x,y) and specified width and height. The current transform matrix and color properties will be used when drawing the rectangle. ");
    
    QUERY->add_mfun(QUERY, chugl_triangle, "void", "triangle");
    QUERY->add_arg(QUERY, "float", "ax"); QUERY->add_arg(QUERY, "float", "ay");
    QUERY->add_arg(QUERY, "float", "bx"); QUERY->add_arg(QUERY, "float", "by");
    QUERY->add_arg(QUERY, "float", "cx"); QUERY->add_arg(QUERY, "float", "cy");
    QUERY->doc_func(QUERY, "Draw a triangle described by the specified vertices. The current transform matrix and color properties will be used when drawing the triangle. ");
    
    QUERY->add_mfun(QUERY, chugl_ellipse, "void", "ellipse");
    QUERY->add_arg(QUERY, "float", "x");     QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "width"); QUERY->add_arg(QUERY, "float", "height");
    QUERY->doc_func(QUERY, "Draw an ellipse bottom-left corner at (x,y) and specified width and height. The current transform matrix and color properties will be used when drawing the ellipse. ");
    
    QUERY->add_mfun(QUERY, chugl_line, "void", "line");
    QUERY->add_arg(QUERY, "float", "x1"); QUERY->add_arg(QUERY, "float", "y1");
    QUERY->add_arg(QUERY, "float", "x2"); QUERY->add_arg(QUERY, "float", "y2");
    QUERY->doc_func(QUERY, "Draw a line between (x1,y1) and (x2,y2). The current transform matrix and color properties will be used when drawing the line. ");
    
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
    
    QUERY->add_mfun(QUERY, curveExp_setT40, "void", "t40");
    QUERY->add_arg(QUERY, "float", "t40");

    QUERY->end_class(QUERY);
    
    
    // wasn't that a breeze?
    return TRUE;
}

