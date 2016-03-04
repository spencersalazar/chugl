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
#include "chugl_ix.h"

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <OpenGL/OpenGL.h>
//#import <CoreGraphics/CoreGraphics.h>
#import <ApplicationServices/ApplicationServices.h>
#import <dispatch/queue.h>

// general includes
#include <stdio.h>
#include <limits.h>


@class CKOpenGLWindow;
@class CKOpenGLView;


class chugl_osx : public chugl
{
public:
    chugl_osx() : chugl(), m_ctx(nil) { }
    virtual ~chugl_osx() { }
    
    void openWindow(t_CKFLOAT width, t_CKFLOAT height);
    void openFullscreen();
    
    virtual void hideCursor();
    virtual void showCursor();
    
    // void lock();
    // void unlock();
        
protected:
    virtual void platformEnter();
    virtual void platformExit();
    virtual t_CKBOOL isMainThread() { return dispatch_get_current_queue() == dispatch_get_main_queue(); }
    
private:
    NSOpenGLContext *m_ctx;
    CKOpenGLWindow *m_window;
    CKOpenGLWindow *m_view;
};


class chugl_image_osx : public chugl_image
{
public:
    chugl_image_osx();
    virtual ~chugl_image_osx();

    t_CKBOOL load(const std::string &filepath);
    t_CKBOOL unload();

    GLuint tex();
};


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
{
    chugl *_chugl;
}

@property (nonatomic) chugl *chugl;

@end


chugl *chugl::platformMake()
{
    return new chugl_osx();
}


void chugl_osx::hideCursor()
{
    dispatch_async(dispatch_get_main_queue(), ^{
        [NSCursor hide];
    });
}


void chugl_osx::showCursor()
{
    dispatch_async(dispatch_get_main_queue(), ^{
        [NSCursor unhide];
    });
}


void chugl_osx::openWindow(t_CKFLOAT width, t_CKFLOAT height)
{
    m_windowWidth = width;
    m_windowHeight = height;
    
    void (^block)(void) = ^{
        CKOpenGLWindow *window = [[CKOpenGLWindow alloc] initWithContentRect:NSMakeRect(0, 0, width, height)
            styleMask:NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask
            backing:NSBackingStoreBuffered
            defer:NO];
        [window setTitle:@"chugl"];
        [window center];
        [window setExcludedFromWindowsMenu:NO];
        window.acceptsMouseMovedEvents = YES;

        NSOpenGLPixelFormatAttribute attr[] = {
            NSOpenGLPFADepthSize, 32,
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersionLegacy,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleBuffers, (NSOpenGLPixelFormatAttribute)1,
            NSOpenGLPFASamples, (NSOpenGLPixelFormatAttribute)4,
            0
        };
        
        NSOpenGLPixelFormat *pixformat = [[[NSOpenGLPixelFormat alloc] initWithAttributes:attr] autorelease];
        
        CKOpenGLView *glView = [[CKOpenGLView alloc] initWithFrame:[[window contentView] bounds] pixelFormat:pixformat];
        [glView setAutoresizingMask:NSViewMinXMargin|NSViewMaxXMargin|NSViewMinYMargin|NSViewMaxYMargin];
        [[window contentView] addSubview:glView];
        glView.chugl = this;
        window.openGLView = glView;
        
        window.isFullscreen = NO;
        
        [window makeKeyAndOrderFront:nil];
        
        m_ctx = [glView openGLContext];
        m_good = TRUE;
    };
    
    if(isMainThread())
        block();
    else
        dispatch_sync(dispatch_get_main_queue(), block);
}

void chugl_osx::openFullscreen()
{
    NSRect mainDisplayRect = [[NSScreen mainScreen] frame];
    m_windowWidth = mainDisplayRect.size.width;
    m_windowHeight = mainDisplayRect.size.height;
    
    void (^block)(void) = ^{
        CKOpenGLWindow *window = [[CKOpenGLWindow alloc] initWithContentRect:mainDisplayRect
            styleMask:NSBorderlessWindowMask
            backing:NSBackingStoreBuffered
            defer:YES];
        [window setTitle:@"chugl"];
        [window setExcludedFromWindowsMenu:NO];
        window.acceptsMouseMovedEvents = YES;

        NSOpenGLPixelFormatAttribute attr[] = {
            NSOpenGLPFADepthSize, 32,
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersionLegacy,
            0
        };
        
        NSOpenGLPixelFormat *pixformat = [[[NSOpenGLPixelFormat alloc] initWithAttributes:attr] autorelease];
        
        CKOpenGLView *glView = [[CKOpenGLView alloc] initWithFrame:[[window contentView] bounds] pixelFormat:pixformat];
        [glView setAutoresizingMask:NSViewMinXMargin|NSViewMaxXMargin|NSViewMinYMargin|NSViewMaxYMargin];
        [[window contentView] addSubview:glView];
        glView.chugl = this;
        window.openGLView = glView;
        
        window.isFullscreen = YES;
        
        [window makeKeyAndOrderFront:nil];
        
        m_ctx = [glView openGLContext];
        m_good = TRUE;
    };
    
    if(isMainThread())
        block();
    else
        dispatch_sync(dispatch_get_main_queue(), block);
}

// void chugl_osx::lock()
// {
//     //NSLog(@"chugl_osx::lock");
//     assert(m_lock >= 0);
//
//     if(good())
//     {
//         if(m_lock > 0)
//         {
//             // already locked
//             //NSLog(@"lock++");
//             m_lock++;
//         }
//         else
//         {
//             //NSLog(@"lock");
//             CGLLockContext((CGLContextObj)[m_ctx CGLContextObj]);
//             [m_ctx makeCurrentContext];
//             m_lock = 1;
//         }
//     }
// }
//
// void chugl_osx::unlock()
// {
//     //NSLog(@"chugl_osx::unlock");
//     assert(m_lock >= 0);
//
//     if(good())
//     {
//         if(m_lock > 0)
//         {
//             m_lock--;
//             //NSLog(@"lock--");
//
//             if(m_lock == 0)
//             {
//                 //NSLog(@"unlock");
//                 CGLUnlockContext((CGLContextObj)[m_ctx CGLContextObj]);
//                 cleanupArrayData();
//             }
//         }
//     }
// }

void chugl_osx::platformEnter()
{
    if(m_enterMainThread && !isMainThread())
    {
        // exit on main thread
        dispatch_sync(dispatch_get_main_queue(), ^{
            glFlush();
            
            platformExit();
            
            m_enterMainThread = FALSE;
        });
        
    }
        
    CGLLockContext((CGLContextObj)[m_ctx CGLContextObj]);
    [m_ctx makeCurrentContext];
}

void chugl_osx::platformExit()
{
    // NSLog(@"platform_exit");
    CGLUnlockContext((CGLContextObj)[m_ctx CGLContextObj]);
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

@synthesize chugl = _chugl;

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

- (void)mouseMoved:(NSEvent *)theEvent
{
    NSPoint event_location = [theEvent locationInWindow];
    NSPoint local_point = [self convertPoint:event_location fromView:nil];
    self.chugl->pointer()->move(local_point.x, local_point.y);
}

- (void)mouseDragged:(NSEvent *)theEvent
{
    NSPoint event_location = [theEvent locationInWindow];
    NSPoint local_point = [self convertPoint:event_location fromView:nil];
    self.chugl->pointer()->move(local_point.x, local_point.y);
}

- (void)mouseDown:(NSEvent *)theEvent
{
    int newState = self.chugl->pointer()->state() | 0x1;
    self.chugl->pointer()->stateChange(newState);
}

- (void)mouseUp:(NSEvent *)theEvent
{
    int newState = self.chugl->pointer()->state() & ~(0x1);
    self.chugl->pointer()->stateChange(newState);
}

@end


chugl_image *chugl_image::platformMake()
{
    return new chugl_image_osx;
}

chugl_image_osx::chugl_image_osx()
{
    
}

chugl_image_osx::~chugl_image_osx()
{
    unload();
}

bool has_extension(const std::string &filepath, const std::string &ext)
{
    return filepath.compare(filepath.size()-ext.size(), ext.size(), ext) == 0;
}

t_CKBOOL chugl_image_osx::load(const std::string &filepath)
{
    GLuint spriteTexture = 0;
    CGImageRef spriteImage = NULL;
    CGContextRef spriteContext = NULL;
    CGDataProviderRef dataProvider = NULL;
    GLubyte *spriteData = NULL;
    size_t width, height;
    
    bool jpeg = false, png = false;
    
    if(has_extension(filepath, ".png")) png = true;
    else if(has_extension(filepath, ".jpeg")) jpeg = true;
    else if(has_extension(filepath, ".jpg")) jpeg = true;
    
    dataProvider = CGDataProviderCreateWithFilename(filepath.c_str());
    
    // Creates a Core Graphics image from an image file
    if(dataProvider)
    {
        if(png)
            spriteImage = CGImageCreateWithPNGDataProvider(dataProvider, NULL, true, kCGRenderingIntentDefault);
        else if(jpeg)
            spriteImage = CGImageCreateWithJPEGDataProvider(dataProvider, NULL, true, kCGRenderingIntentDefault);
    }
    
    // Texture dimensions must be a power of 2. If you write an application that allows users to supply an image,
    // you'll want to add code that checks the dimensions and takes appropriate action if they are not a power of 2.
    
    if(spriteImage)
    {
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        // Get the width and height of the image
        width = CGImageGetWidth(spriteImage);
        height = CGImageGetHeight(spriteImage);
        // Allocated memory needed for the bitmap context
        spriteData = (GLubyte *) calloc(width * height * 4, sizeof(GLubyte));
        // Uses the bitmap creation function provided by the Core Graphics framework. 
        spriteContext = CGBitmapContextCreate(spriteData, width, height, 8, width * 4, colorSpace, kCGImageAlphaPremultipliedLast);
        // After you create the context, you can draw the sprite image to the context.
        CGContextDrawImage(spriteContext, CGRectMake(0.0, 0.0, (CGFloat)width, (CGFloat)height), spriteImage);
        // You don't need the context at this point, so you need to release it to avoid memory leaks.
        CGContextRelease(spriteContext);
        CGColorSpaceRelease(colorSpace);
        
        // Use OpenGL ES to generate a name for the texture.
        glGenTextures(1, &spriteTexture);
        // Bind the texture name. 
        glBindTexture(GL_TEXTURE_2D, spriteTexture);
        // Set the texture parameters to use a minifying filter and a linear filer (weighted average)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // Specify a 2D texture image, providing the a pointer to the image data in memory
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, spriteData);
        // Release the image data
        free(spriteData);
    }
    
    m_tex = spriteTexture;    
    
    if(spriteImage != NULL) { CGImageRelease(spriteImage); spriteImage = NULL; }
    if(dataProvider != NULL) { CGDataProviderRelease(dataProvider); dataProvider = NULL; }
    
    return m_tex != 0;
}

t_CKBOOL chugl_image_osx::unload()
{
    if(m_tex != 0)
    {
        glDeleteTextures(1, &m_tex);
        m_tex = 0;
    }
    
    return TRUE;
}



