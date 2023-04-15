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

#include "chugl_api.h"
#include "chugl.h"

#include "util_opengl.h"

#include "chuck_type.h"
#include "chuck_instr.h"
#include "chuck_vm.h"

#include <math.h>


template<typename T>
T rad2deg(T rad)
{
    return rad/M_PI*180.0;
}


extern t_CKINT chugl_offset_data;


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

CK_DLL_MFUN(chugl_isOpen)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    
    RETURN->v_int = chgl->isOpen();
}

CK_DLL_MFUN(chugl_hideCursor)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    chgl->hideCursor();
}

CK_DLL_MFUN(chugl_showCursor)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    chgl->showCursor();
}

CK_DLL_MFUN(chugl_color3)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT r = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT g = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT b = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    glColor4f(r, g, b, 1.0);
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_color4)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT r = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT g = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT b = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT a = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    glColor4f(r, g, b, a);
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_hsv3)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT h = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT s = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT v = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    t_CKFLOAT r, g, b;
    HSVtoRGB(&r, &g, &b, h*360, s, v);
    glColor4f(r, g, b, 1.0);
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_hsv4)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT h = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT s = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT v = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT a = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    t_CKFLOAT r, g, b;
    HSVtoRGB(&r, &g, &b, h*360, s, v);
    glColor4f(r, g, b, a);
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_translate2)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    glTranslatef(x, y, 0);
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_scale2)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    glScalef(x, y, 1);
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_rotateZ)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT z = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    glRotatef(rad2deg(z), 0, 0, 1);
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_pushMatrix)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    chgl->enter(); // chgl->lock();
    
    glPushMatrix();
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_popMatrix)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    chgl->enter(); // chgl->lock();
    
    glPopMatrix();
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_rect)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT width = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT height = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(x, y, 0);
    glVertex3f(x+width, y, 0);
    glVertex3f(x, y+height, 0);
    glVertex3f(x+width, y+height, 0);
    glEnd();
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_triangle)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT ax = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT ay = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT bx = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT by = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT cx = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT cy = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    glBegin(GL_TRIANGLES);
    glVertex3f(ax, ay, 0);
    glVertex3f(bx, by, 0);
    glVertex3f(cx, cy, 0);
    glEnd();
}

CK_DLL_MFUN(chugl_line)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT x1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT x2 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y2 = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    glBegin(GL_LINES);
    glVertex3f(x1, y1, 0);
    glVertex3f(x2, y2, 0);
    glEnd();
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_ellipse)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT width = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT height = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    int nGeo = 48;
    GLfloat geo[nGeo*2];
    gen2d_ellipse_fan(geo, nGeo, x, y, width/2, height/2);
    
    glVertexPointer(2, GL_FLOAT, 0, geo);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glDrawArrays(GL_TRIANGLE_FAN, 0, nGeo);
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_clear)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    chgl->enter(); // chgl->lock();
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // chgl->unlock();
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
    
    RETURN->v_int = img->load(str->str());
    
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

CK_DLL_MFUN(chuglImage_draw)
{
    RETURN->v_int = 0;
    
    chugl_image *img = (chugl_image *) OBJ_MEMBER_INT(SELF, chuglImage_offset_data);
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, chuglImage_offset_chugl);
    if(!img || !chgl || !chgl->good()) return;
    
    t_CKFLOAT x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT width = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT height = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, img->tex());
    
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0,0);
    glVertex3f(x, y, 0);
    glTexCoord2f(1,0);
    glVertex3f(x+width, y, 0);
    glTexCoord2f(0,1);
    glVertex3f(x, y+height, 0);
    glTexCoord2f(1,1);
    glVertex3f(x+width, y+height, 0);
    glEnd();
    
    img->tex();
}


