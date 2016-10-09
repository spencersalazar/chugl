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
#include "chugl_es.h"

#include "util_opengl.h"

#include "chuck_type.h"
#include "chuck_instr.h"
#include "chuck_vm.h"

#include "glm/vec2.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
    chugl_es *chgl = (chugl_es *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT r = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT g = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT b = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    chgl->color = glm::vec4(r, g, b, 1.0);
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_color4)
{
    chugl_es *chgl = (chugl_es *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT r = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT g = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT b = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT a = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    chgl->color = glm::vec4(r, g, b, a);
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_hsv3)
{
    chugl_es *chgl = (chugl_es *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT h = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT s = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT v = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    t_CKFLOAT r, g, b;
    HSVtoRGB(&r, &g, &b, h*360, s, v);

    chgl->color = glm::vec4(r, g, b, 1.0f);

    // chgl->unlock();
}

CK_DLL_MFUN(chugl_hsv4)
{
    chugl_es *chgl = (chugl_es *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT h = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT s = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT v = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT a = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    t_CKFLOAT r, g, b;
    HSVtoRGB(&r, &g, &b, h*360, s, v);

    chgl->color = glm::vec4(r, g, b, a);
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_translate2)
{
    chugl_es *chgl = (chugl_es *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    chgl->modelview.front() = glm::translate(chgl->modelview.front(), glm::vec3(x, y, 0));
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_scale2)
{
    chugl_es *chgl = (chugl_es *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    chgl->modelview.front() = glm::scale(chgl->modelview.front(), glm::vec3(x, y, 1));
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_rotateZ)
{
    chugl_es *chgl = (chugl_es *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT z = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    chgl->modelview.front() = glm::rotate(chgl->modelview.front(), (float)z, glm::vec3(0.0f, 0.0f, -1.0f));
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_pushMatrix)
{
    chugl_es *chgl = (chugl_es *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    chgl->enter(); // chgl->lock();
    
    chgl->modelview.push_front(chgl->modelview.front());
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_popMatrix)
{
    chugl_es *chgl = (chugl_es *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    chgl->enter(); // chgl->lock();
    
    chgl->modelview.pop_front();
    
    // chgl->unlock();
}

CK_DLL_MFUN(chugl_rect)
{
    chugl_es *chgl = (chugl_es *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT width = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT height = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    glm::vec2 geo[] = {
        { x, y, },
        { x, y+height, },
        { x+width, y, },
        { x+width, y+height, },
    };
    
    chgl->render2d(geo, 4, GL_TRIANGLE_STRIP);

    // chgl->unlock();
}

CK_DLL_MFUN(chugl_triangle)
{
    chugl_es *chgl = (chugl_es *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT ax = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT ay = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT bx = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT by = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT cx = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT cy = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter();
    
    glm::vec2 geo[] = {
        { ax, ay, },
        { bx, by, },
        { cx, cy, },
    };
    
    chgl->render2d(geo, 3, GL_TRIANGLES);
}

CK_DLL_MFUN(chugl_line)
{
    chugl_es *chgl = (chugl_es *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT x1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT x2 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y2 = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter(); // chgl->lock();
    
    glm::vec2 geo[] = {
        { x1, y1, },
        { x2, y2, },
    };
    
    chgl->render2d(geo, 2, GL_LINES);
}

CK_DLL_MFUN(chugl_ellipse)
{
    chugl_es *chgl = (chugl_es *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    t_CKFLOAT x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT width = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT height = GET_NEXT_FLOAT(ARGS);
    
    chgl->enter();
    
    int nGeo = 48;
    GLfloat geo[nGeo*2];
    gen2d_ellipse_fan(geo, nGeo, x, y, width/2, height/2);
    
    chgl->render2d(geo, 48, GL_TRIANGLE_FAN);
}

CK_DLL_MFUN(chugl_clear)
{
    chugl_es *chgl = (chugl_es *) OBJ_MEMBER_INT(SELF, chugl_offset_data);
    if(!chgl->good()) return;
    
    chgl->enter();
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    
    // TODO
    
    img->tex();
}


