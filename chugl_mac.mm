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

@interface CKOpenGLView : NSOpenGLView

@end


chugl *chugl::platformMake()
{
    return new chugl_osx();
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




