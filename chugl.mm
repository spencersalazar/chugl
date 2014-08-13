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
#include "OpenGL/chuck_opengl.h"

#include "chuck_type.h"
#include "chuck_instr.h"

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <OpenGL/OpenGL.h>
#import <dispatch/queue.h>

// general includes
#include <stdio.h>
#include <limits.h>

class chugl_osx : public chugl
{
public:
    chugl_osx() : chugl(), m_ctx(nil) { }
    virtual ~chugl_osx() { }
    
    void openWindow(t_CKFLOAT width, t_CKFLOAT height);
    void openFullscreen();
    
    void lock();
    void unlock();
    
private:
    NSOpenGLContext *m_ctx;
};


@interface CKOpenGLWindow : NSWindow

@end

@implementation CKOpenGLWindow

- (BOOL)canBecomeKeyWindow
{
    return YES;
}

- (BOOL)canBecomeMainWindow
{
    return YES;
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

@end


@interface CKOpenGLView : NSOpenGLView

@end

@implementation CKOpenGLView

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (void)keyDown:(NSEvent *)theEvent
{
    if([[theEvent charactersIgnoringModifiers] isEqualToString:@"w"] &&
       ([theEvent modifierFlags] & NSCommandKeyMask))
    {
        [[self window] close];
    }
    else if([[theEvent charactersIgnoringModifiers] isEqualToString:@"\033"]) 
    {
        // ESC key
        [[self window] orderOut:nil];
    }
    else
    {
        [super keyDown:theEvent];
    }
}

@end


chugl::chugl()
{
    m_Chuck_UI_Manager_start = (void (*)()) dlsym(RTLD_DEFAULT, "Chuck_UI_Manager_start");
    if(m_Chuck_UI_Manager_start != NULL)
        m_Chuck_UI_Manager_start();
    // else fuck it we'll do it live
    // TODO: check if in miniAudicle; otherwise log warning
    
    m_lock = 0;
    m_good = FALSE;
    m_windowWidth = m_windowHeight = 0;
}

chugl::~chugl()
{
}


void chugl_osx::openWindow(t_CKFLOAT width, t_CKFLOAT height)
{
    m_windowWidth = width;
    m_windowHeight = height;
    
    dispatch_async(dispatch_get_main_queue(), ^{
        CKOpenGLWindow *window = [[CKOpenGLWindow alloc] initWithContentRect:NSMakeRect(0, 0, width, height)
            styleMask:NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask
            backing:NSBackingStoreBuffered
            defer:NO];
        [window setTitle:@"chugl"];
        [window center];
        
        CKOpenGLView *glView = [[CKOpenGLView alloc] initWithFrame:[[window contentView] bounds]];
        [[window contentView] addSubview:glView];
        
        [window makeKeyAndOrderFront:nil];
        
        m_ctx = [glView openGLContext];
        m_good = TRUE;
    });
}

void chugl_osx::openFullscreen()
{
    NSRect mainDisplayRect = [[NSScreen mainScreen] frame];
    m_windowWidth = mainDisplayRect.size.width;
    m_windowHeight = mainDisplayRect.size.height;
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        CKOpenGLWindow *window = [[CKOpenGLWindow alloc] initWithContentRect:mainDisplayRect
            styleMask:NSBorderlessWindowMask
            backing:NSBackingStoreBuffered
            defer:YES];
        
        [window setLevel:NSMainMenuWindowLevel+1];
        [window setOpaque:YES];
        [window setHidesOnDeactivate:YES];
        [window setExcludedFromWindowsMenu:NO];
        [window setTitle:@"chugl"];
        
        CKOpenGLView *glView = [[CKOpenGLView alloc] initWithFrame:[[window contentView] bounds]];
        [[window contentView] addSubview:glView];
        [window setInitialFirstResponder:glView];
        
        [window makeKeyAndOrderFront:nil];
        
        m_ctx = [glView openGLContext];
        m_good = TRUE;
    });
}

void chugl_osx::lock()
{
    //NSLog(@"chugl_osx::lock");
    assert(m_lock >= 0);
    
    if(good())
    {
        if(m_lock > 0)
        {
            // already locked
            //NSLog(@"lock++");
            m_lock++;
        }
        else
        {
            //NSLog(@"lock");
            CGLLockContext((CGLContextObj)[m_ctx CGLContextObj]);
            [m_ctx makeCurrentContext];
            m_lock = 1;
        }
    }        
}

void chugl_osx::unlock()
{
    //NSLog(@"chugl_osx::unlock");
    assert(m_lock >= 0);
    
    if(good())
    {
        if(m_lock > 0)
        {
            m_lock--;
            //NSLog(@"lock--");
            
            if(m_lock == 0)
            {
                //NSLog(@"unlock");
                CGLUnlockContext((CGLContextObj)[m_ctx CGLContextObj]);
            }
        }
    }
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
    chugl *chgl = new chugl_osx();
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
    if(chgl) delete chgl;
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


// query function: chuck calls this when loading the Chugin
// NOTE: developer will need to modify this function to
// add additional functions to this Chugin
CK_DLL_QUERY( chugl )
{
    // hmm, don't change this...
    QUERY->setname(QUERY, "chugl");
    
    // add OpenGL
    OpenGL_query(QUERY);
    
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



