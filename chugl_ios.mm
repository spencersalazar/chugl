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

#import "glplat.h"

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#import <dispatch/queue.h>

// general includes
#include <stdio.h>
#include <limits.h>


@class ChuglViewController;


class chugl_ios : public chugl
{
public:
    chugl_ios() : chugl(), m_ctx(nil) { }
    virtual ~chugl_ios();
    
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
    EAGLContext *m_ctx;
    NSLock *m_ctxLock;
    ChuglViewController *m_viewController;
};


class chugl_image_ios : public chugl_image
{
public:
    chugl_image_ios();
    virtual ~chugl_image_ios();

    t_CKBOOL load(const std::string &filepath);
    t_CKBOOL unload();

    GLuint tex();
};

@interface ChuglViewController : UIViewController

@property (nonatomic) chugl *chugl;

- (void)dismiss;

@end


chugl *chugl::platformMake()
{
    return new chugl_ios();
}

chugl_ios::~chugl_ios()
{
    m_ctx = nil;
    m_ctxLock = nil;
    m_viewController = nil;
}

void chugl_ios::hideCursor()
{
    dispatch_async(dispatch_get_main_queue(), ^{
    });
}


void chugl_ios::showCursor()
{
    dispatch_async(dispatch_get_main_queue(), ^{
    });
}


void chugl_ios::openWindow(t_CKFLOAT width, t_CKFLOAT height)
{
    m_windowWidth = width;
    m_windowHeight = height;
    
    void (^block)(void) = ^{
        UIScreen *screen = [UIScreen mainScreen];
        UIWindow *window = [[UIWindow alloc] initWithFrame:[screen bounds]];
        window.windowLevel = UIWindowLevelAlert;
        window.backgroundColor = [UIColor colorWithWhite:0.0 alpha:0.5];
        
        EAGLContext *context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        
        UIViewController *viewController = [[UIViewController alloc] init];

        UIView *contentView = [[UIView alloc] initWithFrame:[window bounds]];
//        contentView.backgroundColor = [UIColor redColor];
        viewController.view = contentView;
        
        CGRect contentBounds = [contentView bounds];
        CGPoint center = CGPointMake(contentBounds.origin.x + contentBounds.size.width/2,
                                     contentBounds.origin.y + contentBounds.size.height/2);
        CGRect viewBounds = CGRectMake(center.x-width/2, center.y-height/2, width, height);
        
        ChuglViewController *chuglViewController = [[ChuglViewController alloc] init];
        chuglViewController.chugl = this;
        
        GLKView *glView = [[GLKView alloc] initWithFrame:viewBounds context:context];
        glView.drawableDepthFormat = GLKViewDrawableDepthFormat24;
        glView.userInteractionEnabled = YES;
        
        chuglViewController.view = glView;
        
//        glView.enableSetNeedsDisplay = NO;
        
        [contentView addSubview:glView];
        
        UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
        [button setTitle:@"x" forState:UIControlStateNormal];
        [button setTitleColor:[UIColor colorWithWhite:0.8 alpha:1.0] forState:UIControlStateNormal];
        [button setTitleColor:[UIColor darkGrayColor] forState:UIControlStateHighlighted];
        button.titleLabel.font = [UIFont fontWithName:@".SFUIDisplay-Light" size:32];
        button.frame = CGRectMake(10, contentBounds.size.height-10-80, 80, 80);
        
        [button addTarget:chuglViewController action:@selector(dismiss) forControlEvents:UIControlEventTouchUpInside];
        
        [contentView addSubview:button];
        
        window.rootViewController = viewController;
        [window addSubview:viewController.view];
        
        window.alpha = 0;
        [window makeKeyAndVisible];
        [UIView animateWithDuration:0.3
                         animations:^{
                             window.alpha = 1;
                         }];

        
        m_ctxLock = [NSLock new];
        
        m_ctx = context;
        m_good = TRUE;
    };
    
    if(isMainThread())
        block();
    else
        dispatch_sync(dispatch_get_main_queue(), block);
}

void chugl_ios::openFullscreen()
{
    UIScreen *screen = [UIScreen mainScreen];
    this->openWindow(screen.bounds.size.width, screen.bounds.size.height);
}

void chugl_ios::platformEnter()
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
    
    [this->m_ctxLock lock];
    BOOL result = [EAGLContext setCurrentContext:this->m_ctx];
    if(!result)
        NSLog(@"error opening current context");
}

void chugl_ios::platformExit()
{
    // NSLog(@"platform_exit");
    [EAGLContext setCurrentContext:nil];
    [this->m_ctxLock unlock];
}


@implementation ChuglViewController

- (void)dismiss
{
    [UIView animateWithDuration:0.3
                     animations:^{
                         self.view.window.alpha = 0;
                     } completion:^(BOOL finished) {
                         [self.view.window removeFromSuperview];
                         self.view.window.hidden = YES;
                     }];
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    NSLog(@"touchesBegan");
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    NSLog(@"touchesMoved");
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    NSLog(@"touchesEnded");
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    NSLog(@"touchesCancelled");
}

@end


chugl_image *chugl_image::platformMake()
{
    return new chugl_image_ios;
}

chugl_image_ios::chugl_image_ios()
{
    
}

chugl_image_ios::~chugl_image_ios()
{
    unload();
}

bool has_extension(const std::string &filepath, const std::string &ext)
{
    return filepath.compare(filepath.size()-ext.size(), ext.size(), ext) == 0;
}

t_CKBOOL chugl_image_ios::load(const std::string &filepath)
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

t_CKBOOL chugl_image_ios::unload()
{
    if(m_tex != 0)
    {
        glDeleteTextures(1, &m_tex);
        m_tex = 0;
    }
    
    return TRUE;
}



