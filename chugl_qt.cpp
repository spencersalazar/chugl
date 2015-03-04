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



// general includes
#include <stdio.h>
#include <limits.h>

class chugl_qt : public chugl
{
public:
    chugl_qt() : chugl() { }
    virtual ~chugl_qt() { }
    
    void openWindow(t_CKFLOAT width, t_CKFLOAT height);
    void openFullscreen();
    
protected:
    virtual void platformEnter();
    virtual void platformExit();
    virtual t_CKBOOL isMainThread() { return FALSE; }
    
private:
};


class chugl_image_qt : public chugl_image
{
public:
    chugl_image_qt();
    virtual ~chugl_image_qt();

    t_CKBOOL load(const std::string &filepath);
    t_CKBOOL unload();

    GLuint tex();
};


chugl *chugl::platformMake()
{
    return new chugl_qt();
}


void chugl_qt::openWindow(t_CKFLOAT width, t_CKFLOAT height)
{
    m_windowWidth = width;
    m_windowHeight = height;
    
    // void (^block)(void) = ^{
    //     CKOpenGLWindow *window = [[CKOpenGLWindow alloc] initWithContentRect:NSMakeRect(0, 0, width, height)
    //         styleMask:NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask
    //         backing:NSBackingStoreBuffered
    //         defer:NO];
    //     [window setTitle:@"chugl"];
    //     [window center];
    //     [window setExcludedFromWindowsMenu:NO];
    //
    //     CKOpenGLView *glView = [[CKOpenGLView alloc] initWithFrame:[[window contentView] bounds]];
    //     [glView setAutoresizingMask:NSViewMinXMargin|NSViewMaxXMargin|NSViewMinYMargin|NSViewMaxYMargin];
    //     [[window contentView] addSubview:glView];
    //     window.openGLView = glView;
    //
    //     window.isFullscreen = NO;
    //
    //     [window makeKeyAndOrderFront:nil];
    //
    //     m_ctx = [glView openGLContext];
    //     m_good = TRUE;
    // };
    //
    // if(isMainThread())
    //     block();
    // else
    //     dispatch_sync(dispatch_get_main_queue(), block);
}

void chugl_qt::openFullscreen()
{
    // NSRect mainDisplayRect = [[NSScreen mainScreen] frame];
    // m_windowWidth = mainDisplayRect.size.width;
    // m_windowHeight = mainDisplayRect.size.height;
    //
    // void (^block)(void) = ^{
    //     CKOpenGLWindow *window = [[CKOpenGLWindow alloc] initWithContentRect:mainDisplayRect
    //         styleMask:NSBorderlessWindowMask
    //         backing:NSBackingStoreBuffered
    //         defer:YES];
    //     [window setTitle:@"chugl"];
    //     [window setExcludedFromWindowsMenu:NO];
    //
    //     CKOpenGLView *glView = [[CKOpenGLView alloc] initWithFrame:[[window contentView] bounds]];
    //     [glView setAutoresizingMask:NSViewMinXMargin|NSViewMaxXMargin|NSViewMinYMargin|NSViewMaxYMargin];
    //     [[window contentView] addSubview:glView];
    //     window.openGLView = glView;
    //
    //     window.isFullscreen = YES;
    //
    //     [window makeKeyAndOrderFront:nil];
    //
    //     m_ctx = [glView openGLContext];
    //     m_good = TRUE;
    // };
    //
    // if(isMainThread())
    //     block();
    // else
    //     dispatch_sync(dispatch_get_main_queue(), block);
}

void chugl_qt::platformEnter()
{
    // if(m_enterMainThread && !isMainThread())
    // {
    //     // exit on main thread
    //     dispatch_sync(dispatch_get_main_queue(), ^{
    //         glFlush();
    //
    //         platformExit();
    //
    //         m_enterMainThread = FALSE;
    //     });
    //
    // }
    //
    // CGLLockContext((CGLContextObj)[m_ctx CGLContextObj]);
    // [m_ctx makeCurrentContext];
}

void chugl_qt::platformExit()
{
    // NSLog(@"platform_exit");
    // CGLUnlockContext((CGLContextObj)[m_ctx CGLContextObj]);
}


chugl_image *chugl_image::platformMake()
{
    return new chugl_image_qt;
}

chugl_image_qt::chugl_image_qt()
{
    
}

chugl_image_qt::~chugl_image_qt()
{
    unload();
}

bool has_extension(const std::string &filepath, const std::string &ext)
{
    return filepath.compare(filepath.size()-ext.size(), ext.size(), ext) == 0;
}

t_CKBOOL chugl_image_qt::load(const std::string &filepath)
{    
    return m_tex != 0;
}

t_CKBOOL chugl_image_qt::unload()
{
    if(m_tex != 0)
    {
        glDeleteTextures(1, &m_tex);
        m_tex = 0;
    }
    
    return TRUE;
}



