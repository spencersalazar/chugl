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


@class CKOpenGLView;

@interface CKOpenGLWindow : NSWindow
{
    CKOpenGLView *_openGLView;
    BOOL _isFullscreen;
    NSRect _windowedSize;
}

@property (retain, nonatomic) CKOpenGLView *openGLView;
@property (nonatomic) BOOL isFullscreen;

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
            styleMask:NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask
            backing:NSBackingStoreBuffered
            defer:NO];
        [window setTitle:@"chugl"];
        [window center];
        [window setExcludedFromWindowsMenu:NO];
        
        CKOpenGLView *glView = [[CKOpenGLView alloc] initWithFrame:[[window contentView] bounds]];
        [glView setAutoresizingMask:NSViewMinXMargin|NSViewMaxXMargin|NSViewMinYMargin|NSViewMaxYMargin];
        [[window contentView] addSubview:glView];
        window.openGLView = glView;
        
        window.isFullscreen = NO;
        
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
        [window setTitle:@"chugl"];
        [window setExcludedFromWindowsMenu:NO];
        
        CKOpenGLView *glView = [[CKOpenGLView alloc] initWithFrame:[[window contentView] bounds]];
        [glView setAutoresizingMask:NSViewMinXMargin|NSViewMaxXMargin|NSViewMinYMargin|NSViewMaxYMargin];
        [[window contentView] addSubview:glView];
        window.openGLView = glView;
        
        window.isFullscreen = YES;
        
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

@synthesize openGLView = _openGLView;
@synthesize isFullscreen = _isFullscreen;

- (void)setIsFullscreen:(BOOL)fullscreen
{
    if(fullscreen != _isFullscreen)
    {
        _isFullscreen = fullscreen;
        
        if(fullscreen)
        {
            _windowedSize = [self frame];
            
            [self setStyleMask:NSBorderlessWindowMask];
            NSRect screenRect = [[self screen] frame];
            [self setFrame:screenRect display:YES];
            
            [self setLevel:NSMainMenuWindowLevel+1];
            [self setOpaque:YES];
            [self setHidesOnDeactivate:YES];
        }
        else
        {
            BOOL doCenter = NO;
            if(_windowedSize.size.width == 0 && _windowedSize.size.height == 0)
            {
                NSRect frame = [self frame];
                _windowedSize.size.width = frame.size.width*0.62;
                _windowedSize.size.height = frame.size.height*0.62;
                doCenter = YES;
            }
            
            [self setStyleMask:NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask];
            [self setFrame:_windowedSize display:YES];
            if(doCenter) [self center];
            
            [self setLevel:NSNormalWindowLevel];
            [self setHidesOnDeactivate:NO];
        }
        
        [self makeKeyAndOrderFront:nil];
        [self makeFirstResponder:self.openGLView];
    }
}

- (id)initWithContentRect:(NSRect)contentRect
    styleMask:(NSUInteger)windowStyle
    backing:(NSBackingStoreType)bufferingType
    defer:(BOOL)deferCreation
{
    if(self = [super initWithContentRect:contentRect
        styleMask:windowStyle
        backing:bufferingType
        defer:deferCreation])
    {
        _windowedSize = NSMakeRect(0, 0, 0, 0);
    }
    
    return self;
}


- (void)zoom:(id)sender
{
    self.isFullscreen = !self.isFullscreen;
}

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
        [[self window] zoom:nil];
    }
    else
    {
        [super keyDown:theEvent];
    }
}

@end




