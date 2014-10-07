
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

#include "chuck_dl.h"
#include "chuck_def.h"
#include "chuck_type.h"

#include "chugl_util.h"

#ifdef __APPLE__
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>
#else
#include <gl/gl.h>
#endif // __APPLE__

// general includes
#include <stdio.h>
#include <limits.h>

t_CKINT Chuck_OpenGL_offset_chugl = 0;

CK_DLL_CTOR(Chuck_OpenGL_ctor)
{
    OBJ_MEMBER_OBJECT(SELF, Chuck_OpenGL_offset_chugl) = NULL;
}


CK_DLL_MFUN(Chuck_OpenGL_CullFace)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);

    glCullFace(arg_mode);
}


CK_DLL_MFUN(Chuck_OpenGL_FrontFace)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);

    glFrontFace(arg_mode);
}


CK_DLL_MFUN(Chuck_OpenGL_Hint)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);

    glHint(arg_target, arg_mode);
}


CK_DLL_MFUN(Chuck_OpenGL_LineWidth)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_width = GET_NEXT_FLOAT(ARGS);

    glLineWidth(arg_width);
}


CK_DLL_MFUN(Chuck_OpenGL_PointSize)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_size = GET_NEXT_FLOAT(ARGS);

    glPointSize(arg_size);
}


CK_DLL_MFUN(Chuck_OpenGL_PolygonMode)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_face = GET_NEXT_INT(ARGS);
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);

    glPolygonMode(arg_face, arg_mode);
}


CK_DLL_MFUN(Chuck_OpenGL_Scissor)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);

    glScissor(arg_x, arg_y, arg_width, arg_height);
}


CK_DLL_MFUN(Chuck_OpenGL_TexParameterf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_param = GET_NEXT_FLOAT(ARGS);

    glTexParameterf(arg_target, arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_TexParameterfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glTexParameterfv(arg_target, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_TexParameteri)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKINT arg_param = GET_NEXT_INT(ARGS);

    glTexParameteri(arg_target, arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_TexParameteriv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glTexParameteriv(arg_target, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_TexImage1D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_internalformat = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_border = GET_NEXT_INT(ARGS);
    t_CKINT arg_format = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pixels_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pixels;
    if(_arg_pixels_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pixels_arr = (Chuck_Array4 *) _arg_pixels_arr;
        GLubyte *arg_pixels_v = new GLubyte[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray4_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }
    else if(_arg_pixels_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pixels_arr = (Chuck_Array8 *) _arg_pixels_arr;
        GLfloat *arg_pixels_v = new GLfloat[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray8_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }

    glTexImage1D(arg_target, arg_level, arg_internalformat, arg_width, arg_border, arg_format, arg_type, arg_pixels);
}


CK_DLL_MFUN(Chuck_OpenGL_TexImage2D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_internalformat = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_border = GET_NEXT_INT(ARGS);
    t_CKINT arg_format = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pixels_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pixels;
    if(_arg_pixels_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pixels_arr = (Chuck_Array4 *) _arg_pixels_arr;
        GLubyte *arg_pixels_v = new GLubyte[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray4_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }
    else if(_arg_pixels_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pixels_arr = (Chuck_Array8 *) _arg_pixels_arr;
        GLfloat *arg_pixels_v = new GLfloat[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray8_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }

    glTexImage2D(arg_target, arg_level, arg_internalformat, arg_width, arg_height, arg_border, arg_format, arg_type, arg_pixels);
}


CK_DLL_MFUN(Chuck_OpenGL_DrawBuffer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_buf = GET_NEXT_INT(ARGS);

    glDrawBuffer(arg_buf);
}


CK_DLL_MFUN(Chuck_OpenGL_Clear)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mask = GET_NEXT_INT(ARGS);

    glClear(arg_mask);
}


CK_DLL_MFUN(Chuck_OpenGL_ClearColor)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_red = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_green = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_blue = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_alpha = GET_NEXT_FLOAT(ARGS);

    glClearColor(arg_red, arg_green, arg_blue, arg_alpha);
}


CK_DLL_MFUN(Chuck_OpenGL_ClearStencil)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_s = GET_NEXT_INT(ARGS);

    glClearStencil(arg_s);
}


CK_DLL_MFUN(Chuck_OpenGL_ClearDepth)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_depth = GET_NEXT_FLOAT(ARGS);

    glClearDepth(arg_depth);
}


CK_DLL_MFUN(Chuck_OpenGL_StencilMask)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mask = GET_NEXT_INT(ARGS);

    glStencilMask(arg_mask);
}


CK_DLL_MFUN(Chuck_OpenGL_ColorMask)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);
    t_CKINT arg_alpha = GET_NEXT_INT(ARGS);

    glColorMask(arg_red, arg_green, arg_blue, arg_alpha);
}


CK_DLL_MFUN(Chuck_OpenGL_DepthMask)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_flag = GET_NEXT_INT(ARGS);

    glDepthMask(arg_flag);
}


CK_DLL_MFUN(Chuck_OpenGL_Disable)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_cap = GET_NEXT_INT(ARGS);

    glDisable(arg_cap);
}


CK_DLL_MFUN(Chuck_OpenGL_Enable)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_cap = GET_NEXT_INT(ARGS);

    glEnable(arg_cap);
}


CK_DLL_MFUN(Chuck_OpenGL_Finish)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    

    glFinish();
}


CK_DLL_MFUN(Chuck_OpenGL_Flush)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    

    glFlush();
}


CK_DLL_MFUN(Chuck_OpenGL_BlendFunc)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_sfactor = GET_NEXT_INT(ARGS);
    t_CKINT arg_dfactor = GET_NEXT_INT(ARGS);

    glBlendFunc(arg_sfactor, arg_dfactor);
}


CK_DLL_MFUN(Chuck_OpenGL_LogicOp)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_opcode = GET_NEXT_INT(ARGS);

    glLogicOp(arg_opcode);
}


CK_DLL_MFUN(Chuck_OpenGL_StencilFunc)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_func = GET_NEXT_INT(ARGS);
    t_CKINT arg_ref = GET_NEXT_INT(ARGS);
    t_CKINT arg_mask = GET_NEXT_INT(ARGS);

    glStencilFunc(arg_func, arg_ref, arg_mask);
}


CK_DLL_MFUN(Chuck_OpenGL_StencilOp)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_fail = GET_NEXT_INT(ARGS);
    t_CKINT arg_zfail = GET_NEXT_INT(ARGS);
    t_CKINT arg_zpass = GET_NEXT_INT(ARGS);

    glStencilOp(arg_fail, arg_zfail, arg_zpass);
}


CK_DLL_MFUN(Chuck_OpenGL_DepthFunc)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_func = GET_NEXT_INT(ARGS);

    glDepthFunc(arg_func);
}


CK_DLL_MFUN(Chuck_OpenGL_PixelStoref)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_param = GET_NEXT_FLOAT(ARGS);

    glPixelStoref(arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_PixelStorei)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKINT arg_param = GET_NEXT_INT(ARGS);

    glPixelStorei(arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_ReadBuffer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_src = GET_NEXT_INT(ARGS);

    glReadBuffer(arg_src);
}


CK_DLL_MFUN(Chuck_OpenGL_ReadPixels)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_format = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pixels_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pixels;
    if(_arg_pixels_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pixels_arr = (Chuck_Array4 *) _arg_pixels_arr;
        GLubyte *arg_pixels_v = new GLubyte[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray4_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }
    else if(_arg_pixels_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pixels_arr = (Chuck_Array8 *) _arg_pixels_arr;
        GLfloat *arg_pixels_v = new GLfloat[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray8_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }

    glReadPixels(arg_x, arg_y, arg_width, arg_height, arg_format, arg_type, arg_pixels);
}


CK_DLL_MFUN(Chuck_OpenGL_GetBooleanv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_data_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLboolean *arg_data = new GLboolean[arg_data_arr->size()];
    chgl->scheduleArrayForCleanup(arg_data);
    copy_ckarray4_to_array(arg_data, arg_data_arr);

    glGetBooleanv(arg_pname, arg_data);
}


CK_DLL_MFUN(Chuck_OpenGL_GetDoublev)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_data_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_data = new GLdouble[arg_data_arr->size()];
    chgl->scheduleArrayForCleanup(arg_data);
    copy_ckarray8_to_array(arg_data, arg_data_arr);

    glGetDoublev(arg_pname, arg_data);
}


CK_DLL_MFUN(Chuck_OpenGL_GetError)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    

    RETURN->v_int = glGetError();
}


CK_DLL_MFUN(Chuck_OpenGL_GetFloatv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_data_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_data = new GLfloat[arg_data_arr->size()];
    chgl->scheduleArrayForCleanup(arg_data);
    copy_ckarray8_to_array(arg_data, arg_data_arr);

    glGetFloatv(arg_pname, arg_data);
}


CK_DLL_MFUN(Chuck_OpenGL_GetIntegerv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_data_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_data = new GLint[arg_data_arr->size()];
    chgl->scheduleArrayForCleanup(arg_data);
    copy_ckarray4_to_array(arg_data, arg_data_arr);

    glGetIntegerv(arg_pname, arg_data);
}


CK_DLL_MFUN(Chuck_OpenGL_GetTexImage)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_format = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pixels_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pixels;
    if(_arg_pixels_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pixels_arr = (Chuck_Array4 *) _arg_pixels_arr;
        GLubyte *arg_pixels_v = new GLubyte[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray4_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }
    else if(_arg_pixels_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pixels_arr = (Chuck_Array8 *) _arg_pixels_arr;
        GLfloat *arg_pixels_v = new GLfloat[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray8_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }

    glGetTexImage(arg_target, arg_level, arg_format, arg_type, arg_pixels);
}


CK_DLL_MFUN(Chuck_OpenGL_GetTexParameterfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glGetTexParameterfv(arg_target, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetTexParameteriv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetTexParameteriv(arg_target, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetTexLevelParameterfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glGetTexLevelParameterfv(arg_target, arg_level, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetTexLevelParameteriv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetTexLevelParameteriv(arg_target, arg_level, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_IsEnabled)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_cap = GET_NEXT_INT(ARGS);

    RETURN->v_int = glIsEnabled(arg_cap);
}


CK_DLL_MFUN(Chuck_OpenGL_DepthRange)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_near = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_far = GET_NEXT_FLOAT(ARGS);

    glDepthRange(arg_near, arg_far);
}


CK_DLL_MFUN(Chuck_OpenGL_Viewport)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);

    glViewport(arg_x, arg_y, arg_width, arg_height);
}


CK_DLL_MFUN(Chuck_OpenGL_NewList)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_list = GET_NEXT_INT(ARGS);
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);

    glNewList(arg_list, arg_mode);
}


CK_DLL_MFUN(Chuck_OpenGL_EndList)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    

    glEndList();
}


CK_DLL_MFUN(Chuck_OpenGL_CallList)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_list = GET_NEXT_INT(ARGS);

    glCallList(arg_list);
}


CK_DLL_MFUN(Chuck_OpenGL_CallLists)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_lists_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_lists;
    if(_arg_lists_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_lists_arr = (Chuck_Array4 *) _arg_lists_arr;
        GLubyte *arg_lists_v = new GLubyte[arg_lists_arr->size()];
        chgl->scheduleArrayForCleanup(arg_lists_v);
        copy_ckarray4_to_array(arg_lists_v, arg_lists_arr);
        arg_lists = (void *) arg_lists_v;
    }
    else if(_arg_lists_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_lists_arr = (Chuck_Array8 *) _arg_lists_arr;
        GLfloat *arg_lists_v = new GLfloat[arg_lists_arr->size()];
        chgl->scheduleArrayForCleanup(arg_lists_v);
        copy_ckarray8_to_array(arg_lists_v, arg_lists_arr);
        arg_lists = (void *) arg_lists_v;
    }

    glCallLists(arg_n, arg_type, arg_lists);
}


CK_DLL_MFUN(Chuck_OpenGL_DeleteLists)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_list = GET_NEXT_INT(ARGS);
    t_CKINT arg_range = GET_NEXT_INT(ARGS);

    glDeleteLists(arg_list, arg_range);
}


CK_DLL_MFUN(Chuck_OpenGL_GenLists)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_range = GET_NEXT_INT(ARGS);

    RETURN->v_int = glGenLists(arg_range);
}


CK_DLL_MFUN(Chuck_OpenGL_ListBase)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_base = GET_NEXT_INT(ARGS);

    glListBase(arg_base);
}


CK_DLL_MFUN(Chuck_OpenGL_Begin)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);

    glBegin(arg_mode);
}


CK_DLL_MFUN(Chuck_OpenGL_Bitmap)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_xorig = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_yorig = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_xmove = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_ymove = GET_NEXT_FLOAT(ARGS);
    Chuck_Array4 *arg_bitmap_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLubyte *arg_bitmap = new GLubyte[arg_bitmap_arr->size()];
    chgl->scheduleArrayForCleanup(arg_bitmap);
    copy_ckarray4_to_array(arg_bitmap, arg_bitmap_arr);

    glBitmap(arg_width, arg_height, arg_xorig, arg_yorig, arg_xmove, arg_ymove, arg_bitmap);
}


CK_DLL_MFUN(Chuck_OpenGL_Color3b)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);

    glColor3b(arg_red, arg_green, arg_blue);
}


CK_DLL_MFUN(Chuck_OpenGL_Color3bv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLbyte *arg_v = new GLbyte[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glColor3bv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Color3d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_red = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_green = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_blue = GET_NEXT_FLOAT(ARGS);

    glColor3d(arg_red, arg_green, arg_blue);
}


CK_DLL_MFUN(Chuck_OpenGL_Color3dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glColor3dv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Color3f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_red = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_green = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_blue = GET_NEXT_FLOAT(ARGS);

    glColor3f(arg_red, arg_green, arg_blue);
}


CK_DLL_MFUN(Chuck_OpenGL_Color3fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glColor3fv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Color3i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);

    glColor3i(arg_red, arg_green, arg_blue);
}


CK_DLL_MFUN(Chuck_OpenGL_Color3iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glColor3iv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Color3s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);

    glColor3s(arg_red, arg_green, arg_blue);
}


CK_DLL_MFUN(Chuck_OpenGL_Color3sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glColor3sv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Color3ub)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);

    glColor3ub(arg_red, arg_green, arg_blue);
}


CK_DLL_MFUN(Chuck_OpenGL_Color3ubv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLubyte *arg_v = new GLubyte[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glColor3ubv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Color3ui)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);

    glColor3ui(arg_red, arg_green, arg_blue);
}


CK_DLL_MFUN(Chuck_OpenGL_Color3uiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_v = new GLuint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glColor3uiv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Color3us)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);

    glColor3us(arg_red, arg_green, arg_blue);
}


CK_DLL_MFUN(Chuck_OpenGL_Color3usv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLushort *arg_v = new GLushort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glColor3usv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Color4b)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);
    t_CKINT arg_alpha = GET_NEXT_INT(ARGS);

    glColor4b(arg_red, arg_green, arg_blue, arg_alpha);
}


CK_DLL_MFUN(Chuck_OpenGL_Color4bv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLbyte *arg_v = new GLbyte[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glColor4bv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Color4d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_red = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_green = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_blue = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_alpha = GET_NEXT_FLOAT(ARGS);

    glColor4d(arg_red, arg_green, arg_blue, arg_alpha);
}


CK_DLL_MFUN(Chuck_OpenGL_Color4dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glColor4dv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Color4f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_red = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_green = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_blue = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_alpha = GET_NEXT_FLOAT(ARGS);

    glColor4f(arg_red, arg_green, arg_blue, arg_alpha);
}


CK_DLL_MFUN(Chuck_OpenGL_Color4fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glColor4fv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Color4i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);
    t_CKINT arg_alpha = GET_NEXT_INT(ARGS);

    glColor4i(arg_red, arg_green, arg_blue, arg_alpha);
}


CK_DLL_MFUN(Chuck_OpenGL_Color4iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glColor4iv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Color4s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);
    t_CKINT arg_alpha = GET_NEXT_INT(ARGS);

    glColor4s(arg_red, arg_green, arg_blue, arg_alpha);
}


CK_DLL_MFUN(Chuck_OpenGL_Color4sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glColor4sv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Color4ub)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);
    t_CKINT arg_alpha = GET_NEXT_INT(ARGS);

    glColor4ub(arg_red, arg_green, arg_blue, arg_alpha);
}


CK_DLL_MFUN(Chuck_OpenGL_Color4ubv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLubyte *arg_v = new GLubyte[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glColor4ubv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Color4ui)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);
    t_CKINT arg_alpha = GET_NEXT_INT(ARGS);

    glColor4ui(arg_red, arg_green, arg_blue, arg_alpha);
}


CK_DLL_MFUN(Chuck_OpenGL_Color4uiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_v = new GLuint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glColor4uiv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Color4us)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);
    t_CKINT arg_alpha = GET_NEXT_INT(ARGS);

    glColor4us(arg_red, arg_green, arg_blue, arg_alpha);
}


CK_DLL_MFUN(Chuck_OpenGL_Color4usv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLushort *arg_v = new GLushort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glColor4usv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_EdgeFlag)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_flag = GET_NEXT_INT(ARGS);

    glEdgeFlag(arg_flag);
}


CK_DLL_MFUN(Chuck_OpenGL_EdgeFlagv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_flag_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLboolean *arg_flag = new GLboolean[arg_flag_arr->size()];
    chgl->scheduleArrayForCleanup(arg_flag);
    copy_ckarray4_to_array(arg_flag, arg_flag_arr);

    glEdgeFlagv(arg_flag);
}


CK_DLL_MFUN(Chuck_OpenGL_End)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    

    glEnd();
}


CK_DLL_MFUN(Chuck_OpenGL_Indexd)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_c = GET_NEXT_FLOAT(ARGS);

    glIndexd(arg_c);
}


CK_DLL_MFUN(Chuck_OpenGL_Indexdv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_c_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_c = new GLdouble[arg_c_arr->size()];
    chgl->scheduleArrayForCleanup(arg_c);
    copy_ckarray8_to_array(arg_c, arg_c_arr);

    glIndexdv(arg_c);
}


CK_DLL_MFUN(Chuck_OpenGL_Indexf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_c = GET_NEXT_FLOAT(ARGS);

    glIndexf(arg_c);
}


CK_DLL_MFUN(Chuck_OpenGL_Indexfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_c_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_c = new GLfloat[arg_c_arr->size()];
    chgl->scheduleArrayForCleanup(arg_c);
    copy_ckarray8_to_array(arg_c, arg_c_arr);

    glIndexfv(arg_c);
}


CK_DLL_MFUN(Chuck_OpenGL_Indexi)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_c = GET_NEXT_INT(ARGS);

    glIndexi(arg_c);
}


CK_DLL_MFUN(Chuck_OpenGL_Indexiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_c_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_c = new GLint[arg_c_arr->size()];
    chgl->scheduleArrayForCleanup(arg_c);
    copy_ckarray4_to_array(arg_c, arg_c_arr);

    glIndexiv(arg_c);
}


CK_DLL_MFUN(Chuck_OpenGL_Indexs)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_c = GET_NEXT_INT(ARGS);

    glIndexs(arg_c);
}


CK_DLL_MFUN(Chuck_OpenGL_Indexsv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_c_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_c = new GLshort[arg_c_arr->size()];
    chgl->scheduleArrayForCleanup(arg_c);
    copy_ckarray4_to_array(arg_c, arg_c_arr);

    glIndexsv(arg_c);
}


CK_DLL_MFUN(Chuck_OpenGL_Normal3b)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_nx = GET_NEXT_INT(ARGS);
    t_CKINT arg_ny = GET_NEXT_INT(ARGS);
    t_CKINT arg_nz = GET_NEXT_INT(ARGS);

    glNormal3b(arg_nx, arg_ny, arg_nz);
}


CK_DLL_MFUN(Chuck_OpenGL_Normal3bv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLbyte *arg_v = new GLbyte[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glNormal3bv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Normal3d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_nx = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_ny = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_nz = GET_NEXT_FLOAT(ARGS);

    glNormal3d(arg_nx, arg_ny, arg_nz);
}


CK_DLL_MFUN(Chuck_OpenGL_Normal3dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glNormal3dv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Normal3f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_nx = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_ny = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_nz = GET_NEXT_FLOAT(ARGS);

    glNormal3f(arg_nx, arg_ny, arg_nz);
}


CK_DLL_MFUN(Chuck_OpenGL_Normal3fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glNormal3fv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Normal3i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_nx = GET_NEXT_INT(ARGS);
    t_CKINT arg_ny = GET_NEXT_INT(ARGS);
    t_CKINT arg_nz = GET_NEXT_INT(ARGS);

    glNormal3i(arg_nx, arg_ny, arg_nz);
}


CK_DLL_MFUN(Chuck_OpenGL_Normal3iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glNormal3iv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Normal3s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_nx = GET_NEXT_INT(ARGS);
    t_CKINT arg_ny = GET_NEXT_INT(ARGS);
    t_CKINT arg_nz = GET_NEXT_INT(ARGS);

    glNormal3s(arg_nx, arg_ny, arg_nz);
}


CK_DLL_MFUN(Chuck_OpenGL_Normal3sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glNormal3sv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos2d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);

    glRasterPos2d(arg_x, arg_y);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos2dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glRasterPos2dv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos2f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);

    glRasterPos2f(arg_x, arg_y);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos2fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glRasterPos2fv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos2i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);

    glRasterPos2i(arg_x, arg_y);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos2iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glRasterPos2iv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos2s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);

    glRasterPos2s(arg_x, arg_y);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos2sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glRasterPos2sv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos3d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);

    glRasterPos3d(arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos3dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glRasterPos3dv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos3f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);

    glRasterPos3f(arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos3fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glRasterPos3fv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos3i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_z = GET_NEXT_INT(ARGS);

    glRasterPos3i(arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos3iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glRasterPos3iv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos3s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_z = GET_NEXT_INT(ARGS);

    glRasterPos3s(arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos3sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glRasterPos3sv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos4d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_w = GET_NEXT_FLOAT(ARGS);

    glRasterPos4d(arg_x, arg_y, arg_z, arg_w);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos4dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glRasterPos4dv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos4f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_w = GET_NEXT_FLOAT(ARGS);

    glRasterPos4f(arg_x, arg_y, arg_z, arg_w);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos4fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glRasterPos4fv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos4i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_z = GET_NEXT_INT(ARGS);
    t_CKINT arg_w = GET_NEXT_INT(ARGS);

    glRasterPos4i(arg_x, arg_y, arg_z, arg_w);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos4iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glRasterPos4iv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos4s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_z = GET_NEXT_INT(ARGS);
    t_CKINT arg_w = GET_NEXT_INT(ARGS);

    glRasterPos4s(arg_x, arg_y, arg_z, arg_w);
}


CK_DLL_MFUN(Chuck_OpenGL_RasterPos4sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glRasterPos4sv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Rectd)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_x2 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y2 = GET_NEXT_FLOAT(ARGS);

    glRectd(arg_x1, arg_y1, arg_x2, arg_y2);
}


CK_DLL_MFUN(Chuck_OpenGL_Rectdv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v1_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v1 = new GLdouble[arg_v1_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v1);
    copy_ckarray8_to_array(arg_v1, arg_v1_arr);
    Chuck_Array8 *arg_v2_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v2 = new GLdouble[arg_v2_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v2);
    copy_ckarray8_to_array(arg_v2, arg_v2_arr);

    glRectdv(arg_v1, arg_v2);
}


CK_DLL_MFUN(Chuck_OpenGL_Rectf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_x2 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y2 = GET_NEXT_FLOAT(ARGS);

    glRectf(arg_x1, arg_y1, arg_x2, arg_y2);
}


CK_DLL_MFUN(Chuck_OpenGL_Rectfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v1_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v1 = new GLfloat[arg_v1_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v1);
    copy_ckarray8_to_array(arg_v1, arg_v1_arr);
    Chuck_Array8 *arg_v2_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v2 = new GLfloat[arg_v2_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v2);
    copy_ckarray8_to_array(arg_v2, arg_v2_arr);

    glRectfv(arg_v1, arg_v2);
}


CK_DLL_MFUN(Chuck_OpenGL_Recti)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x1 = GET_NEXT_INT(ARGS);
    t_CKINT arg_y1 = GET_NEXT_INT(ARGS);
    t_CKINT arg_x2 = GET_NEXT_INT(ARGS);
    t_CKINT arg_y2 = GET_NEXT_INT(ARGS);

    glRecti(arg_x1, arg_y1, arg_x2, arg_y2);
}


CK_DLL_MFUN(Chuck_OpenGL_Rectiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v1_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v1 = new GLint[arg_v1_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v1);
    copy_ckarray4_to_array(arg_v1, arg_v1_arr);
    Chuck_Array4 *arg_v2_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v2 = new GLint[arg_v2_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v2);
    copy_ckarray4_to_array(arg_v2, arg_v2_arr);

    glRectiv(arg_v1, arg_v2);
}


CK_DLL_MFUN(Chuck_OpenGL_Rects)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x1 = GET_NEXT_INT(ARGS);
    t_CKINT arg_y1 = GET_NEXT_INT(ARGS);
    t_CKINT arg_x2 = GET_NEXT_INT(ARGS);
    t_CKINT arg_y2 = GET_NEXT_INT(ARGS);

    glRects(arg_x1, arg_y1, arg_x2, arg_y2);
}


CK_DLL_MFUN(Chuck_OpenGL_Rectsv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v1_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v1 = new GLshort[arg_v1_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v1);
    copy_ckarray4_to_array(arg_v1, arg_v1_arr);
    Chuck_Array4 *arg_v2_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v2 = new GLshort[arg_v2_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v2);
    copy_ckarray4_to_array(arg_v2, arg_v2_arr);

    glRectsv(arg_v1, arg_v2);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord1d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_s = GET_NEXT_FLOAT(ARGS);

    glTexCoord1d(arg_s);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord1dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glTexCoord1dv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord1f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_s = GET_NEXT_FLOAT(ARGS);

    glTexCoord1f(arg_s);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord1fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glTexCoord1fv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord1i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_s = GET_NEXT_INT(ARGS);

    glTexCoord1i(arg_s);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord1iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glTexCoord1iv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord1s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_s = GET_NEXT_INT(ARGS);

    glTexCoord1s(arg_s);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord1sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glTexCoord1sv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord2d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_s = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_t = GET_NEXT_FLOAT(ARGS);

    glTexCoord2d(arg_s, arg_t);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord2dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glTexCoord2dv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord2f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_s = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_t = GET_NEXT_FLOAT(ARGS);

    glTexCoord2f(arg_s, arg_t);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord2fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glTexCoord2fv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord2i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_s = GET_NEXT_INT(ARGS);
    t_CKINT arg_t = GET_NEXT_INT(ARGS);

    glTexCoord2i(arg_s, arg_t);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord2iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glTexCoord2iv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord2s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_s = GET_NEXT_INT(ARGS);
    t_CKINT arg_t = GET_NEXT_INT(ARGS);

    glTexCoord2s(arg_s, arg_t);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord2sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glTexCoord2sv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord3d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_s = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_t = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_r = GET_NEXT_FLOAT(ARGS);

    glTexCoord3d(arg_s, arg_t, arg_r);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord3dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glTexCoord3dv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord3f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_s = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_t = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_r = GET_NEXT_FLOAT(ARGS);

    glTexCoord3f(arg_s, arg_t, arg_r);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord3fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glTexCoord3fv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord3i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_s = GET_NEXT_INT(ARGS);
    t_CKINT arg_t = GET_NEXT_INT(ARGS);
    t_CKINT arg_r = GET_NEXT_INT(ARGS);

    glTexCoord3i(arg_s, arg_t, arg_r);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord3iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glTexCoord3iv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord3s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_s = GET_NEXT_INT(ARGS);
    t_CKINT arg_t = GET_NEXT_INT(ARGS);
    t_CKINT arg_r = GET_NEXT_INT(ARGS);

    glTexCoord3s(arg_s, arg_t, arg_r);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord3sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glTexCoord3sv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord4d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_s = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_t = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_r = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_q = GET_NEXT_FLOAT(ARGS);

    glTexCoord4d(arg_s, arg_t, arg_r, arg_q);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord4dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glTexCoord4dv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord4f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_s = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_t = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_r = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_q = GET_NEXT_FLOAT(ARGS);

    glTexCoord4f(arg_s, arg_t, arg_r, arg_q);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord4fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glTexCoord4fv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord4i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_s = GET_NEXT_INT(ARGS);
    t_CKINT arg_t = GET_NEXT_INT(ARGS);
    t_CKINT arg_r = GET_NEXT_INT(ARGS);
    t_CKINT arg_q = GET_NEXT_INT(ARGS);

    glTexCoord4i(arg_s, arg_t, arg_r, arg_q);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord4iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glTexCoord4iv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord4s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_s = GET_NEXT_INT(ARGS);
    t_CKINT arg_t = GET_NEXT_INT(ARGS);
    t_CKINT arg_r = GET_NEXT_INT(ARGS);
    t_CKINT arg_q = GET_NEXT_INT(ARGS);

    glTexCoord4s(arg_s, arg_t, arg_r, arg_q);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoord4sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glTexCoord4sv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex2d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);

    glVertex2d(arg_x, arg_y);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex2dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertex2dv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex2f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);

    glVertex2f(arg_x, arg_y);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex2fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertex2fv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex2i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);

    glVertex2i(arg_x, arg_y);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex2iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertex2iv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex2s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);

    glVertex2s(arg_x, arg_y);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex2sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertex2sv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex3d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);

    glVertex3d(arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex3dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertex3dv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex3f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);

    glVertex3f(arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex3fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertex3fv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex3i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_z = GET_NEXT_INT(ARGS);

    glVertex3i(arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex3iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertex3iv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex3s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_z = GET_NEXT_INT(ARGS);

    glVertex3s(arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex3sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertex3sv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex4d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_w = GET_NEXT_FLOAT(ARGS);

    glVertex4d(arg_x, arg_y, arg_z, arg_w);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex4dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertex4dv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex4f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_w = GET_NEXT_FLOAT(ARGS);

    glVertex4f(arg_x, arg_y, arg_z, arg_w);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex4fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertex4fv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex4i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_z = GET_NEXT_INT(ARGS);
    t_CKINT arg_w = GET_NEXT_INT(ARGS);

    glVertex4i(arg_x, arg_y, arg_z, arg_w);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex4iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertex4iv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex4s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_z = GET_NEXT_INT(ARGS);
    t_CKINT arg_w = GET_NEXT_INT(ARGS);

    glVertex4s(arg_x, arg_y, arg_z, arg_w);
}


CK_DLL_MFUN(Chuck_OpenGL_Vertex4sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertex4sv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_ClipPlane)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_plane = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_equation_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_equation = new GLdouble[arg_equation_arr->size()];
    chgl->scheduleArrayForCleanup(arg_equation);
    copy_ckarray8_to_array(arg_equation, arg_equation_arr);

    glClipPlane(arg_plane, arg_equation);
}


CK_DLL_MFUN(Chuck_OpenGL_ColorMaterial)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_face = GET_NEXT_INT(ARGS);
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);

    glColorMaterial(arg_face, arg_mode);
}


CK_DLL_MFUN(Chuck_OpenGL_Fogf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_param = GET_NEXT_FLOAT(ARGS);

    glFogf(arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_Fogfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glFogfv(arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_Fogi)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKINT arg_param = GET_NEXT_INT(ARGS);

    glFogi(arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_Fogiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glFogiv(arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_Lightf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_light = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_param = GET_NEXT_FLOAT(ARGS);

    glLightf(arg_light, arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_Lightfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_light = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glLightfv(arg_light, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_Lighti)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_light = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKINT arg_param = GET_NEXT_INT(ARGS);

    glLighti(arg_light, arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_Lightiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_light = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glLightiv(arg_light, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_LightModelf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_param = GET_NEXT_FLOAT(ARGS);

    glLightModelf(arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_LightModelfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glLightModelfv(arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_LightModeli)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKINT arg_param = GET_NEXT_INT(ARGS);

    glLightModeli(arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_LightModeliv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glLightModeliv(arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_LineStipple)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_factor = GET_NEXT_INT(ARGS);
    t_CKINT arg_pattern = GET_NEXT_INT(ARGS);

    glLineStipple(arg_factor, arg_pattern);
}


CK_DLL_MFUN(Chuck_OpenGL_Materialf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_face = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_param = GET_NEXT_FLOAT(ARGS);

    glMaterialf(arg_face, arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_Materialfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_face = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glMaterialfv(arg_face, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_Materiali)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_face = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKINT arg_param = GET_NEXT_INT(ARGS);

    glMateriali(arg_face, arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_Materialiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_face = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glMaterialiv(arg_face, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_PolygonStipple)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_mask_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLubyte *arg_mask = new GLubyte[arg_mask_arr->size()];
    chgl->scheduleArrayForCleanup(arg_mask);
    copy_ckarray4_to_array(arg_mask, arg_mask_arr);

    glPolygonStipple(arg_mask);
}


CK_DLL_MFUN(Chuck_OpenGL_ShadeModel)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);

    glShadeModel(arg_mode);
}


CK_DLL_MFUN(Chuck_OpenGL_TexEnvf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_param = GET_NEXT_FLOAT(ARGS);

    glTexEnvf(arg_target, arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_TexEnvfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glTexEnvfv(arg_target, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_TexEnvi)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKINT arg_param = GET_NEXT_INT(ARGS);

    glTexEnvi(arg_target, arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_TexEnviv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glTexEnviv(arg_target, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_TexGend)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_coord = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_param = GET_NEXT_FLOAT(ARGS);

    glTexGend(arg_coord, arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_TexGendv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_coord = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_params = new GLdouble[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glTexGendv(arg_coord, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_TexGenf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_coord = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_param = GET_NEXT_FLOAT(ARGS);

    glTexGenf(arg_coord, arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_TexGenfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_coord = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glTexGenfv(arg_coord, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_TexGeni)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_coord = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKINT arg_param = GET_NEXT_INT(ARGS);

    glTexGeni(arg_coord, arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_TexGeniv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_coord = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glTexGeniv(arg_coord, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_FeedbackBuffer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_size = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_buffer_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_buffer = new GLfloat[arg_buffer_arr->size()];
    chgl->scheduleArrayForCleanup(arg_buffer);
    copy_ckarray8_to_array(arg_buffer, arg_buffer_arr);

    glFeedbackBuffer(arg_size, arg_type, arg_buffer);
}


CK_DLL_MFUN(Chuck_OpenGL_SelectBuffer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_size = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_buffer_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_buffer = new GLuint[arg_buffer_arr->size()];
    chgl->scheduleArrayForCleanup(arg_buffer);
    copy_ckarray4_to_array(arg_buffer, arg_buffer_arr);

    glSelectBuffer(arg_size, arg_buffer);
}


CK_DLL_MFUN(Chuck_OpenGL_RenderMode)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);

    RETURN->v_int = glRenderMode(arg_mode);
}


CK_DLL_MFUN(Chuck_OpenGL_InitNames)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    

    glInitNames();
}


CK_DLL_MFUN(Chuck_OpenGL_LoadName)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_name = GET_NEXT_INT(ARGS);

    glLoadName(arg_name);
}


CK_DLL_MFUN(Chuck_OpenGL_PassThrough)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_token = GET_NEXT_FLOAT(ARGS);

    glPassThrough(arg_token);
}


CK_DLL_MFUN(Chuck_OpenGL_PopName)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    

    glPopName();
}


CK_DLL_MFUN(Chuck_OpenGL_PushName)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_name = GET_NEXT_INT(ARGS);

    glPushName(arg_name);
}


CK_DLL_MFUN(Chuck_OpenGL_ClearAccum)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_red = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_green = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_blue = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_alpha = GET_NEXT_FLOAT(ARGS);

    glClearAccum(arg_red, arg_green, arg_blue, arg_alpha);
}


CK_DLL_MFUN(Chuck_OpenGL_ClearIndex)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_c = GET_NEXT_FLOAT(ARGS);

    glClearIndex(arg_c);
}


CK_DLL_MFUN(Chuck_OpenGL_IndexMask)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mask = GET_NEXT_INT(ARGS);

    glIndexMask(arg_mask);
}


CK_DLL_MFUN(Chuck_OpenGL_Accum)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_op = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_value = GET_NEXT_FLOAT(ARGS);

    glAccum(arg_op, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_PopAttrib)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    

    glPopAttrib();
}


CK_DLL_MFUN(Chuck_OpenGL_PushAttrib)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mask = GET_NEXT_INT(ARGS);

    glPushAttrib(arg_mask);
}


CK_DLL_MFUN(Chuck_OpenGL_Map1d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_u1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_u2 = GET_NEXT_FLOAT(ARGS);
    t_CKINT arg_stride = GET_NEXT_INT(ARGS);
    t_CKINT arg_order = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_points_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_points = new GLdouble[arg_points_arr->size()];
    chgl->scheduleArrayForCleanup(arg_points);
    copy_ckarray8_to_array(arg_points, arg_points_arr);

    glMap1d(arg_target, arg_u1, arg_u2, arg_stride, arg_order, arg_points);
}


CK_DLL_MFUN(Chuck_OpenGL_Map1f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_u1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_u2 = GET_NEXT_FLOAT(ARGS);
    t_CKINT arg_stride = GET_NEXT_INT(ARGS);
    t_CKINT arg_order = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_points_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_points = new GLfloat[arg_points_arr->size()];
    chgl->scheduleArrayForCleanup(arg_points);
    copy_ckarray8_to_array(arg_points, arg_points_arr);

    glMap1f(arg_target, arg_u1, arg_u2, arg_stride, arg_order, arg_points);
}


CK_DLL_MFUN(Chuck_OpenGL_Map2d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_u1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_u2 = GET_NEXT_FLOAT(ARGS);
    t_CKINT arg_ustride = GET_NEXT_INT(ARGS);
    t_CKINT arg_uorder = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_v1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v2 = GET_NEXT_FLOAT(ARGS);
    t_CKINT arg_vstride = GET_NEXT_INT(ARGS);
    t_CKINT arg_vorder = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_points_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_points = new GLdouble[arg_points_arr->size()];
    chgl->scheduleArrayForCleanup(arg_points);
    copy_ckarray8_to_array(arg_points, arg_points_arr);

    glMap2d(arg_target, arg_u1, arg_u2, arg_ustride, arg_uorder, arg_v1, arg_v2, arg_vstride, arg_vorder, arg_points);
}


CK_DLL_MFUN(Chuck_OpenGL_Map2f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_u1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_u2 = GET_NEXT_FLOAT(ARGS);
    t_CKINT arg_ustride = GET_NEXT_INT(ARGS);
    t_CKINT arg_uorder = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_v1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v2 = GET_NEXT_FLOAT(ARGS);
    t_CKINT arg_vstride = GET_NEXT_INT(ARGS);
    t_CKINT arg_vorder = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_points_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_points = new GLfloat[arg_points_arr->size()];
    chgl->scheduleArrayForCleanup(arg_points);
    copy_ckarray8_to_array(arg_points, arg_points_arr);

    glMap2f(arg_target, arg_u1, arg_u2, arg_ustride, arg_uorder, arg_v1, arg_v2, arg_vstride, arg_vorder, arg_points);
}


CK_DLL_MFUN(Chuck_OpenGL_MapGrid1d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_un = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_u1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_u2 = GET_NEXT_FLOAT(ARGS);

    glMapGrid1d(arg_un, arg_u1, arg_u2);
}


CK_DLL_MFUN(Chuck_OpenGL_MapGrid1f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_un = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_u1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_u2 = GET_NEXT_FLOAT(ARGS);

    glMapGrid1f(arg_un, arg_u1, arg_u2);
}


CK_DLL_MFUN(Chuck_OpenGL_MapGrid2d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_un = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_u1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_u2 = GET_NEXT_FLOAT(ARGS);
    t_CKINT arg_vn = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_v1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v2 = GET_NEXT_FLOAT(ARGS);

    glMapGrid2d(arg_un, arg_u1, arg_u2, arg_vn, arg_v1, arg_v2);
}


CK_DLL_MFUN(Chuck_OpenGL_MapGrid2f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_un = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_u1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_u2 = GET_NEXT_FLOAT(ARGS);
    t_CKINT arg_vn = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_v1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v2 = GET_NEXT_FLOAT(ARGS);

    glMapGrid2f(arg_un, arg_u1, arg_u2, arg_vn, arg_v1, arg_v2);
}


CK_DLL_MFUN(Chuck_OpenGL_EvalCoord1d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_u = GET_NEXT_FLOAT(ARGS);

    glEvalCoord1d(arg_u);
}


CK_DLL_MFUN(Chuck_OpenGL_EvalCoord1dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_u_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_u = new GLdouble[arg_u_arr->size()];
    chgl->scheduleArrayForCleanup(arg_u);
    copy_ckarray8_to_array(arg_u, arg_u_arr);

    glEvalCoord1dv(arg_u);
}


CK_DLL_MFUN(Chuck_OpenGL_EvalCoord1f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_u = GET_NEXT_FLOAT(ARGS);

    glEvalCoord1f(arg_u);
}


CK_DLL_MFUN(Chuck_OpenGL_EvalCoord1fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_u_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_u = new GLfloat[arg_u_arr->size()];
    chgl->scheduleArrayForCleanup(arg_u);
    copy_ckarray8_to_array(arg_u, arg_u_arr);

    glEvalCoord1fv(arg_u);
}


CK_DLL_MFUN(Chuck_OpenGL_EvalCoord2d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_u = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v = GET_NEXT_FLOAT(ARGS);

    glEvalCoord2d(arg_u, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_EvalCoord2dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_u_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_u = new GLdouble[arg_u_arr->size()];
    chgl->scheduleArrayForCleanup(arg_u);
    copy_ckarray8_to_array(arg_u, arg_u_arr);

    glEvalCoord2dv(arg_u);
}


CK_DLL_MFUN(Chuck_OpenGL_EvalCoord2f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_u = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v = GET_NEXT_FLOAT(ARGS);

    glEvalCoord2f(arg_u, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_EvalCoord2fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_u_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_u = new GLfloat[arg_u_arr->size()];
    chgl->scheduleArrayForCleanup(arg_u);
    copy_ckarray8_to_array(arg_u, arg_u_arr);

    glEvalCoord2fv(arg_u);
}


CK_DLL_MFUN(Chuck_OpenGL_EvalMesh1)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);
    t_CKINT arg_i1 = GET_NEXT_INT(ARGS);
    t_CKINT arg_i2 = GET_NEXT_INT(ARGS);

    glEvalMesh1(arg_mode, arg_i1, arg_i2);
}


CK_DLL_MFUN(Chuck_OpenGL_EvalPoint1)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_i = GET_NEXT_INT(ARGS);

    glEvalPoint1(arg_i);
}


CK_DLL_MFUN(Chuck_OpenGL_EvalMesh2)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);
    t_CKINT arg_i1 = GET_NEXT_INT(ARGS);
    t_CKINT arg_i2 = GET_NEXT_INT(ARGS);
    t_CKINT arg_j1 = GET_NEXT_INT(ARGS);
    t_CKINT arg_j2 = GET_NEXT_INT(ARGS);

    glEvalMesh2(arg_mode, arg_i1, arg_i2, arg_j1, arg_j2);
}


CK_DLL_MFUN(Chuck_OpenGL_EvalPoint2)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_i = GET_NEXT_INT(ARGS);
    t_CKINT arg_j = GET_NEXT_INT(ARGS);

    glEvalPoint2(arg_i, arg_j);
}


CK_DLL_MFUN(Chuck_OpenGL_AlphaFunc)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_func = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_ref = GET_NEXT_FLOAT(ARGS);

    glAlphaFunc(arg_func, arg_ref);
}


CK_DLL_MFUN(Chuck_OpenGL_PixelZoom)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_xfactor = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_yfactor = GET_NEXT_FLOAT(ARGS);

    glPixelZoom(arg_xfactor, arg_yfactor);
}


CK_DLL_MFUN(Chuck_OpenGL_PixelTransferf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_param = GET_NEXT_FLOAT(ARGS);

    glPixelTransferf(arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_PixelTransferi)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKINT arg_param = GET_NEXT_INT(ARGS);

    glPixelTransferi(arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_PixelMapfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_map = GET_NEXT_INT(ARGS);
    t_CKINT arg_mapsize = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_values_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_values = new GLfloat[arg_values_arr->size()];
    chgl->scheduleArrayForCleanup(arg_values);
    copy_ckarray8_to_array(arg_values, arg_values_arr);

    glPixelMapfv(arg_map, arg_mapsize, arg_values);
}


CK_DLL_MFUN(Chuck_OpenGL_PixelMapuiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_map = GET_NEXT_INT(ARGS);
    t_CKINT arg_mapsize = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_values_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_values = new GLuint[arg_values_arr->size()];
    chgl->scheduleArrayForCleanup(arg_values);
    copy_ckarray4_to_array(arg_values, arg_values_arr);

    glPixelMapuiv(arg_map, arg_mapsize, arg_values);
}


CK_DLL_MFUN(Chuck_OpenGL_PixelMapusv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_map = GET_NEXT_INT(ARGS);
    t_CKINT arg_mapsize = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_values_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLushort *arg_values = new GLushort[arg_values_arr->size()];
    chgl->scheduleArrayForCleanup(arg_values);
    copy_ckarray4_to_array(arg_values, arg_values_arr);

    glPixelMapusv(arg_map, arg_mapsize, arg_values);
}


CK_DLL_MFUN(Chuck_OpenGL_CopyPixels)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);

    glCopyPixels(arg_x, arg_y, arg_width, arg_height, arg_type);
}


CK_DLL_MFUN(Chuck_OpenGL_DrawPixels)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_format = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pixels_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pixels;
    if(_arg_pixels_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pixels_arr = (Chuck_Array4 *) _arg_pixels_arr;
        GLubyte *arg_pixels_v = new GLubyte[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray4_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }
    else if(_arg_pixels_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pixels_arr = (Chuck_Array8 *) _arg_pixels_arr;
        GLfloat *arg_pixels_v = new GLfloat[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray8_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }

    glDrawPixels(arg_width, arg_height, arg_format, arg_type, arg_pixels);
}


CK_DLL_MFUN(Chuck_OpenGL_GetClipPlane)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_plane = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_equation_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_equation = new GLdouble[arg_equation_arr->size()];
    chgl->scheduleArrayForCleanup(arg_equation);
    copy_ckarray8_to_array(arg_equation, arg_equation_arr);

    glGetClipPlane(arg_plane, arg_equation);
}


CK_DLL_MFUN(Chuck_OpenGL_GetLightfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_light = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glGetLightfv(arg_light, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetLightiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_light = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetLightiv(arg_light, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetMapdv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_query = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glGetMapdv(arg_target, arg_query, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_GetMapfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_query = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glGetMapfv(arg_target, arg_query, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_GetMapiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_query = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glGetMapiv(arg_target, arg_query, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_GetMaterialfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_face = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glGetMaterialfv(arg_face, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetMaterialiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_face = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetMaterialiv(arg_face, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetPixelMapfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_map = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_values_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_values = new GLfloat[arg_values_arr->size()];
    chgl->scheduleArrayForCleanup(arg_values);
    copy_ckarray8_to_array(arg_values, arg_values_arr);

    glGetPixelMapfv(arg_map, arg_values);
}


CK_DLL_MFUN(Chuck_OpenGL_GetPixelMapuiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_map = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_values_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_values = new GLuint[arg_values_arr->size()];
    chgl->scheduleArrayForCleanup(arg_values);
    copy_ckarray4_to_array(arg_values, arg_values_arr);

    glGetPixelMapuiv(arg_map, arg_values);
}


CK_DLL_MFUN(Chuck_OpenGL_GetPixelMapusv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_map = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_values_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLushort *arg_values = new GLushort[arg_values_arr->size()];
    chgl->scheduleArrayForCleanup(arg_values);
    copy_ckarray4_to_array(arg_values, arg_values_arr);

    glGetPixelMapusv(arg_map, arg_values);
}


CK_DLL_MFUN(Chuck_OpenGL_GetPolygonStipple)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_mask_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLubyte *arg_mask = new GLubyte[arg_mask_arr->size()];
    chgl->scheduleArrayForCleanup(arg_mask);
    copy_ckarray4_to_array(arg_mask, arg_mask_arr);

    glGetPolygonStipple(arg_mask);
}


CK_DLL_MFUN(Chuck_OpenGL_GetTexEnvfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glGetTexEnvfv(arg_target, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetTexEnviv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetTexEnviv(arg_target, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetTexGendv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_coord = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_params = new GLdouble[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glGetTexGendv(arg_coord, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetTexGenfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_coord = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glGetTexGenfv(arg_coord, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetTexGeniv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_coord = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetTexGeniv(arg_coord, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_IsList)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_list = GET_NEXT_INT(ARGS);

    RETURN->v_int = glIsList(arg_list);
}


CK_DLL_MFUN(Chuck_OpenGL_Frustum)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_left = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_right = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_bottom = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_top = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_zNear = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_zFar = GET_NEXT_FLOAT(ARGS);

    glFrustum(arg_left, arg_right, arg_bottom, arg_top, arg_zNear, arg_zFar);
}


CK_DLL_MFUN(Chuck_OpenGL_LoadIdentity)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    

    glLoadIdentity();
}


CK_DLL_MFUN(Chuck_OpenGL_LoadMatrixf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_m_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_m = new GLfloat[arg_m_arr->size()];
    chgl->scheduleArrayForCleanup(arg_m);
    copy_ckarray8_to_array(arg_m, arg_m_arr);

    glLoadMatrixf(arg_m);
}


CK_DLL_MFUN(Chuck_OpenGL_LoadMatrixd)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_m_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_m = new GLdouble[arg_m_arr->size()];
    chgl->scheduleArrayForCleanup(arg_m);
    copy_ckarray8_to_array(arg_m, arg_m_arr);

    glLoadMatrixd(arg_m);
}


CK_DLL_MFUN(Chuck_OpenGL_MatrixMode)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);

    glMatrixMode(arg_mode);
}


CK_DLL_MFUN(Chuck_OpenGL_MultMatrixf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_m_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_m = new GLfloat[arg_m_arr->size()];
    chgl->scheduleArrayForCleanup(arg_m);
    copy_ckarray8_to_array(arg_m, arg_m_arr);

    glMultMatrixf(arg_m);
}


CK_DLL_MFUN(Chuck_OpenGL_MultMatrixd)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_m_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_m = new GLdouble[arg_m_arr->size()];
    chgl->scheduleArrayForCleanup(arg_m);
    copy_ckarray8_to_array(arg_m, arg_m_arr);

    glMultMatrixd(arg_m);
}


CK_DLL_MFUN(Chuck_OpenGL_Ortho)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_left = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_right = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_bottom = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_top = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_zNear = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_zFar = GET_NEXT_FLOAT(ARGS);

    glOrtho(arg_left, arg_right, arg_bottom, arg_top, arg_zNear, arg_zFar);
}


CK_DLL_MFUN(Chuck_OpenGL_PopMatrix)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    

    glPopMatrix();
}


CK_DLL_MFUN(Chuck_OpenGL_PushMatrix)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    

    glPushMatrix();
}


CK_DLL_MFUN(Chuck_OpenGL_Rotated)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_angle = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);

    glRotated(arg_angle, arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_Rotatef)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_angle = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);

    glRotatef(arg_angle, arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_Scaled)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);

    glScaled(arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_Scalef)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);

    glScalef(arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_Translated)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);

    glTranslated(arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_Translatef)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);

    glTranslatef(arg_x, arg_y, arg_z);
}

static const t_CKINT Chuck_OpenGL_DEPTH_BUFFER_BIT = GL_DEPTH_BUFFER_BIT;
static const t_CKINT Chuck_OpenGL_STENCIL_BUFFER_BIT = GL_STENCIL_BUFFER_BIT;
static const t_CKINT Chuck_OpenGL_COLOR_BUFFER_BIT = GL_COLOR_BUFFER_BIT;
static const t_CKINT Chuck_OpenGL_FALSE = GL_FALSE;
static const t_CKINT Chuck_OpenGL_TRUE = GL_TRUE;
static const t_CKINT Chuck_OpenGL_POINTS = GL_POINTS;
static const t_CKINT Chuck_OpenGL_LINES = GL_LINES;
static const t_CKINT Chuck_OpenGL_LINE_LOOP = GL_LINE_LOOP;
static const t_CKINT Chuck_OpenGL_LINE_STRIP = GL_LINE_STRIP;
static const t_CKINT Chuck_OpenGL_TRIANGLES = GL_TRIANGLES;
static const t_CKINT Chuck_OpenGL_TRIANGLE_STRIP = GL_TRIANGLE_STRIP;
static const t_CKINT Chuck_OpenGL_TRIANGLE_FAN = GL_TRIANGLE_FAN;
static const t_CKINT Chuck_OpenGL_QUADS = GL_QUADS;
static const t_CKINT Chuck_OpenGL_NEVER = GL_NEVER;
static const t_CKINT Chuck_OpenGL_LESS = GL_LESS;
static const t_CKINT Chuck_OpenGL_EQUAL = GL_EQUAL;
static const t_CKINT Chuck_OpenGL_LEQUAL = GL_LEQUAL;
static const t_CKINT Chuck_OpenGL_GREATER = GL_GREATER;
static const t_CKINT Chuck_OpenGL_NOTEQUAL = GL_NOTEQUAL;
static const t_CKINT Chuck_OpenGL_GEQUAL = GL_GEQUAL;
static const t_CKINT Chuck_OpenGL_ALWAYS = GL_ALWAYS;
static const t_CKINT Chuck_OpenGL_ZERO = GL_ZERO;
static const t_CKINT Chuck_OpenGL_ONE = GL_ONE;
static const t_CKINT Chuck_OpenGL_SRC_COLOR = GL_SRC_COLOR;
static const t_CKINT Chuck_OpenGL_ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR;
static const t_CKINT Chuck_OpenGL_SRC_ALPHA = GL_SRC_ALPHA;
static const t_CKINT Chuck_OpenGL_ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA;
static const t_CKINT Chuck_OpenGL_DST_ALPHA = GL_DST_ALPHA;
static const t_CKINT Chuck_OpenGL_ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA;
static const t_CKINT Chuck_OpenGL_DST_COLOR = GL_DST_COLOR;
static const t_CKINT Chuck_OpenGL_ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR;
static const t_CKINT Chuck_OpenGL_SRC_ALPHA_SATURATE = GL_SRC_ALPHA_SATURATE;
static const t_CKINT Chuck_OpenGL_NONE = GL_NONE;
static const t_CKINT Chuck_OpenGL_FRONT_LEFT = GL_FRONT_LEFT;
static const t_CKINT Chuck_OpenGL_FRONT_RIGHT = GL_FRONT_RIGHT;
static const t_CKINT Chuck_OpenGL_BACK_LEFT = GL_BACK_LEFT;
static const t_CKINT Chuck_OpenGL_BACK_RIGHT = GL_BACK_RIGHT;
static const t_CKINT Chuck_OpenGL_FRONT = GL_FRONT;
static const t_CKINT Chuck_OpenGL_BACK = GL_BACK;
static const t_CKINT Chuck_OpenGL_LEFT = GL_LEFT;
static const t_CKINT Chuck_OpenGL_RIGHT = GL_RIGHT;
static const t_CKINT Chuck_OpenGL_FRONT_AND_BACK = GL_FRONT_AND_BACK;
static const t_CKINT Chuck_OpenGL_NO_ERROR = GL_NO_ERROR;
static const t_CKINT Chuck_OpenGL_INVALID_ENUM = GL_INVALID_ENUM;
static const t_CKINT Chuck_OpenGL_INVALID_VALUE = GL_INVALID_VALUE;
static const t_CKINT Chuck_OpenGL_INVALID_OPERATION = GL_INVALID_OPERATION;
static const t_CKINT Chuck_OpenGL_OUT_OF_MEMORY = GL_OUT_OF_MEMORY;
static const t_CKINT Chuck_OpenGL_CW = GL_CW;
static const t_CKINT Chuck_OpenGL_CCW = GL_CCW;
static const t_CKINT Chuck_OpenGL_POINT_SIZE = GL_POINT_SIZE;
static const t_CKINT Chuck_OpenGL_POINT_SIZE_RANGE = GL_POINT_SIZE_RANGE;
static const t_CKINT Chuck_OpenGL_POINT_SIZE_GRANULARITY = GL_POINT_SIZE_GRANULARITY;
static const t_CKINT Chuck_OpenGL_LINE_SMOOTH = GL_LINE_SMOOTH;
static const t_CKINT Chuck_OpenGL_LINE_WIDTH = GL_LINE_WIDTH;
static const t_CKINT Chuck_OpenGL_LINE_WIDTH_RANGE = GL_LINE_WIDTH_RANGE;
static const t_CKINT Chuck_OpenGL_LINE_WIDTH_GRANULARITY = GL_LINE_WIDTH_GRANULARITY;
static const t_CKINT Chuck_OpenGL_POLYGON_MODE = GL_POLYGON_MODE;
static const t_CKINT Chuck_OpenGL_POLYGON_SMOOTH = GL_POLYGON_SMOOTH;
static const t_CKINT Chuck_OpenGL_CULL_FACE = GL_CULL_FACE;
static const t_CKINT Chuck_OpenGL_CULL_FACE_MODE = GL_CULL_FACE_MODE;
static const t_CKINT Chuck_OpenGL_FRONT_FACE = GL_FRONT_FACE;
static const t_CKINT Chuck_OpenGL_DEPTH_RANGE = GL_DEPTH_RANGE;
static const t_CKINT Chuck_OpenGL_DEPTH_TEST = GL_DEPTH_TEST;
static const t_CKINT Chuck_OpenGL_DEPTH_WRITEMASK = GL_DEPTH_WRITEMASK;
static const t_CKINT Chuck_OpenGL_DEPTH_CLEAR_VALUE = GL_DEPTH_CLEAR_VALUE;
static const t_CKINT Chuck_OpenGL_DEPTH_FUNC = GL_DEPTH_FUNC;
static const t_CKINT Chuck_OpenGL_STENCIL_TEST = GL_STENCIL_TEST;
static const t_CKINT Chuck_OpenGL_STENCIL_CLEAR_VALUE = GL_STENCIL_CLEAR_VALUE;
static const t_CKINT Chuck_OpenGL_STENCIL_FUNC = GL_STENCIL_FUNC;
static const t_CKINT Chuck_OpenGL_STENCIL_VALUE_MASK = GL_STENCIL_VALUE_MASK;
static const t_CKINT Chuck_OpenGL_STENCIL_FAIL = GL_STENCIL_FAIL;
static const t_CKINT Chuck_OpenGL_STENCIL_PASS_DEPTH_FAIL = GL_STENCIL_PASS_DEPTH_FAIL;
static const t_CKINT Chuck_OpenGL_STENCIL_PASS_DEPTH_PASS = GL_STENCIL_PASS_DEPTH_PASS;
static const t_CKINT Chuck_OpenGL_STENCIL_REF = GL_STENCIL_REF;
static const t_CKINT Chuck_OpenGL_STENCIL_WRITEMASK = GL_STENCIL_WRITEMASK;
static const t_CKINT Chuck_OpenGL_VIEWPORT = GL_VIEWPORT;
static const t_CKINT Chuck_OpenGL_DITHER = GL_DITHER;
static const t_CKINT Chuck_OpenGL_BLEND_DST = GL_BLEND_DST;
static const t_CKINT Chuck_OpenGL_BLEND_SRC = GL_BLEND_SRC;
static const t_CKINT Chuck_OpenGL_BLEND = GL_BLEND;
static const t_CKINT Chuck_OpenGL_LOGIC_OP_MODE = GL_LOGIC_OP_MODE;
static const t_CKINT Chuck_OpenGL_COLOR_LOGIC_OP = GL_COLOR_LOGIC_OP;
static const t_CKINT Chuck_OpenGL_DRAW_BUFFER = GL_DRAW_BUFFER;
static const t_CKINT Chuck_OpenGL_READ_BUFFER = GL_READ_BUFFER;
static const t_CKINT Chuck_OpenGL_SCISSOR_BOX = GL_SCISSOR_BOX;
static const t_CKINT Chuck_OpenGL_SCISSOR_TEST = GL_SCISSOR_TEST;
static const t_CKINT Chuck_OpenGL_COLOR_CLEAR_VALUE = GL_COLOR_CLEAR_VALUE;
static const t_CKINT Chuck_OpenGL_COLOR_WRITEMASK = GL_COLOR_WRITEMASK;
static const t_CKINT Chuck_OpenGL_DOUBLEBUFFER = GL_DOUBLEBUFFER;
static const t_CKINT Chuck_OpenGL_STEREO = GL_STEREO;
static const t_CKINT Chuck_OpenGL_LINE_SMOOTH_HINT = GL_LINE_SMOOTH_HINT;
static const t_CKINT Chuck_OpenGL_POLYGON_SMOOTH_HINT = GL_POLYGON_SMOOTH_HINT;
static const t_CKINT Chuck_OpenGL_UNPACK_SWAP_BYTES = GL_UNPACK_SWAP_BYTES;
static const t_CKINT Chuck_OpenGL_UNPACK_LSB_FIRST = GL_UNPACK_LSB_FIRST;
static const t_CKINT Chuck_OpenGL_UNPACK_ROW_LENGTH = GL_UNPACK_ROW_LENGTH;
static const t_CKINT Chuck_OpenGL_UNPACK_SKIP_ROWS = GL_UNPACK_SKIP_ROWS;
static const t_CKINT Chuck_OpenGL_UNPACK_SKIP_PIXELS = GL_UNPACK_SKIP_PIXELS;
static const t_CKINT Chuck_OpenGL_UNPACK_ALIGNMENT = GL_UNPACK_ALIGNMENT;
static const t_CKINT Chuck_OpenGL_PACK_SWAP_BYTES = GL_PACK_SWAP_BYTES;
static const t_CKINT Chuck_OpenGL_PACK_LSB_FIRST = GL_PACK_LSB_FIRST;
static const t_CKINT Chuck_OpenGL_PACK_ROW_LENGTH = GL_PACK_ROW_LENGTH;
static const t_CKINT Chuck_OpenGL_PACK_SKIP_ROWS = GL_PACK_SKIP_ROWS;
static const t_CKINT Chuck_OpenGL_PACK_SKIP_PIXELS = GL_PACK_SKIP_PIXELS;
static const t_CKINT Chuck_OpenGL_PACK_ALIGNMENT = GL_PACK_ALIGNMENT;
static const t_CKINT Chuck_OpenGL_MAX_TEXTURE_SIZE = GL_MAX_TEXTURE_SIZE;
static const t_CKINT Chuck_OpenGL_MAX_VIEWPORT_DIMS = GL_MAX_VIEWPORT_DIMS;
static const t_CKINT Chuck_OpenGL_SUBPIXEL_BITS = GL_SUBPIXEL_BITS;
static const t_CKINT Chuck_OpenGL_TEXTURE_1D = GL_TEXTURE_1D;
static const t_CKINT Chuck_OpenGL_TEXTURE_2D = GL_TEXTURE_2D;
static const t_CKINT Chuck_OpenGL_POLYGON_OFFSET_UNITS = GL_POLYGON_OFFSET_UNITS;
static const t_CKINT Chuck_OpenGL_POLYGON_OFFSET_POINT = GL_POLYGON_OFFSET_POINT;
static const t_CKINT Chuck_OpenGL_POLYGON_OFFSET_LINE = GL_POLYGON_OFFSET_LINE;
static const t_CKINT Chuck_OpenGL_POLYGON_OFFSET_FILL = GL_POLYGON_OFFSET_FILL;
static const t_CKINT Chuck_OpenGL_POLYGON_OFFSET_FACTOR = GL_POLYGON_OFFSET_FACTOR;
static const t_CKINT Chuck_OpenGL_TEXTURE_BINDING_1D = GL_TEXTURE_BINDING_1D;
static const t_CKINT Chuck_OpenGL_TEXTURE_BINDING_2D = GL_TEXTURE_BINDING_2D;
static const t_CKINT Chuck_OpenGL_TEXTURE_WIDTH = GL_TEXTURE_WIDTH;
static const t_CKINT Chuck_OpenGL_TEXTURE_HEIGHT = GL_TEXTURE_HEIGHT;
static const t_CKINT Chuck_OpenGL_TEXTURE_INTERNAL_FORMAT = GL_TEXTURE_INTERNAL_FORMAT;
static const t_CKINT Chuck_OpenGL_TEXTURE_BORDER_COLOR = GL_TEXTURE_BORDER_COLOR;
static const t_CKINT Chuck_OpenGL_TEXTURE_RED_SIZE = GL_TEXTURE_RED_SIZE;
static const t_CKINT Chuck_OpenGL_TEXTURE_GREEN_SIZE = GL_TEXTURE_GREEN_SIZE;
static const t_CKINT Chuck_OpenGL_TEXTURE_BLUE_SIZE = GL_TEXTURE_BLUE_SIZE;
static const t_CKINT Chuck_OpenGL_TEXTURE_ALPHA_SIZE = GL_TEXTURE_ALPHA_SIZE;
static const t_CKINT Chuck_OpenGL_DONT_CARE = GL_DONT_CARE;
static const t_CKINT Chuck_OpenGL_FASTEST = GL_FASTEST;
static const t_CKINT Chuck_OpenGL_NICEST = GL_NICEST;
static const t_CKINT Chuck_OpenGL_BYTE = GL_BYTE;
static const t_CKINT Chuck_OpenGL_UNSIGNED_BYTE = GL_UNSIGNED_BYTE;
static const t_CKINT Chuck_OpenGL_SHORT = GL_SHORT;
static const t_CKINT Chuck_OpenGL_UNSIGNED_SHORT = GL_UNSIGNED_SHORT;
static const t_CKINT Chuck_OpenGL_INT = GL_INT;
static const t_CKINT Chuck_OpenGL_UNSIGNED_INT = GL_UNSIGNED_INT;
static const t_CKINT Chuck_OpenGL_FLOAT = GL_FLOAT;
static const t_CKINT Chuck_OpenGL_DOUBLE = GL_DOUBLE;
static const t_CKINT Chuck_OpenGL_STACK_OVERFLOW = GL_STACK_OVERFLOW;
static const t_CKINT Chuck_OpenGL_STACK_UNDERFLOW = GL_STACK_UNDERFLOW;
static const t_CKINT Chuck_OpenGL_CLEAR = GL_CLEAR;
static const t_CKINT Chuck_OpenGL_AND = GL_AND;
static const t_CKINT Chuck_OpenGL_AND_REVERSE = GL_AND_REVERSE;
static const t_CKINT Chuck_OpenGL_COPY = GL_COPY;
static const t_CKINT Chuck_OpenGL_AND_INVERTED = GL_AND_INVERTED;
static const t_CKINT Chuck_OpenGL_NOOP = GL_NOOP;
static const t_CKINT Chuck_OpenGL_XOR = GL_XOR;
static const t_CKINT Chuck_OpenGL_OR = GL_OR;
static const t_CKINT Chuck_OpenGL_NOR = GL_NOR;
static const t_CKINT Chuck_OpenGL_EQUIV = GL_EQUIV;
static const t_CKINT Chuck_OpenGL_INVERT = GL_INVERT;
static const t_CKINT Chuck_OpenGL_OR_REVERSE = GL_OR_REVERSE;
static const t_CKINT Chuck_OpenGL_COPY_INVERTED = GL_COPY_INVERTED;
static const t_CKINT Chuck_OpenGL_OR_INVERTED = GL_OR_INVERTED;
static const t_CKINT Chuck_OpenGL_NAND = GL_NAND;
static const t_CKINT Chuck_OpenGL_SET = GL_SET;
static const t_CKINT Chuck_OpenGL_TEXTURE = GL_TEXTURE;
static const t_CKINT Chuck_OpenGL_COLOR = GL_COLOR;
static const t_CKINT Chuck_OpenGL_DEPTH = GL_DEPTH;
static const t_CKINT Chuck_OpenGL_STENCIL = GL_STENCIL;
static const t_CKINT Chuck_OpenGL_STENCIL_INDEX = GL_STENCIL_INDEX;
static const t_CKINT Chuck_OpenGL_DEPTH_COMPONENT = GL_DEPTH_COMPONENT;
static const t_CKINT Chuck_OpenGL_RED = GL_RED;
static const t_CKINT Chuck_OpenGL_GREEN = GL_GREEN;
static const t_CKINT Chuck_OpenGL_BLUE = GL_BLUE;
static const t_CKINT Chuck_OpenGL_ALPHA = GL_ALPHA;
static const t_CKINT Chuck_OpenGL_RGB = GL_RGB;
static const t_CKINT Chuck_OpenGL_RGBA = GL_RGBA;
static const t_CKINT Chuck_OpenGL_POINT = GL_POINT;
static const t_CKINT Chuck_OpenGL_LINE = GL_LINE;
static const t_CKINT Chuck_OpenGL_FILL = GL_FILL;
static const t_CKINT Chuck_OpenGL_KEEP = GL_KEEP;
static const t_CKINT Chuck_OpenGL_REPLACE = GL_REPLACE;
static const t_CKINT Chuck_OpenGL_INCR = GL_INCR;
static const t_CKINT Chuck_OpenGL_DECR = GL_DECR;
static const t_CKINT Chuck_OpenGL_VENDOR = GL_VENDOR;
static const t_CKINT Chuck_OpenGL_RENDERER = GL_RENDERER;
static const t_CKINT Chuck_OpenGL_VERSION = GL_VERSION;
static const t_CKINT Chuck_OpenGL_EXTENSIONS = GL_EXTENSIONS;
static const t_CKINT Chuck_OpenGL_NEAREST = GL_NEAREST;
static const t_CKINT Chuck_OpenGL_LINEAR = GL_LINEAR;
static const t_CKINT Chuck_OpenGL_NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST;
static const t_CKINT Chuck_OpenGL_LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST;
static const t_CKINT Chuck_OpenGL_NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR;
static const t_CKINT Chuck_OpenGL_LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR;
static const t_CKINT Chuck_OpenGL_TEXTURE_MAG_FILTER = GL_TEXTURE_MAG_FILTER;
static const t_CKINT Chuck_OpenGL_TEXTURE_MIN_FILTER = GL_TEXTURE_MIN_FILTER;
static const t_CKINT Chuck_OpenGL_TEXTURE_WRAP_S = GL_TEXTURE_WRAP_S;
static const t_CKINT Chuck_OpenGL_TEXTURE_WRAP_T = GL_TEXTURE_WRAP_T;
static const t_CKINT Chuck_OpenGL_PROXY_TEXTURE_1D = GL_PROXY_TEXTURE_1D;
static const t_CKINT Chuck_OpenGL_PROXY_TEXTURE_2D = GL_PROXY_TEXTURE_2D;
static const t_CKINT Chuck_OpenGL_REPEAT = GL_REPEAT;
static const t_CKINT Chuck_OpenGL_R3_G3_B2 = GL_R3_G3_B2;
static const t_CKINT Chuck_OpenGL_RGB4 = GL_RGB4;
static const t_CKINT Chuck_OpenGL_RGB5 = GL_RGB5;
static const t_CKINT Chuck_OpenGL_RGB8 = GL_RGB8;
static const t_CKINT Chuck_OpenGL_RGB10 = GL_RGB10;
static const t_CKINT Chuck_OpenGL_RGB12 = GL_RGB12;
static const t_CKINT Chuck_OpenGL_RGB16 = GL_RGB16;
static const t_CKINT Chuck_OpenGL_RGBA2 = GL_RGBA2;
static const t_CKINT Chuck_OpenGL_RGBA4 = GL_RGBA4;
static const t_CKINT Chuck_OpenGL_RGB5_A1 = GL_RGB5_A1;
static const t_CKINT Chuck_OpenGL_RGBA8 = GL_RGBA8;
static const t_CKINT Chuck_OpenGL_RGB10_A2 = GL_RGB10_A2;
static const t_CKINT Chuck_OpenGL_RGBA12 = GL_RGBA12;
static const t_CKINT Chuck_OpenGL_RGBA16 = GL_RGBA16;
static const t_CKINT Chuck_OpenGL_CURRENT_BIT = GL_CURRENT_BIT;
static const t_CKINT Chuck_OpenGL_POINT_BIT = GL_POINT_BIT;
static const t_CKINT Chuck_OpenGL_LINE_BIT = GL_LINE_BIT;
static const t_CKINT Chuck_OpenGL_POLYGON_BIT = GL_POLYGON_BIT;
static const t_CKINT Chuck_OpenGL_POLYGON_STIPPLE_BIT = GL_POLYGON_STIPPLE_BIT;
static const t_CKINT Chuck_OpenGL_PIXEL_MODE_BIT = GL_PIXEL_MODE_BIT;
static const t_CKINT Chuck_OpenGL_LIGHTING_BIT = GL_LIGHTING_BIT;
static const t_CKINT Chuck_OpenGL_FOG_BIT = GL_FOG_BIT;
static const t_CKINT Chuck_OpenGL_ACCUM_BUFFER_BIT = GL_ACCUM_BUFFER_BIT;
static const t_CKINT Chuck_OpenGL_VIEWPORT_BIT = GL_VIEWPORT_BIT;
static const t_CKINT Chuck_OpenGL_TRANSFORM_BIT = GL_TRANSFORM_BIT;
static const t_CKINT Chuck_OpenGL_ENABLE_BIT = GL_ENABLE_BIT;
static const t_CKINT Chuck_OpenGL_HINT_BIT = GL_HINT_BIT;
static const t_CKINT Chuck_OpenGL_EVAL_BIT = GL_EVAL_BIT;
static const t_CKINT Chuck_OpenGL_LIST_BIT = GL_LIST_BIT;
static const t_CKINT Chuck_OpenGL_TEXTURE_BIT = GL_TEXTURE_BIT;
static const t_CKINT Chuck_OpenGL_SCISSOR_BIT = GL_SCISSOR_BIT;
static const t_CKINT Chuck_OpenGL_ALL_ATTRIB_BITS = GL_ALL_ATTRIB_BITS;
static const t_CKINT Chuck_OpenGL_CLIENT_PIXEL_STORE_BIT = GL_CLIENT_PIXEL_STORE_BIT;
static const t_CKINT Chuck_OpenGL_CLIENT_VERTEX_ARRAY_BIT = GL_CLIENT_VERTEX_ARRAY_BIT;
static const t_CKINT Chuck_OpenGL_CLIENT_ALL_ATTRIB_BITS = GL_CLIENT_ALL_ATTRIB_BITS;
static const t_CKINT Chuck_OpenGL_QUAD_STRIP = GL_QUAD_STRIP;
static const t_CKINT Chuck_OpenGL_POLYGON = GL_POLYGON;
static const t_CKINT Chuck_OpenGL_ACCUM = GL_ACCUM;
static const t_CKINT Chuck_OpenGL_LOAD = GL_LOAD;
static const t_CKINT Chuck_OpenGL_RETURN = GL_RETURN;
static const t_CKINT Chuck_OpenGL_MULT = GL_MULT;
static const t_CKINT Chuck_OpenGL_ADD = GL_ADD;
static const t_CKINT Chuck_OpenGL_AUX0 = GL_AUX0;
static const t_CKINT Chuck_OpenGL_AUX1 = GL_AUX1;
static const t_CKINT Chuck_OpenGL_AUX2 = GL_AUX2;
static const t_CKINT Chuck_OpenGL_AUX3 = GL_AUX3;
static const t_CKINT Chuck_OpenGL_2D = GL_2D;
static const t_CKINT Chuck_OpenGL_3D = GL_3D;
static const t_CKINT Chuck_OpenGL_3D_COLOR = GL_3D_COLOR;
static const t_CKINT Chuck_OpenGL_3D_COLOR_TEXTURE = GL_3D_COLOR_TEXTURE;
static const t_CKINT Chuck_OpenGL_4D_COLOR_TEXTURE = GL_4D_COLOR_TEXTURE;
static const t_CKINT Chuck_OpenGL_PASS_THROUGH_TOKEN = GL_PASS_THROUGH_TOKEN;
static const t_CKINT Chuck_OpenGL_POINT_TOKEN = GL_POINT_TOKEN;
static const t_CKINT Chuck_OpenGL_LINE_TOKEN = GL_LINE_TOKEN;
static const t_CKINT Chuck_OpenGL_POLYGON_TOKEN = GL_POLYGON_TOKEN;
static const t_CKINT Chuck_OpenGL_BITMAP_TOKEN = GL_BITMAP_TOKEN;
static const t_CKINT Chuck_OpenGL_DRAW_PIXEL_TOKEN = GL_DRAW_PIXEL_TOKEN;
static const t_CKINT Chuck_OpenGL_COPY_PIXEL_TOKEN = GL_COPY_PIXEL_TOKEN;
static const t_CKINT Chuck_OpenGL_LINE_RESET_TOKEN = GL_LINE_RESET_TOKEN;
static const t_CKINT Chuck_OpenGL_EXP = GL_EXP;
static const t_CKINT Chuck_OpenGL_EXP2 = GL_EXP2;
static const t_CKINT Chuck_OpenGL_COEFF = GL_COEFF;
static const t_CKINT Chuck_OpenGL_ORDER = GL_ORDER;
static const t_CKINT Chuck_OpenGL_DOMAIN = GL_DOMAIN;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_I_TO_I = GL_PIXEL_MAP_I_TO_I;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_S_TO_S = GL_PIXEL_MAP_S_TO_S;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_I_TO_R = GL_PIXEL_MAP_I_TO_R;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_I_TO_G = GL_PIXEL_MAP_I_TO_G;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_I_TO_B = GL_PIXEL_MAP_I_TO_B;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_I_TO_A = GL_PIXEL_MAP_I_TO_A;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_R_TO_R = GL_PIXEL_MAP_R_TO_R;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_G_TO_G = GL_PIXEL_MAP_G_TO_G;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_B_TO_B = GL_PIXEL_MAP_B_TO_B;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_A_TO_A = GL_PIXEL_MAP_A_TO_A;
static const t_CKINT Chuck_OpenGL_VERTEX_ARRAY_POINTER = GL_VERTEX_ARRAY_POINTER;
static const t_CKINT Chuck_OpenGL_NORMAL_ARRAY_POINTER = GL_NORMAL_ARRAY_POINTER;
static const t_CKINT Chuck_OpenGL_COLOR_ARRAY_POINTER = GL_COLOR_ARRAY_POINTER;
static const t_CKINT Chuck_OpenGL_INDEX_ARRAY_POINTER = GL_INDEX_ARRAY_POINTER;
static const t_CKINT Chuck_OpenGL_TEXTURE_COORD_ARRAY_POINTER = GL_TEXTURE_COORD_ARRAY_POINTER;
static const t_CKINT Chuck_OpenGL_EDGE_FLAG_ARRAY_POINTER = GL_EDGE_FLAG_ARRAY_POINTER;
static const t_CKINT Chuck_OpenGL_FEEDBACK_BUFFER_POINTER = GL_FEEDBACK_BUFFER_POINTER;
static const t_CKINT Chuck_OpenGL_SELECTION_BUFFER_POINTER = GL_SELECTION_BUFFER_POINTER;
static const t_CKINT Chuck_OpenGL_CURRENT_COLOR = GL_CURRENT_COLOR;
static const t_CKINT Chuck_OpenGL_CURRENT_INDEX = GL_CURRENT_INDEX;
static const t_CKINT Chuck_OpenGL_CURRENT_NORMAL = GL_CURRENT_NORMAL;
static const t_CKINT Chuck_OpenGL_CURRENT_TEXTURE_COORDS = GL_CURRENT_TEXTURE_COORDS;
static const t_CKINT Chuck_OpenGL_CURRENT_RASTER_COLOR = GL_CURRENT_RASTER_COLOR;
static const t_CKINT Chuck_OpenGL_CURRENT_RASTER_INDEX = GL_CURRENT_RASTER_INDEX;
static const t_CKINT Chuck_OpenGL_CURRENT_RASTER_TEXTURE_COORDS = GL_CURRENT_RASTER_TEXTURE_COORDS;
static const t_CKINT Chuck_OpenGL_CURRENT_RASTER_POSITION = GL_CURRENT_RASTER_POSITION;
static const t_CKINT Chuck_OpenGL_CURRENT_RASTER_POSITION_VALID = GL_CURRENT_RASTER_POSITION_VALID;
static const t_CKINT Chuck_OpenGL_CURRENT_RASTER_DISTANCE = GL_CURRENT_RASTER_DISTANCE;
static const t_CKINT Chuck_OpenGL_POINT_SMOOTH = GL_POINT_SMOOTH;
static const t_CKINT Chuck_OpenGL_LINE_STIPPLE = GL_LINE_STIPPLE;
static const t_CKINT Chuck_OpenGL_LINE_STIPPLE_PATTERN = GL_LINE_STIPPLE_PATTERN;
static const t_CKINT Chuck_OpenGL_LINE_STIPPLE_REPEAT = GL_LINE_STIPPLE_REPEAT;
static const t_CKINT Chuck_OpenGL_LIST_MODE = GL_LIST_MODE;
static const t_CKINT Chuck_OpenGL_MAX_LIST_NESTING = GL_MAX_LIST_NESTING;
static const t_CKINT Chuck_OpenGL_LIST_BASE = GL_LIST_BASE;
static const t_CKINT Chuck_OpenGL_LIST_INDEX = GL_LIST_INDEX;
static const t_CKINT Chuck_OpenGL_POLYGON_STIPPLE = GL_POLYGON_STIPPLE;
static const t_CKINT Chuck_OpenGL_EDGE_FLAG = GL_EDGE_FLAG;
static const t_CKINT Chuck_OpenGL_LIGHTING = GL_LIGHTING;
static const t_CKINT Chuck_OpenGL_LIGHT_MODEL_LOCAL_VIEWER = GL_LIGHT_MODEL_LOCAL_VIEWER;
static const t_CKINT Chuck_OpenGL_LIGHT_MODEL_TWO_SIDE = GL_LIGHT_MODEL_TWO_SIDE;
static const t_CKINT Chuck_OpenGL_LIGHT_MODEL_AMBIENT = GL_LIGHT_MODEL_AMBIENT;
static const t_CKINT Chuck_OpenGL_SHADE_MODEL = GL_SHADE_MODEL;
static const t_CKINT Chuck_OpenGL_COLOR_MATERIAL_FACE = GL_COLOR_MATERIAL_FACE;
static const t_CKINT Chuck_OpenGL_COLOR_MATERIAL_PARAMETER = GL_COLOR_MATERIAL_PARAMETER;
static const t_CKINT Chuck_OpenGL_COLOR_MATERIAL = GL_COLOR_MATERIAL;
static const t_CKINT Chuck_OpenGL_FOG = GL_FOG;
static const t_CKINT Chuck_OpenGL_FOG_INDEX = GL_FOG_INDEX;
static const t_CKINT Chuck_OpenGL_FOG_DENSITY = GL_FOG_DENSITY;
static const t_CKINT Chuck_OpenGL_FOG_START = GL_FOG_START;
static const t_CKINT Chuck_OpenGL_FOG_END = GL_FOG_END;
static const t_CKINT Chuck_OpenGL_FOG_MODE = GL_FOG_MODE;
static const t_CKINT Chuck_OpenGL_FOG_COLOR = GL_FOG_COLOR;
static const t_CKINT Chuck_OpenGL_ACCUM_CLEAR_VALUE = GL_ACCUM_CLEAR_VALUE;
static const t_CKINT Chuck_OpenGL_MATRIX_MODE = GL_MATRIX_MODE;
static const t_CKINT Chuck_OpenGL_NORMALIZE = GL_NORMALIZE;
static const t_CKINT Chuck_OpenGL_MODELVIEW_STACK_DEPTH = GL_MODELVIEW_STACK_DEPTH;
static const t_CKINT Chuck_OpenGL_PROJECTION_STACK_DEPTH = GL_PROJECTION_STACK_DEPTH;
static const t_CKINT Chuck_OpenGL_TEXTURE_STACK_DEPTH = GL_TEXTURE_STACK_DEPTH;
static const t_CKINT Chuck_OpenGL_MODELVIEW_MATRIX = GL_MODELVIEW_MATRIX;
static const t_CKINT Chuck_OpenGL_PROJECTION_MATRIX = GL_PROJECTION_MATRIX;
static const t_CKINT Chuck_OpenGL_TEXTURE_MATRIX = GL_TEXTURE_MATRIX;
static const t_CKINT Chuck_OpenGL_ATTRIB_STACK_DEPTH = GL_ATTRIB_STACK_DEPTH;
static const t_CKINT Chuck_OpenGL_CLIENT_ATTRIB_STACK_DEPTH = GL_CLIENT_ATTRIB_STACK_DEPTH;
static const t_CKINT Chuck_OpenGL_ALPHA_TEST = GL_ALPHA_TEST;
static const t_CKINT Chuck_OpenGL_ALPHA_TEST_FUNC = GL_ALPHA_TEST_FUNC;
static const t_CKINT Chuck_OpenGL_ALPHA_TEST_REF = GL_ALPHA_TEST_REF;
static const t_CKINT Chuck_OpenGL_INDEX_LOGIC_OP = GL_INDEX_LOGIC_OP;
static const t_CKINT Chuck_OpenGL_LOGIC_OP = GL_LOGIC_OP;
static const t_CKINT Chuck_OpenGL_AUX_BUFFERS = GL_AUX_BUFFERS;
static const t_CKINT Chuck_OpenGL_INDEX_CLEAR_VALUE = GL_INDEX_CLEAR_VALUE;
static const t_CKINT Chuck_OpenGL_INDEX_WRITEMASK = GL_INDEX_WRITEMASK;
static const t_CKINT Chuck_OpenGL_INDEX_MODE = GL_INDEX_MODE;
static const t_CKINT Chuck_OpenGL_RGBA_MODE = GL_RGBA_MODE;
static const t_CKINT Chuck_OpenGL_RENDER_MODE = GL_RENDER_MODE;
static const t_CKINT Chuck_OpenGL_PERSPECTIVE_CORRECTION_HINT = GL_PERSPECTIVE_CORRECTION_HINT;
static const t_CKINT Chuck_OpenGL_POINT_SMOOTH_HINT = GL_POINT_SMOOTH_HINT;
static const t_CKINT Chuck_OpenGL_FOG_HINT = GL_FOG_HINT;
static const t_CKINT Chuck_OpenGL_TEXTURE_GEN_S = GL_TEXTURE_GEN_S;
static const t_CKINT Chuck_OpenGL_TEXTURE_GEN_T = GL_TEXTURE_GEN_T;
static const t_CKINT Chuck_OpenGL_TEXTURE_GEN_R = GL_TEXTURE_GEN_R;
static const t_CKINT Chuck_OpenGL_TEXTURE_GEN_Q = GL_TEXTURE_GEN_Q;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_I_TO_I_SIZE = GL_PIXEL_MAP_I_TO_I_SIZE;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_S_TO_S_SIZE = GL_PIXEL_MAP_S_TO_S_SIZE;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_I_TO_R_SIZE = GL_PIXEL_MAP_I_TO_R_SIZE;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_I_TO_G_SIZE = GL_PIXEL_MAP_I_TO_G_SIZE;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_I_TO_B_SIZE = GL_PIXEL_MAP_I_TO_B_SIZE;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_I_TO_A_SIZE = GL_PIXEL_MAP_I_TO_A_SIZE;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_R_TO_R_SIZE = GL_PIXEL_MAP_R_TO_R_SIZE;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_G_TO_G_SIZE = GL_PIXEL_MAP_G_TO_G_SIZE;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_B_TO_B_SIZE = GL_PIXEL_MAP_B_TO_B_SIZE;
static const t_CKINT Chuck_OpenGL_PIXEL_MAP_A_TO_A_SIZE = GL_PIXEL_MAP_A_TO_A_SIZE;
static const t_CKINT Chuck_OpenGL_MAP_COLOR = GL_MAP_COLOR;
static const t_CKINT Chuck_OpenGL_MAP_STENCIL = GL_MAP_STENCIL;
static const t_CKINT Chuck_OpenGL_INDEX_SHIFT = GL_INDEX_SHIFT;
static const t_CKINT Chuck_OpenGL_INDEX_OFFSET = GL_INDEX_OFFSET;
static const t_CKINT Chuck_OpenGL_RED_SCALE = GL_RED_SCALE;
static const t_CKINT Chuck_OpenGL_RED_BIAS = GL_RED_BIAS;
static const t_CKINT Chuck_OpenGL_ZOOM_X = GL_ZOOM_X;
static const t_CKINT Chuck_OpenGL_ZOOM_Y = GL_ZOOM_Y;
static const t_CKINT Chuck_OpenGL_GREEN_SCALE = GL_GREEN_SCALE;
static const t_CKINT Chuck_OpenGL_GREEN_BIAS = GL_GREEN_BIAS;
static const t_CKINT Chuck_OpenGL_BLUE_SCALE = GL_BLUE_SCALE;
static const t_CKINT Chuck_OpenGL_BLUE_BIAS = GL_BLUE_BIAS;
static const t_CKINT Chuck_OpenGL_ALPHA_SCALE = GL_ALPHA_SCALE;
static const t_CKINT Chuck_OpenGL_ALPHA_BIAS = GL_ALPHA_BIAS;
static const t_CKINT Chuck_OpenGL_DEPTH_SCALE = GL_DEPTH_SCALE;
static const t_CKINT Chuck_OpenGL_DEPTH_BIAS = GL_DEPTH_BIAS;
static const t_CKINT Chuck_OpenGL_MAX_EVAL_ORDER = GL_MAX_EVAL_ORDER;
static const t_CKINT Chuck_OpenGL_MAX_LIGHTS = GL_MAX_LIGHTS;
static const t_CKINT Chuck_OpenGL_MAX_CLIP_PLANES = GL_MAX_CLIP_PLANES;
static const t_CKINT Chuck_OpenGL_MAX_PIXEL_MAP_TABLE = GL_MAX_PIXEL_MAP_TABLE;
static const t_CKINT Chuck_OpenGL_MAX_ATTRIB_STACK_DEPTH = GL_MAX_ATTRIB_STACK_DEPTH;
static const t_CKINT Chuck_OpenGL_MAX_MODELVIEW_STACK_DEPTH = GL_MAX_MODELVIEW_STACK_DEPTH;
static const t_CKINT Chuck_OpenGL_MAX_NAME_STACK_DEPTH = GL_MAX_NAME_STACK_DEPTH;
static const t_CKINT Chuck_OpenGL_MAX_PROJECTION_STACK_DEPTH = GL_MAX_PROJECTION_STACK_DEPTH;
static const t_CKINT Chuck_OpenGL_MAX_TEXTURE_STACK_DEPTH = GL_MAX_TEXTURE_STACK_DEPTH;
static const t_CKINT Chuck_OpenGL_MAX_CLIENT_ATTRIB_STACK_DEPTH = GL_MAX_CLIENT_ATTRIB_STACK_DEPTH;
static const t_CKINT Chuck_OpenGL_INDEX_BITS = GL_INDEX_BITS;
static const t_CKINT Chuck_OpenGL_RED_BITS = GL_RED_BITS;
static const t_CKINT Chuck_OpenGL_GREEN_BITS = GL_GREEN_BITS;
static const t_CKINT Chuck_OpenGL_BLUE_BITS = GL_BLUE_BITS;
static const t_CKINT Chuck_OpenGL_ALPHA_BITS = GL_ALPHA_BITS;
static const t_CKINT Chuck_OpenGL_DEPTH_BITS = GL_DEPTH_BITS;
static const t_CKINT Chuck_OpenGL_STENCIL_BITS = GL_STENCIL_BITS;
static const t_CKINT Chuck_OpenGL_ACCUM_RED_BITS = GL_ACCUM_RED_BITS;
static const t_CKINT Chuck_OpenGL_ACCUM_GREEN_BITS = GL_ACCUM_GREEN_BITS;
static const t_CKINT Chuck_OpenGL_ACCUM_BLUE_BITS = GL_ACCUM_BLUE_BITS;
static const t_CKINT Chuck_OpenGL_ACCUM_ALPHA_BITS = GL_ACCUM_ALPHA_BITS;
static const t_CKINT Chuck_OpenGL_NAME_STACK_DEPTH = GL_NAME_STACK_DEPTH;
static const t_CKINT Chuck_OpenGL_AUTO_NORMAL = GL_AUTO_NORMAL;
static const t_CKINT Chuck_OpenGL_MAP1_COLOR_4 = GL_MAP1_COLOR_4;
static const t_CKINT Chuck_OpenGL_MAP1_INDEX = GL_MAP1_INDEX;
static const t_CKINT Chuck_OpenGL_MAP1_NORMAL = GL_MAP1_NORMAL;
static const t_CKINT Chuck_OpenGL_MAP1_TEXTURE_COORD_1 = GL_MAP1_TEXTURE_COORD_1;
static const t_CKINT Chuck_OpenGL_MAP1_TEXTURE_COORD_2 = GL_MAP1_TEXTURE_COORD_2;
static const t_CKINT Chuck_OpenGL_MAP1_TEXTURE_COORD_3 = GL_MAP1_TEXTURE_COORD_3;
static const t_CKINT Chuck_OpenGL_MAP1_TEXTURE_COORD_4 = GL_MAP1_TEXTURE_COORD_4;
static const t_CKINT Chuck_OpenGL_MAP1_VERTEX_3 = GL_MAP1_VERTEX_3;
static const t_CKINT Chuck_OpenGL_MAP1_VERTEX_4 = GL_MAP1_VERTEX_4;
static const t_CKINT Chuck_OpenGL_MAP2_COLOR_4 = GL_MAP2_COLOR_4;
static const t_CKINT Chuck_OpenGL_MAP2_INDEX = GL_MAP2_INDEX;
static const t_CKINT Chuck_OpenGL_MAP2_NORMAL = GL_MAP2_NORMAL;
static const t_CKINT Chuck_OpenGL_MAP2_TEXTURE_COORD_1 = GL_MAP2_TEXTURE_COORD_1;
static const t_CKINT Chuck_OpenGL_MAP2_TEXTURE_COORD_2 = GL_MAP2_TEXTURE_COORD_2;
static const t_CKINT Chuck_OpenGL_MAP2_TEXTURE_COORD_3 = GL_MAP2_TEXTURE_COORD_3;
static const t_CKINT Chuck_OpenGL_MAP2_TEXTURE_COORD_4 = GL_MAP2_TEXTURE_COORD_4;
static const t_CKINT Chuck_OpenGL_MAP2_VERTEX_3 = GL_MAP2_VERTEX_3;
static const t_CKINT Chuck_OpenGL_MAP2_VERTEX_4 = GL_MAP2_VERTEX_4;
static const t_CKINT Chuck_OpenGL_MAP1_GRID_DOMAIN = GL_MAP1_GRID_DOMAIN;
static const t_CKINT Chuck_OpenGL_MAP1_GRID_SEGMENTS = GL_MAP1_GRID_SEGMENTS;
static const t_CKINT Chuck_OpenGL_MAP2_GRID_DOMAIN = GL_MAP2_GRID_DOMAIN;
static const t_CKINT Chuck_OpenGL_MAP2_GRID_SEGMENTS = GL_MAP2_GRID_SEGMENTS;
static const t_CKINT Chuck_OpenGL_FEEDBACK_BUFFER_SIZE = GL_FEEDBACK_BUFFER_SIZE;
static const t_CKINT Chuck_OpenGL_FEEDBACK_BUFFER_TYPE = GL_FEEDBACK_BUFFER_TYPE;
static const t_CKINT Chuck_OpenGL_SELECTION_BUFFER_SIZE = GL_SELECTION_BUFFER_SIZE;
static const t_CKINT Chuck_OpenGL_VERTEX_ARRAY = GL_VERTEX_ARRAY;
static const t_CKINT Chuck_OpenGL_NORMAL_ARRAY = GL_NORMAL_ARRAY;
static const t_CKINT Chuck_OpenGL_COLOR_ARRAY = GL_COLOR_ARRAY;
static const t_CKINT Chuck_OpenGL_INDEX_ARRAY = GL_INDEX_ARRAY;
static const t_CKINT Chuck_OpenGL_TEXTURE_COORD_ARRAY = GL_TEXTURE_COORD_ARRAY;
static const t_CKINT Chuck_OpenGL_EDGE_FLAG_ARRAY = GL_EDGE_FLAG_ARRAY;
static const t_CKINT Chuck_OpenGL_VERTEX_ARRAY_SIZE = GL_VERTEX_ARRAY_SIZE;
static const t_CKINT Chuck_OpenGL_VERTEX_ARRAY_TYPE = GL_VERTEX_ARRAY_TYPE;
static const t_CKINT Chuck_OpenGL_VERTEX_ARRAY_STRIDE = GL_VERTEX_ARRAY_STRIDE;
static const t_CKINT Chuck_OpenGL_NORMAL_ARRAY_TYPE = GL_NORMAL_ARRAY_TYPE;
static const t_CKINT Chuck_OpenGL_NORMAL_ARRAY_STRIDE = GL_NORMAL_ARRAY_STRIDE;
static const t_CKINT Chuck_OpenGL_COLOR_ARRAY_SIZE = GL_COLOR_ARRAY_SIZE;
static const t_CKINT Chuck_OpenGL_COLOR_ARRAY_TYPE = GL_COLOR_ARRAY_TYPE;
static const t_CKINT Chuck_OpenGL_COLOR_ARRAY_STRIDE = GL_COLOR_ARRAY_STRIDE;
static const t_CKINT Chuck_OpenGL_INDEX_ARRAY_TYPE = GL_INDEX_ARRAY_TYPE;
static const t_CKINT Chuck_OpenGL_INDEX_ARRAY_STRIDE = GL_INDEX_ARRAY_STRIDE;
static const t_CKINT Chuck_OpenGL_TEXTURE_COORD_ARRAY_SIZE = GL_TEXTURE_COORD_ARRAY_SIZE;
static const t_CKINT Chuck_OpenGL_TEXTURE_COORD_ARRAY_TYPE = GL_TEXTURE_COORD_ARRAY_TYPE;
static const t_CKINT Chuck_OpenGL_TEXTURE_COORD_ARRAY_STRIDE = GL_TEXTURE_COORD_ARRAY_STRIDE;
static const t_CKINT Chuck_OpenGL_EDGE_FLAG_ARRAY_STRIDE = GL_EDGE_FLAG_ARRAY_STRIDE;
static const t_CKINT Chuck_OpenGL_TEXTURE_COMPONENTS = GL_TEXTURE_COMPONENTS;
static const t_CKINT Chuck_OpenGL_TEXTURE_BORDER = GL_TEXTURE_BORDER;
static const t_CKINT Chuck_OpenGL_TEXTURE_LUMINANCE_SIZE = GL_TEXTURE_LUMINANCE_SIZE;
static const t_CKINT Chuck_OpenGL_TEXTURE_INTENSITY_SIZE = GL_TEXTURE_INTENSITY_SIZE;
static const t_CKINT Chuck_OpenGL_TEXTURE_PRIORITY = GL_TEXTURE_PRIORITY;
static const t_CKINT Chuck_OpenGL_TEXTURE_RESIDENT = GL_TEXTURE_RESIDENT;
static const t_CKINT Chuck_OpenGL_AMBIENT = GL_AMBIENT;
static const t_CKINT Chuck_OpenGL_DIFFUSE = GL_DIFFUSE;
static const t_CKINT Chuck_OpenGL_SPECULAR = GL_SPECULAR;
static const t_CKINT Chuck_OpenGL_POSITION = GL_POSITION;
static const t_CKINT Chuck_OpenGL_SPOT_DIRECTION = GL_SPOT_DIRECTION;
static const t_CKINT Chuck_OpenGL_SPOT_EXPONENT = GL_SPOT_EXPONENT;
static const t_CKINT Chuck_OpenGL_SPOT_CUTOFF = GL_SPOT_CUTOFF;
static const t_CKINT Chuck_OpenGL_CONSTANT_ATTENUATION = GL_CONSTANT_ATTENUATION;
static const t_CKINT Chuck_OpenGL_LINEAR_ATTENUATION = GL_LINEAR_ATTENUATION;
static const t_CKINT Chuck_OpenGL_QUADRATIC_ATTENUATION = GL_QUADRATIC_ATTENUATION;
static const t_CKINT Chuck_OpenGL_COMPILE = GL_COMPILE;
static const t_CKINT Chuck_OpenGL_COMPILE_AND_EXECUTE = GL_COMPILE_AND_EXECUTE;
static const t_CKINT Chuck_OpenGL_2_BYTES = GL_2_BYTES;
static const t_CKINT Chuck_OpenGL_3_BYTES = GL_3_BYTES;
static const t_CKINT Chuck_OpenGL_4_BYTES = GL_4_BYTES;
static const t_CKINT Chuck_OpenGL_EMISSION = GL_EMISSION;
static const t_CKINT Chuck_OpenGL_SHININESS = GL_SHININESS;
static const t_CKINT Chuck_OpenGL_AMBIENT_AND_DIFFUSE = GL_AMBIENT_AND_DIFFUSE;
static const t_CKINT Chuck_OpenGL_COLOR_INDEXES = GL_COLOR_INDEXES;
static const t_CKINT Chuck_OpenGL_MODELVIEW = GL_MODELVIEW;
static const t_CKINT Chuck_OpenGL_PROJECTION = GL_PROJECTION;
static const t_CKINT Chuck_OpenGL_COLOR_INDEX = GL_COLOR_INDEX;
static const t_CKINT Chuck_OpenGL_LUMINANCE = GL_LUMINANCE;
static const t_CKINT Chuck_OpenGL_LUMINANCE_ALPHA = GL_LUMINANCE_ALPHA;
static const t_CKINT Chuck_OpenGL_BITMAP = GL_BITMAP;
static const t_CKINT Chuck_OpenGL_RENDER = GL_RENDER;
static const t_CKINT Chuck_OpenGL_FEEDBACK = GL_FEEDBACK;
static const t_CKINT Chuck_OpenGL_SELECT = GL_SELECT;
static const t_CKINT Chuck_OpenGL_FLAT = GL_FLAT;
static const t_CKINT Chuck_OpenGL_SMOOTH = GL_SMOOTH;
static const t_CKINT Chuck_OpenGL_S = GL_S;
static const t_CKINT Chuck_OpenGL_T = GL_T;
static const t_CKINT Chuck_OpenGL_R = GL_R;
static const t_CKINT Chuck_OpenGL_Q = GL_Q;
static const t_CKINT Chuck_OpenGL_MODULATE = GL_MODULATE;
static const t_CKINT Chuck_OpenGL_DECAL = GL_DECAL;
static const t_CKINT Chuck_OpenGL_TEXTURE_ENV_MODE = GL_TEXTURE_ENV_MODE;
static const t_CKINT Chuck_OpenGL_TEXTURE_ENV_COLOR = GL_TEXTURE_ENV_COLOR;
static const t_CKINT Chuck_OpenGL_TEXTURE_ENV = GL_TEXTURE_ENV;
static const t_CKINT Chuck_OpenGL_EYE_LINEAR = GL_EYE_LINEAR;
static const t_CKINT Chuck_OpenGL_OBJECT_LINEAR = GL_OBJECT_LINEAR;
static const t_CKINT Chuck_OpenGL_SPHERE_MAP = GL_SPHERE_MAP;
static const t_CKINT Chuck_OpenGL_TEXTURE_GEN_MODE = GL_TEXTURE_GEN_MODE;
static const t_CKINT Chuck_OpenGL_OBJECT_PLANE = GL_OBJECT_PLANE;
static const t_CKINT Chuck_OpenGL_EYE_PLANE = GL_EYE_PLANE;
static const t_CKINT Chuck_OpenGL_CLAMP = GL_CLAMP;
static const t_CKINT Chuck_OpenGL_ALPHA4 = GL_ALPHA4;
static const t_CKINT Chuck_OpenGL_ALPHA8 = GL_ALPHA8;
static const t_CKINT Chuck_OpenGL_ALPHA12 = GL_ALPHA12;
static const t_CKINT Chuck_OpenGL_ALPHA16 = GL_ALPHA16;
static const t_CKINT Chuck_OpenGL_LUMINANCE4 = GL_LUMINANCE4;
static const t_CKINT Chuck_OpenGL_LUMINANCE8 = GL_LUMINANCE8;
static const t_CKINT Chuck_OpenGL_LUMINANCE12 = GL_LUMINANCE12;
static const t_CKINT Chuck_OpenGL_LUMINANCE16 = GL_LUMINANCE16;
static const t_CKINT Chuck_OpenGL_LUMINANCE4_ALPHA4 = GL_LUMINANCE4_ALPHA4;
static const t_CKINT Chuck_OpenGL_LUMINANCE6_ALPHA2 = GL_LUMINANCE6_ALPHA2;
static const t_CKINT Chuck_OpenGL_LUMINANCE8_ALPHA8 = GL_LUMINANCE8_ALPHA8;
static const t_CKINT Chuck_OpenGL_LUMINANCE12_ALPHA4 = GL_LUMINANCE12_ALPHA4;
static const t_CKINT Chuck_OpenGL_LUMINANCE12_ALPHA12 = GL_LUMINANCE12_ALPHA12;
static const t_CKINT Chuck_OpenGL_LUMINANCE16_ALPHA16 = GL_LUMINANCE16_ALPHA16;
static const t_CKINT Chuck_OpenGL_INTENSITY = GL_INTENSITY;
static const t_CKINT Chuck_OpenGL_INTENSITY4 = GL_INTENSITY4;
static const t_CKINT Chuck_OpenGL_INTENSITY8 = GL_INTENSITY8;
static const t_CKINT Chuck_OpenGL_INTENSITY12 = GL_INTENSITY12;
static const t_CKINT Chuck_OpenGL_INTENSITY16 = GL_INTENSITY16;
static const t_CKINT Chuck_OpenGL_V2F = GL_V2F;
static const t_CKINT Chuck_OpenGL_V3F = GL_V3F;
static const t_CKINT Chuck_OpenGL_C4UB_V2F = GL_C4UB_V2F;
static const t_CKINT Chuck_OpenGL_C4UB_V3F = GL_C4UB_V3F;
static const t_CKINT Chuck_OpenGL_C3F_V3F = GL_C3F_V3F;
static const t_CKINT Chuck_OpenGL_N3F_V3F = GL_N3F_V3F;
static const t_CKINT Chuck_OpenGL_C4F_N3F_V3F = GL_C4F_N3F_V3F;
static const t_CKINT Chuck_OpenGL_T2F_V3F = GL_T2F_V3F;
static const t_CKINT Chuck_OpenGL_T4F_V4F = GL_T4F_V4F;
static const t_CKINT Chuck_OpenGL_T2F_C4UB_V3F = GL_T2F_C4UB_V3F;
static const t_CKINT Chuck_OpenGL_T2F_C3F_V3F = GL_T2F_C3F_V3F;
static const t_CKINT Chuck_OpenGL_T2F_N3F_V3F = GL_T2F_N3F_V3F;
static const t_CKINT Chuck_OpenGL_T2F_C4F_N3F_V3F = GL_T2F_C4F_N3F_V3F;
static const t_CKINT Chuck_OpenGL_T4F_C4F_N3F_V4F = GL_T4F_C4F_N3F_V4F;
static const t_CKINT Chuck_OpenGL_CLIP_PLANE0 = GL_CLIP_PLANE0;
static const t_CKINT Chuck_OpenGL_CLIP_PLANE1 = GL_CLIP_PLANE1;
static const t_CKINT Chuck_OpenGL_CLIP_PLANE2 = GL_CLIP_PLANE2;
static const t_CKINT Chuck_OpenGL_CLIP_PLANE3 = GL_CLIP_PLANE3;
static const t_CKINT Chuck_OpenGL_CLIP_PLANE4 = GL_CLIP_PLANE4;
static const t_CKINT Chuck_OpenGL_CLIP_PLANE5 = GL_CLIP_PLANE5;
static const t_CKINT Chuck_OpenGL_LIGHT0 = GL_LIGHT0;
static const t_CKINT Chuck_OpenGL_LIGHT1 = GL_LIGHT1;
static const t_CKINT Chuck_OpenGL_LIGHT2 = GL_LIGHT2;
static const t_CKINT Chuck_OpenGL_LIGHT3 = GL_LIGHT3;
static const t_CKINT Chuck_OpenGL_LIGHT4 = GL_LIGHT4;
static const t_CKINT Chuck_OpenGL_LIGHT5 = GL_LIGHT5;
static const t_CKINT Chuck_OpenGL_LIGHT6 = GL_LIGHT6;
static const t_CKINT Chuck_OpenGL_LIGHT7 = GL_LIGHT7;

CK_DLL_MFUN(Chuck_OpenGL_DrawArrays)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);
    t_CKINT arg_first = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);

    glDrawArrays(arg_mode, arg_first, arg_count);
}


CK_DLL_MFUN(Chuck_OpenGL_DrawElements)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_indices_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_indices;
    if(_arg_indices_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_indices_arr = (Chuck_Array4 *) _arg_indices_arr;
        GLubyte *arg_indices_v = new GLubyte[arg_indices_arr->size()];
        chgl->scheduleArrayForCleanup(arg_indices_v);
        copy_ckarray4_to_array(arg_indices_v, arg_indices_arr);
        arg_indices = (void *) arg_indices_v;
    }
    else if(_arg_indices_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_indices_arr = (Chuck_Array8 *) _arg_indices_arr;
        GLfloat *arg_indices_v = new GLfloat[arg_indices_arr->size()];
        chgl->scheduleArrayForCleanup(arg_indices_v);
        copy_ckarray8_to_array(arg_indices_v, arg_indices_arr);
        arg_indices = (void *) arg_indices_v;
    }

    glDrawElements(arg_mode, arg_count, arg_type, arg_indices);
}


CK_DLL_MFUN(Chuck_OpenGL_PolygonOffset)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_factor = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_units = GET_NEXT_FLOAT(ARGS);

    glPolygonOffset(arg_factor, arg_units);
}


CK_DLL_MFUN(Chuck_OpenGL_CopyTexImage1D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_internalformat = GET_NEXT_INT(ARGS);
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_border = GET_NEXT_INT(ARGS);

    glCopyTexImage1D(arg_target, arg_level, arg_internalformat, arg_x, arg_y, arg_width, arg_border);
}


CK_DLL_MFUN(Chuck_OpenGL_CopyTexImage2D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_internalformat = GET_NEXT_INT(ARGS);
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_border = GET_NEXT_INT(ARGS);

    glCopyTexImage2D(arg_target, arg_level, arg_internalformat, arg_x, arg_y, arg_width, arg_height, arg_border);
}


CK_DLL_MFUN(Chuck_OpenGL_CopyTexSubImage1D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_xoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);

    glCopyTexSubImage1D(arg_target, arg_level, arg_xoffset, arg_x, arg_y, arg_width);
}


CK_DLL_MFUN(Chuck_OpenGL_CopyTexSubImage2D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_xoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_yoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);

    glCopyTexSubImage2D(arg_target, arg_level, arg_xoffset, arg_yoffset, arg_x, arg_y, arg_width, arg_height);
}


CK_DLL_MFUN(Chuck_OpenGL_TexSubImage1D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_xoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_format = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pixels_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pixels;
    if(_arg_pixels_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pixels_arr = (Chuck_Array4 *) _arg_pixels_arr;
        GLubyte *arg_pixels_v = new GLubyte[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray4_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }
    else if(_arg_pixels_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pixels_arr = (Chuck_Array8 *) _arg_pixels_arr;
        GLfloat *arg_pixels_v = new GLfloat[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray8_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }

    glTexSubImage1D(arg_target, arg_level, arg_xoffset, arg_width, arg_format, arg_type, arg_pixels);
}


CK_DLL_MFUN(Chuck_OpenGL_TexSubImage2D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_xoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_yoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_format = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pixels_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pixels;
    if(_arg_pixels_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pixels_arr = (Chuck_Array4 *) _arg_pixels_arr;
        GLubyte *arg_pixels_v = new GLubyte[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray4_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }
    else if(_arg_pixels_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pixels_arr = (Chuck_Array8 *) _arg_pixels_arr;
        GLfloat *arg_pixels_v = new GLfloat[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray8_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }

    glTexSubImage2D(arg_target, arg_level, arg_xoffset, arg_yoffset, arg_width, arg_height, arg_format, arg_type, arg_pixels);
}


CK_DLL_MFUN(Chuck_OpenGL_BindTexture)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_texture = GET_NEXT_INT(ARGS);

    glBindTexture(arg_target, arg_texture);
}


CK_DLL_MFUN(Chuck_OpenGL_DeleteTextures)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_textures_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_textures = new GLuint[arg_textures_arr->size()];
    chgl->scheduleArrayForCleanup(arg_textures);
    copy_ckarray4_to_array(arg_textures, arg_textures_arr);

    glDeleteTextures(arg_n, arg_textures);
}


CK_DLL_MFUN(Chuck_OpenGL_GenTextures)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_textures_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_textures = new GLuint[arg_textures_arr->size()];
    chgl->scheduleArrayForCleanup(arg_textures);
    copy_ckarray4_to_array(arg_textures, arg_textures_arr);

    glGenTextures(arg_n, arg_textures);
}


CK_DLL_MFUN(Chuck_OpenGL_IsTexture)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_texture = GET_NEXT_INT(ARGS);

    RETURN->v_int = glIsTexture(arg_texture);
}


CK_DLL_MFUN(Chuck_OpenGL_ArrayElement)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_i = GET_NEXT_INT(ARGS);

    glArrayElement(arg_i);
}


CK_DLL_MFUN(Chuck_OpenGL_ColorPointer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_size = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    t_CKINT arg_stride = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pointer_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pointer;
    if(_arg_pointer_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pointer_arr = (Chuck_Array4 *) _arg_pointer_arr;
        GLubyte *arg_pointer_v = new GLubyte[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray4_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }
    else if(_arg_pointer_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pointer_arr = (Chuck_Array8 *) _arg_pointer_arr;
        GLfloat *arg_pointer_v = new GLfloat[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray8_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }

    glColorPointer(arg_size, arg_type, arg_stride, arg_pointer);
}


CK_DLL_MFUN(Chuck_OpenGL_DisableClientState)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_array = GET_NEXT_INT(ARGS);

    glDisableClientState(arg_array);
}


CK_DLL_MFUN(Chuck_OpenGL_EdgeFlagPointer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_stride = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pointer_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pointer;
    if(_arg_pointer_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pointer_arr = (Chuck_Array4 *) _arg_pointer_arr;
        GLubyte *arg_pointer_v = new GLubyte[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray4_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }
    else if(_arg_pointer_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pointer_arr = (Chuck_Array8 *) _arg_pointer_arr;
        GLfloat *arg_pointer_v = new GLfloat[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray8_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }

    glEdgeFlagPointer(arg_stride, arg_pointer);
}


CK_DLL_MFUN(Chuck_OpenGL_EnableClientState)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_array = GET_NEXT_INT(ARGS);

    glEnableClientState(arg_array);
}


CK_DLL_MFUN(Chuck_OpenGL_IndexPointer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    t_CKINT arg_stride = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pointer_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pointer;
    if(_arg_pointer_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pointer_arr = (Chuck_Array4 *) _arg_pointer_arr;
        GLubyte *arg_pointer_v = new GLubyte[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray4_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }
    else if(_arg_pointer_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pointer_arr = (Chuck_Array8 *) _arg_pointer_arr;
        GLfloat *arg_pointer_v = new GLfloat[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray8_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }

    glIndexPointer(arg_type, arg_stride, arg_pointer);
}


CK_DLL_MFUN(Chuck_OpenGL_InterleavedArrays)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_format = GET_NEXT_INT(ARGS);
    t_CKINT arg_stride = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pointer_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pointer;
    if(_arg_pointer_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pointer_arr = (Chuck_Array4 *) _arg_pointer_arr;
        GLubyte *arg_pointer_v = new GLubyte[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray4_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }
    else if(_arg_pointer_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pointer_arr = (Chuck_Array8 *) _arg_pointer_arr;
        GLfloat *arg_pointer_v = new GLfloat[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray8_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }

    glInterleavedArrays(arg_format, arg_stride, arg_pointer);
}


CK_DLL_MFUN(Chuck_OpenGL_NormalPointer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    t_CKINT arg_stride = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pointer_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pointer;
    if(_arg_pointer_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pointer_arr = (Chuck_Array4 *) _arg_pointer_arr;
        GLubyte *arg_pointer_v = new GLubyte[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray4_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }
    else if(_arg_pointer_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pointer_arr = (Chuck_Array8 *) _arg_pointer_arr;
        GLfloat *arg_pointer_v = new GLfloat[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray8_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }

    glNormalPointer(arg_type, arg_stride, arg_pointer);
}


CK_DLL_MFUN(Chuck_OpenGL_TexCoordPointer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_size = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    t_CKINT arg_stride = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pointer_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pointer;
    if(_arg_pointer_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pointer_arr = (Chuck_Array4 *) _arg_pointer_arr;
        GLubyte *arg_pointer_v = new GLubyte[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray4_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }
    else if(_arg_pointer_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pointer_arr = (Chuck_Array8 *) _arg_pointer_arr;
        GLfloat *arg_pointer_v = new GLfloat[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray8_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }

    glTexCoordPointer(arg_size, arg_type, arg_stride, arg_pointer);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexPointer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_size = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    t_CKINT arg_stride = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pointer_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pointer;
    if(_arg_pointer_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pointer_arr = (Chuck_Array4 *) _arg_pointer_arr;
        GLubyte *arg_pointer_v = new GLubyte[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray4_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }
    else if(_arg_pointer_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pointer_arr = (Chuck_Array8 *) _arg_pointer_arr;
        GLfloat *arg_pointer_v = new GLfloat[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray8_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }

    glVertexPointer(arg_size, arg_type, arg_stride, arg_pointer);
}


CK_DLL_MFUN(Chuck_OpenGL_AreTexturesResident)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_textures_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_textures = new GLuint[arg_textures_arr->size()];
    chgl->scheduleArrayForCleanup(arg_textures);
    copy_ckarray4_to_array(arg_textures, arg_textures_arr);
    Chuck_Array4 *arg_residences_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLboolean *arg_residences = new GLboolean[arg_residences_arr->size()];
    chgl->scheduleArrayForCleanup(arg_residences);
    copy_ckarray4_to_array(arg_residences, arg_residences_arr);

    RETURN->v_int = glAreTexturesResident(arg_n, arg_textures, arg_residences);
}


CK_DLL_MFUN(Chuck_OpenGL_PrioritizeTextures)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_textures_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_textures = new GLuint[arg_textures_arr->size()];
    chgl->scheduleArrayForCleanup(arg_textures);
    copy_ckarray4_to_array(arg_textures, arg_textures_arr);
    Chuck_Array8 *arg_priorities_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_priorities = new GLfloat[arg_priorities_arr->size()];
    chgl->scheduleArrayForCleanup(arg_priorities);
    copy_ckarray8_to_array(arg_priorities, arg_priorities_arr);

    glPrioritizeTextures(arg_n, arg_textures, arg_priorities);
}


CK_DLL_MFUN(Chuck_OpenGL_Indexub)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_c = GET_NEXT_INT(ARGS);

    glIndexub(arg_c);
}


CK_DLL_MFUN(Chuck_OpenGL_Indexubv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_c_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLubyte *arg_c = new GLubyte[arg_c_arr->size()];
    chgl->scheduleArrayForCleanup(arg_c);
    copy_ckarray4_to_array(arg_c, arg_c_arr);

    glIndexubv(arg_c);
}


CK_DLL_MFUN(Chuck_OpenGL_PopClientAttrib)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    

    glPopClientAttrib();
}


CK_DLL_MFUN(Chuck_OpenGL_PushClientAttrib)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mask = GET_NEXT_INT(ARGS);

    glPushClientAttrib(arg_mask);
}

static const t_CKINT Chuck_OpenGL_UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2;
static const t_CKINT Chuck_OpenGL_UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4;
static const t_CKINT Chuck_OpenGL_UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1;
static const t_CKINT Chuck_OpenGL_UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8;
static const t_CKINT Chuck_OpenGL_UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2;
static const t_CKINT Chuck_OpenGL_TEXTURE_BINDING_3D = GL_TEXTURE_BINDING_3D;
static const t_CKINT Chuck_OpenGL_PACK_SKIP_IMAGES = GL_PACK_SKIP_IMAGES;
static const t_CKINT Chuck_OpenGL_PACK_IMAGE_HEIGHT = GL_PACK_IMAGE_HEIGHT;
static const t_CKINT Chuck_OpenGL_UNPACK_SKIP_IMAGES = GL_UNPACK_SKIP_IMAGES;
static const t_CKINT Chuck_OpenGL_UNPACK_IMAGE_HEIGHT = GL_UNPACK_IMAGE_HEIGHT;
static const t_CKINT Chuck_OpenGL_TEXTURE_3D = GL_TEXTURE_3D;
static const t_CKINT Chuck_OpenGL_PROXY_TEXTURE_3D = GL_PROXY_TEXTURE_3D;
static const t_CKINT Chuck_OpenGL_TEXTURE_DEPTH = GL_TEXTURE_DEPTH;
static const t_CKINT Chuck_OpenGL_TEXTURE_WRAP_R = GL_TEXTURE_WRAP_R;
static const t_CKINT Chuck_OpenGL_MAX_3D_TEXTURE_SIZE = GL_MAX_3D_TEXTURE_SIZE;
static const t_CKINT Chuck_OpenGL_UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV;
static const t_CKINT Chuck_OpenGL_UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5;
static const t_CKINT Chuck_OpenGL_UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV;
static const t_CKINT Chuck_OpenGL_UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV;
static const t_CKINT Chuck_OpenGL_UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV;
static const t_CKINT Chuck_OpenGL_UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV;
static const t_CKINT Chuck_OpenGL_UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV;
static const t_CKINT Chuck_OpenGL_BGR = GL_BGR;
static const t_CKINT Chuck_OpenGL_BGRA = GL_BGRA;
static const t_CKINT Chuck_OpenGL_MAX_ELEMENTS_VERTICES = GL_MAX_ELEMENTS_VERTICES;
static const t_CKINT Chuck_OpenGL_MAX_ELEMENTS_INDICES = GL_MAX_ELEMENTS_INDICES;
static const t_CKINT Chuck_OpenGL_CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE;
static const t_CKINT Chuck_OpenGL_TEXTURE_MIN_LOD = GL_TEXTURE_MIN_LOD;
static const t_CKINT Chuck_OpenGL_TEXTURE_MAX_LOD = GL_TEXTURE_MAX_LOD;
static const t_CKINT Chuck_OpenGL_TEXTURE_BASE_LEVEL = GL_TEXTURE_BASE_LEVEL;
static const t_CKINT Chuck_OpenGL_TEXTURE_MAX_LEVEL = GL_TEXTURE_MAX_LEVEL;
static const t_CKINT Chuck_OpenGL_SMOOTH_POINT_SIZE_RANGE = GL_SMOOTH_POINT_SIZE_RANGE;
static const t_CKINT Chuck_OpenGL_SMOOTH_POINT_SIZE_GRANULARITY = GL_SMOOTH_POINT_SIZE_GRANULARITY;
static const t_CKINT Chuck_OpenGL_SMOOTH_LINE_WIDTH_RANGE = GL_SMOOTH_LINE_WIDTH_RANGE;
static const t_CKINT Chuck_OpenGL_SMOOTH_LINE_WIDTH_GRANULARITY = GL_SMOOTH_LINE_WIDTH_GRANULARITY;
static const t_CKINT Chuck_OpenGL_ALIASED_LINE_WIDTH_RANGE = GL_ALIASED_LINE_WIDTH_RANGE;
static const t_CKINT Chuck_OpenGL_RESCALE_NORMAL = GL_RESCALE_NORMAL;
static const t_CKINT Chuck_OpenGL_LIGHT_MODEL_COLOR_CONTROL = GL_LIGHT_MODEL_COLOR_CONTROL;
static const t_CKINT Chuck_OpenGL_SINGLE_COLOR = GL_SINGLE_COLOR;
static const t_CKINT Chuck_OpenGL_SEPARATE_SPECULAR_COLOR = GL_SEPARATE_SPECULAR_COLOR;
static const t_CKINT Chuck_OpenGL_ALIASED_POINT_SIZE_RANGE = GL_ALIASED_POINT_SIZE_RANGE;

CK_DLL_MFUN(Chuck_OpenGL_DrawRangeElements)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);
    t_CKINT arg_start = GET_NEXT_INT(ARGS);
    t_CKINT arg_end = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_indices_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_indices;
    if(_arg_indices_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_indices_arr = (Chuck_Array4 *) _arg_indices_arr;
        GLubyte *arg_indices_v = new GLubyte[arg_indices_arr->size()];
        chgl->scheduleArrayForCleanup(arg_indices_v);
        copy_ckarray4_to_array(arg_indices_v, arg_indices_arr);
        arg_indices = (void *) arg_indices_v;
    }
    else if(_arg_indices_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_indices_arr = (Chuck_Array8 *) _arg_indices_arr;
        GLfloat *arg_indices_v = new GLfloat[arg_indices_arr->size()];
        chgl->scheduleArrayForCleanup(arg_indices_v);
        copy_ckarray8_to_array(arg_indices_v, arg_indices_arr);
        arg_indices = (void *) arg_indices_v;
    }

    glDrawRangeElements(arg_mode, arg_start, arg_end, arg_count, arg_type, arg_indices);
}


CK_DLL_MFUN(Chuck_OpenGL_TexImage3D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_internalformat = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_depth = GET_NEXT_INT(ARGS);
    t_CKINT arg_border = GET_NEXT_INT(ARGS);
    t_CKINT arg_format = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pixels_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pixels;
    if(_arg_pixels_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pixels_arr = (Chuck_Array4 *) _arg_pixels_arr;
        GLubyte *arg_pixels_v = new GLubyte[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray4_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }
    else if(_arg_pixels_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pixels_arr = (Chuck_Array8 *) _arg_pixels_arr;
        GLfloat *arg_pixels_v = new GLfloat[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray8_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }

    glTexImage3D(arg_target, arg_level, arg_internalformat, arg_width, arg_height, arg_depth, arg_border, arg_format, arg_type, arg_pixels);
}


CK_DLL_MFUN(Chuck_OpenGL_TexSubImage3D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_xoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_yoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_zoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_depth = GET_NEXT_INT(ARGS);
    t_CKINT arg_format = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pixels_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pixels;
    if(_arg_pixels_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pixels_arr = (Chuck_Array4 *) _arg_pixels_arr;
        GLubyte *arg_pixels_v = new GLubyte[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray4_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }
    else if(_arg_pixels_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pixels_arr = (Chuck_Array8 *) _arg_pixels_arr;
        GLfloat *arg_pixels_v = new GLfloat[arg_pixels_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pixels_v);
        copy_ckarray8_to_array(arg_pixels_v, arg_pixels_arr);
        arg_pixels = (void *) arg_pixels_v;
    }

    glTexSubImage3D(arg_target, arg_level, arg_xoffset, arg_yoffset, arg_zoffset, arg_width, arg_height, arg_depth, arg_format, arg_type, arg_pixels);
}


CK_DLL_MFUN(Chuck_OpenGL_CopyTexSubImage3D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_xoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_yoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_zoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);

    glCopyTexSubImage3D(arg_target, arg_level, arg_xoffset, arg_yoffset, arg_zoffset, arg_x, arg_y, arg_width, arg_height);
}

static const t_CKINT Chuck_OpenGL_TEXTURE0 = GL_TEXTURE0;
static const t_CKINT Chuck_OpenGL_TEXTURE1 = GL_TEXTURE1;
static const t_CKINT Chuck_OpenGL_TEXTURE2 = GL_TEXTURE2;
static const t_CKINT Chuck_OpenGL_TEXTURE3 = GL_TEXTURE3;
static const t_CKINT Chuck_OpenGL_TEXTURE4 = GL_TEXTURE4;
static const t_CKINT Chuck_OpenGL_TEXTURE5 = GL_TEXTURE5;
static const t_CKINT Chuck_OpenGL_TEXTURE6 = GL_TEXTURE6;
static const t_CKINT Chuck_OpenGL_TEXTURE7 = GL_TEXTURE7;
static const t_CKINT Chuck_OpenGL_TEXTURE8 = GL_TEXTURE8;
static const t_CKINT Chuck_OpenGL_TEXTURE9 = GL_TEXTURE9;
static const t_CKINT Chuck_OpenGL_TEXTURE10 = GL_TEXTURE10;
static const t_CKINT Chuck_OpenGL_TEXTURE11 = GL_TEXTURE11;
static const t_CKINT Chuck_OpenGL_TEXTURE12 = GL_TEXTURE12;
static const t_CKINT Chuck_OpenGL_TEXTURE13 = GL_TEXTURE13;
static const t_CKINT Chuck_OpenGL_TEXTURE14 = GL_TEXTURE14;
static const t_CKINT Chuck_OpenGL_TEXTURE15 = GL_TEXTURE15;
static const t_CKINT Chuck_OpenGL_TEXTURE16 = GL_TEXTURE16;
static const t_CKINT Chuck_OpenGL_TEXTURE17 = GL_TEXTURE17;
static const t_CKINT Chuck_OpenGL_TEXTURE18 = GL_TEXTURE18;
static const t_CKINT Chuck_OpenGL_TEXTURE19 = GL_TEXTURE19;
static const t_CKINT Chuck_OpenGL_TEXTURE20 = GL_TEXTURE20;
static const t_CKINT Chuck_OpenGL_TEXTURE21 = GL_TEXTURE21;
static const t_CKINT Chuck_OpenGL_TEXTURE22 = GL_TEXTURE22;
static const t_CKINT Chuck_OpenGL_TEXTURE23 = GL_TEXTURE23;
static const t_CKINT Chuck_OpenGL_TEXTURE24 = GL_TEXTURE24;
static const t_CKINT Chuck_OpenGL_TEXTURE25 = GL_TEXTURE25;
static const t_CKINT Chuck_OpenGL_TEXTURE26 = GL_TEXTURE26;
static const t_CKINT Chuck_OpenGL_TEXTURE27 = GL_TEXTURE27;
static const t_CKINT Chuck_OpenGL_TEXTURE28 = GL_TEXTURE28;
static const t_CKINT Chuck_OpenGL_TEXTURE29 = GL_TEXTURE29;
static const t_CKINT Chuck_OpenGL_TEXTURE30 = GL_TEXTURE30;
static const t_CKINT Chuck_OpenGL_TEXTURE31 = GL_TEXTURE31;
static const t_CKINT Chuck_OpenGL_ACTIVE_TEXTURE = GL_ACTIVE_TEXTURE;
static const t_CKINT Chuck_OpenGL_MULTISAMPLE = GL_MULTISAMPLE;
static const t_CKINT Chuck_OpenGL_SAMPLE_ALPHA_TO_COVERAGE = GL_SAMPLE_ALPHA_TO_COVERAGE;
static const t_CKINT Chuck_OpenGL_SAMPLE_ALPHA_TO_ONE = GL_SAMPLE_ALPHA_TO_ONE;
static const t_CKINT Chuck_OpenGL_SAMPLE_COVERAGE = GL_SAMPLE_COVERAGE;
static const t_CKINT Chuck_OpenGL_SAMPLE_BUFFERS = GL_SAMPLE_BUFFERS;
static const t_CKINT Chuck_OpenGL_SAMPLES = GL_SAMPLES;
static const t_CKINT Chuck_OpenGL_SAMPLE_COVERAGE_VALUE = GL_SAMPLE_COVERAGE_VALUE;
static const t_CKINT Chuck_OpenGL_SAMPLE_COVERAGE_INVERT = GL_SAMPLE_COVERAGE_INVERT;
static const t_CKINT Chuck_OpenGL_TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP;
static const t_CKINT Chuck_OpenGL_TEXTURE_BINDING_CUBE_MAP = GL_TEXTURE_BINDING_CUBE_MAP;
static const t_CKINT Chuck_OpenGL_TEXTURE_CUBE_MAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
static const t_CKINT Chuck_OpenGL_TEXTURE_CUBE_MAP_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
static const t_CKINT Chuck_OpenGL_TEXTURE_CUBE_MAP_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
static const t_CKINT Chuck_OpenGL_TEXTURE_CUBE_MAP_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
static const t_CKINT Chuck_OpenGL_TEXTURE_CUBE_MAP_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
static const t_CKINT Chuck_OpenGL_TEXTURE_CUBE_MAP_NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
static const t_CKINT Chuck_OpenGL_PROXY_TEXTURE_CUBE_MAP = GL_PROXY_TEXTURE_CUBE_MAP;
static const t_CKINT Chuck_OpenGL_MAX_CUBE_MAP_TEXTURE_SIZE = GL_MAX_CUBE_MAP_TEXTURE_SIZE;
static const t_CKINT Chuck_OpenGL_COMPRESSED_RGB = GL_COMPRESSED_RGB;
static const t_CKINT Chuck_OpenGL_COMPRESSED_RGBA = GL_COMPRESSED_RGBA;
static const t_CKINT Chuck_OpenGL_TEXTURE_COMPRESSION_HINT = GL_TEXTURE_COMPRESSION_HINT;
static const t_CKINT Chuck_OpenGL_TEXTURE_COMPRESSED_IMAGE_SIZE = GL_TEXTURE_COMPRESSED_IMAGE_SIZE;
static const t_CKINT Chuck_OpenGL_TEXTURE_COMPRESSED = GL_TEXTURE_COMPRESSED;
static const t_CKINT Chuck_OpenGL_NUM_COMPRESSED_TEXTURE_FORMATS = GL_NUM_COMPRESSED_TEXTURE_FORMATS;
static const t_CKINT Chuck_OpenGL_COMPRESSED_TEXTURE_FORMATS = GL_COMPRESSED_TEXTURE_FORMATS;
static const t_CKINT Chuck_OpenGL_CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER;
static const t_CKINT Chuck_OpenGL_CLIENT_ACTIVE_TEXTURE = GL_CLIENT_ACTIVE_TEXTURE;
static const t_CKINT Chuck_OpenGL_MAX_TEXTURE_UNITS = GL_MAX_TEXTURE_UNITS;
static const t_CKINT Chuck_OpenGL_TRANSPOSE_MODELVIEW_MATRIX = GL_TRANSPOSE_MODELVIEW_MATRIX;
static const t_CKINT Chuck_OpenGL_TRANSPOSE_PROJECTION_MATRIX = GL_TRANSPOSE_PROJECTION_MATRIX;
static const t_CKINT Chuck_OpenGL_TRANSPOSE_TEXTURE_MATRIX = GL_TRANSPOSE_TEXTURE_MATRIX;
static const t_CKINT Chuck_OpenGL_TRANSPOSE_COLOR_MATRIX = GL_TRANSPOSE_COLOR_MATRIX;
static const t_CKINT Chuck_OpenGL_MULTISAMPLE_BIT = GL_MULTISAMPLE_BIT;
static const t_CKINT Chuck_OpenGL_NORMAL_MAP = GL_NORMAL_MAP;
static const t_CKINT Chuck_OpenGL_REFLECTION_MAP = GL_REFLECTION_MAP;
static const t_CKINT Chuck_OpenGL_COMPRESSED_ALPHA = GL_COMPRESSED_ALPHA;
static const t_CKINT Chuck_OpenGL_COMPRESSED_LUMINANCE = GL_COMPRESSED_LUMINANCE;
static const t_CKINT Chuck_OpenGL_COMPRESSED_LUMINANCE_ALPHA = GL_COMPRESSED_LUMINANCE_ALPHA;
static const t_CKINT Chuck_OpenGL_COMPRESSED_INTENSITY = GL_COMPRESSED_INTENSITY;
static const t_CKINT Chuck_OpenGL_COMBINE = GL_COMBINE;
static const t_CKINT Chuck_OpenGL_COMBINE_RGB = GL_COMBINE_RGB;
static const t_CKINT Chuck_OpenGL_COMBINE_ALPHA = GL_COMBINE_ALPHA;
static const t_CKINT Chuck_OpenGL_SOURCE0_RGB = GL_SOURCE0_RGB;
static const t_CKINT Chuck_OpenGL_SOURCE1_RGB = GL_SOURCE1_RGB;
static const t_CKINT Chuck_OpenGL_SOURCE2_RGB = GL_SOURCE2_RGB;
static const t_CKINT Chuck_OpenGL_SOURCE0_ALPHA = GL_SOURCE0_ALPHA;
static const t_CKINT Chuck_OpenGL_SOURCE1_ALPHA = GL_SOURCE1_ALPHA;
static const t_CKINT Chuck_OpenGL_SOURCE2_ALPHA = GL_SOURCE2_ALPHA;
static const t_CKINT Chuck_OpenGL_OPERAND0_RGB = GL_OPERAND0_RGB;
static const t_CKINT Chuck_OpenGL_OPERAND1_RGB = GL_OPERAND1_RGB;
static const t_CKINT Chuck_OpenGL_OPERAND2_RGB = GL_OPERAND2_RGB;
static const t_CKINT Chuck_OpenGL_OPERAND0_ALPHA = GL_OPERAND0_ALPHA;
static const t_CKINT Chuck_OpenGL_OPERAND1_ALPHA = GL_OPERAND1_ALPHA;
static const t_CKINT Chuck_OpenGL_OPERAND2_ALPHA = GL_OPERAND2_ALPHA;
static const t_CKINT Chuck_OpenGL_RGB_SCALE = GL_RGB_SCALE;
static const t_CKINT Chuck_OpenGL_ADD_SIGNED = GL_ADD_SIGNED;
static const t_CKINT Chuck_OpenGL_INTERPOLATE = GL_INTERPOLATE;
static const t_CKINT Chuck_OpenGL_SUBTRACT = GL_SUBTRACT;
static const t_CKINT Chuck_OpenGL_CONSTANT = GL_CONSTANT;
static const t_CKINT Chuck_OpenGL_PRIMARY_COLOR = GL_PRIMARY_COLOR;
static const t_CKINT Chuck_OpenGL_PREVIOUS = GL_PREVIOUS;
static const t_CKINT Chuck_OpenGL_DOT3_RGB = GL_DOT3_RGB;
static const t_CKINT Chuck_OpenGL_DOT3_RGBA = GL_DOT3_RGBA;

CK_DLL_MFUN(Chuck_OpenGL_ActiveTexture)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_texture = GET_NEXT_INT(ARGS);

    glActiveTexture(arg_texture);
}


CK_DLL_MFUN(Chuck_OpenGL_SampleCoverage)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_value = GET_NEXT_FLOAT(ARGS);
    t_CKINT arg_invert = GET_NEXT_INT(ARGS);

    glSampleCoverage(arg_value, arg_invert);
}


CK_DLL_MFUN(Chuck_OpenGL_CompressedTexImage3D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_internalformat = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_depth = GET_NEXT_INT(ARGS);
    t_CKINT arg_border = GET_NEXT_INT(ARGS);
    t_CKINT arg_imageSize = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_data_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_data;
    if(_arg_data_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_data_arr = (Chuck_Array4 *) _arg_data_arr;
        GLubyte *arg_data_v = new GLubyte[arg_data_arr->size()];
        chgl->scheduleArrayForCleanup(arg_data_v);
        copy_ckarray4_to_array(arg_data_v, arg_data_arr);
        arg_data = (void *) arg_data_v;
    }
    else if(_arg_data_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_data_arr = (Chuck_Array8 *) _arg_data_arr;
        GLfloat *arg_data_v = new GLfloat[arg_data_arr->size()];
        chgl->scheduleArrayForCleanup(arg_data_v);
        copy_ckarray8_to_array(arg_data_v, arg_data_arr);
        arg_data = (void *) arg_data_v;
    }

    glCompressedTexImage3D(arg_target, arg_level, arg_internalformat, arg_width, arg_height, arg_depth, arg_border, arg_imageSize, arg_data);
}


CK_DLL_MFUN(Chuck_OpenGL_CompressedTexImage2D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_internalformat = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_border = GET_NEXT_INT(ARGS);
    t_CKINT arg_imageSize = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_data_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_data;
    if(_arg_data_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_data_arr = (Chuck_Array4 *) _arg_data_arr;
        GLubyte *arg_data_v = new GLubyte[arg_data_arr->size()];
        chgl->scheduleArrayForCleanup(arg_data_v);
        copy_ckarray4_to_array(arg_data_v, arg_data_arr);
        arg_data = (void *) arg_data_v;
    }
    else if(_arg_data_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_data_arr = (Chuck_Array8 *) _arg_data_arr;
        GLfloat *arg_data_v = new GLfloat[arg_data_arr->size()];
        chgl->scheduleArrayForCleanup(arg_data_v);
        copy_ckarray8_to_array(arg_data_v, arg_data_arr);
        arg_data = (void *) arg_data_v;
    }

    glCompressedTexImage2D(arg_target, arg_level, arg_internalformat, arg_width, arg_height, arg_border, arg_imageSize, arg_data);
}


CK_DLL_MFUN(Chuck_OpenGL_CompressedTexImage1D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_internalformat = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_border = GET_NEXT_INT(ARGS);
    t_CKINT arg_imageSize = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_data_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_data;
    if(_arg_data_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_data_arr = (Chuck_Array4 *) _arg_data_arr;
        GLubyte *arg_data_v = new GLubyte[arg_data_arr->size()];
        chgl->scheduleArrayForCleanup(arg_data_v);
        copy_ckarray4_to_array(arg_data_v, arg_data_arr);
        arg_data = (void *) arg_data_v;
    }
    else if(_arg_data_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_data_arr = (Chuck_Array8 *) _arg_data_arr;
        GLfloat *arg_data_v = new GLfloat[arg_data_arr->size()];
        chgl->scheduleArrayForCleanup(arg_data_v);
        copy_ckarray8_to_array(arg_data_v, arg_data_arr);
        arg_data = (void *) arg_data_v;
    }

    glCompressedTexImage1D(arg_target, arg_level, arg_internalformat, arg_width, arg_border, arg_imageSize, arg_data);
}


CK_DLL_MFUN(Chuck_OpenGL_CompressedTexSubImage3D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_xoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_yoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_zoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_depth = GET_NEXT_INT(ARGS);
    t_CKINT arg_format = GET_NEXT_INT(ARGS);
    t_CKINT arg_imageSize = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_data_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_data;
    if(_arg_data_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_data_arr = (Chuck_Array4 *) _arg_data_arr;
        GLubyte *arg_data_v = new GLubyte[arg_data_arr->size()];
        chgl->scheduleArrayForCleanup(arg_data_v);
        copy_ckarray4_to_array(arg_data_v, arg_data_arr);
        arg_data = (void *) arg_data_v;
    }
    else if(_arg_data_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_data_arr = (Chuck_Array8 *) _arg_data_arr;
        GLfloat *arg_data_v = new GLfloat[arg_data_arr->size()];
        chgl->scheduleArrayForCleanup(arg_data_v);
        copy_ckarray8_to_array(arg_data_v, arg_data_arr);
        arg_data = (void *) arg_data_v;
    }

    glCompressedTexSubImage3D(arg_target, arg_level, arg_xoffset, arg_yoffset, arg_zoffset, arg_width, arg_height, arg_depth, arg_format, arg_imageSize, arg_data);
}


CK_DLL_MFUN(Chuck_OpenGL_CompressedTexSubImage2D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_xoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_yoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_height = GET_NEXT_INT(ARGS);
    t_CKINT arg_format = GET_NEXT_INT(ARGS);
    t_CKINT arg_imageSize = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_data_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_data;
    if(_arg_data_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_data_arr = (Chuck_Array4 *) _arg_data_arr;
        GLubyte *arg_data_v = new GLubyte[arg_data_arr->size()];
        chgl->scheduleArrayForCleanup(arg_data_v);
        copy_ckarray4_to_array(arg_data_v, arg_data_arr);
        arg_data = (void *) arg_data_v;
    }
    else if(_arg_data_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_data_arr = (Chuck_Array8 *) _arg_data_arr;
        GLfloat *arg_data_v = new GLfloat[arg_data_arr->size()];
        chgl->scheduleArrayForCleanup(arg_data_v);
        copy_ckarray8_to_array(arg_data_v, arg_data_arr);
        arg_data = (void *) arg_data_v;
    }

    glCompressedTexSubImage2D(arg_target, arg_level, arg_xoffset, arg_yoffset, arg_width, arg_height, arg_format, arg_imageSize, arg_data);
}


CK_DLL_MFUN(Chuck_OpenGL_CompressedTexSubImage1D)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    t_CKINT arg_xoffset = GET_NEXT_INT(ARGS);
    t_CKINT arg_width = GET_NEXT_INT(ARGS);
    t_CKINT arg_format = GET_NEXT_INT(ARGS);
    t_CKINT arg_imageSize = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_data_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_data;
    if(_arg_data_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_data_arr = (Chuck_Array4 *) _arg_data_arr;
        GLubyte *arg_data_v = new GLubyte[arg_data_arr->size()];
        chgl->scheduleArrayForCleanup(arg_data_v);
        copy_ckarray4_to_array(arg_data_v, arg_data_arr);
        arg_data = (void *) arg_data_v;
    }
    else if(_arg_data_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_data_arr = (Chuck_Array8 *) _arg_data_arr;
        GLfloat *arg_data_v = new GLfloat[arg_data_arr->size()];
        chgl->scheduleArrayForCleanup(arg_data_v);
        copy_ckarray8_to_array(arg_data_v, arg_data_arr);
        arg_data = (void *) arg_data_v;
    }

    glCompressedTexSubImage1D(arg_target, arg_level, arg_xoffset, arg_width, arg_format, arg_imageSize, arg_data);
}


CK_DLL_MFUN(Chuck_OpenGL_GetCompressedTexImage)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_level = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_img_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_img;
    if(_arg_img_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_img_arr = (Chuck_Array4 *) _arg_img_arr;
        GLubyte *arg_img_v = new GLubyte[arg_img_arr->size()];
        chgl->scheduleArrayForCleanup(arg_img_v);
        copy_ckarray4_to_array(arg_img_v, arg_img_arr);
        arg_img = (void *) arg_img_v;
    }
    else if(_arg_img_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_img_arr = (Chuck_Array8 *) _arg_img_arr;
        GLfloat *arg_img_v = new GLfloat[arg_img_arr->size()];
        chgl->scheduleArrayForCleanup(arg_img_v);
        copy_ckarray8_to_array(arg_img_v, arg_img_arr);
        arg_img = (void *) arg_img_v;
    }

    glGetCompressedTexImage(arg_target, arg_level, arg_img);
}


CK_DLL_MFUN(Chuck_OpenGL_ClientActiveTexture)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_texture = GET_NEXT_INT(ARGS);

    glClientActiveTexture(arg_texture);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord1d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_s = GET_NEXT_FLOAT(ARGS);

    glMultiTexCoord1d(arg_target, arg_s);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord1dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glMultiTexCoord1dv(arg_target, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord1f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_s = GET_NEXT_FLOAT(ARGS);

    glMultiTexCoord1f(arg_target, arg_s);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord1fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glMultiTexCoord1fv(arg_target, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord1i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_s = GET_NEXT_INT(ARGS);

    glMultiTexCoord1i(arg_target, arg_s);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord1iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glMultiTexCoord1iv(arg_target, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord1s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_s = GET_NEXT_INT(ARGS);

    glMultiTexCoord1s(arg_target, arg_s);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord1sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glMultiTexCoord1sv(arg_target, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord2d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_s = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_t = GET_NEXT_FLOAT(ARGS);

    glMultiTexCoord2d(arg_target, arg_s, arg_t);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord2dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glMultiTexCoord2dv(arg_target, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord2f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_s = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_t = GET_NEXT_FLOAT(ARGS);

    glMultiTexCoord2f(arg_target, arg_s, arg_t);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord2fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glMultiTexCoord2fv(arg_target, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord2i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_s = GET_NEXT_INT(ARGS);
    t_CKINT arg_t = GET_NEXT_INT(ARGS);

    glMultiTexCoord2i(arg_target, arg_s, arg_t);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord2iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glMultiTexCoord2iv(arg_target, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord2s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_s = GET_NEXT_INT(ARGS);
    t_CKINT arg_t = GET_NEXT_INT(ARGS);

    glMultiTexCoord2s(arg_target, arg_s, arg_t);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord2sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glMultiTexCoord2sv(arg_target, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord3d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_s = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_t = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_r = GET_NEXT_FLOAT(ARGS);

    glMultiTexCoord3d(arg_target, arg_s, arg_t, arg_r);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord3dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glMultiTexCoord3dv(arg_target, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord3f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_s = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_t = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_r = GET_NEXT_FLOAT(ARGS);

    glMultiTexCoord3f(arg_target, arg_s, arg_t, arg_r);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord3fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glMultiTexCoord3fv(arg_target, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord3i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_s = GET_NEXT_INT(ARGS);
    t_CKINT arg_t = GET_NEXT_INT(ARGS);
    t_CKINT arg_r = GET_NEXT_INT(ARGS);

    glMultiTexCoord3i(arg_target, arg_s, arg_t, arg_r);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord3iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glMultiTexCoord3iv(arg_target, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord3s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_s = GET_NEXT_INT(ARGS);
    t_CKINT arg_t = GET_NEXT_INT(ARGS);
    t_CKINT arg_r = GET_NEXT_INT(ARGS);

    glMultiTexCoord3s(arg_target, arg_s, arg_t, arg_r);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord3sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glMultiTexCoord3sv(arg_target, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord4d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_s = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_t = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_r = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_q = GET_NEXT_FLOAT(ARGS);

    glMultiTexCoord4d(arg_target, arg_s, arg_t, arg_r, arg_q);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord4dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glMultiTexCoord4dv(arg_target, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord4f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_s = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_t = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_r = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_q = GET_NEXT_FLOAT(ARGS);

    glMultiTexCoord4f(arg_target, arg_s, arg_t, arg_r, arg_q);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord4fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glMultiTexCoord4fv(arg_target, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord4i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_s = GET_NEXT_INT(ARGS);
    t_CKINT arg_t = GET_NEXT_INT(ARGS);
    t_CKINT arg_r = GET_NEXT_INT(ARGS);
    t_CKINT arg_q = GET_NEXT_INT(ARGS);

    glMultiTexCoord4i(arg_target, arg_s, arg_t, arg_r, arg_q);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord4iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glMultiTexCoord4iv(arg_target, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord4s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_s = GET_NEXT_INT(ARGS);
    t_CKINT arg_t = GET_NEXT_INT(ARGS);
    t_CKINT arg_r = GET_NEXT_INT(ARGS);
    t_CKINT arg_q = GET_NEXT_INT(ARGS);

    glMultiTexCoord4s(arg_target, arg_s, arg_t, arg_r, arg_q);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiTexCoord4sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glMultiTexCoord4sv(arg_target, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_LoadTransposeMatrixf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_m_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_m = new GLfloat[arg_m_arr->size()];
    chgl->scheduleArrayForCleanup(arg_m);
    copy_ckarray8_to_array(arg_m, arg_m_arr);

    glLoadTransposeMatrixf(arg_m);
}


CK_DLL_MFUN(Chuck_OpenGL_LoadTransposeMatrixd)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_m_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_m = new GLdouble[arg_m_arr->size()];
    chgl->scheduleArrayForCleanup(arg_m);
    copy_ckarray8_to_array(arg_m, arg_m_arr);

    glLoadTransposeMatrixd(arg_m);
}


CK_DLL_MFUN(Chuck_OpenGL_MultTransposeMatrixf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_m_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_m = new GLfloat[arg_m_arr->size()];
    chgl->scheduleArrayForCleanup(arg_m);
    copy_ckarray8_to_array(arg_m, arg_m_arr);

    glMultTransposeMatrixf(arg_m);
}


CK_DLL_MFUN(Chuck_OpenGL_MultTransposeMatrixd)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_m_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_m = new GLdouble[arg_m_arr->size()];
    chgl->scheduleArrayForCleanup(arg_m);
    copy_ckarray8_to_array(arg_m, arg_m_arr);

    glMultTransposeMatrixd(arg_m);
}

static const t_CKINT Chuck_OpenGL_BLEND_DST_RGB = GL_BLEND_DST_RGB;
static const t_CKINT Chuck_OpenGL_BLEND_SRC_RGB = GL_BLEND_SRC_RGB;
static const t_CKINT Chuck_OpenGL_BLEND_DST_ALPHA = GL_BLEND_DST_ALPHA;
static const t_CKINT Chuck_OpenGL_BLEND_SRC_ALPHA = GL_BLEND_SRC_ALPHA;
static const t_CKINT Chuck_OpenGL_POINT_FADE_THRESHOLD_SIZE = GL_POINT_FADE_THRESHOLD_SIZE;
static const t_CKINT Chuck_OpenGL_DEPTH_COMPONENT16 = GL_DEPTH_COMPONENT16;
static const t_CKINT Chuck_OpenGL_DEPTH_COMPONENT24 = GL_DEPTH_COMPONENT24;
static const t_CKINT Chuck_OpenGL_DEPTH_COMPONENT32 = GL_DEPTH_COMPONENT32;
static const t_CKINT Chuck_OpenGL_MIRRORED_REPEAT = GL_MIRRORED_REPEAT;
static const t_CKINT Chuck_OpenGL_MAX_TEXTURE_LOD_BIAS = GL_MAX_TEXTURE_LOD_BIAS;
static const t_CKINT Chuck_OpenGL_TEXTURE_LOD_BIAS = GL_TEXTURE_LOD_BIAS;
static const t_CKINT Chuck_OpenGL_INCR_WRAP = GL_INCR_WRAP;
static const t_CKINT Chuck_OpenGL_DECR_WRAP = GL_DECR_WRAP;
static const t_CKINT Chuck_OpenGL_TEXTURE_DEPTH_SIZE = GL_TEXTURE_DEPTH_SIZE;
static const t_CKINT Chuck_OpenGL_TEXTURE_COMPARE_MODE = GL_TEXTURE_COMPARE_MODE;
static const t_CKINT Chuck_OpenGL_TEXTURE_COMPARE_FUNC = GL_TEXTURE_COMPARE_FUNC;
static const t_CKINT Chuck_OpenGL_POINT_SIZE_MIN = GL_POINT_SIZE_MIN;
static const t_CKINT Chuck_OpenGL_POINT_SIZE_MAX = GL_POINT_SIZE_MAX;
static const t_CKINT Chuck_OpenGL_POINT_DISTANCE_ATTENUATION = GL_POINT_DISTANCE_ATTENUATION;
static const t_CKINT Chuck_OpenGL_GENERATE_MIPMAP = GL_GENERATE_MIPMAP;
static const t_CKINT Chuck_OpenGL_GENERATE_MIPMAP_HINT = GL_GENERATE_MIPMAP_HINT;
static const t_CKINT Chuck_OpenGL_FOG_COORDINATE_SOURCE = GL_FOG_COORDINATE_SOURCE;
static const t_CKINT Chuck_OpenGL_FOG_COORDINATE = GL_FOG_COORDINATE;
static const t_CKINT Chuck_OpenGL_FRAGMENT_DEPTH = GL_FRAGMENT_DEPTH;
static const t_CKINT Chuck_OpenGL_CURRENT_FOG_COORDINATE = GL_CURRENT_FOG_COORDINATE;
static const t_CKINT Chuck_OpenGL_FOG_COORDINATE_ARRAY_TYPE = GL_FOG_COORDINATE_ARRAY_TYPE;
static const t_CKINT Chuck_OpenGL_FOG_COORDINATE_ARRAY_STRIDE = GL_FOG_COORDINATE_ARRAY_STRIDE;
static const t_CKINT Chuck_OpenGL_FOG_COORDINATE_ARRAY_POINTER = GL_FOG_COORDINATE_ARRAY_POINTER;
static const t_CKINT Chuck_OpenGL_FOG_COORDINATE_ARRAY = GL_FOG_COORDINATE_ARRAY;
static const t_CKINT Chuck_OpenGL_COLOR_SUM = GL_COLOR_SUM;
static const t_CKINT Chuck_OpenGL_CURRENT_SECONDARY_COLOR = GL_CURRENT_SECONDARY_COLOR;
static const t_CKINT Chuck_OpenGL_SECONDARY_COLOR_ARRAY_SIZE = GL_SECONDARY_COLOR_ARRAY_SIZE;
static const t_CKINT Chuck_OpenGL_SECONDARY_COLOR_ARRAY_TYPE = GL_SECONDARY_COLOR_ARRAY_TYPE;
static const t_CKINT Chuck_OpenGL_SECONDARY_COLOR_ARRAY_STRIDE = GL_SECONDARY_COLOR_ARRAY_STRIDE;
static const t_CKINT Chuck_OpenGL_SECONDARY_COLOR_ARRAY_POINTER = GL_SECONDARY_COLOR_ARRAY_POINTER;
static const t_CKINT Chuck_OpenGL_SECONDARY_COLOR_ARRAY = GL_SECONDARY_COLOR_ARRAY;
static const t_CKINT Chuck_OpenGL_TEXTURE_FILTER_CONTROL = GL_TEXTURE_FILTER_CONTROL;
static const t_CKINT Chuck_OpenGL_DEPTH_TEXTURE_MODE = GL_DEPTH_TEXTURE_MODE;
static const t_CKINT Chuck_OpenGL_COMPARE_R_TO_TEXTURE = GL_COMPARE_R_TO_TEXTURE;

CK_DLL_MFUN(Chuck_OpenGL_BlendFuncSeparate)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_sfactorRGB = GET_NEXT_INT(ARGS);
    t_CKINT arg_dfactorRGB = GET_NEXT_INT(ARGS);
    t_CKINT arg_sfactorAlpha = GET_NEXT_INT(ARGS);
    t_CKINT arg_dfactorAlpha = GET_NEXT_INT(ARGS);

    glBlendFuncSeparate(arg_sfactorRGB, arg_dfactorRGB, arg_sfactorAlpha, arg_dfactorAlpha);
}


CK_DLL_MFUN(Chuck_OpenGL_MultiDrawArrays)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_first_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_first = new GLint[arg_first_arr->size()];
    chgl->scheduleArrayForCleanup(arg_first);
    copy_ckarray4_to_array(arg_first, arg_first_arr);
    Chuck_Array4 *arg_count_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLsizei *arg_count = new GLsizei[arg_count_arr->size()];
    chgl->scheduleArrayForCleanup(arg_count);
    copy_ckarray4_to_array(arg_count, arg_count_arr);
    t_CKINT arg_drawcount = GET_NEXT_INT(ARGS);

    glMultiDrawArrays(arg_mode, arg_first, arg_count, arg_drawcount);
}


CK_DLL_MFUN(Chuck_OpenGL_PointParameterf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_param = GET_NEXT_FLOAT(ARGS);

    glPointParameterf(arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_PointParameterfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glPointParameterfv(arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_PointParameteri)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    t_CKINT arg_param = GET_NEXT_INT(ARGS);

    glPointParameteri(arg_pname, arg_param);
}


CK_DLL_MFUN(Chuck_OpenGL_PointParameteriv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glPointParameteriv(arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_FogCoordf)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_coord = GET_NEXT_FLOAT(ARGS);

    glFogCoordf(arg_coord);
}


CK_DLL_MFUN(Chuck_OpenGL_FogCoordfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_coord_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_coord = new GLfloat[arg_coord_arr->size()];
    chgl->scheduleArrayForCleanup(arg_coord);
    copy_ckarray8_to_array(arg_coord, arg_coord_arr);

    glFogCoordfv(arg_coord);
}


CK_DLL_MFUN(Chuck_OpenGL_FogCoordd)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_coord = GET_NEXT_FLOAT(ARGS);

    glFogCoordd(arg_coord);
}


CK_DLL_MFUN(Chuck_OpenGL_FogCoorddv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_coord_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_coord = new GLdouble[arg_coord_arr->size()];
    chgl->scheduleArrayForCleanup(arg_coord);
    copy_ckarray8_to_array(arg_coord, arg_coord_arr);

    glFogCoorddv(arg_coord);
}


CK_DLL_MFUN(Chuck_OpenGL_FogCoordPointer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    t_CKINT arg_stride = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pointer_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pointer;
    if(_arg_pointer_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pointer_arr = (Chuck_Array4 *) _arg_pointer_arr;
        GLubyte *arg_pointer_v = new GLubyte[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray4_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }
    else if(_arg_pointer_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pointer_arr = (Chuck_Array8 *) _arg_pointer_arr;
        GLfloat *arg_pointer_v = new GLfloat[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray8_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }

    glFogCoordPointer(arg_type, arg_stride, arg_pointer);
}


CK_DLL_MFUN(Chuck_OpenGL_SecondaryColor3b)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);

    glSecondaryColor3b(arg_red, arg_green, arg_blue);
}


CK_DLL_MFUN(Chuck_OpenGL_SecondaryColor3bv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLbyte *arg_v = new GLbyte[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glSecondaryColor3bv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_SecondaryColor3d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_red = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_green = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_blue = GET_NEXT_FLOAT(ARGS);

    glSecondaryColor3d(arg_red, arg_green, arg_blue);
}


CK_DLL_MFUN(Chuck_OpenGL_SecondaryColor3dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glSecondaryColor3dv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_SecondaryColor3f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_red = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_green = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_blue = GET_NEXT_FLOAT(ARGS);

    glSecondaryColor3f(arg_red, arg_green, arg_blue);
}


CK_DLL_MFUN(Chuck_OpenGL_SecondaryColor3fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glSecondaryColor3fv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_SecondaryColor3i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);

    glSecondaryColor3i(arg_red, arg_green, arg_blue);
}


CK_DLL_MFUN(Chuck_OpenGL_SecondaryColor3iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glSecondaryColor3iv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_SecondaryColor3s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);

    glSecondaryColor3s(arg_red, arg_green, arg_blue);
}


CK_DLL_MFUN(Chuck_OpenGL_SecondaryColor3sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glSecondaryColor3sv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_SecondaryColor3ub)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);

    glSecondaryColor3ub(arg_red, arg_green, arg_blue);
}


CK_DLL_MFUN(Chuck_OpenGL_SecondaryColor3ubv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLubyte *arg_v = new GLubyte[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glSecondaryColor3ubv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_SecondaryColor3ui)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);

    glSecondaryColor3ui(arg_red, arg_green, arg_blue);
}


CK_DLL_MFUN(Chuck_OpenGL_SecondaryColor3uiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_v = new GLuint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glSecondaryColor3uiv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_SecondaryColor3us)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_red = GET_NEXT_INT(ARGS);
    t_CKINT arg_green = GET_NEXT_INT(ARGS);
    t_CKINT arg_blue = GET_NEXT_INT(ARGS);

    glSecondaryColor3us(arg_red, arg_green, arg_blue);
}


CK_DLL_MFUN(Chuck_OpenGL_SecondaryColor3usv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLushort *arg_v = new GLushort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glSecondaryColor3usv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_SecondaryColorPointer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_size = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    t_CKINT arg_stride = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pointer_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pointer;
    if(_arg_pointer_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pointer_arr = (Chuck_Array4 *) _arg_pointer_arr;
        GLubyte *arg_pointer_v = new GLubyte[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray4_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }
    else if(_arg_pointer_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pointer_arr = (Chuck_Array8 *) _arg_pointer_arr;
        GLfloat *arg_pointer_v = new GLfloat[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray8_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }

    glSecondaryColorPointer(arg_size, arg_type, arg_stride, arg_pointer);
}


CK_DLL_MFUN(Chuck_OpenGL_WindowPos2d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);

    glWindowPos2d(arg_x, arg_y);
}


CK_DLL_MFUN(Chuck_OpenGL_WindowPos2dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glWindowPos2dv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_WindowPos2f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);

    glWindowPos2f(arg_x, arg_y);
}


CK_DLL_MFUN(Chuck_OpenGL_WindowPos2fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glWindowPos2fv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_WindowPos2i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);

    glWindowPos2i(arg_x, arg_y);
}


CK_DLL_MFUN(Chuck_OpenGL_WindowPos2iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glWindowPos2iv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_WindowPos2s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);

    glWindowPos2s(arg_x, arg_y);
}


CK_DLL_MFUN(Chuck_OpenGL_WindowPos2sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glWindowPos2sv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_WindowPos3d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);

    glWindowPos3d(arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_WindowPos3dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glWindowPos3dv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_WindowPos3f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);

    glWindowPos3f(arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_WindowPos3fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glWindowPos3fv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_WindowPos3i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_z = GET_NEXT_INT(ARGS);

    glWindowPos3i(arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_WindowPos3iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glWindowPos3iv(arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_WindowPos3s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_z = GET_NEXT_INT(ARGS);

    glWindowPos3s(arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_WindowPos3sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glWindowPos3sv(arg_v);
}

static const t_CKINT Chuck_OpenGL_FUNC_ADD = GL_FUNC_ADD;
static const t_CKINT Chuck_OpenGL_FUNC_SUBTRACT = GL_FUNC_SUBTRACT;
static const t_CKINT Chuck_OpenGL_FUNC_REVERSE_SUBTRACT = GL_FUNC_REVERSE_SUBTRACT;
static const t_CKINT Chuck_OpenGL_MIN = GL_MIN;
static const t_CKINT Chuck_OpenGL_MAX = GL_MAX;
static const t_CKINT Chuck_OpenGL_CONSTANT_COLOR = GL_CONSTANT_COLOR;
static const t_CKINT Chuck_OpenGL_ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR;
static const t_CKINT Chuck_OpenGL_CONSTANT_ALPHA = GL_CONSTANT_ALPHA;
static const t_CKINT Chuck_OpenGL_ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA;

CK_DLL_MFUN(Chuck_OpenGL_BlendColor)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKFLOAT arg_red = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_green = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_blue = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_alpha = GET_NEXT_FLOAT(ARGS);

    glBlendColor(arg_red, arg_green, arg_blue, arg_alpha);
}


CK_DLL_MFUN(Chuck_OpenGL_BlendEquation)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_mode = GET_NEXT_INT(ARGS);

    glBlendEquation(arg_mode);
}

static const t_CKINT Chuck_OpenGL_BUFFER_SIZE = GL_BUFFER_SIZE;
static const t_CKINT Chuck_OpenGL_BUFFER_USAGE = GL_BUFFER_USAGE;
static const t_CKINT Chuck_OpenGL_QUERY_COUNTER_BITS = GL_QUERY_COUNTER_BITS;
static const t_CKINT Chuck_OpenGL_CURRENT_QUERY = GL_CURRENT_QUERY;
static const t_CKINT Chuck_OpenGL_QUERY_RESULT = GL_QUERY_RESULT;
static const t_CKINT Chuck_OpenGL_QUERY_RESULT_AVAILABLE = GL_QUERY_RESULT_AVAILABLE;
static const t_CKINT Chuck_OpenGL_ARRAY_BUFFER = GL_ARRAY_BUFFER;
static const t_CKINT Chuck_OpenGL_ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER;
static const t_CKINT Chuck_OpenGL_ARRAY_BUFFER_BINDING = GL_ARRAY_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_ELEMENT_ARRAY_BUFFER_BINDING = GL_ELEMENT_ARRAY_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING = GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_READ_ONLY = GL_READ_ONLY;
static const t_CKINT Chuck_OpenGL_WRITE_ONLY = GL_WRITE_ONLY;
static const t_CKINT Chuck_OpenGL_READ_WRITE = GL_READ_WRITE;
static const t_CKINT Chuck_OpenGL_BUFFER_ACCESS = GL_BUFFER_ACCESS;
static const t_CKINT Chuck_OpenGL_BUFFER_MAPPED = GL_BUFFER_MAPPED;
static const t_CKINT Chuck_OpenGL_BUFFER_MAP_POINTER = GL_BUFFER_MAP_POINTER;
static const t_CKINT Chuck_OpenGL_STREAM_DRAW = GL_STREAM_DRAW;
static const t_CKINT Chuck_OpenGL_STREAM_READ = GL_STREAM_READ;
static const t_CKINT Chuck_OpenGL_STREAM_COPY = GL_STREAM_COPY;
static const t_CKINT Chuck_OpenGL_STATIC_DRAW = GL_STATIC_DRAW;
static const t_CKINT Chuck_OpenGL_STATIC_READ = GL_STATIC_READ;
static const t_CKINT Chuck_OpenGL_STATIC_COPY = GL_STATIC_COPY;
static const t_CKINT Chuck_OpenGL_DYNAMIC_DRAW = GL_DYNAMIC_DRAW;
static const t_CKINT Chuck_OpenGL_DYNAMIC_READ = GL_DYNAMIC_READ;
static const t_CKINT Chuck_OpenGL_DYNAMIC_COPY = GL_DYNAMIC_COPY;
static const t_CKINT Chuck_OpenGL_SAMPLES_PASSED = GL_SAMPLES_PASSED;
static const t_CKINT Chuck_OpenGL_SRC1_ALPHA = GL_SRC1_ALPHA;
static const t_CKINT Chuck_OpenGL_VERTEX_ARRAY_BUFFER_BINDING = GL_VERTEX_ARRAY_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_NORMAL_ARRAY_BUFFER_BINDING = GL_NORMAL_ARRAY_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_COLOR_ARRAY_BUFFER_BINDING = GL_COLOR_ARRAY_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_INDEX_ARRAY_BUFFER_BINDING = GL_INDEX_ARRAY_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_TEXTURE_COORD_ARRAY_BUFFER_BINDING = GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_EDGE_FLAG_ARRAY_BUFFER_BINDING = GL_EDGE_FLAG_ARRAY_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING = GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_FOG_COORDINATE_ARRAY_BUFFER_BINDING = GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_WEIGHT_ARRAY_BUFFER_BINDING = GL_WEIGHT_ARRAY_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_FOG_COORD_SRC = GL_FOG_COORD_SRC;
static const t_CKINT Chuck_OpenGL_FOG_COORD = GL_FOG_COORD;
static const t_CKINT Chuck_OpenGL_CURRENT_FOG_COORD = GL_CURRENT_FOG_COORD;
static const t_CKINT Chuck_OpenGL_FOG_COORD_ARRAY_TYPE = GL_FOG_COORD_ARRAY_TYPE;
static const t_CKINT Chuck_OpenGL_FOG_COORD_ARRAY_STRIDE = GL_FOG_COORD_ARRAY_STRIDE;
static const t_CKINT Chuck_OpenGL_FOG_COORD_ARRAY_POINTER = GL_FOG_COORD_ARRAY_POINTER;
static const t_CKINT Chuck_OpenGL_FOG_COORD_ARRAY = GL_FOG_COORD_ARRAY;
static const t_CKINT Chuck_OpenGL_FOG_COORD_ARRAY_BUFFER_BINDING = GL_FOG_COORD_ARRAY_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_SRC0_RGB = GL_SRC0_RGB;
static const t_CKINT Chuck_OpenGL_SRC1_RGB = GL_SRC1_RGB;
static const t_CKINT Chuck_OpenGL_SRC2_RGB = GL_SRC2_RGB;
static const t_CKINT Chuck_OpenGL_SRC0_ALPHA = GL_SRC0_ALPHA;
static const t_CKINT Chuck_OpenGL_SRC2_ALPHA = GL_SRC2_ALPHA;

CK_DLL_MFUN(Chuck_OpenGL_GenQueries)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_ids_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_ids = new GLuint[arg_ids_arr->size()];
    chgl->scheduleArrayForCleanup(arg_ids);
    copy_ckarray4_to_array(arg_ids, arg_ids_arr);

    glGenQueries(arg_n, arg_ids);
}


CK_DLL_MFUN(Chuck_OpenGL_DeleteQueries)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_ids_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_ids = new GLuint[arg_ids_arr->size()];
    chgl->scheduleArrayForCleanup(arg_ids);
    copy_ckarray4_to_array(arg_ids, arg_ids_arr);

    glDeleteQueries(arg_n, arg_ids);
}


CK_DLL_MFUN(Chuck_OpenGL_IsQuery)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_id = GET_NEXT_INT(ARGS);

    RETURN->v_int = glIsQuery(arg_id);
}


CK_DLL_MFUN(Chuck_OpenGL_BeginQuery)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_id = GET_NEXT_INT(ARGS);

    glBeginQuery(arg_target, arg_id);
}


CK_DLL_MFUN(Chuck_OpenGL_EndQuery)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);

    glEndQuery(arg_target);
}


CK_DLL_MFUN(Chuck_OpenGL_GetQueryiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetQueryiv(arg_target, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetQueryObjectiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_id = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetQueryObjectiv(arg_id, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetQueryObjectuiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_id = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_params = new GLuint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetQueryObjectuiv(arg_id, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_BindBuffer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_buffer = GET_NEXT_INT(ARGS);

    glBindBuffer(arg_target, arg_buffer);
}


CK_DLL_MFUN(Chuck_OpenGL_DeleteBuffers)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_buffers_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_buffers = new GLuint[arg_buffers_arr->size()];
    chgl->scheduleArrayForCleanup(arg_buffers);
    copy_ckarray4_to_array(arg_buffers, arg_buffers_arr);

    glDeleteBuffers(arg_n, arg_buffers);
}


CK_DLL_MFUN(Chuck_OpenGL_GenBuffers)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_buffers_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_buffers = new GLuint[arg_buffers_arr->size()];
    chgl->scheduleArrayForCleanup(arg_buffers);
    copy_ckarray4_to_array(arg_buffers, arg_buffers_arr);

    glGenBuffers(arg_n, arg_buffers);
}


CK_DLL_MFUN(Chuck_OpenGL_IsBuffer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_buffer = GET_NEXT_INT(ARGS);

    RETURN->v_int = glIsBuffer(arg_buffer);
}


CK_DLL_MFUN(Chuck_OpenGL_UnmapBuffer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);

    RETURN->v_int = glUnmapBuffer(arg_target);
}


CK_DLL_MFUN(Chuck_OpenGL_GetBufferParameteriv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_target = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetBufferParameteriv(arg_target, arg_pname, arg_params);
}

static const t_CKINT Chuck_OpenGL_BLEND_EQUATION_RGB = GL_BLEND_EQUATION_RGB;
static const t_CKINT Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_ENABLED = GL_VERTEX_ATTRIB_ARRAY_ENABLED;
static const t_CKINT Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_SIZE = GL_VERTEX_ATTRIB_ARRAY_SIZE;
static const t_CKINT Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_STRIDE = GL_VERTEX_ATTRIB_ARRAY_STRIDE;
static const t_CKINT Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_TYPE = GL_VERTEX_ATTRIB_ARRAY_TYPE;
static const t_CKINT Chuck_OpenGL_CURRENT_VERTEX_ATTRIB = GL_CURRENT_VERTEX_ATTRIB;
static const t_CKINT Chuck_OpenGL_VERTEX_PROGRAM_POINT_SIZE = GL_VERTEX_PROGRAM_POINT_SIZE;
static const t_CKINT Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_POINTER = GL_VERTEX_ATTRIB_ARRAY_POINTER;
static const t_CKINT Chuck_OpenGL_STENCIL_BACK_FUNC = GL_STENCIL_BACK_FUNC;
static const t_CKINT Chuck_OpenGL_STENCIL_BACK_FAIL = GL_STENCIL_BACK_FAIL;
static const t_CKINT Chuck_OpenGL_STENCIL_BACK_PASS_DEPTH_FAIL = GL_STENCIL_BACK_PASS_DEPTH_FAIL;
static const t_CKINT Chuck_OpenGL_STENCIL_BACK_PASS_DEPTH_PASS = GL_STENCIL_BACK_PASS_DEPTH_PASS;
static const t_CKINT Chuck_OpenGL_MAX_DRAW_BUFFERS = GL_MAX_DRAW_BUFFERS;
static const t_CKINT Chuck_OpenGL_DRAW_BUFFER0 = GL_DRAW_BUFFER0;
static const t_CKINT Chuck_OpenGL_DRAW_BUFFER1 = GL_DRAW_BUFFER1;
static const t_CKINT Chuck_OpenGL_DRAW_BUFFER2 = GL_DRAW_BUFFER2;
static const t_CKINT Chuck_OpenGL_DRAW_BUFFER3 = GL_DRAW_BUFFER3;
static const t_CKINT Chuck_OpenGL_DRAW_BUFFER4 = GL_DRAW_BUFFER4;
static const t_CKINT Chuck_OpenGL_DRAW_BUFFER5 = GL_DRAW_BUFFER5;
static const t_CKINT Chuck_OpenGL_DRAW_BUFFER6 = GL_DRAW_BUFFER6;
static const t_CKINT Chuck_OpenGL_DRAW_BUFFER7 = GL_DRAW_BUFFER7;
static const t_CKINT Chuck_OpenGL_DRAW_BUFFER8 = GL_DRAW_BUFFER8;
static const t_CKINT Chuck_OpenGL_DRAW_BUFFER9 = GL_DRAW_BUFFER9;
static const t_CKINT Chuck_OpenGL_DRAW_BUFFER10 = GL_DRAW_BUFFER10;
static const t_CKINT Chuck_OpenGL_DRAW_BUFFER11 = GL_DRAW_BUFFER11;
static const t_CKINT Chuck_OpenGL_DRAW_BUFFER12 = GL_DRAW_BUFFER12;
static const t_CKINT Chuck_OpenGL_DRAW_BUFFER13 = GL_DRAW_BUFFER13;
static const t_CKINT Chuck_OpenGL_DRAW_BUFFER14 = GL_DRAW_BUFFER14;
static const t_CKINT Chuck_OpenGL_DRAW_BUFFER15 = GL_DRAW_BUFFER15;
static const t_CKINT Chuck_OpenGL_BLEND_EQUATION_ALPHA = GL_BLEND_EQUATION_ALPHA;
static const t_CKINT Chuck_OpenGL_MAX_VERTEX_ATTRIBS = GL_MAX_VERTEX_ATTRIBS;
static const t_CKINT Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_NORMALIZED = GL_VERTEX_ATTRIB_ARRAY_NORMALIZED;
static const t_CKINT Chuck_OpenGL_MAX_TEXTURE_IMAGE_UNITS = GL_MAX_TEXTURE_IMAGE_UNITS;
static const t_CKINT Chuck_OpenGL_FRAGMENT_SHADER = GL_FRAGMENT_SHADER;
static const t_CKINT Chuck_OpenGL_VERTEX_SHADER = GL_VERTEX_SHADER;
static const t_CKINT Chuck_OpenGL_MAX_FRAGMENT_UNIFORM_COMPONENTS = GL_MAX_FRAGMENT_UNIFORM_COMPONENTS;
static const t_CKINT Chuck_OpenGL_MAX_VERTEX_UNIFORM_COMPONENTS = GL_MAX_VERTEX_UNIFORM_COMPONENTS;
static const t_CKINT Chuck_OpenGL_MAX_VARYING_FLOATS = GL_MAX_VARYING_FLOATS;
static const t_CKINT Chuck_OpenGL_MAX_VERTEX_TEXTURE_IMAGE_UNITS = GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS;
static const t_CKINT Chuck_OpenGL_MAX_COMBINED_TEXTURE_IMAGE_UNITS = GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;
static const t_CKINT Chuck_OpenGL_SHADER_TYPE = GL_SHADER_TYPE;
static const t_CKINT Chuck_OpenGL_FLOAT_VEC2 = GL_FLOAT_VEC2;
static const t_CKINT Chuck_OpenGL_FLOAT_VEC3 = GL_FLOAT_VEC3;
static const t_CKINT Chuck_OpenGL_FLOAT_VEC4 = GL_FLOAT_VEC4;
static const t_CKINT Chuck_OpenGL_INT_VEC2 = GL_INT_VEC2;
static const t_CKINT Chuck_OpenGL_INT_VEC3 = GL_INT_VEC3;
static const t_CKINT Chuck_OpenGL_INT_VEC4 = GL_INT_VEC4;
static const t_CKINT Chuck_OpenGL_BOOL = GL_BOOL;
static const t_CKINT Chuck_OpenGL_BOOL_VEC2 = GL_BOOL_VEC2;
static const t_CKINT Chuck_OpenGL_BOOL_VEC3 = GL_BOOL_VEC3;
static const t_CKINT Chuck_OpenGL_BOOL_VEC4 = GL_BOOL_VEC4;
static const t_CKINT Chuck_OpenGL_FLOAT_MAT2 = GL_FLOAT_MAT2;
static const t_CKINT Chuck_OpenGL_FLOAT_MAT3 = GL_FLOAT_MAT3;
static const t_CKINT Chuck_OpenGL_FLOAT_MAT4 = GL_FLOAT_MAT4;
static const t_CKINT Chuck_OpenGL_SAMPLER_1D = GL_SAMPLER_1D;
static const t_CKINT Chuck_OpenGL_SAMPLER_2D = GL_SAMPLER_2D;
static const t_CKINT Chuck_OpenGL_SAMPLER_3D = GL_SAMPLER_3D;
static const t_CKINT Chuck_OpenGL_SAMPLER_CUBE = GL_SAMPLER_CUBE;
static const t_CKINT Chuck_OpenGL_SAMPLER_1D_SHADOW = GL_SAMPLER_1D_SHADOW;
static const t_CKINT Chuck_OpenGL_SAMPLER_2D_SHADOW = GL_SAMPLER_2D_SHADOW;
static const t_CKINT Chuck_OpenGL_DELETE_STATUS = GL_DELETE_STATUS;
static const t_CKINT Chuck_OpenGL_COMPILE_STATUS = GL_COMPILE_STATUS;
static const t_CKINT Chuck_OpenGL_LINK_STATUS = GL_LINK_STATUS;
static const t_CKINT Chuck_OpenGL_VALIDATE_STATUS = GL_VALIDATE_STATUS;
static const t_CKINT Chuck_OpenGL_INFO_LOG_LENGTH = GL_INFO_LOG_LENGTH;
static const t_CKINT Chuck_OpenGL_ATTACHED_SHADERS = GL_ATTACHED_SHADERS;
static const t_CKINT Chuck_OpenGL_ACTIVE_UNIFORMS = GL_ACTIVE_UNIFORMS;
static const t_CKINT Chuck_OpenGL_ACTIVE_UNIFORM_MAX_LENGTH = GL_ACTIVE_UNIFORM_MAX_LENGTH;
static const t_CKINT Chuck_OpenGL_SHADER_SOURCE_LENGTH = GL_SHADER_SOURCE_LENGTH;
static const t_CKINT Chuck_OpenGL_ACTIVE_ATTRIBUTES = GL_ACTIVE_ATTRIBUTES;
static const t_CKINT Chuck_OpenGL_ACTIVE_ATTRIBUTE_MAX_LENGTH = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH;
static const t_CKINT Chuck_OpenGL_FRAGMENT_SHADER_DERIVATIVE_HINT = GL_FRAGMENT_SHADER_DERIVATIVE_HINT;
static const t_CKINT Chuck_OpenGL_SHADING_LANGUAGE_VERSION = GL_SHADING_LANGUAGE_VERSION;
static const t_CKINT Chuck_OpenGL_CURRENT_PROGRAM = GL_CURRENT_PROGRAM;
static const t_CKINT Chuck_OpenGL_POINT_SPRITE_COORD_ORIGIN = GL_POINT_SPRITE_COORD_ORIGIN;
static const t_CKINT Chuck_OpenGL_LOWER_LEFT = GL_LOWER_LEFT;
static const t_CKINT Chuck_OpenGL_UPPER_LEFT = GL_UPPER_LEFT;
static const t_CKINT Chuck_OpenGL_STENCIL_BACK_REF = GL_STENCIL_BACK_REF;
static const t_CKINT Chuck_OpenGL_STENCIL_BACK_VALUE_MASK = GL_STENCIL_BACK_VALUE_MASK;
static const t_CKINT Chuck_OpenGL_STENCIL_BACK_WRITEMASK = GL_STENCIL_BACK_WRITEMASK;
static const t_CKINT Chuck_OpenGL_VERTEX_PROGRAM_TWO_SIDE = GL_VERTEX_PROGRAM_TWO_SIDE;
static const t_CKINT Chuck_OpenGL_POINT_SPRITE = GL_POINT_SPRITE;
static const t_CKINT Chuck_OpenGL_COORD_REPLACE = GL_COORD_REPLACE;
static const t_CKINT Chuck_OpenGL_MAX_TEXTURE_COORDS = GL_MAX_TEXTURE_COORDS;

CK_DLL_MFUN(Chuck_OpenGL_BlendEquationSeparate)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_modeRGB = GET_NEXT_INT(ARGS);
    t_CKINT arg_modeAlpha = GET_NEXT_INT(ARGS);

    glBlendEquationSeparate(arg_modeRGB, arg_modeAlpha);
}


CK_DLL_MFUN(Chuck_OpenGL_DrawBuffers)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_n = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_bufs_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLenum *arg_bufs = new GLenum[arg_bufs_arr->size()];
    chgl->scheduleArrayForCleanup(arg_bufs);
    copy_ckarray4_to_array(arg_bufs, arg_bufs_arr);

    glDrawBuffers(arg_n, arg_bufs);
}


CK_DLL_MFUN(Chuck_OpenGL_StencilOpSeparate)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_face = GET_NEXT_INT(ARGS);
    t_CKINT arg_sfail = GET_NEXT_INT(ARGS);
    t_CKINT arg_dpfail = GET_NEXT_INT(ARGS);
    t_CKINT arg_dppass = GET_NEXT_INT(ARGS);

    glStencilOpSeparate(arg_face, arg_sfail, arg_dpfail, arg_dppass);
}


CK_DLL_MFUN(Chuck_OpenGL_StencilFuncSeparate)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_face = GET_NEXT_INT(ARGS);
    t_CKINT arg_func = GET_NEXT_INT(ARGS);
    t_CKINT arg_ref = GET_NEXT_INT(ARGS);
    t_CKINT arg_mask = GET_NEXT_INT(ARGS);

    glStencilFuncSeparate(arg_face, arg_func, arg_ref, arg_mask);
}


CK_DLL_MFUN(Chuck_OpenGL_StencilMaskSeparate)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_face = GET_NEXT_INT(ARGS);
    t_CKINT arg_mask = GET_NEXT_INT(ARGS);

    glStencilMaskSeparate(arg_face, arg_mask);
}


CK_DLL_MFUN(Chuck_OpenGL_AttachShader)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_shader = GET_NEXT_INT(ARGS);

    glAttachShader(arg_program, arg_shader);
}


CK_DLL_MFUN(Chuck_OpenGL_BindAttribLocation)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_name_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLchar *arg_name = new GLchar[arg_name_arr->size()];
    chgl->scheduleArrayForCleanup(arg_name);
    copy_ckarray4_to_array(arg_name, arg_name_arr);

    glBindAttribLocation(arg_program, arg_index, arg_name);
}


CK_DLL_MFUN(Chuck_OpenGL_CompileShader)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_shader = GET_NEXT_INT(ARGS);

    glCompileShader(arg_shader);
}


CK_DLL_MFUN(Chuck_OpenGL_CreateProgram)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    

    RETURN->v_int = glCreateProgram();
}


CK_DLL_MFUN(Chuck_OpenGL_CreateShader)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_type = GET_NEXT_INT(ARGS);

    RETURN->v_int = glCreateShader(arg_type);
}


CK_DLL_MFUN(Chuck_OpenGL_DeleteProgram)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);

    glDeleteProgram(arg_program);
}


CK_DLL_MFUN(Chuck_OpenGL_DeleteShader)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_shader = GET_NEXT_INT(ARGS);

    glDeleteShader(arg_shader);
}


CK_DLL_MFUN(Chuck_OpenGL_DetachShader)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_shader = GET_NEXT_INT(ARGS);

    glDetachShader(arg_program, arg_shader);
}


CK_DLL_MFUN(Chuck_OpenGL_DisableVertexAttribArray)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);

    glDisableVertexAttribArray(arg_index);
}


CK_DLL_MFUN(Chuck_OpenGL_EnableVertexAttribArray)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);

    glEnableVertexAttribArray(arg_index);
}


CK_DLL_MFUN(Chuck_OpenGL_GetActiveAttrib)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKINT arg_bufSize = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_length_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLsizei *arg_length = new GLsizei[arg_length_arr->size()];
    chgl->scheduleArrayForCleanup(arg_length);
    copy_ckarray4_to_array(arg_length, arg_length_arr);
    Chuck_Array4 *arg_size_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_size = new GLint[arg_size_arr->size()];
    chgl->scheduleArrayForCleanup(arg_size);
    copy_ckarray4_to_array(arg_size, arg_size_arr);
    Chuck_Array4 *arg_type_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLenum *arg_type = new GLenum[arg_type_arr->size()];
    chgl->scheduleArrayForCleanup(arg_type);
    copy_ckarray4_to_array(arg_type, arg_type_arr);
    Chuck_Array4 *arg_name_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLchar *arg_name = new GLchar[arg_name_arr->size()];
    chgl->scheduleArrayForCleanup(arg_name);
    copy_ckarray4_to_array(arg_name, arg_name_arr);

    glGetActiveAttrib(arg_program, arg_index, arg_bufSize, arg_length, arg_size, arg_type, arg_name);
}


CK_DLL_MFUN(Chuck_OpenGL_GetActiveUniform)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKINT arg_bufSize = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_length_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLsizei *arg_length = new GLsizei[arg_length_arr->size()];
    chgl->scheduleArrayForCleanup(arg_length);
    copy_ckarray4_to_array(arg_length, arg_length_arr);
    Chuck_Array4 *arg_size_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_size = new GLint[arg_size_arr->size()];
    chgl->scheduleArrayForCleanup(arg_size);
    copy_ckarray4_to_array(arg_size, arg_size_arr);
    Chuck_Array4 *arg_type_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLenum *arg_type = new GLenum[arg_type_arr->size()];
    chgl->scheduleArrayForCleanup(arg_type);
    copy_ckarray4_to_array(arg_type, arg_type_arr);
    Chuck_Array4 *arg_name_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLchar *arg_name = new GLchar[arg_name_arr->size()];
    chgl->scheduleArrayForCleanup(arg_name);
    copy_ckarray4_to_array(arg_name, arg_name_arr);

    glGetActiveUniform(arg_program, arg_index, arg_bufSize, arg_length, arg_size, arg_type, arg_name);
}


CK_DLL_MFUN(Chuck_OpenGL_GetAttachedShaders)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_maxCount = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_count_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLsizei *arg_count = new GLsizei[arg_count_arr->size()];
    chgl->scheduleArrayForCleanup(arg_count);
    copy_ckarray4_to_array(arg_count, arg_count_arr);
    Chuck_Array4 *arg_shaders_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_shaders = new GLuint[arg_shaders_arr->size()];
    chgl->scheduleArrayForCleanup(arg_shaders);
    copy_ckarray4_to_array(arg_shaders, arg_shaders_arr);

    glGetAttachedShaders(arg_program, arg_maxCount, arg_count, arg_shaders);
}


CK_DLL_MFUN(Chuck_OpenGL_GetAttribLocation)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_name_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLchar *arg_name = new GLchar[arg_name_arr->size()];
    chgl->scheduleArrayForCleanup(arg_name);
    copy_ckarray4_to_array(arg_name, arg_name_arr);

    RETURN->v_int = glGetAttribLocation(arg_program, arg_name);
}


CK_DLL_MFUN(Chuck_OpenGL_GetProgramiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetProgramiv(arg_program, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetProgramInfoLog)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_bufSize = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_length_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLsizei *arg_length = new GLsizei[arg_length_arr->size()];
    chgl->scheduleArrayForCleanup(arg_length);
    copy_ckarray4_to_array(arg_length, arg_length_arr);
    Chuck_Array4 *arg_infoLog_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLchar *arg_infoLog = new GLchar[arg_infoLog_arr->size()];
    chgl->scheduleArrayForCleanup(arg_infoLog);
    copy_ckarray4_to_array(arg_infoLog, arg_infoLog_arr);

    glGetProgramInfoLog(arg_program, arg_bufSize, arg_length, arg_infoLog);
}


CK_DLL_MFUN(Chuck_OpenGL_GetShaderiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_shader = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetShaderiv(arg_shader, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetShaderInfoLog)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_shader = GET_NEXT_INT(ARGS);
    t_CKINT arg_bufSize = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_length_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLsizei *arg_length = new GLsizei[arg_length_arr->size()];
    chgl->scheduleArrayForCleanup(arg_length);
    copy_ckarray4_to_array(arg_length, arg_length_arr);
    Chuck_Array4 *arg_infoLog_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLchar *arg_infoLog = new GLchar[arg_infoLog_arr->size()];
    chgl->scheduleArrayForCleanup(arg_infoLog);
    copy_ckarray4_to_array(arg_infoLog, arg_infoLog_arr);

    glGetShaderInfoLog(arg_shader, arg_bufSize, arg_length, arg_infoLog);
}


CK_DLL_MFUN(Chuck_OpenGL_GetShaderSource)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_shader = GET_NEXT_INT(ARGS);
    t_CKINT arg_bufSize = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_length_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLsizei *arg_length = new GLsizei[arg_length_arr->size()];
    chgl->scheduleArrayForCleanup(arg_length);
    copy_ckarray4_to_array(arg_length, arg_length_arr);
    Chuck_Array4 *arg_source_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLchar *arg_source = new GLchar[arg_source_arr->size()];
    chgl->scheduleArrayForCleanup(arg_source);
    copy_ckarray4_to_array(arg_source, arg_source_arr);

    glGetShaderSource(arg_shader, arg_bufSize, arg_length, arg_source);
}


CK_DLL_MFUN(Chuck_OpenGL_GetUniformLocation)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_name_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLchar *arg_name = new GLchar[arg_name_arr->size()];
    chgl->scheduleArrayForCleanup(arg_name);
    copy_ckarray4_to_array(arg_name, arg_name_arr);

    RETURN->v_int = glGetUniformLocation(arg_program, arg_name);
}


CK_DLL_MFUN(Chuck_OpenGL_GetUniformfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glGetUniformfv(arg_program, arg_location, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetUniformiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetUniformiv(arg_program, arg_location, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetVertexAttribdv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_params = new GLdouble[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glGetVertexAttribdv(arg_index, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetVertexAttribfv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_params_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_params = new GLfloat[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray8_to_array(arg_params, arg_params_arr);

    glGetVertexAttribfv(arg_index, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_GetVertexAttribiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKINT arg_pname = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_params_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_params = new GLint[arg_params_arr->size()];
    chgl->scheduleArrayForCleanup(arg_params);
    copy_ckarray4_to_array(arg_params, arg_params_arr);

    glGetVertexAttribiv(arg_index, arg_pname, arg_params);
}


CK_DLL_MFUN(Chuck_OpenGL_IsProgram)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);

    RETURN->v_int = glIsProgram(arg_program);
}


CK_DLL_MFUN(Chuck_OpenGL_IsShader)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_shader = GET_NEXT_INT(ARGS);

    RETURN->v_int = glIsShader(arg_shader);
}


CK_DLL_MFUN(Chuck_OpenGL_LinkProgram)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);

    glLinkProgram(arg_program);
}


CK_DLL_MFUN(Chuck_OpenGL_UseProgram)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);

    glUseProgram(arg_program);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform1f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_v0 = GET_NEXT_FLOAT(ARGS);

    glUniform1f(arg_location, arg_v0);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform2f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_v0 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v1 = GET_NEXT_FLOAT(ARGS);

    glUniform2f(arg_location, arg_v0, arg_v1);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform3f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_v0 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v2 = GET_NEXT_FLOAT(ARGS);

    glUniform3f(arg_location, arg_v0, arg_v1, arg_v2);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform4f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_v0 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v1 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v2 = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_v3 = GET_NEXT_FLOAT(ARGS);

    glUniform4f(arg_location, arg_v0, arg_v1, arg_v2, arg_v3);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform1i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_v0 = GET_NEXT_INT(ARGS);

    glUniform1i(arg_location, arg_v0);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform2i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_v0 = GET_NEXT_INT(ARGS);
    t_CKINT arg_v1 = GET_NEXT_INT(ARGS);

    glUniform2i(arg_location, arg_v0, arg_v1);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform3i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_v0 = GET_NEXT_INT(ARGS);
    t_CKINT arg_v1 = GET_NEXT_INT(ARGS);
    t_CKINT arg_v2 = GET_NEXT_INT(ARGS);

    glUniform3i(arg_location, arg_v0, arg_v1, arg_v2);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform4i)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_v0 = GET_NEXT_INT(ARGS);
    t_CKINT arg_v1 = GET_NEXT_INT(ARGS);
    t_CKINT arg_v2 = GET_NEXT_INT(ARGS);
    t_CKINT arg_v3 = GET_NEXT_INT(ARGS);

    glUniform4i(arg_location, arg_v0, arg_v1, arg_v2, arg_v3);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform1fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleArrayForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniform1fv(arg_location, arg_count, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform2fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleArrayForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniform2fv(arg_location, arg_count, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform3fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleArrayForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniform3fv(arg_location, arg_count, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform4fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleArrayForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniform4fv(arg_location, arg_count, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform1iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_value_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_value = new GLint[arg_value_arr->size()];
    chgl->scheduleArrayForCleanup(arg_value);
    copy_ckarray4_to_array(arg_value, arg_value_arr);

    glUniform1iv(arg_location, arg_count, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform2iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_value_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_value = new GLint[arg_value_arr->size()];
    chgl->scheduleArrayForCleanup(arg_value);
    copy_ckarray4_to_array(arg_value, arg_value_arr);

    glUniform2iv(arg_location, arg_count, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform3iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_value_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_value = new GLint[arg_value_arr->size()];
    chgl->scheduleArrayForCleanup(arg_value);
    copy_ckarray4_to_array(arg_value, arg_value_arr);

    glUniform3iv(arg_location, arg_count, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_Uniform4iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_value_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_value = new GLint[arg_value_arr->size()];
    chgl->scheduleArrayForCleanup(arg_value);
    copy_ckarray4_to_array(arg_value, arg_value_arr);

    glUniform4iv(arg_location, arg_count, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_UniformMatrix2fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    t_CKINT arg_transpose = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleArrayForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniformMatrix2fv(arg_location, arg_count, arg_transpose, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_UniformMatrix3fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    t_CKINT arg_transpose = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleArrayForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniformMatrix3fv(arg_location, arg_count, arg_transpose, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_UniformMatrix4fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    t_CKINT arg_transpose = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleArrayForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniformMatrix4fv(arg_location, arg_count, arg_transpose, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_ValidateProgram)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_program = GET_NEXT_INT(ARGS);

    glValidateProgram(arg_program);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib1d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);

    glVertexAttrib1d(arg_index, arg_x);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib1dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertexAttrib1dv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib1f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);

    glVertexAttrib1f(arg_index, arg_x);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib1fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertexAttrib1fv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib1s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKINT arg_x = GET_NEXT_INT(ARGS);

    glVertexAttrib1s(arg_index, arg_x);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib1sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertexAttrib1sv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib2d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);

    glVertexAttrib2d(arg_index, arg_x, arg_y);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib2dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertexAttrib2dv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib2f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);

    glVertexAttrib2f(arg_index, arg_x, arg_y);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib2fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertexAttrib2fv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib2s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);

    glVertexAttrib2s(arg_index, arg_x, arg_y);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib2sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertexAttrib2sv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib3d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);

    glVertexAttrib3d(arg_index, arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib3dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertexAttrib3dv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib3f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);

    glVertexAttrib3f(arg_index, arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib3fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertexAttrib3fv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib3s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_z = GET_NEXT_INT(ARGS);

    glVertexAttrib3s(arg_index, arg_x, arg_y, arg_z);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib3sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertexAttrib3sv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4Nbv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLbyte *arg_v = new GLbyte[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertexAttrib4Nbv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4Niv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertexAttrib4Niv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4Nsv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertexAttrib4Nsv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4Nub)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_z = GET_NEXT_INT(ARGS);
    t_CKINT arg_w = GET_NEXT_INT(ARGS);

    glVertexAttrib4Nub(arg_index, arg_x, arg_y, arg_z, arg_w);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4Nubv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLubyte *arg_v = new GLubyte[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertexAttrib4Nubv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4Nuiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_v = new GLuint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertexAttrib4Nuiv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4Nusv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLushort *arg_v = new GLushort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertexAttrib4Nusv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4bv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLbyte *arg_v = new GLbyte[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertexAttrib4bv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4d)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_w = GET_NEXT_FLOAT(ARGS);

    glVertexAttrib4d(arg_index, arg_x, arg_y, arg_z, arg_w);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4dv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLdouble *arg_v = new GLdouble[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertexAttrib4dv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4f)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKFLOAT arg_x = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_y = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_z = GET_NEXT_FLOAT(ARGS);
    t_CKFLOAT arg_w = GET_NEXT_FLOAT(ARGS);

    glVertexAttrib4f(arg_index, arg_x, arg_y, arg_z, arg_w);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_v_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_v = new GLfloat[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray8_to_array(arg_v, arg_v_arr);

    glVertexAttrib4fv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4iv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLint *arg_v = new GLint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertexAttrib4iv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4s)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKINT arg_x = GET_NEXT_INT(ARGS);
    t_CKINT arg_y = GET_NEXT_INT(ARGS);
    t_CKINT arg_z = GET_NEXT_INT(ARGS);
    t_CKINT arg_w = GET_NEXT_INT(ARGS);

    glVertexAttrib4s(arg_index, arg_x, arg_y, arg_z, arg_w);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4sv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLshort *arg_v = new GLshort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertexAttrib4sv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4ubv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLubyte *arg_v = new GLubyte[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertexAttrib4ubv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4uiv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLuint *arg_v = new GLuint[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertexAttrib4uiv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttrib4usv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    Chuck_Array4 *arg_v_arr = (Chuck_Array4 *) GET_NEXT_OBJECT(ARGS);
    GLushort *arg_v = new GLushort[arg_v_arr->size()];
    chgl->scheduleArrayForCleanup(arg_v);
    copy_ckarray4_to_array(arg_v, arg_v_arr);

    glVertexAttrib4usv(arg_index, arg_v);
}


CK_DLL_MFUN(Chuck_OpenGL_VertexAttribPointer)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_index = GET_NEXT_INT(ARGS);
    t_CKINT arg_size = GET_NEXT_INT(ARGS);
    t_CKINT arg_type = GET_NEXT_INT(ARGS);
    t_CKINT arg_normalized = GET_NEXT_INT(ARGS);
    t_CKINT arg_stride = GET_NEXT_INT(ARGS);
    Chuck_Array *_arg_pointer_arr = (Chuck_Array *) GET_NEXT_OBJECT(ARGS);
    void *arg_pointer;
    if(_arg_pointer_arr->m_array_type == &t_int)
    {
        Chuck_Array4 *arg_pointer_arr = (Chuck_Array4 *) _arg_pointer_arr;
        GLubyte *arg_pointer_v = new GLubyte[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray4_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }
    else if(_arg_pointer_arr->m_array_type == &t_float)
    {
        Chuck_Array8 *arg_pointer_arr = (Chuck_Array8 *) _arg_pointer_arr;
        GLfloat *arg_pointer_v = new GLfloat[arg_pointer_arr->size()];
        chgl->scheduleArrayForCleanup(arg_pointer_v);
        copy_ckarray8_to_array(arg_pointer_v, arg_pointer_arr);
        arg_pointer = (void *) arg_pointer_v;
    }

    glVertexAttribPointer(arg_index, arg_size, arg_type, arg_normalized, arg_stride, arg_pointer);
}

static const t_CKINT Chuck_OpenGL_PIXEL_PACK_BUFFER = GL_PIXEL_PACK_BUFFER;
static const t_CKINT Chuck_OpenGL_PIXEL_UNPACK_BUFFER = GL_PIXEL_UNPACK_BUFFER;
static const t_CKINT Chuck_OpenGL_PIXEL_PACK_BUFFER_BINDING = GL_PIXEL_PACK_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_PIXEL_UNPACK_BUFFER_BINDING = GL_PIXEL_UNPACK_BUFFER_BINDING;
static const t_CKINT Chuck_OpenGL_FLOAT_MAT2x3 = GL_FLOAT_MAT2x3;
static const t_CKINT Chuck_OpenGL_FLOAT_MAT2x4 = GL_FLOAT_MAT2x4;
static const t_CKINT Chuck_OpenGL_FLOAT_MAT3x2 = GL_FLOAT_MAT3x2;
static const t_CKINT Chuck_OpenGL_FLOAT_MAT3x4 = GL_FLOAT_MAT3x4;
static const t_CKINT Chuck_OpenGL_FLOAT_MAT4x2 = GL_FLOAT_MAT4x2;
static const t_CKINT Chuck_OpenGL_FLOAT_MAT4x3 = GL_FLOAT_MAT4x3;
static const t_CKINT Chuck_OpenGL_SRGB = GL_SRGB;
static const t_CKINT Chuck_OpenGL_SRGB8 = GL_SRGB8;
static const t_CKINT Chuck_OpenGL_SRGB_ALPHA = GL_SRGB_ALPHA;
static const t_CKINT Chuck_OpenGL_SRGB8_ALPHA8 = GL_SRGB8_ALPHA8;
static const t_CKINT Chuck_OpenGL_COMPRESSED_SRGB = GL_COMPRESSED_SRGB;
static const t_CKINT Chuck_OpenGL_COMPRESSED_SRGB_ALPHA = GL_COMPRESSED_SRGB_ALPHA;
static const t_CKINT Chuck_OpenGL_CURRENT_RASTER_SECONDARY_COLOR = GL_CURRENT_RASTER_SECONDARY_COLOR;
static const t_CKINT Chuck_OpenGL_SLUMINANCE_ALPHA = GL_SLUMINANCE_ALPHA;
static const t_CKINT Chuck_OpenGL_SLUMINANCE8_ALPHA8 = GL_SLUMINANCE8_ALPHA8;
static const t_CKINT Chuck_OpenGL_SLUMINANCE = GL_SLUMINANCE;
static const t_CKINT Chuck_OpenGL_SLUMINANCE8 = GL_SLUMINANCE8;
static const t_CKINT Chuck_OpenGL_COMPRESSED_SLUMINANCE = GL_COMPRESSED_SLUMINANCE;
static const t_CKINT Chuck_OpenGL_COMPRESSED_SLUMINANCE_ALPHA = GL_COMPRESSED_SLUMINANCE_ALPHA;

CK_DLL_MFUN(Chuck_OpenGL_UniformMatrix2x3fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    t_CKINT arg_transpose = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleArrayForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniformMatrix2x3fv(arg_location, arg_count, arg_transpose, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_UniformMatrix3x2fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    t_CKINT arg_transpose = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleArrayForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniformMatrix3x2fv(arg_location, arg_count, arg_transpose, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_UniformMatrix2x4fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    t_CKINT arg_transpose = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleArrayForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniformMatrix2x4fv(arg_location, arg_count, arg_transpose, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_UniformMatrix4x2fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    t_CKINT arg_transpose = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleArrayForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniformMatrix4x2fv(arg_location, arg_count, arg_transpose, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_UniformMatrix3x4fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    t_CKINT arg_transpose = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleArrayForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniformMatrix3x4fv(arg_location, arg_count, arg_transpose, arg_value);
}


CK_DLL_MFUN(Chuck_OpenGL_UniformMatrix4x3fv)
{
    chugl *chgl = (chugl *) OBJ_MEMBER_INT(SELF, Chuck_OpenGL_offset_chugl);
    if(chgl == NULL || !chgl->good() || !chgl->locked()) return;
    
    t_CKINT arg_location = GET_NEXT_INT(ARGS);
    t_CKINT arg_count = GET_NEXT_INT(ARGS);
    t_CKINT arg_transpose = GET_NEXT_INT(ARGS);
    Chuck_Array8 *arg_value_arr = (Chuck_Array8 *) GET_NEXT_OBJECT(ARGS);
    GLfloat *arg_value = new GLfloat[arg_value_arr->size()];
    chgl->scheduleArrayForCleanup(arg_value);
    copy_ckarray8_to_array(arg_value, arg_value_arr);

    glUniformMatrix4x3fv(arg_location, arg_count, arg_transpose, arg_value);
}



t_CKBOOL OpenGL_query(Chuck_DL_Query *QUERY)
{
    // hmm, don't change this...
    QUERY->setname(QUERY, "OpenGL");
    
    // begin the class definition
    // can change the second argument to extend a different ChucK class
    QUERY->begin_class(QUERY, "OpenGL", "Object");
    
    Chuck_OpenGL_offset_chugl = QUERY->add_mvar(QUERY, "int", "@chugl_data", FALSE);
    
    QUERY->add_ctor(QUERY, Chuck_OpenGL_ctor);
    

    QUERY->add_mfun(QUERY, Chuck_OpenGL_CullFace, "void", "CullFace");
    QUERY->add_arg(QUERY, "int", "mode");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_FrontFace, "void", "FrontFace");
    QUERY->add_arg(QUERY, "int", "mode");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Hint, "void", "Hint");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "mode");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_LineWidth, "void", "LineWidth");
    QUERY->add_arg(QUERY, "float", "width");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PointSize, "void", "PointSize");
    QUERY->add_arg(QUERY, "float", "size");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PolygonMode, "void", "PolygonMode");
    QUERY->add_arg(QUERY, "int", "face");
    QUERY->add_arg(QUERY, "int", "mode");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Scissor, "void", "Scissor");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexParameterf, "void", "TexParameterf");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexParameterfv, "void", "TexParameterfv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexParameteri, "void", "TexParameteri");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexParameteriv, "void", "TexParameteriv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexImage1D, "void", "TexImage1D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "internalformat");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "border");
    QUERY->add_arg(QUERY, "int", "format");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "Object", "pixels");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexImage2D, "void", "TexImage2D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "internalformat");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "border");
    QUERY->add_arg(QUERY, "int", "format");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "Object", "pixels");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DrawBuffer, "void", "DrawBuffer");
    QUERY->add_arg(QUERY, "int", "buf");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Clear, "void", "Clear");
    QUERY->add_arg(QUERY, "int", "mask");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ClearColor, "void", "ClearColor");
    QUERY->add_arg(QUERY, "float", "red");
    QUERY->add_arg(QUERY, "float", "green");
    QUERY->add_arg(QUERY, "float", "blue");
    QUERY->add_arg(QUERY, "float", "alpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ClearStencil, "void", "ClearStencil");
    QUERY->add_arg(QUERY, "int", "s");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ClearDepth, "void", "ClearDepth");
    QUERY->add_arg(QUERY, "float", "depth");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_StencilMask, "void", "StencilMask");
    QUERY->add_arg(QUERY, "int", "mask");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ColorMask, "void", "ColorMask");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");
    QUERY->add_arg(QUERY, "int", "alpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DepthMask, "void", "DepthMask");
    QUERY->add_arg(QUERY, "int", "flag");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Disable, "void", "Disable");
    QUERY->add_arg(QUERY, "int", "cap");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Enable, "void", "Enable");
    QUERY->add_arg(QUERY, "int", "cap");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Finish, "void", "Finish");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Flush, "void", "Flush");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_BlendFunc, "void", "BlendFunc");
    QUERY->add_arg(QUERY, "int", "sfactor");
    QUERY->add_arg(QUERY, "int", "dfactor");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_LogicOp, "void", "LogicOp");
    QUERY->add_arg(QUERY, "int", "opcode");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_StencilFunc, "void", "StencilFunc");
    QUERY->add_arg(QUERY, "int", "func");
    QUERY->add_arg(QUERY, "int", "ref");
    QUERY->add_arg(QUERY, "int", "mask");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_StencilOp, "void", "StencilOp");
    QUERY->add_arg(QUERY, "int", "fail");
    QUERY->add_arg(QUERY, "int", "zfail");
    QUERY->add_arg(QUERY, "int", "zpass");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DepthFunc, "void", "DepthFunc");
    QUERY->add_arg(QUERY, "int", "func");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PixelStoref, "void", "PixelStoref");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PixelStorei, "void", "PixelStorei");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ReadBuffer, "void", "ReadBuffer");
    QUERY->add_arg(QUERY, "int", "src");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ReadPixels, "void", "ReadPixels");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "format");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "Object", "pixels");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetBooleanv, "void", "GetBooleanv");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "data");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetDoublev, "void", "GetDoublev");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "data");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetError, "int", "GetError");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetFloatv, "void", "GetFloatv");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "data");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetIntegerv, "void", "GetIntegerv");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "data");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetTexImage, "void", "GetTexImage");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "format");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "Object", "pixels");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetTexParameterfv, "void", "GetTexParameterfv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetTexParameteriv, "void", "GetTexParameteriv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetTexLevelParameterfv, "void", "GetTexLevelParameterfv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetTexLevelParameteriv, "void", "GetTexLevelParameteriv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_IsEnabled, "int", "IsEnabled");
    QUERY->add_arg(QUERY, "int", "cap");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DepthRange, "void", "DepthRange");
    QUERY->add_arg(QUERY, "float", "near");
    QUERY->add_arg(QUERY, "float", "far");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Viewport, "void", "Viewport");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_NewList, "void", "NewList");
    QUERY->add_arg(QUERY, "int", "list");
    QUERY->add_arg(QUERY, "int", "mode");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EndList, "void", "EndList");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CallList, "void", "CallList");
    QUERY->add_arg(QUERY, "int", "list");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CallLists, "void", "CallLists");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "Object", "lists");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DeleteLists, "void", "DeleteLists");
    QUERY->add_arg(QUERY, "int", "list");
    QUERY->add_arg(QUERY, "int", "range");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GenLists, "int", "GenLists");
    QUERY->add_arg(QUERY, "int", "range");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ListBase, "void", "ListBase");
    QUERY->add_arg(QUERY, "int", "base");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Begin, "void", "Begin");
    QUERY->add_arg(QUERY, "int", "mode");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Bitmap, "void", "Bitmap");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "float", "xorig");
    QUERY->add_arg(QUERY, "float", "yorig");
    QUERY->add_arg(QUERY, "float", "xmove");
    QUERY->add_arg(QUERY, "float", "ymove");
    QUERY->add_arg(QUERY, "int[]", "bitmap");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color3b, "void", "Color3b");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color3bv, "void", "Color3bv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color3d, "void", "Color3d");
    QUERY->add_arg(QUERY, "float", "red");
    QUERY->add_arg(QUERY, "float", "green");
    QUERY->add_arg(QUERY, "float", "blue");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color3dv, "void", "Color3dv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color3f, "void", "Color3f");
    QUERY->add_arg(QUERY, "float", "red");
    QUERY->add_arg(QUERY, "float", "green");
    QUERY->add_arg(QUERY, "float", "blue");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color3fv, "void", "Color3fv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color3i, "void", "Color3i");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color3iv, "void", "Color3iv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color3s, "void", "Color3s");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color3sv, "void", "Color3sv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color3ub, "void", "Color3ub");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color3ubv, "void", "Color3ubv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color3ui, "void", "Color3ui");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color3uiv, "void", "Color3uiv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color3us, "void", "Color3us");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color3usv, "void", "Color3usv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color4b, "void", "Color4b");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");
    QUERY->add_arg(QUERY, "int", "alpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color4bv, "void", "Color4bv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color4d, "void", "Color4d");
    QUERY->add_arg(QUERY, "float", "red");
    QUERY->add_arg(QUERY, "float", "green");
    QUERY->add_arg(QUERY, "float", "blue");
    QUERY->add_arg(QUERY, "float", "alpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color4dv, "void", "Color4dv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color4f, "void", "Color4f");
    QUERY->add_arg(QUERY, "float", "red");
    QUERY->add_arg(QUERY, "float", "green");
    QUERY->add_arg(QUERY, "float", "blue");
    QUERY->add_arg(QUERY, "float", "alpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color4fv, "void", "Color4fv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color4i, "void", "Color4i");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");
    QUERY->add_arg(QUERY, "int", "alpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color4iv, "void", "Color4iv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color4s, "void", "Color4s");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");
    QUERY->add_arg(QUERY, "int", "alpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color4sv, "void", "Color4sv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color4ub, "void", "Color4ub");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");
    QUERY->add_arg(QUERY, "int", "alpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color4ubv, "void", "Color4ubv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color4ui, "void", "Color4ui");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");
    QUERY->add_arg(QUERY, "int", "alpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color4uiv, "void", "Color4uiv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color4us, "void", "Color4us");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");
    QUERY->add_arg(QUERY, "int", "alpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Color4usv, "void", "Color4usv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EdgeFlag, "void", "EdgeFlag");
    QUERY->add_arg(QUERY, "int", "flag");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EdgeFlagv, "void", "EdgeFlagv");
    QUERY->add_arg(QUERY, "int[]", "flag");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_End, "void", "End");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Indexd, "void", "Indexd");
    QUERY->add_arg(QUERY, "float", "c");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Indexdv, "void", "Indexdv");
    QUERY->add_arg(QUERY, "float[]", "c");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Indexf, "void", "Indexf");
    QUERY->add_arg(QUERY, "float", "c");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Indexfv, "void", "Indexfv");
    QUERY->add_arg(QUERY, "float[]", "c");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Indexi, "void", "Indexi");
    QUERY->add_arg(QUERY, "int", "c");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Indexiv, "void", "Indexiv");
    QUERY->add_arg(QUERY, "int[]", "c");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Indexs, "void", "Indexs");
    QUERY->add_arg(QUERY, "int", "c");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Indexsv, "void", "Indexsv");
    QUERY->add_arg(QUERY, "int[]", "c");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Normal3b, "void", "Normal3b");
    QUERY->add_arg(QUERY, "int", "nx");
    QUERY->add_arg(QUERY, "int", "ny");
    QUERY->add_arg(QUERY, "int", "nz");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Normal3bv, "void", "Normal3bv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Normal3d, "void", "Normal3d");
    QUERY->add_arg(QUERY, "float", "nx");
    QUERY->add_arg(QUERY, "float", "ny");
    QUERY->add_arg(QUERY, "float", "nz");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Normal3dv, "void", "Normal3dv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Normal3f, "void", "Normal3f");
    QUERY->add_arg(QUERY, "float", "nx");
    QUERY->add_arg(QUERY, "float", "ny");
    QUERY->add_arg(QUERY, "float", "nz");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Normal3fv, "void", "Normal3fv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Normal3i, "void", "Normal3i");
    QUERY->add_arg(QUERY, "int", "nx");
    QUERY->add_arg(QUERY, "int", "ny");
    QUERY->add_arg(QUERY, "int", "nz");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Normal3iv, "void", "Normal3iv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Normal3s, "void", "Normal3s");
    QUERY->add_arg(QUERY, "int", "nx");
    QUERY->add_arg(QUERY, "int", "ny");
    QUERY->add_arg(QUERY, "int", "nz");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Normal3sv, "void", "Normal3sv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos2d, "void", "RasterPos2d");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos2dv, "void", "RasterPos2dv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos2f, "void", "RasterPos2f");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos2fv, "void", "RasterPos2fv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos2i, "void", "RasterPos2i");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos2iv, "void", "RasterPos2iv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos2s, "void", "RasterPos2s");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos2sv, "void", "RasterPos2sv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos3d, "void", "RasterPos3d");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos3dv, "void", "RasterPos3dv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos3f, "void", "RasterPos3f");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos3fv, "void", "RasterPos3fv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos3i, "void", "RasterPos3i");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos3iv, "void", "RasterPos3iv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos3s, "void", "RasterPos3s");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos3sv, "void", "RasterPos3sv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos4d, "void", "RasterPos4d");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");
    QUERY->add_arg(QUERY, "float", "w");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos4dv, "void", "RasterPos4dv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos4f, "void", "RasterPos4f");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");
    QUERY->add_arg(QUERY, "float", "w");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos4fv, "void", "RasterPos4fv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos4i, "void", "RasterPos4i");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "z");
    QUERY->add_arg(QUERY, "int", "w");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos4iv, "void", "RasterPos4iv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos4s, "void", "RasterPos4s");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "z");
    QUERY->add_arg(QUERY, "int", "w");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RasterPos4sv, "void", "RasterPos4sv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Rectd, "void", "Rectd");
    QUERY->add_arg(QUERY, "float", "x1");
    QUERY->add_arg(QUERY, "float", "y1");
    QUERY->add_arg(QUERY, "float", "x2");
    QUERY->add_arg(QUERY, "float", "y2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Rectdv, "void", "Rectdv");
    QUERY->add_arg(QUERY, "float[]", "v1");
    QUERY->add_arg(QUERY, "float[]", "v2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Rectf, "void", "Rectf");
    QUERY->add_arg(QUERY, "float", "x1");
    QUERY->add_arg(QUERY, "float", "y1");
    QUERY->add_arg(QUERY, "float", "x2");
    QUERY->add_arg(QUERY, "float", "y2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Rectfv, "void", "Rectfv");
    QUERY->add_arg(QUERY, "float[]", "v1");
    QUERY->add_arg(QUERY, "float[]", "v2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Recti, "void", "Recti");
    QUERY->add_arg(QUERY, "int", "x1");
    QUERY->add_arg(QUERY, "int", "y1");
    QUERY->add_arg(QUERY, "int", "x2");
    QUERY->add_arg(QUERY, "int", "y2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Rectiv, "void", "Rectiv");
    QUERY->add_arg(QUERY, "int[]", "v1");
    QUERY->add_arg(QUERY, "int[]", "v2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Rects, "void", "Rects");
    QUERY->add_arg(QUERY, "int", "x1");
    QUERY->add_arg(QUERY, "int", "y1");
    QUERY->add_arg(QUERY, "int", "x2");
    QUERY->add_arg(QUERY, "int", "y2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Rectsv, "void", "Rectsv");
    QUERY->add_arg(QUERY, "int[]", "v1");
    QUERY->add_arg(QUERY, "int[]", "v2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord1d, "void", "TexCoord1d");
    QUERY->add_arg(QUERY, "float", "s");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord1dv, "void", "TexCoord1dv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord1f, "void", "TexCoord1f");
    QUERY->add_arg(QUERY, "float", "s");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord1fv, "void", "TexCoord1fv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord1i, "void", "TexCoord1i");
    QUERY->add_arg(QUERY, "int", "s");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord1iv, "void", "TexCoord1iv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord1s, "void", "TexCoord1s");
    QUERY->add_arg(QUERY, "int", "s");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord1sv, "void", "TexCoord1sv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord2d, "void", "TexCoord2d");
    QUERY->add_arg(QUERY, "float", "s");
    QUERY->add_arg(QUERY, "float", "t");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord2dv, "void", "TexCoord2dv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord2f, "void", "TexCoord2f");
    QUERY->add_arg(QUERY, "float", "s");
    QUERY->add_arg(QUERY, "float", "t");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord2fv, "void", "TexCoord2fv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord2i, "void", "TexCoord2i");
    QUERY->add_arg(QUERY, "int", "s");
    QUERY->add_arg(QUERY, "int", "t");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord2iv, "void", "TexCoord2iv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord2s, "void", "TexCoord2s");
    QUERY->add_arg(QUERY, "int", "s");
    QUERY->add_arg(QUERY, "int", "t");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord2sv, "void", "TexCoord2sv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord3d, "void", "TexCoord3d");
    QUERY->add_arg(QUERY, "float", "s");
    QUERY->add_arg(QUERY, "float", "t");
    QUERY->add_arg(QUERY, "float", "r");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord3dv, "void", "TexCoord3dv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord3f, "void", "TexCoord3f");
    QUERY->add_arg(QUERY, "float", "s");
    QUERY->add_arg(QUERY, "float", "t");
    QUERY->add_arg(QUERY, "float", "r");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord3fv, "void", "TexCoord3fv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord3i, "void", "TexCoord3i");
    QUERY->add_arg(QUERY, "int", "s");
    QUERY->add_arg(QUERY, "int", "t");
    QUERY->add_arg(QUERY, "int", "r");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord3iv, "void", "TexCoord3iv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord3s, "void", "TexCoord3s");
    QUERY->add_arg(QUERY, "int", "s");
    QUERY->add_arg(QUERY, "int", "t");
    QUERY->add_arg(QUERY, "int", "r");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord3sv, "void", "TexCoord3sv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord4d, "void", "TexCoord4d");
    QUERY->add_arg(QUERY, "float", "s");
    QUERY->add_arg(QUERY, "float", "t");
    QUERY->add_arg(QUERY, "float", "r");
    QUERY->add_arg(QUERY, "float", "q");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord4dv, "void", "TexCoord4dv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord4f, "void", "TexCoord4f");
    QUERY->add_arg(QUERY, "float", "s");
    QUERY->add_arg(QUERY, "float", "t");
    QUERY->add_arg(QUERY, "float", "r");
    QUERY->add_arg(QUERY, "float", "q");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord4fv, "void", "TexCoord4fv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord4i, "void", "TexCoord4i");
    QUERY->add_arg(QUERY, "int", "s");
    QUERY->add_arg(QUERY, "int", "t");
    QUERY->add_arg(QUERY, "int", "r");
    QUERY->add_arg(QUERY, "int", "q");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord4iv, "void", "TexCoord4iv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord4s, "void", "TexCoord4s");
    QUERY->add_arg(QUERY, "int", "s");
    QUERY->add_arg(QUERY, "int", "t");
    QUERY->add_arg(QUERY, "int", "r");
    QUERY->add_arg(QUERY, "int", "q");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoord4sv, "void", "TexCoord4sv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex2d, "void", "Vertex2d");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex2dv, "void", "Vertex2dv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex2f, "void", "Vertex2f");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex2fv, "void", "Vertex2fv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex2i, "void", "Vertex2i");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex2iv, "void", "Vertex2iv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex2s, "void", "Vertex2s");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex2sv, "void", "Vertex2sv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex3d, "void", "Vertex3d");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex3dv, "void", "Vertex3dv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex3f, "void", "Vertex3f");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex3fv, "void", "Vertex3fv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex3i, "void", "Vertex3i");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex3iv, "void", "Vertex3iv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex3s, "void", "Vertex3s");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex3sv, "void", "Vertex3sv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex4d, "void", "Vertex4d");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");
    QUERY->add_arg(QUERY, "float", "w");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex4dv, "void", "Vertex4dv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex4f, "void", "Vertex4f");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");
    QUERY->add_arg(QUERY, "float", "w");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex4fv, "void", "Vertex4fv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex4i, "void", "Vertex4i");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "z");
    QUERY->add_arg(QUERY, "int", "w");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex4iv, "void", "Vertex4iv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex4s, "void", "Vertex4s");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "z");
    QUERY->add_arg(QUERY, "int", "w");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Vertex4sv, "void", "Vertex4sv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ClipPlane, "void", "ClipPlane");
    QUERY->add_arg(QUERY, "int", "plane");
    QUERY->add_arg(QUERY, "float[]", "equation");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ColorMaterial, "void", "ColorMaterial");
    QUERY->add_arg(QUERY, "int", "face");
    QUERY->add_arg(QUERY, "int", "mode");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Fogf, "void", "Fogf");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Fogfv, "void", "Fogfv");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Fogi, "void", "Fogi");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Fogiv, "void", "Fogiv");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Lightf, "void", "Lightf");
    QUERY->add_arg(QUERY, "int", "light");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Lightfv, "void", "Lightfv");
    QUERY->add_arg(QUERY, "int", "light");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Lighti, "void", "Lighti");
    QUERY->add_arg(QUERY, "int", "light");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Lightiv, "void", "Lightiv");
    QUERY->add_arg(QUERY, "int", "light");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_LightModelf, "void", "LightModelf");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_LightModelfv, "void", "LightModelfv");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_LightModeli, "void", "LightModeli");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_LightModeliv, "void", "LightModeliv");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_LineStipple, "void", "LineStipple");
    QUERY->add_arg(QUERY, "int", "factor");
    QUERY->add_arg(QUERY, "int", "pattern");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Materialf, "void", "Materialf");
    QUERY->add_arg(QUERY, "int", "face");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Materialfv, "void", "Materialfv");
    QUERY->add_arg(QUERY, "int", "face");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Materiali, "void", "Materiali");
    QUERY->add_arg(QUERY, "int", "face");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Materialiv, "void", "Materialiv");
    QUERY->add_arg(QUERY, "int", "face");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PolygonStipple, "void", "PolygonStipple");
    QUERY->add_arg(QUERY, "int[]", "mask");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ShadeModel, "void", "ShadeModel");
    QUERY->add_arg(QUERY, "int", "mode");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexEnvf, "void", "TexEnvf");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexEnvfv, "void", "TexEnvfv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexEnvi, "void", "TexEnvi");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexEnviv, "void", "TexEnviv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexGend, "void", "TexGend");
    QUERY->add_arg(QUERY, "int", "coord");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexGendv, "void", "TexGendv");
    QUERY->add_arg(QUERY, "int", "coord");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexGenf, "void", "TexGenf");
    QUERY->add_arg(QUERY, "int", "coord");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexGenfv, "void", "TexGenfv");
    QUERY->add_arg(QUERY, "int", "coord");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexGeni, "void", "TexGeni");
    QUERY->add_arg(QUERY, "int", "coord");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexGeniv, "void", "TexGeniv");
    QUERY->add_arg(QUERY, "int", "coord");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_FeedbackBuffer, "void", "FeedbackBuffer");
    QUERY->add_arg(QUERY, "int", "size");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "float[]", "buffer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SelectBuffer, "void", "SelectBuffer");
    QUERY->add_arg(QUERY, "int", "size");
    QUERY->add_arg(QUERY, "int[]", "buffer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_RenderMode, "int", "RenderMode");
    QUERY->add_arg(QUERY, "int", "mode");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_InitNames, "void", "InitNames");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_LoadName, "void", "LoadName");
    QUERY->add_arg(QUERY, "int", "name");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PassThrough, "void", "PassThrough");
    QUERY->add_arg(QUERY, "float", "token");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PopName, "void", "PopName");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PushName, "void", "PushName");
    QUERY->add_arg(QUERY, "int", "name");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ClearAccum, "void", "ClearAccum");
    QUERY->add_arg(QUERY, "float", "red");
    QUERY->add_arg(QUERY, "float", "green");
    QUERY->add_arg(QUERY, "float", "blue");
    QUERY->add_arg(QUERY, "float", "alpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ClearIndex, "void", "ClearIndex");
    QUERY->add_arg(QUERY, "float", "c");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_IndexMask, "void", "IndexMask");
    QUERY->add_arg(QUERY, "int", "mask");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Accum, "void", "Accum");
    QUERY->add_arg(QUERY, "int", "op");
    QUERY->add_arg(QUERY, "float", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PopAttrib, "void", "PopAttrib");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PushAttrib, "void", "PushAttrib");
    QUERY->add_arg(QUERY, "int", "mask");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Map1d, "void", "Map1d");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float", "u1");
    QUERY->add_arg(QUERY, "float", "u2");
    QUERY->add_arg(QUERY, "int", "stride");
    QUERY->add_arg(QUERY, "int", "order");
    QUERY->add_arg(QUERY, "float[]", "points");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Map1f, "void", "Map1f");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float", "u1");
    QUERY->add_arg(QUERY, "float", "u2");
    QUERY->add_arg(QUERY, "int", "stride");
    QUERY->add_arg(QUERY, "int", "order");
    QUERY->add_arg(QUERY, "float[]", "points");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Map2d, "void", "Map2d");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float", "u1");
    QUERY->add_arg(QUERY, "float", "u2");
    QUERY->add_arg(QUERY, "int", "ustride");
    QUERY->add_arg(QUERY, "int", "uorder");
    QUERY->add_arg(QUERY, "float", "v1");
    QUERY->add_arg(QUERY, "float", "v2");
    QUERY->add_arg(QUERY, "int", "vstride");
    QUERY->add_arg(QUERY, "int", "vorder");
    QUERY->add_arg(QUERY, "float[]", "points");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Map2f, "void", "Map2f");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float", "u1");
    QUERY->add_arg(QUERY, "float", "u2");
    QUERY->add_arg(QUERY, "int", "ustride");
    QUERY->add_arg(QUERY, "int", "uorder");
    QUERY->add_arg(QUERY, "float", "v1");
    QUERY->add_arg(QUERY, "float", "v2");
    QUERY->add_arg(QUERY, "int", "vstride");
    QUERY->add_arg(QUERY, "int", "vorder");
    QUERY->add_arg(QUERY, "float[]", "points");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MapGrid1d, "void", "MapGrid1d");
    QUERY->add_arg(QUERY, "int", "un");
    QUERY->add_arg(QUERY, "float", "u1");
    QUERY->add_arg(QUERY, "float", "u2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MapGrid1f, "void", "MapGrid1f");
    QUERY->add_arg(QUERY, "int", "un");
    QUERY->add_arg(QUERY, "float", "u1");
    QUERY->add_arg(QUERY, "float", "u2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MapGrid2d, "void", "MapGrid2d");
    QUERY->add_arg(QUERY, "int", "un");
    QUERY->add_arg(QUERY, "float", "u1");
    QUERY->add_arg(QUERY, "float", "u2");
    QUERY->add_arg(QUERY, "int", "vn");
    QUERY->add_arg(QUERY, "float", "v1");
    QUERY->add_arg(QUERY, "float", "v2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MapGrid2f, "void", "MapGrid2f");
    QUERY->add_arg(QUERY, "int", "un");
    QUERY->add_arg(QUERY, "float", "u1");
    QUERY->add_arg(QUERY, "float", "u2");
    QUERY->add_arg(QUERY, "int", "vn");
    QUERY->add_arg(QUERY, "float", "v1");
    QUERY->add_arg(QUERY, "float", "v2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EvalCoord1d, "void", "EvalCoord1d");
    QUERY->add_arg(QUERY, "float", "u");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EvalCoord1dv, "void", "EvalCoord1dv");
    QUERY->add_arg(QUERY, "float[]", "u");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EvalCoord1f, "void", "EvalCoord1f");
    QUERY->add_arg(QUERY, "float", "u");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EvalCoord1fv, "void", "EvalCoord1fv");
    QUERY->add_arg(QUERY, "float[]", "u");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EvalCoord2d, "void", "EvalCoord2d");
    QUERY->add_arg(QUERY, "float", "u");
    QUERY->add_arg(QUERY, "float", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EvalCoord2dv, "void", "EvalCoord2dv");
    QUERY->add_arg(QUERY, "float[]", "u");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EvalCoord2f, "void", "EvalCoord2f");
    QUERY->add_arg(QUERY, "float", "u");
    QUERY->add_arg(QUERY, "float", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EvalCoord2fv, "void", "EvalCoord2fv");
    QUERY->add_arg(QUERY, "float[]", "u");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EvalMesh1, "void", "EvalMesh1");
    QUERY->add_arg(QUERY, "int", "mode");
    QUERY->add_arg(QUERY, "int", "i1");
    QUERY->add_arg(QUERY, "int", "i2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EvalPoint1, "void", "EvalPoint1");
    QUERY->add_arg(QUERY, "int", "i");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EvalMesh2, "void", "EvalMesh2");
    QUERY->add_arg(QUERY, "int", "mode");
    QUERY->add_arg(QUERY, "int", "i1");
    QUERY->add_arg(QUERY, "int", "i2");
    QUERY->add_arg(QUERY, "int", "j1");
    QUERY->add_arg(QUERY, "int", "j2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EvalPoint2, "void", "EvalPoint2");
    QUERY->add_arg(QUERY, "int", "i");
    QUERY->add_arg(QUERY, "int", "j");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_AlphaFunc, "void", "AlphaFunc");
    QUERY->add_arg(QUERY, "int", "func");
    QUERY->add_arg(QUERY, "float", "ref");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PixelZoom, "void", "PixelZoom");
    QUERY->add_arg(QUERY, "float", "xfactor");
    QUERY->add_arg(QUERY, "float", "yfactor");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PixelTransferf, "void", "PixelTransferf");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PixelTransferi, "void", "PixelTransferi");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PixelMapfv, "void", "PixelMapfv");
    QUERY->add_arg(QUERY, "int", "map");
    QUERY->add_arg(QUERY, "int", "mapsize");
    QUERY->add_arg(QUERY, "float[]", "values");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PixelMapuiv, "void", "PixelMapuiv");
    QUERY->add_arg(QUERY, "int", "map");
    QUERY->add_arg(QUERY, "int", "mapsize");
    QUERY->add_arg(QUERY, "int[]", "values");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PixelMapusv, "void", "PixelMapusv");
    QUERY->add_arg(QUERY, "int", "map");
    QUERY->add_arg(QUERY, "int", "mapsize");
    QUERY->add_arg(QUERY, "int[]", "values");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CopyPixels, "void", "CopyPixels");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "type");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DrawPixels, "void", "DrawPixels");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "format");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "Object", "pixels");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetClipPlane, "void", "GetClipPlane");
    QUERY->add_arg(QUERY, "int", "plane");
    QUERY->add_arg(QUERY, "float[]", "equation");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetLightfv, "void", "GetLightfv");
    QUERY->add_arg(QUERY, "int", "light");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetLightiv, "void", "GetLightiv");
    QUERY->add_arg(QUERY, "int", "light");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetMapdv, "void", "GetMapdv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "query");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetMapfv, "void", "GetMapfv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "query");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetMapiv, "void", "GetMapiv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "query");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetMaterialfv, "void", "GetMaterialfv");
    QUERY->add_arg(QUERY, "int", "face");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetMaterialiv, "void", "GetMaterialiv");
    QUERY->add_arg(QUERY, "int", "face");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetPixelMapfv, "void", "GetPixelMapfv");
    QUERY->add_arg(QUERY, "int", "map");
    QUERY->add_arg(QUERY, "float[]", "values");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetPixelMapuiv, "void", "GetPixelMapuiv");
    QUERY->add_arg(QUERY, "int", "map");
    QUERY->add_arg(QUERY, "int[]", "values");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetPixelMapusv, "void", "GetPixelMapusv");
    QUERY->add_arg(QUERY, "int", "map");
    QUERY->add_arg(QUERY, "int[]", "values");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetPolygonStipple, "void", "GetPolygonStipple");
    QUERY->add_arg(QUERY, "int[]", "mask");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetTexEnvfv, "void", "GetTexEnvfv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetTexEnviv, "void", "GetTexEnviv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetTexGendv, "void", "GetTexGendv");
    QUERY->add_arg(QUERY, "int", "coord");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetTexGenfv, "void", "GetTexGenfv");
    QUERY->add_arg(QUERY, "int", "coord");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetTexGeniv, "void", "GetTexGeniv");
    QUERY->add_arg(QUERY, "int", "coord");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_IsList, "int", "IsList");
    QUERY->add_arg(QUERY, "int", "list");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Frustum, "void", "Frustum");
    QUERY->add_arg(QUERY, "float", "left");
    QUERY->add_arg(QUERY, "float", "right");
    QUERY->add_arg(QUERY, "float", "bottom");
    QUERY->add_arg(QUERY, "float", "top");
    QUERY->add_arg(QUERY, "float", "zNear");
    QUERY->add_arg(QUERY, "float", "zFar");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_LoadIdentity, "void", "LoadIdentity");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_LoadMatrixf, "void", "LoadMatrixf");
    QUERY->add_arg(QUERY, "float[]", "m");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_LoadMatrixd, "void", "LoadMatrixd");
    QUERY->add_arg(QUERY, "float[]", "m");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MatrixMode, "void", "MatrixMode");
    QUERY->add_arg(QUERY, "int", "mode");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultMatrixf, "void", "MultMatrixf");
    QUERY->add_arg(QUERY, "float[]", "m");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultMatrixd, "void", "MultMatrixd");
    QUERY->add_arg(QUERY, "float[]", "m");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Ortho, "void", "Ortho");
    QUERY->add_arg(QUERY, "float", "left");
    QUERY->add_arg(QUERY, "float", "right");
    QUERY->add_arg(QUERY, "float", "bottom");
    QUERY->add_arg(QUERY, "float", "top");
    QUERY->add_arg(QUERY, "float", "zNear");
    QUERY->add_arg(QUERY, "float", "zFar");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PopMatrix, "void", "PopMatrix");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PushMatrix, "void", "PushMatrix");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Rotated, "void", "Rotated");
    QUERY->add_arg(QUERY, "float", "angle");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Rotatef, "void", "Rotatef");
    QUERY->add_arg(QUERY, "float", "angle");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Scaled, "void", "Scaled");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Scalef, "void", "Scalef");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Translated, "void", "Translated");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Translatef, "void", "Translatef");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");

    QUERY->add_svar( QUERY, "int", "DEPTH_BUFFER_BIT", TRUE, (void *)&Chuck_OpenGL_DEPTH_BUFFER_BIT );
    QUERY->add_svar( QUERY, "int", "STENCIL_BUFFER_BIT", TRUE, (void *)&Chuck_OpenGL_STENCIL_BUFFER_BIT );
    QUERY->add_svar( QUERY, "int", "COLOR_BUFFER_BIT", TRUE, (void *)&Chuck_OpenGL_COLOR_BUFFER_BIT );
    QUERY->add_svar( QUERY, "int", "FALSE", TRUE, (void *)&Chuck_OpenGL_FALSE );
    QUERY->add_svar( QUERY, "int", "TRUE", TRUE, (void *)&Chuck_OpenGL_TRUE );
    QUERY->add_svar( QUERY, "int", "POINTS", TRUE, (void *)&Chuck_OpenGL_POINTS );
    QUERY->add_svar( QUERY, "int", "LINES", TRUE, (void *)&Chuck_OpenGL_LINES );
    QUERY->add_svar( QUERY, "int", "LINE_LOOP", TRUE, (void *)&Chuck_OpenGL_LINE_LOOP );
    QUERY->add_svar( QUERY, "int", "LINE_STRIP", TRUE, (void *)&Chuck_OpenGL_LINE_STRIP );
    QUERY->add_svar( QUERY, "int", "TRIANGLES", TRUE, (void *)&Chuck_OpenGL_TRIANGLES );
    QUERY->add_svar( QUERY, "int", "TRIANGLE_STRIP", TRUE, (void *)&Chuck_OpenGL_TRIANGLE_STRIP );
    QUERY->add_svar( QUERY, "int", "TRIANGLE_FAN", TRUE, (void *)&Chuck_OpenGL_TRIANGLE_FAN );
    QUERY->add_svar( QUERY, "int", "QUADS", TRUE, (void *)&Chuck_OpenGL_QUADS );
    QUERY->add_svar( QUERY, "int", "NEVER", TRUE, (void *)&Chuck_OpenGL_NEVER );
    QUERY->add_svar( QUERY, "int", "LESS", TRUE, (void *)&Chuck_OpenGL_LESS );
    QUERY->add_svar( QUERY, "int", "EQUAL", TRUE, (void *)&Chuck_OpenGL_EQUAL );
    QUERY->add_svar( QUERY, "int", "LEQUAL", TRUE, (void *)&Chuck_OpenGL_LEQUAL );
    QUERY->add_svar( QUERY, "int", "GREATER", TRUE, (void *)&Chuck_OpenGL_GREATER );
    QUERY->add_svar( QUERY, "int", "NOTEQUAL", TRUE, (void *)&Chuck_OpenGL_NOTEQUAL );
    QUERY->add_svar( QUERY, "int", "GEQUAL", TRUE, (void *)&Chuck_OpenGL_GEQUAL );
    QUERY->add_svar( QUERY, "int", "ALWAYS", TRUE, (void *)&Chuck_OpenGL_ALWAYS );
    QUERY->add_svar( QUERY, "int", "ZERO", TRUE, (void *)&Chuck_OpenGL_ZERO );
    QUERY->add_svar( QUERY, "int", "ONE", TRUE, (void *)&Chuck_OpenGL_ONE );
    QUERY->add_svar( QUERY, "int", "SRC_COLOR", TRUE, (void *)&Chuck_OpenGL_SRC_COLOR );
    QUERY->add_svar( QUERY, "int", "ONE_MINUS_SRC_COLOR", TRUE, (void *)&Chuck_OpenGL_ONE_MINUS_SRC_COLOR );
    QUERY->add_svar( QUERY, "int", "SRC_ALPHA", TRUE, (void *)&Chuck_OpenGL_SRC_ALPHA );
    QUERY->add_svar( QUERY, "int", "ONE_MINUS_SRC_ALPHA", TRUE, (void *)&Chuck_OpenGL_ONE_MINUS_SRC_ALPHA );
    QUERY->add_svar( QUERY, "int", "DST_ALPHA", TRUE, (void *)&Chuck_OpenGL_DST_ALPHA );
    QUERY->add_svar( QUERY, "int", "ONE_MINUS_DST_ALPHA", TRUE, (void *)&Chuck_OpenGL_ONE_MINUS_DST_ALPHA );
    QUERY->add_svar( QUERY, "int", "DST_COLOR", TRUE, (void *)&Chuck_OpenGL_DST_COLOR );
    QUERY->add_svar( QUERY, "int", "ONE_MINUS_DST_COLOR", TRUE, (void *)&Chuck_OpenGL_ONE_MINUS_DST_COLOR );
    QUERY->add_svar( QUERY, "int", "SRC_ALPHA_SATURATE", TRUE, (void *)&Chuck_OpenGL_SRC_ALPHA_SATURATE );
    QUERY->add_svar( QUERY, "int", "NONE", TRUE, (void *)&Chuck_OpenGL_NONE );
    QUERY->add_svar( QUERY, "int", "FRONT_LEFT", TRUE, (void *)&Chuck_OpenGL_FRONT_LEFT );
    QUERY->add_svar( QUERY, "int", "FRONT_RIGHT", TRUE, (void *)&Chuck_OpenGL_FRONT_RIGHT );
    QUERY->add_svar( QUERY, "int", "BACK_LEFT", TRUE, (void *)&Chuck_OpenGL_BACK_LEFT );
    QUERY->add_svar( QUERY, "int", "BACK_RIGHT", TRUE, (void *)&Chuck_OpenGL_BACK_RIGHT );
    QUERY->add_svar( QUERY, "int", "FRONT", TRUE, (void *)&Chuck_OpenGL_FRONT );
    QUERY->add_svar( QUERY, "int", "BACK", TRUE, (void *)&Chuck_OpenGL_BACK );
    QUERY->add_svar( QUERY, "int", "LEFT", TRUE, (void *)&Chuck_OpenGL_LEFT );
    QUERY->add_svar( QUERY, "int", "RIGHT", TRUE, (void *)&Chuck_OpenGL_RIGHT );
    QUERY->add_svar( QUERY, "int", "FRONT_AND_BACK", TRUE, (void *)&Chuck_OpenGL_FRONT_AND_BACK );
    QUERY->add_svar( QUERY, "int", "NO_ERROR", TRUE, (void *)&Chuck_OpenGL_NO_ERROR );
    QUERY->add_svar( QUERY, "int", "INVALID_ENUM", TRUE, (void *)&Chuck_OpenGL_INVALID_ENUM );
    QUERY->add_svar( QUERY, "int", "INVALID_VALUE", TRUE, (void *)&Chuck_OpenGL_INVALID_VALUE );
    QUERY->add_svar( QUERY, "int", "INVALID_OPERATION", TRUE, (void *)&Chuck_OpenGL_INVALID_OPERATION );
    QUERY->add_svar( QUERY, "int", "OUT_OF_MEMORY", TRUE, (void *)&Chuck_OpenGL_OUT_OF_MEMORY );
    QUERY->add_svar( QUERY, "int", "CW", TRUE, (void *)&Chuck_OpenGL_CW );
    QUERY->add_svar( QUERY, "int", "CCW", TRUE, (void *)&Chuck_OpenGL_CCW );
    QUERY->add_svar( QUERY, "int", "POINT_SIZE", TRUE, (void *)&Chuck_OpenGL_POINT_SIZE );
    QUERY->add_svar( QUERY, "int", "POINT_SIZE_RANGE", TRUE, (void *)&Chuck_OpenGL_POINT_SIZE_RANGE );
    QUERY->add_svar( QUERY, "int", "POINT_SIZE_GRANULARITY", TRUE, (void *)&Chuck_OpenGL_POINT_SIZE_GRANULARITY );
    QUERY->add_svar( QUERY, "int", "LINE_SMOOTH", TRUE, (void *)&Chuck_OpenGL_LINE_SMOOTH );
    QUERY->add_svar( QUERY, "int", "LINE_WIDTH", TRUE, (void *)&Chuck_OpenGL_LINE_WIDTH );
    QUERY->add_svar( QUERY, "int", "LINE_WIDTH_RANGE", TRUE, (void *)&Chuck_OpenGL_LINE_WIDTH_RANGE );
    QUERY->add_svar( QUERY, "int", "LINE_WIDTH_GRANULARITY", TRUE, (void *)&Chuck_OpenGL_LINE_WIDTH_GRANULARITY );
    QUERY->add_svar( QUERY, "int", "POLYGON_MODE", TRUE, (void *)&Chuck_OpenGL_POLYGON_MODE );
    QUERY->add_svar( QUERY, "int", "POLYGON_SMOOTH", TRUE, (void *)&Chuck_OpenGL_POLYGON_SMOOTH );
    QUERY->add_svar( QUERY, "int", "CULL_FACE", TRUE, (void *)&Chuck_OpenGL_CULL_FACE );
    QUERY->add_svar( QUERY, "int", "CULL_FACE_MODE", TRUE, (void *)&Chuck_OpenGL_CULL_FACE_MODE );
    QUERY->add_svar( QUERY, "int", "FRONT_FACE", TRUE, (void *)&Chuck_OpenGL_FRONT_FACE );
    QUERY->add_svar( QUERY, "int", "DEPTH_RANGE", TRUE, (void *)&Chuck_OpenGL_DEPTH_RANGE );
    QUERY->add_svar( QUERY, "int", "DEPTH_TEST", TRUE, (void *)&Chuck_OpenGL_DEPTH_TEST );
    QUERY->add_svar( QUERY, "int", "DEPTH_WRITEMASK", TRUE, (void *)&Chuck_OpenGL_DEPTH_WRITEMASK );
    QUERY->add_svar( QUERY, "int", "DEPTH_CLEAR_VALUE", TRUE, (void *)&Chuck_OpenGL_DEPTH_CLEAR_VALUE );
    QUERY->add_svar( QUERY, "int", "DEPTH_FUNC", TRUE, (void *)&Chuck_OpenGL_DEPTH_FUNC );
    QUERY->add_svar( QUERY, "int", "STENCIL_TEST", TRUE, (void *)&Chuck_OpenGL_STENCIL_TEST );
    QUERY->add_svar( QUERY, "int", "STENCIL_CLEAR_VALUE", TRUE, (void *)&Chuck_OpenGL_STENCIL_CLEAR_VALUE );
    QUERY->add_svar( QUERY, "int", "STENCIL_FUNC", TRUE, (void *)&Chuck_OpenGL_STENCIL_FUNC );
    QUERY->add_svar( QUERY, "int", "STENCIL_VALUE_MASK", TRUE, (void *)&Chuck_OpenGL_STENCIL_VALUE_MASK );
    QUERY->add_svar( QUERY, "int", "STENCIL_FAIL", TRUE, (void *)&Chuck_OpenGL_STENCIL_FAIL );
    QUERY->add_svar( QUERY, "int", "STENCIL_PASS_DEPTH_FAIL", TRUE, (void *)&Chuck_OpenGL_STENCIL_PASS_DEPTH_FAIL );
    QUERY->add_svar( QUERY, "int", "STENCIL_PASS_DEPTH_PASS", TRUE, (void *)&Chuck_OpenGL_STENCIL_PASS_DEPTH_PASS );
    QUERY->add_svar( QUERY, "int", "STENCIL_REF", TRUE, (void *)&Chuck_OpenGL_STENCIL_REF );
    QUERY->add_svar( QUERY, "int", "STENCIL_WRITEMASK", TRUE, (void *)&Chuck_OpenGL_STENCIL_WRITEMASK );
    QUERY->add_svar( QUERY, "int", "VIEWPORT", TRUE, (void *)&Chuck_OpenGL_VIEWPORT );
    QUERY->add_svar( QUERY, "int", "DITHER", TRUE, (void *)&Chuck_OpenGL_DITHER );
    QUERY->add_svar( QUERY, "int", "BLEND_DST", TRUE, (void *)&Chuck_OpenGL_BLEND_DST );
    QUERY->add_svar( QUERY, "int", "BLEND_SRC", TRUE, (void *)&Chuck_OpenGL_BLEND_SRC );
    QUERY->add_svar( QUERY, "int", "BLEND", TRUE, (void *)&Chuck_OpenGL_BLEND );
    QUERY->add_svar( QUERY, "int", "LOGIC_OP_MODE", TRUE, (void *)&Chuck_OpenGL_LOGIC_OP_MODE );
    QUERY->add_svar( QUERY, "int", "COLOR_LOGIC_OP", TRUE, (void *)&Chuck_OpenGL_COLOR_LOGIC_OP );
    QUERY->add_svar( QUERY, "int", "DRAW_BUFFER", TRUE, (void *)&Chuck_OpenGL_DRAW_BUFFER );
    QUERY->add_svar( QUERY, "int", "READ_BUFFER", TRUE, (void *)&Chuck_OpenGL_READ_BUFFER );
    QUERY->add_svar( QUERY, "int", "SCISSOR_BOX", TRUE, (void *)&Chuck_OpenGL_SCISSOR_BOX );
    QUERY->add_svar( QUERY, "int", "SCISSOR_TEST", TRUE, (void *)&Chuck_OpenGL_SCISSOR_TEST );
    QUERY->add_svar( QUERY, "int", "COLOR_CLEAR_VALUE", TRUE, (void *)&Chuck_OpenGL_COLOR_CLEAR_VALUE );
    QUERY->add_svar( QUERY, "int", "COLOR_WRITEMASK", TRUE, (void *)&Chuck_OpenGL_COLOR_WRITEMASK );
    QUERY->add_svar( QUERY, "int", "DOUBLEBUFFER", TRUE, (void *)&Chuck_OpenGL_DOUBLEBUFFER );
    QUERY->add_svar( QUERY, "int", "STEREO", TRUE, (void *)&Chuck_OpenGL_STEREO );
    QUERY->add_svar( QUERY, "int", "LINE_SMOOTH_HINT", TRUE, (void *)&Chuck_OpenGL_LINE_SMOOTH_HINT );
    QUERY->add_svar( QUERY, "int", "POLYGON_SMOOTH_HINT", TRUE, (void *)&Chuck_OpenGL_POLYGON_SMOOTH_HINT );
    QUERY->add_svar( QUERY, "int", "UNPACK_SWAP_BYTES", TRUE, (void *)&Chuck_OpenGL_UNPACK_SWAP_BYTES );
    QUERY->add_svar( QUERY, "int", "UNPACK_LSB_FIRST", TRUE, (void *)&Chuck_OpenGL_UNPACK_LSB_FIRST );
    QUERY->add_svar( QUERY, "int", "UNPACK_ROW_LENGTH", TRUE, (void *)&Chuck_OpenGL_UNPACK_ROW_LENGTH );
    QUERY->add_svar( QUERY, "int", "UNPACK_SKIP_ROWS", TRUE, (void *)&Chuck_OpenGL_UNPACK_SKIP_ROWS );
    QUERY->add_svar( QUERY, "int", "UNPACK_SKIP_PIXELS", TRUE, (void *)&Chuck_OpenGL_UNPACK_SKIP_PIXELS );
    QUERY->add_svar( QUERY, "int", "UNPACK_ALIGNMENT", TRUE, (void *)&Chuck_OpenGL_UNPACK_ALIGNMENT );
    QUERY->add_svar( QUERY, "int", "PACK_SWAP_BYTES", TRUE, (void *)&Chuck_OpenGL_PACK_SWAP_BYTES );
    QUERY->add_svar( QUERY, "int", "PACK_LSB_FIRST", TRUE, (void *)&Chuck_OpenGL_PACK_LSB_FIRST );
    QUERY->add_svar( QUERY, "int", "PACK_ROW_LENGTH", TRUE, (void *)&Chuck_OpenGL_PACK_ROW_LENGTH );
    QUERY->add_svar( QUERY, "int", "PACK_SKIP_ROWS", TRUE, (void *)&Chuck_OpenGL_PACK_SKIP_ROWS );
    QUERY->add_svar( QUERY, "int", "PACK_SKIP_PIXELS", TRUE, (void *)&Chuck_OpenGL_PACK_SKIP_PIXELS );
    QUERY->add_svar( QUERY, "int", "PACK_ALIGNMENT", TRUE, (void *)&Chuck_OpenGL_PACK_ALIGNMENT );
    QUERY->add_svar( QUERY, "int", "MAX_TEXTURE_SIZE", TRUE, (void *)&Chuck_OpenGL_MAX_TEXTURE_SIZE );
    QUERY->add_svar( QUERY, "int", "MAX_VIEWPORT_DIMS", TRUE, (void *)&Chuck_OpenGL_MAX_VIEWPORT_DIMS );
    QUERY->add_svar( QUERY, "int", "SUBPIXEL_BITS", TRUE, (void *)&Chuck_OpenGL_SUBPIXEL_BITS );
    QUERY->add_svar( QUERY, "int", "TEXTURE_1D", TRUE, (void *)&Chuck_OpenGL_TEXTURE_1D );
    QUERY->add_svar( QUERY, "int", "TEXTURE_2D", TRUE, (void *)&Chuck_OpenGL_TEXTURE_2D );
    QUERY->add_svar( QUERY, "int", "POLYGON_OFFSET_UNITS", TRUE, (void *)&Chuck_OpenGL_POLYGON_OFFSET_UNITS );
    QUERY->add_svar( QUERY, "int", "POLYGON_OFFSET_POINT", TRUE, (void *)&Chuck_OpenGL_POLYGON_OFFSET_POINT );
    QUERY->add_svar( QUERY, "int", "POLYGON_OFFSET_LINE", TRUE, (void *)&Chuck_OpenGL_POLYGON_OFFSET_LINE );
    QUERY->add_svar( QUERY, "int", "POLYGON_OFFSET_FILL", TRUE, (void *)&Chuck_OpenGL_POLYGON_OFFSET_FILL );
    QUERY->add_svar( QUERY, "int", "POLYGON_OFFSET_FACTOR", TRUE, (void *)&Chuck_OpenGL_POLYGON_OFFSET_FACTOR );
    QUERY->add_svar( QUERY, "int", "TEXTURE_BINDING_1D", TRUE, (void *)&Chuck_OpenGL_TEXTURE_BINDING_1D );
    QUERY->add_svar( QUERY, "int", "TEXTURE_BINDING_2D", TRUE, (void *)&Chuck_OpenGL_TEXTURE_BINDING_2D );
    QUERY->add_svar( QUERY, "int", "TEXTURE_WIDTH", TRUE, (void *)&Chuck_OpenGL_TEXTURE_WIDTH );
    QUERY->add_svar( QUERY, "int", "TEXTURE_HEIGHT", TRUE, (void *)&Chuck_OpenGL_TEXTURE_HEIGHT );
    QUERY->add_svar( QUERY, "int", "TEXTURE_INTERNAL_FORMAT", TRUE, (void *)&Chuck_OpenGL_TEXTURE_INTERNAL_FORMAT );
    QUERY->add_svar( QUERY, "int", "TEXTURE_BORDER_COLOR", TRUE, (void *)&Chuck_OpenGL_TEXTURE_BORDER_COLOR );
    QUERY->add_svar( QUERY, "int", "TEXTURE_RED_SIZE", TRUE, (void *)&Chuck_OpenGL_TEXTURE_RED_SIZE );
    QUERY->add_svar( QUERY, "int", "TEXTURE_GREEN_SIZE", TRUE, (void *)&Chuck_OpenGL_TEXTURE_GREEN_SIZE );
    QUERY->add_svar( QUERY, "int", "TEXTURE_BLUE_SIZE", TRUE, (void *)&Chuck_OpenGL_TEXTURE_BLUE_SIZE );
    QUERY->add_svar( QUERY, "int", "TEXTURE_ALPHA_SIZE", TRUE, (void *)&Chuck_OpenGL_TEXTURE_ALPHA_SIZE );
    QUERY->add_svar( QUERY, "int", "DONT_CARE", TRUE, (void *)&Chuck_OpenGL_DONT_CARE );
    QUERY->add_svar( QUERY, "int", "FASTEST", TRUE, (void *)&Chuck_OpenGL_FASTEST );
    QUERY->add_svar( QUERY, "int", "NICEST", TRUE, (void *)&Chuck_OpenGL_NICEST );
    QUERY->add_svar( QUERY, "int", "BYTE", TRUE, (void *)&Chuck_OpenGL_BYTE );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_BYTE", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_BYTE );
    QUERY->add_svar( QUERY, "int", "SHORT", TRUE, (void *)&Chuck_OpenGL_SHORT );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_SHORT", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_SHORT );
    QUERY->add_svar( QUERY, "int", "INT", TRUE, (void *)&Chuck_OpenGL_INT );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_INT", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_INT );
    QUERY->add_svar( QUERY, "int", "FLOAT", TRUE, (void *)&Chuck_OpenGL_FLOAT );
    QUERY->add_svar( QUERY, "int", "DOUBLE", TRUE, (void *)&Chuck_OpenGL_DOUBLE );
    QUERY->add_svar( QUERY, "int", "STACK_OVERFLOW", TRUE, (void *)&Chuck_OpenGL_STACK_OVERFLOW );
    QUERY->add_svar( QUERY, "int", "STACK_UNDERFLOW", TRUE, (void *)&Chuck_OpenGL_STACK_UNDERFLOW );
    QUERY->add_svar( QUERY, "int", "CLEAR", TRUE, (void *)&Chuck_OpenGL_CLEAR );
    QUERY->add_svar( QUERY, "int", "AND", TRUE, (void *)&Chuck_OpenGL_AND );
    QUERY->add_svar( QUERY, "int", "AND_REVERSE", TRUE, (void *)&Chuck_OpenGL_AND_REVERSE );
    QUERY->add_svar( QUERY, "int", "COPY", TRUE, (void *)&Chuck_OpenGL_COPY );
    QUERY->add_svar( QUERY, "int", "AND_INVERTED", TRUE, (void *)&Chuck_OpenGL_AND_INVERTED );
    QUERY->add_svar( QUERY, "int", "NOOP", TRUE, (void *)&Chuck_OpenGL_NOOP );
    QUERY->add_svar( QUERY, "int", "XOR", TRUE, (void *)&Chuck_OpenGL_XOR );
    QUERY->add_svar( QUERY, "int", "OR", TRUE, (void *)&Chuck_OpenGL_OR );
    QUERY->add_svar( QUERY, "int", "NOR", TRUE, (void *)&Chuck_OpenGL_NOR );
    QUERY->add_svar( QUERY, "int", "EQUIV", TRUE, (void *)&Chuck_OpenGL_EQUIV );
    QUERY->add_svar( QUERY, "int", "INVERT", TRUE, (void *)&Chuck_OpenGL_INVERT );
    QUERY->add_svar( QUERY, "int", "OR_REVERSE", TRUE, (void *)&Chuck_OpenGL_OR_REVERSE );
    QUERY->add_svar( QUERY, "int", "COPY_INVERTED", TRUE, (void *)&Chuck_OpenGL_COPY_INVERTED );
    QUERY->add_svar( QUERY, "int", "OR_INVERTED", TRUE, (void *)&Chuck_OpenGL_OR_INVERTED );
    QUERY->add_svar( QUERY, "int", "NAND", TRUE, (void *)&Chuck_OpenGL_NAND );
    QUERY->add_svar( QUERY, "int", "SET", TRUE, (void *)&Chuck_OpenGL_SET );
    QUERY->add_svar( QUERY, "int", "TEXTURE", TRUE, (void *)&Chuck_OpenGL_TEXTURE );
    QUERY->add_svar( QUERY, "int", "COLOR", TRUE, (void *)&Chuck_OpenGL_COLOR );
    QUERY->add_svar( QUERY, "int", "DEPTH", TRUE, (void *)&Chuck_OpenGL_DEPTH );
    QUERY->add_svar( QUERY, "int", "STENCIL", TRUE, (void *)&Chuck_OpenGL_STENCIL );
    QUERY->add_svar( QUERY, "int", "STENCIL_INDEX", TRUE, (void *)&Chuck_OpenGL_STENCIL_INDEX );
    QUERY->add_svar( QUERY, "int", "DEPTH_COMPONENT", TRUE, (void *)&Chuck_OpenGL_DEPTH_COMPONENT );
    QUERY->add_svar( QUERY, "int", "RED", TRUE, (void *)&Chuck_OpenGL_RED );
    QUERY->add_svar( QUERY, "int", "GREEN", TRUE, (void *)&Chuck_OpenGL_GREEN );
    QUERY->add_svar( QUERY, "int", "BLUE", TRUE, (void *)&Chuck_OpenGL_BLUE );
    QUERY->add_svar( QUERY, "int", "ALPHA", TRUE, (void *)&Chuck_OpenGL_ALPHA );
    QUERY->add_svar( QUERY, "int", "RGB", TRUE, (void *)&Chuck_OpenGL_RGB );
    QUERY->add_svar( QUERY, "int", "RGBA", TRUE, (void *)&Chuck_OpenGL_RGBA );
    QUERY->add_svar( QUERY, "int", "POINT", TRUE, (void *)&Chuck_OpenGL_POINT );
    QUERY->add_svar( QUERY, "int", "LINE", TRUE, (void *)&Chuck_OpenGL_LINE );
    QUERY->add_svar( QUERY, "int", "FILL", TRUE, (void *)&Chuck_OpenGL_FILL );
    QUERY->add_svar( QUERY, "int", "KEEP", TRUE, (void *)&Chuck_OpenGL_KEEP );
    QUERY->add_svar( QUERY, "int", "REPLACE", TRUE, (void *)&Chuck_OpenGL_REPLACE );
    QUERY->add_svar( QUERY, "int", "INCR", TRUE, (void *)&Chuck_OpenGL_INCR );
    QUERY->add_svar( QUERY, "int", "DECR", TRUE, (void *)&Chuck_OpenGL_DECR );
    QUERY->add_svar( QUERY, "int", "VENDOR", TRUE, (void *)&Chuck_OpenGL_VENDOR );
    QUERY->add_svar( QUERY, "int", "RENDERER", TRUE, (void *)&Chuck_OpenGL_RENDERER );
    QUERY->add_svar( QUERY, "int", "VERSION", TRUE, (void *)&Chuck_OpenGL_VERSION );
    QUERY->add_svar( QUERY, "int", "EXTENSIONS", TRUE, (void *)&Chuck_OpenGL_EXTENSIONS );
    QUERY->add_svar( QUERY, "int", "NEAREST", TRUE, (void *)&Chuck_OpenGL_NEAREST );
    QUERY->add_svar( QUERY, "int", "LINEAR", TRUE, (void *)&Chuck_OpenGL_LINEAR );
    QUERY->add_svar( QUERY, "int", "NEAREST_MIPMAP_NEAREST", TRUE, (void *)&Chuck_OpenGL_NEAREST_MIPMAP_NEAREST );
    QUERY->add_svar( QUERY, "int", "LINEAR_MIPMAP_NEAREST", TRUE, (void *)&Chuck_OpenGL_LINEAR_MIPMAP_NEAREST );
    QUERY->add_svar( QUERY, "int", "NEAREST_MIPMAP_LINEAR", TRUE, (void *)&Chuck_OpenGL_NEAREST_MIPMAP_LINEAR );
    QUERY->add_svar( QUERY, "int", "LINEAR_MIPMAP_LINEAR", TRUE, (void *)&Chuck_OpenGL_LINEAR_MIPMAP_LINEAR );
    QUERY->add_svar( QUERY, "int", "TEXTURE_MAG_FILTER", TRUE, (void *)&Chuck_OpenGL_TEXTURE_MAG_FILTER );
    QUERY->add_svar( QUERY, "int", "TEXTURE_MIN_FILTER", TRUE, (void *)&Chuck_OpenGL_TEXTURE_MIN_FILTER );
    QUERY->add_svar( QUERY, "int", "TEXTURE_WRAP_S", TRUE, (void *)&Chuck_OpenGL_TEXTURE_WRAP_S );
    QUERY->add_svar( QUERY, "int", "TEXTURE_WRAP_T", TRUE, (void *)&Chuck_OpenGL_TEXTURE_WRAP_T );
    QUERY->add_svar( QUERY, "int", "PROXY_TEXTURE_1D", TRUE, (void *)&Chuck_OpenGL_PROXY_TEXTURE_1D );
    QUERY->add_svar( QUERY, "int", "PROXY_TEXTURE_2D", TRUE, (void *)&Chuck_OpenGL_PROXY_TEXTURE_2D );
    QUERY->add_svar( QUERY, "int", "REPEAT", TRUE, (void *)&Chuck_OpenGL_REPEAT );
    QUERY->add_svar( QUERY, "int", "R3_G3_B2", TRUE, (void *)&Chuck_OpenGL_R3_G3_B2 );
    QUERY->add_svar( QUERY, "int", "RGB4", TRUE, (void *)&Chuck_OpenGL_RGB4 );
    QUERY->add_svar( QUERY, "int", "RGB5", TRUE, (void *)&Chuck_OpenGL_RGB5 );
    QUERY->add_svar( QUERY, "int", "RGB8", TRUE, (void *)&Chuck_OpenGL_RGB8 );
    QUERY->add_svar( QUERY, "int", "RGB10", TRUE, (void *)&Chuck_OpenGL_RGB10 );
    QUERY->add_svar( QUERY, "int", "RGB12", TRUE, (void *)&Chuck_OpenGL_RGB12 );
    QUERY->add_svar( QUERY, "int", "RGB16", TRUE, (void *)&Chuck_OpenGL_RGB16 );
    QUERY->add_svar( QUERY, "int", "RGBA2", TRUE, (void *)&Chuck_OpenGL_RGBA2 );
    QUERY->add_svar( QUERY, "int", "RGBA4", TRUE, (void *)&Chuck_OpenGL_RGBA4 );
    QUERY->add_svar( QUERY, "int", "RGB5_A1", TRUE, (void *)&Chuck_OpenGL_RGB5_A1 );
    QUERY->add_svar( QUERY, "int", "RGBA8", TRUE, (void *)&Chuck_OpenGL_RGBA8 );
    QUERY->add_svar( QUERY, "int", "RGB10_A2", TRUE, (void *)&Chuck_OpenGL_RGB10_A2 );
    QUERY->add_svar( QUERY, "int", "RGBA12", TRUE, (void *)&Chuck_OpenGL_RGBA12 );
    QUERY->add_svar( QUERY, "int", "RGBA16", TRUE, (void *)&Chuck_OpenGL_RGBA16 );
    QUERY->add_svar( QUERY, "int", "CURRENT_BIT", TRUE, (void *)&Chuck_OpenGL_CURRENT_BIT );
    QUERY->add_svar( QUERY, "int", "POINT_BIT", TRUE, (void *)&Chuck_OpenGL_POINT_BIT );
    QUERY->add_svar( QUERY, "int", "LINE_BIT", TRUE, (void *)&Chuck_OpenGL_LINE_BIT );
    QUERY->add_svar( QUERY, "int", "POLYGON_BIT", TRUE, (void *)&Chuck_OpenGL_POLYGON_BIT );
    QUERY->add_svar( QUERY, "int", "POLYGON_STIPPLE_BIT", TRUE, (void *)&Chuck_OpenGL_POLYGON_STIPPLE_BIT );
    QUERY->add_svar( QUERY, "int", "PIXEL_MODE_BIT", TRUE, (void *)&Chuck_OpenGL_PIXEL_MODE_BIT );
    QUERY->add_svar( QUERY, "int", "LIGHTING_BIT", TRUE, (void *)&Chuck_OpenGL_LIGHTING_BIT );
    QUERY->add_svar( QUERY, "int", "FOG_BIT", TRUE, (void *)&Chuck_OpenGL_FOG_BIT );
    QUERY->add_svar( QUERY, "int", "ACCUM_BUFFER_BIT", TRUE, (void *)&Chuck_OpenGL_ACCUM_BUFFER_BIT );
    QUERY->add_svar( QUERY, "int", "VIEWPORT_BIT", TRUE, (void *)&Chuck_OpenGL_VIEWPORT_BIT );
    QUERY->add_svar( QUERY, "int", "TRANSFORM_BIT", TRUE, (void *)&Chuck_OpenGL_TRANSFORM_BIT );
    QUERY->add_svar( QUERY, "int", "ENABLE_BIT", TRUE, (void *)&Chuck_OpenGL_ENABLE_BIT );
    QUERY->add_svar( QUERY, "int", "HINT_BIT", TRUE, (void *)&Chuck_OpenGL_HINT_BIT );
    QUERY->add_svar( QUERY, "int", "EVAL_BIT", TRUE, (void *)&Chuck_OpenGL_EVAL_BIT );
    QUERY->add_svar( QUERY, "int", "LIST_BIT", TRUE, (void *)&Chuck_OpenGL_LIST_BIT );
    QUERY->add_svar( QUERY, "int", "TEXTURE_BIT", TRUE, (void *)&Chuck_OpenGL_TEXTURE_BIT );
    QUERY->add_svar( QUERY, "int", "SCISSOR_BIT", TRUE, (void *)&Chuck_OpenGL_SCISSOR_BIT );
    QUERY->add_svar( QUERY, "int", "ALL_ATTRIB_BITS", TRUE, (void *)&Chuck_OpenGL_ALL_ATTRIB_BITS );
    QUERY->add_svar( QUERY, "int", "CLIENT_PIXEL_STORE_BIT", TRUE, (void *)&Chuck_OpenGL_CLIENT_PIXEL_STORE_BIT );
    QUERY->add_svar( QUERY, "int", "CLIENT_VERTEX_ARRAY_BIT", TRUE, (void *)&Chuck_OpenGL_CLIENT_VERTEX_ARRAY_BIT );
    QUERY->add_svar( QUERY, "int", "CLIENT_ALL_ATTRIB_BITS", TRUE, (void *)&Chuck_OpenGL_CLIENT_ALL_ATTRIB_BITS );
    QUERY->add_svar( QUERY, "int", "QUAD_STRIP", TRUE, (void *)&Chuck_OpenGL_QUAD_STRIP );
    QUERY->add_svar( QUERY, "int", "POLYGON", TRUE, (void *)&Chuck_OpenGL_POLYGON );
    QUERY->add_svar( QUERY, "int", "ACCUM", TRUE, (void *)&Chuck_OpenGL_ACCUM );
    QUERY->add_svar( QUERY, "int", "LOAD", TRUE, (void *)&Chuck_OpenGL_LOAD );
    QUERY->add_svar( QUERY, "int", "RETURN", TRUE, (void *)&Chuck_OpenGL_RETURN );
    QUERY->add_svar( QUERY, "int", "MULT", TRUE, (void *)&Chuck_OpenGL_MULT );
    QUERY->add_svar( QUERY, "int", "ADD", TRUE, (void *)&Chuck_OpenGL_ADD );
    QUERY->add_svar( QUERY, "int", "AUX0", TRUE, (void *)&Chuck_OpenGL_AUX0 );
    QUERY->add_svar( QUERY, "int", "AUX1", TRUE, (void *)&Chuck_OpenGL_AUX1 );
    QUERY->add_svar( QUERY, "int", "AUX2", TRUE, (void *)&Chuck_OpenGL_AUX2 );
    QUERY->add_svar( QUERY, "int", "AUX3", TRUE, (void *)&Chuck_OpenGL_AUX3 );
    QUERY->add_svar( QUERY, "int", "2D", TRUE, (void *)&Chuck_OpenGL_2D );
    QUERY->add_svar( QUERY, "int", "3D", TRUE, (void *)&Chuck_OpenGL_3D );
    QUERY->add_svar( QUERY, "int", "3D_COLOR", TRUE, (void *)&Chuck_OpenGL_3D_COLOR );
    QUERY->add_svar( QUERY, "int", "3D_COLOR_TEXTURE", TRUE, (void *)&Chuck_OpenGL_3D_COLOR_TEXTURE );
    QUERY->add_svar( QUERY, "int", "4D_COLOR_TEXTURE", TRUE, (void *)&Chuck_OpenGL_4D_COLOR_TEXTURE );
    QUERY->add_svar( QUERY, "int", "PASS_THROUGH_TOKEN", TRUE, (void *)&Chuck_OpenGL_PASS_THROUGH_TOKEN );
    QUERY->add_svar( QUERY, "int", "POINT_TOKEN", TRUE, (void *)&Chuck_OpenGL_POINT_TOKEN );
    QUERY->add_svar( QUERY, "int", "LINE_TOKEN", TRUE, (void *)&Chuck_OpenGL_LINE_TOKEN );
    QUERY->add_svar( QUERY, "int", "POLYGON_TOKEN", TRUE, (void *)&Chuck_OpenGL_POLYGON_TOKEN );
    QUERY->add_svar( QUERY, "int", "BITMAP_TOKEN", TRUE, (void *)&Chuck_OpenGL_BITMAP_TOKEN );
    QUERY->add_svar( QUERY, "int", "DRAW_PIXEL_TOKEN", TRUE, (void *)&Chuck_OpenGL_DRAW_PIXEL_TOKEN );
    QUERY->add_svar( QUERY, "int", "COPY_PIXEL_TOKEN", TRUE, (void *)&Chuck_OpenGL_COPY_PIXEL_TOKEN );
    QUERY->add_svar( QUERY, "int", "LINE_RESET_TOKEN", TRUE, (void *)&Chuck_OpenGL_LINE_RESET_TOKEN );
    QUERY->add_svar( QUERY, "int", "EXP", TRUE, (void *)&Chuck_OpenGL_EXP );
    QUERY->add_svar( QUERY, "int", "EXP2", TRUE, (void *)&Chuck_OpenGL_EXP2 );
    QUERY->add_svar( QUERY, "int", "COEFF", TRUE, (void *)&Chuck_OpenGL_COEFF );
    QUERY->add_svar( QUERY, "int", "ORDER", TRUE, (void *)&Chuck_OpenGL_ORDER );
    QUERY->add_svar( QUERY, "int", "DOMAIN", TRUE, (void *)&Chuck_OpenGL_DOMAIN );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_I_TO_I", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_I_TO_I );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_S_TO_S", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_S_TO_S );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_I_TO_R", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_I_TO_R );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_I_TO_G", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_I_TO_G );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_I_TO_B", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_I_TO_B );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_I_TO_A", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_I_TO_A );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_R_TO_R", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_R_TO_R );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_G_TO_G", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_G_TO_G );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_B_TO_B", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_B_TO_B );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_A_TO_A", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_A_TO_A );
    QUERY->add_svar( QUERY, "int", "VERTEX_ARRAY_POINTER", TRUE, (void *)&Chuck_OpenGL_VERTEX_ARRAY_POINTER );
    QUERY->add_svar( QUERY, "int", "NORMAL_ARRAY_POINTER", TRUE, (void *)&Chuck_OpenGL_NORMAL_ARRAY_POINTER );
    QUERY->add_svar( QUERY, "int", "COLOR_ARRAY_POINTER", TRUE, (void *)&Chuck_OpenGL_COLOR_ARRAY_POINTER );
    QUERY->add_svar( QUERY, "int", "INDEX_ARRAY_POINTER", TRUE, (void *)&Chuck_OpenGL_INDEX_ARRAY_POINTER );
    QUERY->add_svar( QUERY, "int", "TEXTURE_COORD_ARRAY_POINTER", TRUE, (void *)&Chuck_OpenGL_TEXTURE_COORD_ARRAY_POINTER );
    QUERY->add_svar( QUERY, "int", "EDGE_FLAG_ARRAY_POINTER", TRUE, (void *)&Chuck_OpenGL_EDGE_FLAG_ARRAY_POINTER );
    QUERY->add_svar( QUERY, "int", "FEEDBACK_BUFFER_POINTER", TRUE, (void *)&Chuck_OpenGL_FEEDBACK_BUFFER_POINTER );
    QUERY->add_svar( QUERY, "int", "SELECTION_BUFFER_POINTER", TRUE, (void *)&Chuck_OpenGL_SELECTION_BUFFER_POINTER );
    QUERY->add_svar( QUERY, "int", "CURRENT_COLOR", TRUE, (void *)&Chuck_OpenGL_CURRENT_COLOR );
    QUERY->add_svar( QUERY, "int", "CURRENT_INDEX", TRUE, (void *)&Chuck_OpenGL_CURRENT_INDEX );
    QUERY->add_svar( QUERY, "int", "CURRENT_NORMAL", TRUE, (void *)&Chuck_OpenGL_CURRENT_NORMAL );
    QUERY->add_svar( QUERY, "int", "CURRENT_TEXTURE_COORDS", TRUE, (void *)&Chuck_OpenGL_CURRENT_TEXTURE_COORDS );
    QUERY->add_svar( QUERY, "int", "CURRENT_RASTER_COLOR", TRUE, (void *)&Chuck_OpenGL_CURRENT_RASTER_COLOR );
    QUERY->add_svar( QUERY, "int", "CURRENT_RASTER_INDEX", TRUE, (void *)&Chuck_OpenGL_CURRENT_RASTER_INDEX );
    QUERY->add_svar( QUERY, "int", "CURRENT_RASTER_TEXTURE_COORDS", TRUE, (void *)&Chuck_OpenGL_CURRENT_RASTER_TEXTURE_COORDS );
    QUERY->add_svar( QUERY, "int", "CURRENT_RASTER_POSITION", TRUE, (void *)&Chuck_OpenGL_CURRENT_RASTER_POSITION );
    QUERY->add_svar( QUERY, "int", "CURRENT_RASTER_POSITION_VALID", TRUE, (void *)&Chuck_OpenGL_CURRENT_RASTER_POSITION_VALID );
    QUERY->add_svar( QUERY, "int", "CURRENT_RASTER_DISTANCE", TRUE, (void *)&Chuck_OpenGL_CURRENT_RASTER_DISTANCE );
    QUERY->add_svar( QUERY, "int", "POINT_SMOOTH", TRUE, (void *)&Chuck_OpenGL_POINT_SMOOTH );
    QUERY->add_svar( QUERY, "int", "LINE_STIPPLE", TRUE, (void *)&Chuck_OpenGL_LINE_STIPPLE );
    QUERY->add_svar( QUERY, "int", "LINE_STIPPLE_PATTERN", TRUE, (void *)&Chuck_OpenGL_LINE_STIPPLE_PATTERN );
    QUERY->add_svar( QUERY, "int", "LINE_STIPPLE_REPEAT", TRUE, (void *)&Chuck_OpenGL_LINE_STIPPLE_REPEAT );
    QUERY->add_svar( QUERY, "int", "LIST_MODE", TRUE, (void *)&Chuck_OpenGL_LIST_MODE );
    QUERY->add_svar( QUERY, "int", "MAX_LIST_NESTING", TRUE, (void *)&Chuck_OpenGL_MAX_LIST_NESTING );
    QUERY->add_svar( QUERY, "int", "LIST_BASE", TRUE, (void *)&Chuck_OpenGL_LIST_BASE );
    QUERY->add_svar( QUERY, "int", "LIST_INDEX", TRUE, (void *)&Chuck_OpenGL_LIST_INDEX );
    QUERY->add_svar( QUERY, "int", "POLYGON_STIPPLE", TRUE, (void *)&Chuck_OpenGL_POLYGON_STIPPLE );
    QUERY->add_svar( QUERY, "int", "EDGE_FLAG", TRUE, (void *)&Chuck_OpenGL_EDGE_FLAG );
    QUERY->add_svar( QUERY, "int", "LIGHTING", TRUE, (void *)&Chuck_OpenGL_LIGHTING );
    QUERY->add_svar( QUERY, "int", "LIGHT_MODEL_LOCAL_VIEWER", TRUE, (void *)&Chuck_OpenGL_LIGHT_MODEL_LOCAL_VIEWER );
    QUERY->add_svar( QUERY, "int", "LIGHT_MODEL_TWO_SIDE", TRUE, (void *)&Chuck_OpenGL_LIGHT_MODEL_TWO_SIDE );
    QUERY->add_svar( QUERY, "int", "LIGHT_MODEL_AMBIENT", TRUE, (void *)&Chuck_OpenGL_LIGHT_MODEL_AMBIENT );
    QUERY->add_svar( QUERY, "int", "SHADE_MODEL", TRUE, (void *)&Chuck_OpenGL_SHADE_MODEL );
    QUERY->add_svar( QUERY, "int", "COLOR_MATERIAL_FACE", TRUE, (void *)&Chuck_OpenGL_COLOR_MATERIAL_FACE );
    QUERY->add_svar( QUERY, "int", "COLOR_MATERIAL_PARAMETER", TRUE, (void *)&Chuck_OpenGL_COLOR_MATERIAL_PARAMETER );
    QUERY->add_svar( QUERY, "int", "COLOR_MATERIAL", TRUE, (void *)&Chuck_OpenGL_COLOR_MATERIAL );
    QUERY->add_svar( QUERY, "int", "FOG", TRUE, (void *)&Chuck_OpenGL_FOG );
    QUERY->add_svar( QUERY, "int", "FOG_INDEX", TRUE, (void *)&Chuck_OpenGL_FOG_INDEX );
    QUERY->add_svar( QUERY, "int", "FOG_DENSITY", TRUE, (void *)&Chuck_OpenGL_FOG_DENSITY );
    QUERY->add_svar( QUERY, "int", "FOG_START", TRUE, (void *)&Chuck_OpenGL_FOG_START );
    QUERY->add_svar( QUERY, "int", "FOG_END", TRUE, (void *)&Chuck_OpenGL_FOG_END );
    QUERY->add_svar( QUERY, "int", "FOG_MODE", TRUE, (void *)&Chuck_OpenGL_FOG_MODE );
    QUERY->add_svar( QUERY, "int", "FOG_COLOR", TRUE, (void *)&Chuck_OpenGL_FOG_COLOR );
    QUERY->add_svar( QUERY, "int", "ACCUM_CLEAR_VALUE", TRUE, (void *)&Chuck_OpenGL_ACCUM_CLEAR_VALUE );
    QUERY->add_svar( QUERY, "int", "MATRIX_MODE", TRUE, (void *)&Chuck_OpenGL_MATRIX_MODE );
    QUERY->add_svar( QUERY, "int", "NORMALIZE", TRUE, (void *)&Chuck_OpenGL_NORMALIZE );
    QUERY->add_svar( QUERY, "int", "MODELVIEW_STACK_DEPTH", TRUE, (void *)&Chuck_OpenGL_MODELVIEW_STACK_DEPTH );
    QUERY->add_svar( QUERY, "int", "PROJECTION_STACK_DEPTH", TRUE, (void *)&Chuck_OpenGL_PROJECTION_STACK_DEPTH );
    QUERY->add_svar( QUERY, "int", "TEXTURE_STACK_DEPTH", TRUE, (void *)&Chuck_OpenGL_TEXTURE_STACK_DEPTH );
    QUERY->add_svar( QUERY, "int", "MODELVIEW_MATRIX", TRUE, (void *)&Chuck_OpenGL_MODELVIEW_MATRIX );
    QUERY->add_svar( QUERY, "int", "PROJECTION_MATRIX", TRUE, (void *)&Chuck_OpenGL_PROJECTION_MATRIX );
    QUERY->add_svar( QUERY, "int", "TEXTURE_MATRIX", TRUE, (void *)&Chuck_OpenGL_TEXTURE_MATRIX );
    QUERY->add_svar( QUERY, "int", "ATTRIB_STACK_DEPTH", TRUE, (void *)&Chuck_OpenGL_ATTRIB_STACK_DEPTH );
    QUERY->add_svar( QUERY, "int", "CLIENT_ATTRIB_STACK_DEPTH", TRUE, (void *)&Chuck_OpenGL_CLIENT_ATTRIB_STACK_DEPTH );
    QUERY->add_svar( QUERY, "int", "ALPHA_TEST", TRUE, (void *)&Chuck_OpenGL_ALPHA_TEST );
    QUERY->add_svar( QUERY, "int", "ALPHA_TEST_FUNC", TRUE, (void *)&Chuck_OpenGL_ALPHA_TEST_FUNC );
    QUERY->add_svar( QUERY, "int", "ALPHA_TEST_REF", TRUE, (void *)&Chuck_OpenGL_ALPHA_TEST_REF );
    QUERY->add_svar( QUERY, "int", "INDEX_LOGIC_OP", TRUE, (void *)&Chuck_OpenGL_INDEX_LOGIC_OP );
    QUERY->add_svar( QUERY, "int", "LOGIC_OP", TRUE, (void *)&Chuck_OpenGL_LOGIC_OP );
    QUERY->add_svar( QUERY, "int", "AUX_BUFFERS", TRUE, (void *)&Chuck_OpenGL_AUX_BUFFERS );
    QUERY->add_svar( QUERY, "int", "INDEX_CLEAR_VALUE", TRUE, (void *)&Chuck_OpenGL_INDEX_CLEAR_VALUE );
    QUERY->add_svar( QUERY, "int", "INDEX_WRITEMASK", TRUE, (void *)&Chuck_OpenGL_INDEX_WRITEMASK );
    QUERY->add_svar( QUERY, "int", "INDEX_MODE", TRUE, (void *)&Chuck_OpenGL_INDEX_MODE );
    QUERY->add_svar( QUERY, "int", "RGBA_MODE", TRUE, (void *)&Chuck_OpenGL_RGBA_MODE );
    QUERY->add_svar( QUERY, "int", "RENDER_MODE", TRUE, (void *)&Chuck_OpenGL_RENDER_MODE );
    QUERY->add_svar( QUERY, "int", "PERSPECTIVE_CORRECTION_HINT", TRUE, (void *)&Chuck_OpenGL_PERSPECTIVE_CORRECTION_HINT );
    QUERY->add_svar( QUERY, "int", "POINT_SMOOTH_HINT", TRUE, (void *)&Chuck_OpenGL_POINT_SMOOTH_HINT );
    QUERY->add_svar( QUERY, "int", "FOG_HINT", TRUE, (void *)&Chuck_OpenGL_FOG_HINT );
    QUERY->add_svar( QUERY, "int", "TEXTURE_GEN_S", TRUE, (void *)&Chuck_OpenGL_TEXTURE_GEN_S );
    QUERY->add_svar( QUERY, "int", "TEXTURE_GEN_T", TRUE, (void *)&Chuck_OpenGL_TEXTURE_GEN_T );
    QUERY->add_svar( QUERY, "int", "TEXTURE_GEN_R", TRUE, (void *)&Chuck_OpenGL_TEXTURE_GEN_R );
    QUERY->add_svar( QUERY, "int", "TEXTURE_GEN_Q", TRUE, (void *)&Chuck_OpenGL_TEXTURE_GEN_Q );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_I_TO_I_SIZE", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_I_TO_I_SIZE );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_S_TO_S_SIZE", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_S_TO_S_SIZE );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_I_TO_R_SIZE", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_I_TO_R_SIZE );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_I_TO_G_SIZE", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_I_TO_G_SIZE );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_I_TO_B_SIZE", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_I_TO_B_SIZE );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_I_TO_A_SIZE", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_I_TO_A_SIZE );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_R_TO_R_SIZE", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_R_TO_R_SIZE );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_G_TO_G_SIZE", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_G_TO_G_SIZE );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_B_TO_B_SIZE", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_B_TO_B_SIZE );
    QUERY->add_svar( QUERY, "int", "PIXEL_MAP_A_TO_A_SIZE", TRUE, (void *)&Chuck_OpenGL_PIXEL_MAP_A_TO_A_SIZE );
    QUERY->add_svar( QUERY, "int", "MAP_COLOR", TRUE, (void *)&Chuck_OpenGL_MAP_COLOR );
    QUERY->add_svar( QUERY, "int", "MAP_STENCIL", TRUE, (void *)&Chuck_OpenGL_MAP_STENCIL );
    QUERY->add_svar( QUERY, "int", "INDEX_SHIFT", TRUE, (void *)&Chuck_OpenGL_INDEX_SHIFT );
    QUERY->add_svar( QUERY, "int", "INDEX_OFFSET", TRUE, (void *)&Chuck_OpenGL_INDEX_OFFSET );
    QUERY->add_svar( QUERY, "int", "RED_SCALE", TRUE, (void *)&Chuck_OpenGL_RED_SCALE );
    QUERY->add_svar( QUERY, "int", "RED_BIAS", TRUE, (void *)&Chuck_OpenGL_RED_BIAS );
    QUERY->add_svar( QUERY, "int", "ZOOM_X", TRUE, (void *)&Chuck_OpenGL_ZOOM_X );
    QUERY->add_svar( QUERY, "int", "ZOOM_Y", TRUE, (void *)&Chuck_OpenGL_ZOOM_Y );
    QUERY->add_svar( QUERY, "int", "GREEN_SCALE", TRUE, (void *)&Chuck_OpenGL_GREEN_SCALE );
    QUERY->add_svar( QUERY, "int", "GREEN_BIAS", TRUE, (void *)&Chuck_OpenGL_GREEN_BIAS );
    QUERY->add_svar( QUERY, "int", "BLUE_SCALE", TRUE, (void *)&Chuck_OpenGL_BLUE_SCALE );
    QUERY->add_svar( QUERY, "int", "BLUE_BIAS", TRUE, (void *)&Chuck_OpenGL_BLUE_BIAS );
    QUERY->add_svar( QUERY, "int", "ALPHA_SCALE", TRUE, (void *)&Chuck_OpenGL_ALPHA_SCALE );
    QUERY->add_svar( QUERY, "int", "ALPHA_BIAS", TRUE, (void *)&Chuck_OpenGL_ALPHA_BIAS );
    QUERY->add_svar( QUERY, "int", "DEPTH_SCALE", TRUE, (void *)&Chuck_OpenGL_DEPTH_SCALE );
    QUERY->add_svar( QUERY, "int", "DEPTH_BIAS", TRUE, (void *)&Chuck_OpenGL_DEPTH_BIAS );
    QUERY->add_svar( QUERY, "int", "MAX_EVAL_ORDER", TRUE, (void *)&Chuck_OpenGL_MAX_EVAL_ORDER );
    QUERY->add_svar( QUERY, "int", "MAX_LIGHTS", TRUE, (void *)&Chuck_OpenGL_MAX_LIGHTS );
    QUERY->add_svar( QUERY, "int", "MAX_CLIP_PLANES", TRUE, (void *)&Chuck_OpenGL_MAX_CLIP_PLANES );
    QUERY->add_svar( QUERY, "int", "MAX_PIXEL_MAP_TABLE", TRUE, (void *)&Chuck_OpenGL_MAX_PIXEL_MAP_TABLE );
    QUERY->add_svar( QUERY, "int", "MAX_ATTRIB_STACK_DEPTH", TRUE, (void *)&Chuck_OpenGL_MAX_ATTRIB_STACK_DEPTH );
    QUERY->add_svar( QUERY, "int", "MAX_MODELVIEW_STACK_DEPTH", TRUE, (void *)&Chuck_OpenGL_MAX_MODELVIEW_STACK_DEPTH );
    QUERY->add_svar( QUERY, "int", "MAX_NAME_STACK_DEPTH", TRUE, (void *)&Chuck_OpenGL_MAX_NAME_STACK_DEPTH );
    QUERY->add_svar( QUERY, "int", "MAX_PROJECTION_STACK_DEPTH", TRUE, (void *)&Chuck_OpenGL_MAX_PROJECTION_STACK_DEPTH );
    QUERY->add_svar( QUERY, "int", "MAX_TEXTURE_STACK_DEPTH", TRUE, (void *)&Chuck_OpenGL_MAX_TEXTURE_STACK_DEPTH );
    QUERY->add_svar( QUERY, "int", "MAX_CLIENT_ATTRIB_STACK_DEPTH", TRUE, (void *)&Chuck_OpenGL_MAX_CLIENT_ATTRIB_STACK_DEPTH );
    QUERY->add_svar( QUERY, "int", "INDEX_BITS", TRUE, (void *)&Chuck_OpenGL_INDEX_BITS );
    QUERY->add_svar( QUERY, "int", "RED_BITS", TRUE, (void *)&Chuck_OpenGL_RED_BITS );
    QUERY->add_svar( QUERY, "int", "GREEN_BITS", TRUE, (void *)&Chuck_OpenGL_GREEN_BITS );
    QUERY->add_svar( QUERY, "int", "BLUE_BITS", TRUE, (void *)&Chuck_OpenGL_BLUE_BITS );
    QUERY->add_svar( QUERY, "int", "ALPHA_BITS", TRUE, (void *)&Chuck_OpenGL_ALPHA_BITS );
    QUERY->add_svar( QUERY, "int", "DEPTH_BITS", TRUE, (void *)&Chuck_OpenGL_DEPTH_BITS );
    QUERY->add_svar( QUERY, "int", "STENCIL_BITS", TRUE, (void *)&Chuck_OpenGL_STENCIL_BITS );
    QUERY->add_svar( QUERY, "int", "ACCUM_RED_BITS", TRUE, (void *)&Chuck_OpenGL_ACCUM_RED_BITS );
    QUERY->add_svar( QUERY, "int", "ACCUM_GREEN_BITS", TRUE, (void *)&Chuck_OpenGL_ACCUM_GREEN_BITS );
    QUERY->add_svar( QUERY, "int", "ACCUM_BLUE_BITS", TRUE, (void *)&Chuck_OpenGL_ACCUM_BLUE_BITS );
    QUERY->add_svar( QUERY, "int", "ACCUM_ALPHA_BITS", TRUE, (void *)&Chuck_OpenGL_ACCUM_ALPHA_BITS );
    QUERY->add_svar( QUERY, "int", "NAME_STACK_DEPTH", TRUE, (void *)&Chuck_OpenGL_NAME_STACK_DEPTH );
    QUERY->add_svar( QUERY, "int", "AUTO_NORMAL", TRUE, (void *)&Chuck_OpenGL_AUTO_NORMAL );
    QUERY->add_svar( QUERY, "int", "MAP1_COLOR_4", TRUE, (void *)&Chuck_OpenGL_MAP1_COLOR_4 );
    QUERY->add_svar( QUERY, "int", "MAP1_INDEX", TRUE, (void *)&Chuck_OpenGL_MAP1_INDEX );
    QUERY->add_svar( QUERY, "int", "MAP1_NORMAL", TRUE, (void *)&Chuck_OpenGL_MAP1_NORMAL );
    QUERY->add_svar( QUERY, "int", "MAP1_TEXTURE_COORD_1", TRUE, (void *)&Chuck_OpenGL_MAP1_TEXTURE_COORD_1 );
    QUERY->add_svar( QUERY, "int", "MAP1_TEXTURE_COORD_2", TRUE, (void *)&Chuck_OpenGL_MAP1_TEXTURE_COORD_2 );
    QUERY->add_svar( QUERY, "int", "MAP1_TEXTURE_COORD_3", TRUE, (void *)&Chuck_OpenGL_MAP1_TEXTURE_COORD_3 );
    QUERY->add_svar( QUERY, "int", "MAP1_TEXTURE_COORD_4", TRUE, (void *)&Chuck_OpenGL_MAP1_TEXTURE_COORD_4 );
    QUERY->add_svar( QUERY, "int", "MAP1_VERTEX_3", TRUE, (void *)&Chuck_OpenGL_MAP1_VERTEX_3 );
    QUERY->add_svar( QUERY, "int", "MAP1_VERTEX_4", TRUE, (void *)&Chuck_OpenGL_MAP1_VERTEX_4 );
    QUERY->add_svar( QUERY, "int", "MAP2_COLOR_4", TRUE, (void *)&Chuck_OpenGL_MAP2_COLOR_4 );
    QUERY->add_svar( QUERY, "int", "MAP2_INDEX", TRUE, (void *)&Chuck_OpenGL_MAP2_INDEX );
    QUERY->add_svar( QUERY, "int", "MAP2_NORMAL", TRUE, (void *)&Chuck_OpenGL_MAP2_NORMAL );
    QUERY->add_svar( QUERY, "int", "MAP2_TEXTURE_COORD_1", TRUE, (void *)&Chuck_OpenGL_MAP2_TEXTURE_COORD_1 );
    QUERY->add_svar( QUERY, "int", "MAP2_TEXTURE_COORD_2", TRUE, (void *)&Chuck_OpenGL_MAP2_TEXTURE_COORD_2 );
    QUERY->add_svar( QUERY, "int", "MAP2_TEXTURE_COORD_3", TRUE, (void *)&Chuck_OpenGL_MAP2_TEXTURE_COORD_3 );
    QUERY->add_svar( QUERY, "int", "MAP2_TEXTURE_COORD_4", TRUE, (void *)&Chuck_OpenGL_MAP2_TEXTURE_COORD_4 );
    QUERY->add_svar( QUERY, "int", "MAP2_VERTEX_3", TRUE, (void *)&Chuck_OpenGL_MAP2_VERTEX_3 );
    QUERY->add_svar( QUERY, "int", "MAP2_VERTEX_4", TRUE, (void *)&Chuck_OpenGL_MAP2_VERTEX_4 );
    QUERY->add_svar( QUERY, "int", "MAP1_GRID_DOMAIN", TRUE, (void *)&Chuck_OpenGL_MAP1_GRID_DOMAIN );
    QUERY->add_svar( QUERY, "int", "MAP1_GRID_SEGMENTS", TRUE, (void *)&Chuck_OpenGL_MAP1_GRID_SEGMENTS );
    QUERY->add_svar( QUERY, "int", "MAP2_GRID_DOMAIN", TRUE, (void *)&Chuck_OpenGL_MAP2_GRID_DOMAIN );
    QUERY->add_svar( QUERY, "int", "MAP2_GRID_SEGMENTS", TRUE, (void *)&Chuck_OpenGL_MAP2_GRID_SEGMENTS );
    QUERY->add_svar( QUERY, "int", "FEEDBACK_BUFFER_SIZE", TRUE, (void *)&Chuck_OpenGL_FEEDBACK_BUFFER_SIZE );
    QUERY->add_svar( QUERY, "int", "FEEDBACK_BUFFER_TYPE", TRUE, (void *)&Chuck_OpenGL_FEEDBACK_BUFFER_TYPE );
    QUERY->add_svar( QUERY, "int", "SELECTION_BUFFER_SIZE", TRUE, (void *)&Chuck_OpenGL_SELECTION_BUFFER_SIZE );
    QUERY->add_svar( QUERY, "int", "VERTEX_ARRAY", TRUE, (void *)&Chuck_OpenGL_VERTEX_ARRAY );
    QUERY->add_svar( QUERY, "int", "NORMAL_ARRAY", TRUE, (void *)&Chuck_OpenGL_NORMAL_ARRAY );
    QUERY->add_svar( QUERY, "int", "COLOR_ARRAY", TRUE, (void *)&Chuck_OpenGL_COLOR_ARRAY );
    QUERY->add_svar( QUERY, "int", "INDEX_ARRAY", TRUE, (void *)&Chuck_OpenGL_INDEX_ARRAY );
    QUERY->add_svar( QUERY, "int", "TEXTURE_COORD_ARRAY", TRUE, (void *)&Chuck_OpenGL_TEXTURE_COORD_ARRAY );
    QUERY->add_svar( QUERY, "int", "EDGE_FLAG_ARRAY", TRUE, (void *)&Chuck_OpenGL_EDGE_FLAG_ARRAY );
    QUERY->add_svar( QUERY, "int", "VERTEX_ARRAY_SIZE", TRUE, (void *)&Chuck_OpenGL_VERTEX_ARRAY_SIZE );
    QUERY->add_svar( QUERY, "int", "VERTEX_ARRAY_TYPE", TRUE, (void *)&Chuck_OpenGL_VERTEX_ARRAY_TYPE );
    QUERY->add_svar( QUERY, "int", "VERTEX_ARRAY_STRIDE", TRUE, (void *)&Chuck_OpenGL_VERTEX_ARRAY_STRIDE );
    QUERY->add_svar( QUERY, "int", "NORMAL_ARRAY_TYPE", TRUE, (void *)&Chuck_OpenGL_NORMAL_ARRAY_TYPE );
    QUERY->add_svar( QUERY, "int", "NORMAL_ARRAY_STRIDE", TRUE, (void *)&Chuck_OpenGL_NORMAL_ARRAY_STRIDE );
    QUERY->add_svar( QUERY, "int", "COLOR_ARRAY_SIZE", TRUE, (void *)&Chuck_OpenGL_COLOR_ARRAY_SIZE );
    QUERY->add_svar( QUERY, "int", "COLOR_ARRAY_TYPE", TRUE, (void *)&Chuck_OpenGL_COLOR_ARRAY_TYPE );
    QUERY->add_svar( QUERY, "int", "COLOR_ARRAY_STRIDE", TRUE, (void *)&Chuck_OpenGL_COLOR_ARRAY_STRIDE );
    QUERY->add_svar( QUERY, "int", "INDEX_ARRAY_TYPE", TRUE, (void *)&Chuck_OpenGL_INDEX_ARRAY_TYPE );
    QUERY->add_svar( QUERY, "int", "INDEX_ARRAY_STRIDE", TRUE, (void *)&Chuck_OpenGL_INDEX_ARRAY_STRIDE );
    QUERY->add_svar( QUERY, "int", "TEXTURE_COORD_ARRAY_SIZE", TRUE, (void *)&Chuck_OpenGL_TEXTURE_COORD_ARRAY_SIZE );
    QUERY->add_svar( QUERY, "int", "TEXTURE_COORD_ARRAY_TYPE", TRUE, (void *)&Chuck_OpenGL_TEXTURE_COORD_ARRAY_TYPE );
    QUERY->add_svar( QUERY, "int", "TEXTURE_COORD_ARRAY_STRIDE", TRUE, (void *)&Chuck_OpenGL_TEXTURE_COORD_ARRAY_STRIDE );
    QUERY->add_svar( QUERY, "int", "EDGE_FLAG_ARRAY_STRIDE", TRUE, (void *)&Chuck_OpenGL_EDGE_FLAG_ARRAY_STRIDE );
    QUERY->add_svar( QUERY, "int", "TEXTURE_COMPONENTS", TRUE, (void *)&Chuck_OpenGL_TEXTURE_COMPONENTS );
    QUERY->add_svar( QUERY, "int", "TEXTURE_BORDER", TRUE, (void *)&Chuck_OpenGL_TEXTURE_BORDER );
    QUERY->add_svar( QUERY, "int", "TEXTURE_LUMINANCE_SIZE", TRUE, (void *)&Chuck_OpenGL_TEXTURE_LUMINANCE_SIZE );
    QUERY->add_svar( QUERY, "int", "TEXTURE_INTENSITY_SIZE", TRUE, (void *)&Chuck_OpenGL_TEXTURE_INTENSITY_SIZE );
    QUERY->add_svar( QUERY, "int", "TEXTURE_PRIORITY", TRUE, (void *)&Chuck_OpenGL_TEXTURE_PRIORITY );
    QUERY->add_svar( QUERY, "int", "TEXTURE_RESIDENT", TRUE, (void *)&Chuck_OpenGL_TEXTURE_RESIDENT );
    QUERY->add_svar( QUERY, "int", "AMBIENT", TRUE, (void *)&Chuck_OpenGL_AMBIENT );
    QUERY->add_svar( QUERY, "int", "DIFFUSE", TRUE, (void *)&Chuck_OpenGL_DIFFUSE );
    QUERY->add_svar( QUERY, "int", "SPECULAR", TRUE, (void *)&Chuck_OpenGL_SPECULAR );
    QUERY->add_svar( QUERY, "int", "POSITION", TRUE, (void *)&Chuck_OpenGL_POSITION );
    QUERY->add_svar( QUERY, "int", "SPOT_DIRECTION", TRUE, (void *)&Chuck_OpenGL_SPOT_DIRECTION );
    QUERY->add_svar( QUERY, "int", "SPOT_EXPONENT", TRUE, (void *)&Chuck_OpenGL_SPOT_EXPONENT );
    QUERY->add_svar( QUERY, "int", "SPOT_CUTOFF", TRUE, (void *)&Chuck_OpenGL_SPOT_CUTOFF );
    QUERY->add_svar( QUERY, "int", "CONSTANT_ATTENUATION", TRUE, (void *)&Chuck_OpenGL_CONSTANT_ATTENUATION );
    QUERY->add_svar( QUERY, "int", "LINEAR_ATTENUATION", TRUE, (void *)&Chuck_OpenGL_LINEAR_ATTENUATION );
    QUERY->add_svar( QUERY, "int", "QUADRATIC_ATTENUATION", TRUE, (void *)&Chuck_OpenGL_QUADRATIC_ATTENUATION );
    QUERY->add_svar( QUERY, "int", "COMPILE", TRUE, (void *)&Chuck_OpenGL_COMPILE );
    QUERY->add_svar( QUERY, "int", "COMPILE_AND_EXECUTE", TRUE, (void *)&Chuck_OpenGL_COMPILE_AND_EXECUTE );
    QUERY->add_svar( QUERY, "int", "2_BYTES", TRUE, (void *)&Chuck_OpenGL_2_BYTES );
    QUERY->add_svar( QUERY, "int", "3_BYTES", TRUE, (void *)&Chuck_OpenGL_3_BYTES );
    QUERY->add_svar( QUERY, "int", "4_BYTES", TRUE, (void *)&Chuck_OpenGL_4_BYTES );
    QUERY->add_svar( QUERY, "int", "EMISSION", TRUE, (void *)&Chuck_OpenGL_EMISSION );
    QUERY->add_svar( QUERY, "int", "SHININESS", TRUE, (void *)&Chuck_OpenGL_SHININESS );
    QUERY->add_svar( QUERY, "int", "AMBIENT_AND_DIFFUSE", TRUE, (void *)&Chuck_OpenGL_AMBIENT_AND_DIFFUSE );
    QUERY->add_svar( QUERY, "int", "COLOR_INDEXES", TRUE, (void *)&Chuck_OpenGL_COLOR_INDEXES );
    QUERY->add_svar( QUERY, "int", "MODELVIEW", TRUE, (void *)&Chuck_OpenGL_MODELVIEW );
    QUERY->add_svar( QUERY, "int", "PROJECTION", TRUE, (void *)&Chuck_OpenGL_PROJECTION );
    QUERY->add_svar( QUERY, "int", "COLOR_INDEX", TRUE, (void *)&Chuck_OpenGL_COLOR_INDEX );
    QUERY->add_svar( QUERY, "int", "LUMINANCE", TRUE, (void *)&Chuck_OpenGL_LUMINANCE );
    QUERY->add_svar( QUERY, "int", "LUMINANCE_ALPHA", TRUE, (void *)&Chuck_OpenGL_LUMINANCE_ALPHA );
    QUERY->add_svar( QUERY, "int", "BITMAP", TRUE, (void *)&Chuck_OpenGL_BITMAP );
    QUERY->add_svar( QUERY, "int", "RENDER", TRUE, (void *)&Chuck_OpenGL_RENDER );
    QUERY->add_svar( QUERY, "int", "FEEDBACK", TRUE, (void *)&Chuck_OpenGL_FEEDBACK );
    QUERY->add_svar( QUERY, "int", "SELECT", TRUE, (void *)&Chuck_OpenGL_SELECT );
    QUERY->add_svar( QUERY, "int", "FLAT", TRUE, (void *)&Chuck_OpenGL_FLAT );
    QUERY->add_svar( QUERY, "int", "SMOOTH", TRUE, (void *)&Chuck_OpenGL_SMOOTH );
    QUERY->add_svar( QUERY, "int", "S", TRUE, (void *)&Chuck_OpenGL_S );
    QUERY->add_svar( QUERY, "int", "T", TRUE, (void *)&Chuck_OpenGL_T );
    QUERY->add_svar( QUERY, "int", "R", TRUE, (void *)&Chuck_OpenGL_R );
    QUERY->add_svar( QUERY, "int", "Q", TRUE, (void *)&Chuck_OpenGL_Q );
    QUERY->add_svar( QUERY, "int", "MODULATE", TRUE, (void *)&Chuck_OpenGL_MODULATE );
    QUERY->add_svar( QUERY, "int", "DECAL", TRUE, (void *)&Chuck_OpenGL_DECAL );
    QUERY->add_svar( QUERY, "int", "TEXTURE_ENV_MODE", TRUE, (void *)&Chuck_OpenGL_TEXTURE_ENV_MODE );
    QUERY->add_svar( QUERY, "int", "TEXTURE_ENV_COLOR", TRUE, (void *)&Chuck_OpenGL_TEXTURE_ENV_COLOR );
    QUERY->add_svar( QUERY, "int", "TEXTURE_ENV", TRUE, (void *)&Chuck_OpenGL_TEXTURE_ENV );
    QUERY->add_svar( QUERY, "int", "EYE_LINEAR", TRUE, (void *)&Chuck_OpenGL_EYE_LINEAR );
    QUERY->add_svar( QUERY, "int", "OBJECT_LINEAR", TRUE, (void *)&Chuck_OpenGL_OBJECT_LINEAR );
    QUERY->add_svar( QUERY, "int", "SPHERE_MAP", TRUE, (void *)&Chuck_OpenGL_SPHERE_MAP );
    QUERY->add_svar( QUERY, "int", "TEXTURE_GEN_MODE", TRUE, (void *)&Chuck_OpenGL_TEXTURE_GEN_MODE );
    QUERY->add_svar( QUERY, "int", "OBJECT_PLANE", TRUE, (void *)&Chuck_OpenGL_OBJECT_PLANE );
    QUERY->add_svar( QUERY, "int", "EYE_PLANE", TRUE, (void *)&Chuck_OpenGL_EYE_PLANE );
    QUERY->add_svar( QUERY, "int", "CLAMP", TRUE, (void *)&Chuck_OpenGL_CLAMP );
    QUERY->add_svar( QUERY, "int", "ALPHA4", TRUE, (void *)&Chuck_OpenGL_ALPHA4 );
    QUERY->add_svar( QUERY, "int", "ALPHA8", TRUE, (void *)&Chuck_OpenGL_ALPHA8 );
    QUERY->add_svar( QUERY, "int", "ALPHA12", TRUE, (void *)&Chuck_OpenGL_ALPHA12 );
    QUERY->add_svar( QUERY, "int", "ALPHA16", TRUE, (void *)&Chuck_OpenGL_ALPHA16 );
    QUERY->add_svar( QUERY, "int", "LUMINANCE4", TRUE, (void *)&Chuck_OpenGL_LUMINANCE4 );
    QUERY->add_svar( QUERY, "int", "LUMINANCE8", TRUE, (void *)&Chuck_OpenGL_LUMINANCE8 );
    QUERY->add_svar( QUERY, "int", "LUMINANCE12", TRUE, (void *)&Chuck_OpenGL_LUMINANCE12 );
    QUERY->add_svar( QUERY, "int", "LUMINANCE16", TRUE, (void *)&Chuck_OpenGL_LUMINANCE16 );
    QUERY->add_svar( QUERY, "int", "LUMINANCE4_ALPHA4", TRUE, (void *)&Chuck_OpenGL_LUMINANCE4_ALPHA4 );
    QUERY->add_svar( QUERY, "int", "LUMINANCE6_ALPHA2", TRUE, (void *)&Chuck_OpenGL_LUMINANCE6_ALPHA2 );
    QUERY->add_svar( QUERY, "int", "LUMINANCE8_ALPHA8", TRUE, (void *)&Chuck_OpenGL_LUMINANCE8_ALPHA8 );
    QUERY->add_svar( QUERY, "int", "LUMINANCE12_ALPHA4", TRUE, (void *)&Chuck_OpenGL_LUMINANCE12_ALPHA4 );
    QUERY->add_svar( QUERY, "int", "LUMINANCE12_ALPHA12", TRUE, (void *)&Chuck_OpenGL_LUMINANCE12_ALPHA12 );
    QUERY->add_svar( QUERY, "int", "LUMINANCE16_ALPHA16", TRUE, (void *)&Chuck_OpenGL_LUMINANCE16_ALPHA16 );
    QUERY->add_svar( QUERY, "int", "INTENSITY", TRUE, (void *)&Chuck_OpenGL_INTENSITY );
    QUERY->add_svar( QUERY, "int", "INTENSITY4", TRUE, (void *)&Chuck_OpenGL_INTENSITY4 );
    QUERY->add_svar( QUERY, "int", "INTENSITY8", TRUE, (void *)&Chuck_OpenGL_INTENSITY8 );
    QUERY->add_svar( QUERY, "int", "INTENSITY12", TRUE, (void *)&Chuck_OpenGL_INTENSITY12 );
    QUERY->add_svar( QUERY, "int", "INTENSITY16", TRUE, (void *)&Chuck_OpenGL_INTENSITY16 );
    QUERY->add_svar( QUERY, "int", "V2F", TRUE, (void *)&Chuck_OpenGL_V2F );
    QUERY->add_svar( QUERY, "int", "V3F", TRUE, (void *)&Chuck_OpenGL_V3F );
    QUERY->add_svar( QUERY, "int", "C4UB_V2F", TRUE, (void *)&Chuck_OpenGL_C4UB_V2F );
    QUERY->add_svar( QUERY, "int", "C4UB_V3F", TRUE, (void *)&Chuck_OpenGL_C4UB_V3F );
    QUERY->add_svar( QUERY, "int", "C3F_V3F", TRUE, (void *)&Chuck_OpenGL_C3F_V3F );
    QUERY->add_svar( QUERY, "int", "N3F_V3F", TRUE, (void *)&Chuck_OpenGL_N3F_V3F );
    QUERY->add_svar( QUERY, "int", "C4F_N3F_V3F", TRUE, (void *)&Chuck_OpenGL_C4F_N3F_V3F );
    QUERY->add_svar( QUERY, "int", "T2F_V3F", TRUE, (void *)&Chuck_OpenGL_T2F_V3F );
    QUERY->add_svar( QUERY, "int", "T4F_V4F", TRUE, (void *)&Chuck_OpenGL_T4F_V4F );
    QUERY->add_svar( QUERY, "int", "T2F_C4UB_V3F", TRUE, (void *)&Chuck_OpenGL_T2F_C4UB_V3F );
    QUERY->add_svar( QUERY, "int", "T2F_C3F_V3F", TRUE, (void *)&Chuck_OpenGL_T2F_C3F_V3F );
    QUERY->add_svar( QUERY, "int", "T2F_N3F_V3F", TRUE, (void *)&Chuck_OpenGL_T2F_N3F_V3F );
    QUERY->add_svar( QUERY, "int", "T2F_C4F_N3F_V3F", TRUE, (void *)&Chuck_OpenGL_T2F_C4F_N3F_V3F );
    QUERY->add_svar( QUERY, "int", "T4F_C4F_N3F_V4F", TRUE, (void *)&Chuck_OpenGL_T4F_C4F_N3F_V4F );
    QUERY->add_svar( QUERY, "int", "CLIP_PLANE0", TRUE, (void *)&Chuck_OpenGL_CLIP_PLANE0 );
    QUERY->add_svar( QUERY, "int", "CLIP_PLANE1", TRUE, (void *)&Chuck_OpenGL_CLIP_PLANE1 );
    QUERY->add_svar( QUERY, "int", "CLIP_PLANE2", TRUE, (void *)&Chuck_OpenGL_CLIP_PLANE2 );
    QUERY->add_svar( QUERY, "int", "CLIP_PLANE3", TRUE, (void *)&Chuck_OpenGL_CLIP_PLANE3 );
    QUERY->add_svar( QUERY, "int", "CLIP_PLANE4", TRUE, (void *)&Chuck_OpenGL_CLIP_PLANE4 );
    QUERY->add_svar( QUERY, "int", "CLIP_PLANE5", TRUE, (void *)&Chuck_OpenGL_CLIP_PLANE5 );
    QUERY->add_svar( QUERY, "int", "LIGHT0", TRUE, (void *)&Chuck_OpenGL_LIGHT0 );
    QUERY->add_svar( QUERY, "int", "LIGHT1", TRUE, (void *)&Chuck_OpenGL_LIGHT1 );
    QUERY->add_svar( QUERY, "int", "LIGHT2", TRUE, (void *)&Chuck_OpenGL_LIGHT2 );
    QUERY->add_svar( QUERY, "int", "LIGHT3", TRUE, (void *)&Chuck_OpenGL_LIGHT3 );
    QUERY->add_svar( QUERY, "int", "LIGHT4", TRUE, (void *)&Chuck_OpenGL_LIGHT4 );
    QUERY->add_svar( QUERY, "int", "LIGHT5", TRUE, (void *)&Chuck_OpenGL_LIGHT5 );
    QUERY->add_svar( QUERY, "int", "LIGHT6", TRUE, (void *)&Chuck_OpenGL_LIGHT6 );
    QUERY->add_svar( QUERY, "int", "LIGHT7", TRUE, (void *)&Chuck_OpenGL_LIGHT7 );

    QUERY->add_mfun(QUERY, Chuck_OpenGL_DrawArrays, "void", "DrawArrays");
    QUERY->add_arg(QUERY, "int", "mode");
    QUERY->add_arg(QUERY, "int", "first");
    QUERY->add_arg(QUERY, "int", "count");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DrawElements, "void", "DrawElements");
    QUERY->add_arg(QUERY, "int", "mode");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "Object", "indices");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PolygonOffset, "void", "PolygonOffset");
    QUERY->add_arg(QUERY, "float", "factor");
    QUERY->add_arg(QUERY, "float", "units");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CopyTexImage1D, "void", "CopyTexImage1D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "internalformat");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "border");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CopyTexImage2D, "void", "CopyTexImage2D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "internalformat");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "border");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CopyTexSubImage1D, "void", "CopyTexSubImage1D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "xoffset");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "width");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CopyTexSubImage2D, "void", "CopyTexSubImage2D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "xoffset");
    QUERY->add_arg(QUERY, "int", "yoffset");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexSubImage1D, "void", "TexSubImage1D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "xoffset");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "format");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "Object", "pixels");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexSubImage2D, "void", "TexSubImage2D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "xoffset");
    QUERY->add_arg(QUERY, "int", "yoffset");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "format");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "Object", "pixels");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_BindTexture, "void", "BindTexture");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "texture");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DeleteTextures, "void", "DeleteTextures");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int[]", "textures");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GenTextures, "void", "GenTextures");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int[]", "textures");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_IsTexture, "int", "IsTexture");
    QUERY->add_arg(QUERY, "int", "texture");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ArrayElement, "void", "ArrayElement");
    QUERY->add_arg(QUERY, "int", "i");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ColorPointer, "void", "ColorPointer");
    QUERY->add_arg(QUERY, "int", "size");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "int", "stride");
    QUERY->add_arg(QUERY, "Object", "pointer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DisableClientState, "void", "DisableClientState");
    QUERY->add_arg(QUERY, "int", "array");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EdgeFlagPointer, "void", "EdgeFlagPointer");
    QUERY->add_arg(QUERY, "int", "stride");
    QUERY->add_arg(QUERY, "Object", "pointer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EnableClientState, "void", "EnableClientState");
    QUERY->add_arg(QUERY, "int", "array");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_IndexPointer, "void", "IndexPointer");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "int", "stride");
    QUERY->add_arg(QUERY, "Object", "pointer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_InterleavedArrays, "void", "InterleavedArrays");
    QUERY->add_arg(QUERY, "int", "format");
    QUERY->add_arg(QUERY, "int", "stride");
    QUERY->add_arg(QUERY, "Object", "pointer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_NormalPointer, "void", "NormalPointer");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "int", "stride");
    QUERY->add_arg(QUERY, "Object", "pointer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexCoordPointer, "void", "TexCoordPointer");
    QUERY->add_arg(QUERY, "int", "size");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "int", "stride");
    QUERY->add_arg(QUERY, "Object", "pointer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexPointer, "void", "VertexPointer");
    QUERY->add_arg(QUERY, "int", "size");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "int", "stride");
    QUERY->add_arg(QUERY, "Object", "pointer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_AreTexturesResident, "int", "AreTexturesResident");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int[]", "textures");
    QUERY->add_arg(QUERY, "int[]", "residences");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PrioritizeTextures, "void", "PrioritizeTextures");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int[]", "textures");
    QUERY->add_arg(QUERY, "float[]", "priorities");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Indexub, "void", "Indexub");
    QUERY->add_arg(QUERY, "int", "c");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Indexubv, "void", "Indexubv");
    QUERY->add_arg(QUERY, "int[]", "c");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PopClientAttrib, "void", "PopClientAttrib");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PushClientAttrib, "void", "PushClientAttrib");
    QUERY->add_arg(QUERY, "int", "mask");

    QUERY->add_svar( QUERY, "int", "UNSIGNED_BYTE_3_3_2", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_BYTE_3_3_2 );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_SHORT_4_4_4_4", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_SHORT_4_4_4_4 );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_SHORT_5_5_5_1", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_SHORT_5_5_5_1 );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_INT_8_8_8_8", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_INT_8_8_8_8 );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_INT_10_10_10_2", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_INT_10_10_10_2 );
    QUERY->add_svar( QUERY, "int", "TEXTURE_BINDING_3D", TRUE, (void *)&Chuck_OpenGL_TEXTURE_BINDING_3D );
    QUERY->add_svar( QUERY, "int", "PACK_SKIP_IMAGES", TRUE, (void *)&Chuck_OpenGL_PACK_SKIP_IMAGES );
    QUERY->add_svar( QUERY, "int", "PACK_IMAGE_HEIGHT", TRUE, (void *)&Chuck_OpenGL_PACK_IMAGE_HEIGHT );
    QUERY->add_svar( QUERY, "int", "UNPACK_SKIP_IMAGES", TRUE, (void *)&Chuck_OpenGL_UNPACK_SKIP_IMAGES );
    QUERY->add_svar( QUERY, "int", "UNPACK_IMAGE_HEIGHT", TRUE, (void *)&Chuck_OpenGL_UNPACK_IMAGE_HEIGHT );
    QUERY->add_svar( QUERY, "int", "TEXTURE_3D", TRUE, (void *)&Chuck_OpenGL_TEXTURE_3D );
    QUERY->add_svar( QUERY, "int", "PROXY_TEXTURE_3D", TRUE, (void *)&Chuck_OpenGL_PROXY_TEXTURE_3D );
    QUERY->add_svar( QUERY, "int", "TEXTURE_DEPTH", TRUE, (void *)&Chuck_OpenGL_TEXTURE_DEPTH );
    QUERY->add_svar( QUERY, "int", "TEXTURE_WRAP_R", TRUE, (void *)&Chuck_OpenGL_TEXTURE_WRAP_R );
    QUERY->add_svar( QUERY, "int", "MAX_3D_TEXTURE_SIZE", TRUE, (void *)&Chuck_OpenGL_MAX_3D_TEXTURE_SIZE );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_BYTE_2_3_3_REV", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_BYTE_2_3_3_REV );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_SHORT_5_6_5", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_SHORT_5_6_5 );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_SHORT_5_6_5_REV", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_SHORT_5_6_5_REV );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_SHORT_4_4_4_4_REV", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_SHORT_4_4_4_4_REV );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_SHORT_1_5_5_5_REV", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_SHORT_1_5_5_5_REV );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_INT_8_8_8_8_REV", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_INT_8_8_8_8_REV );
    QUERY->add_svar( QUERY, "int", "UNSIGNED_INT_2_10_10_10_REV", TRUE, (void *)&Chuck_OpenGL_UNSIGNED_INT_2_10_10_10_REV );
    QUERY->add_svar( QUERY, "int", "BGR", TRUE, (void *)&Chuck_OpenGL_BGR );
    QUERY->add_svar( QUERY, "int", "BGRA", TRUE, (void *)&Chuck_OpenGL_BGRA );
    QUERY->add_svar( QUERY, "int", "MAX_ELEMENTS_VERTICES", TRUE, (void *)&Chuck_OpenGL_MAX_ELEMENTS_VERTICES );
    QUERY->add_svar( QUERY, "int", "MAX_ELEMENTS_INDICES", TRUE, (void *)&Chuck_OpenGL_MAX_ELEMENTS_INDICES );
    QUERY->add_svar( QUERY, "int", "CLAMP_TO_EDGE", TRUE, (void *)&Chuck_OpenGL_CLAMP_TO_EDGE );
    QUERY->add_svar( QUERY, "int", "TEXTURE_MIN_LOD", TRUE, (void *)&Chuck_OpenGL_TEXTURE_MIN_LOD );
    QUERY->add_svar( QUERY, "int", "TEXTURE_MAX_LOD", TRUE, (void *)&Chuck_OpenGL_TEXTURE_MAX_LOD );
    QUERY->add_svar( QUERY, "int", "TEXTURE_BASE_LEVEL", TRUE, (void *)&Chuck_OpenGL_TEXTURE_BASE_LEVEL );
    QUERY->add_svar( QUERY, "int", "TEXTURE_MAX_LEVEL", TRUE, (void *)&Chuck_OpenGL_TEXTURE_MAX_LEVEL );
    QUERY->add_svar( QUERY, "int", "SMOOTH_POINT_SIZE_RANGE", TRUE, (void *)&Chuck_OpenGL_SMOOTH_POINT_SIZE_RANGE );
    QUERY->add_svar( QUERY, "int", "SMOOTH_POINT_SIZE_GRANULARITY", TRUE, (void *)&Chuck_OpenGL_SMOOTH_POINT_SIZE_GRANULARITY );
    QUERY->add_svar( QUERY, "int", "SMOOTH_LINE_WIDTH_RANGE", TRUE, (void *)&Chuck_OpenGL_SMOOTH_LINE_WIDTH_RANGE );
    QUERY->add_svar( QUERY, "int", "SMOOTH_LINE_WIDTH_GRANULARITY", TRUE, (void *)&Chuck_OpenGL_SMOOTH_LINE_WIDTH_GRANULARITY );
    QUERY->add_svar( QUERY, "int", "ALIASED_LINE_WIDTH_RANGE", TRUE, (void *)&Chuck_OpenGL_ALIASED_LINE_WIDTH_RANGE );
    QUERY->add_svar( QUERY, "int", "RESCALE_NORMAL", TRUE, (void *)&Chuck_OpenGL_RESCALE_NORMAL );
    QUERY->add_svar( QUERY, "int", "LIGHT_MODEL_COLOR_CONTROL", TRUE, (void *)&Chuck_OpenGL_LIGHT_MODEL_COLOR_CONTROL );
    QUERY->add_svar( QUERY, "int", "SINGLE_COLOR", TRUE, (void *)&Chuck_OpenGL_SINGLE_COLOR );
    QUERY->add_svar( QUERY, "int", "SEPARATE_SPECULAR_COLOR", TRUE, (void *)&Chuck_OpenGL_SEPARATE_SPECULAR_COLOR );
    QUERY->add_svar( QUERY, "int", "ALIASED_POINT_SIZE_RANGE", TRUE, (void *)&Chuck_OpenGL_ALIASED_POINT_SIZE_RANGE );

    QUERY->add_mfun(QUERY, Chuck_OpenGL_DrawRangeElements, "void", "DrawRangeElements");
    QUERY->add_arg(QUERY, "int", "mode");
    QUERY->add_arg(QUERY, "int", "start");
    QUERY->add_arg(QUERY, "int", "end");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "Object", "indices");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexImage3D, "void", "TexImage3D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "internalformat");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "depth");
    QUERY->add_arg(QUERY, "int", "border");
    QUERY->add_arg(QUERY, "int", "format");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "Object", "pixels");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_TexSubImage3D, "void", "TexSubImage3D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "xoffset");
    QUERY->add_arg(QUERY, "int", "yoffset");
    QUERY->add_arg(QUERY, "int", "zoffset");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "depth");
    QUERY->add_arg(QUERY, "int", "format");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "Object", "pixels");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CopyTexSubImage3D, "void", "CopyTexSubImage3D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "xoffset");
    QUERY->add_arg(QUERY, "int", "yoffset");
    QUERY->add_arg(QUERY, "int", "zoffset");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");

    QUERY->add_svar( QUERY, "int", "TEXTURE0", TRUE, (void *)&Chuck_OpenGL_TEXTURE0 );
    QUERY->add_svar( QUERY, "int", "TEXTURE1", TRUE, (void *)&Chuck_OpenGL_TEXTURE1 );
    QUERY->add_svar( QUERY, "int", "TEXTURE2", TRUE, (void *)&Chuck_OpenGL_TEXTURE2 );
    QUERY->add_svar( QUERY, "int", "TEXTURE3", TRUE, (void *)&Chuck_OpenGL_TEXTURE3 );
    QUERY->add_svar( QUERY, "int", "TEXTURE4", TRUE, (void *)&Chuck_OpenGL_TEXTURE4 );
    QUERY->add_svar( QUERY, "int", "TEXTURE5", TRUE, (void *)&Chuck_OpenGL_TEXTURE5 );
    QUERY->add_svar( QUERY, "int", "TEXTURE6", TRUE, (void *)&Chuck_OpenGL_TEXTURE6 );
    QUERY->add_svar( QUERY, "int", "TEXTURE7", TRUE, (void *)&Chuck_OpenGL_TEXTURE7 );
    QUERY->add_svar( QUERY, "int", "TEXTURE8", TRUE, (void *)&Chuck_OpenGL_TEXTURE8 );
    QUERY->add_svar( QUERY, "int", "TEXTURE9", TRUE, (void *)&Chuck_OpenGL_TEXTURE9 );
    QUERY->add_svar( QUERY, "int", "TEXTURE10", TRUE, (void *)&Chuck_OpenGL_TEXTURE10 );
    QUERY->add_svar( QUERY, "int", "TEXTURE11", TRUE, (void *)&Chuck_OpenGL_TEXTURE11 );
    QUERY->add_svar( QUERY, "int", "TEXTURE12", TRUE, (void *)&Chuck_OpenGL_TEXTURE12 );
    QUERY->add_svar( QUERY, "int", "TEXTURE13", TRUE, (void *)&Chuck_OpenGL_TEXTURE13 );
    QUERY->add_svar( QUERY, "int", "TEXTURE14", TRUE, (void *)&Chuck_OpenGL_TEXTURE14 );
    QUERY->add_svar( QUERY, "int", "TEXTURE15", TRUE, (void *)&Chuck_OpenGL_TEXTURE15 );
    QUERY->add_svar( QUERY, "int", "TEXTURE16", TRUE, (void *)&Chuck_OpenGL_TEXTURE16 );
    QUERY->add_svar( QUERY, "int", "TEXTURE17", TRUE, (void *)&Chuck_OpenGL_TEXTURE17 );
    QUERY->add_svar( QUERY, "int", "TEXTURE18", TRUE, (void *)&Chuck_OpenGL_TEXTURE18 );
    QUERY->add_svar( QUERY, "int", "TEXTURE19", TRUE, (void *)&Chuck_OpenGL_TEXTURE19 );
    QUERY->add_svar( QUERY, "int", "TEXTURE20", TRUE, (void *)&Chuck_OpenGL_TEXTURE20 );
    QUERY->add_svar( QUERY, "int", "TEXTURE21", TRUE, (void *)&Chuck_OpenGL_TEXTURE21 );
    QUERY->add_svar( QUERY, "int", "TEXTURE22", TRUE, (void *)&Chuck_OpenGL_TEXTURE22 );
    QUERY->add_svar( QUERY, "int", "TEXTURE23", TRUE, (void *)&Chuck_OpenGL_TEXTURE23 );
    QUERY->add_svar( QUERY, "int", "TEXTURE24", TRUE, (void *)&Chuck_OpenGL_TEXTURE24 );
    QUERY->add_svar( QUERY, "int", "TEXTURE25", TRUE, (void *)&Chuck_OpenGL_TEXTURE25 );
    QUERY->add_svar( QUERY, "int", "TEXTURE26", TRUE, (void *)&Chuck_OpenGL_TEXTURE26 );
    QUERY->add_svar( QUERY, "int", "TEXTURE27", TRUE, (void *)&Chuck_OpenGL_TEXTURE27 );
    QUERY->add_svar( QUERY, "int", "TEXTURE28", TRUE, (void *)&Chuck_OpenGL_TEXTURE28 );
    QUERY->add_svar( QUERY, "int", "TEXTURE29", TRUE, (void *)&Chuck_OpenGL_TEXTURE29 );
    QUERY->add_svar( QUERY, "int", "TEXTURE30", TRUE, (void *)&Chuck_OpenGL_TEXTURE30 );
    QUERY->add_svar( QUERY, "int", "TEXTURE31", TRUE, (void *)&Chuck_OpenGL_TEXTURE31 );
    QUERY->add_svar( QUERY, "int", "ACTIVE_TEXTURE", TRUE, (void *)&Chuck_OpenGL_ACTIVE_TEXTURE );
    QUERY->add_svar( QUERY, "int", "MULTISAMPLE", TRUE, (void *)&Chuck_OpenGL_MULTISAMPLE );
    QUERY->add_svar( QUERY, "int", "SAMPLE_ALPHA_TO_COVERAGE", TRUE, (void *)&Chuck_OpenGL_SAMPLE_ALPHA_TO_COVERAGE );
    QUERY->add_svar( QUERY, "int", "SAMPLE_ALPHA_TO_ONE", TRUE, (void *)&Chuck_OpenGL_SAMPLE_ALPHA_TO_ONE );
    QUERY->add_svar( QUERY, "int", "SAMPLE_COVERAGE", TRUE, (void *)&Chuck_OpenGL_SAMPLE_COVERAGE );
    QUERY->add_svar( QUERY, "int", "SAMPLE_BUFFERS", TRUE, (void *)&Chuck_OpenGL_SAMPLE_BUFFERS );
    QUERY->add_svar( QUERY, "int", "SAMPLES", TRUE, (void *)&Chuck_OpenGL_SAMPLES );
    QUERY->add_svar( QUERY, "int", "SAMPLE_COVERAGE_VALUE", TRUE, (void *)&Chuck_OpenGL_SAMPLE_COVERAGE_VALUE );
    QUERY->add_svar( QUERY, "int", "SAMPLE_COVERAGE_INVERT", TRUE, (void *)&Chuck_OpenGL_SAMPLE_COVERAGE_INVERT );
    QUERY->add_svar( QUERY, "int", "TEXTURE_CUBE_MAP", TRUE, (void *)&Chuck_OpenGL_TEXTURE_CUBE_MAP );
    QUERY->add_svar( QUERY, "int", "TEXTURE_BINDING_CUBE_MAP", TRUE, (void *)&Chuck_OpenGL_TEXTURE_BINDING_CUBE_MAP );
    QUERY->add_svar( QUERY, "int", "TEXTURE_CUBE_MAP_POSITIVE_X", TRUE, (void *)&Chuck_OpenGL_TEXTURE_CUBE_MAP_POSITIVE_X );
    QUERY->add_svar( QUERY, "int", "TEXTURE_CUBE_MAP_NEGATIVE_X", TRUE, (void *)&Chuck_OpenGL_TEXTURE_CUBE_MAP_NEGATIVE_X );
    QUERY->add_svar( QUERY, "int", "TEXTURE_CUBE_MAP_POSITIVE_Y", TRUE, (void *)&Chuck_OpenGL_TEXTURE_CUBE_MAP_POSITIVE_Y );
    QUERY->add_svar( QUERY, "int", "TEXTURE_CUBE_MAP_NEGATIVE_Y", TRUE, (void *)&Chuck_OpenGL_TEXTURE_CUBE_MAP_NEGATIVE_Y );
    QUERY->add_svar( QUERY, "int", "TEXTURE_CUBE_MAP_POSITIVE_Z", TRUE, (void *)&Chuck_OpenGL_TEXTURE_CUBE_MAP_POSITIVE_Z );
    QUERY->add_svar( QUERY, "int", "TEXTURE_CUBE_MAP_NEGATIVE_Z", TRUE, (void *)&Chuck_OpenGL_TEXTURE_CUBE_MAP_NEGATIVE_Z );
    QUERY->add_svar( QUERY, "int", "PROXY_TEXTURE_CUBE_MAP", TRUE, (void *)&Chuck_OpenGL_PROXY_TEXTURE_CUBE_MAP );
    QUERY->add_svar( QUERY, "int", "MAX_CUBE_MAP_TEXTURE_SIZE", TRUE, (void *)&Chuck_OpenGL_MAX_CUBE_MAP_TEXTURE_SIZE );
    QUERY->add_svar( QUERY, "int", "COMPRESSED_RGB", TRUE, (void *)&Chuck_OpenGL_COMPRESSED_RGB );
    QUERY->add_svar( QUERY, "int", "COMPRESSED_RGBA", TRUE, (void *)&Chuck_OpenGL_COMPRESSED_RGBA );
    QUERY->add_svar( QUERY, "int", "TEXTURE_COMPRESSION_HINT", TRUE, (void *)&Chuck_OpenGL_TEXTURE_COMPRESSION_HINT );
    QUERY->add_svar( QUERY, "int", "TEXTURE_COMPRESSED_IMAGE_SIZE", TRUE, (void *)&Chuck_OpenGL_TEXTURE_COMPRESSED_IMAGE_SIZE );
    QUERY->add_svar( QUERY, "int", "TEXTURE_COMPRESSED", TRUE, (void *)&Chuck_OpenGL_TEXTURE_COMPRESSED );
    QUERY->add_svar( QUERY, "int", "NUM_COMPRESSED_TEXTURE_FORMATS", TRUE, (void *)&Chuck_OpenGL_NUM_COMPRESSED_TEXTURE_FORMATS );
    QUERY->add_svar( QUERY, "int", "COMPRESSED_TEXTURE_FORMATS", TRUE, (void *)&Chuck_OpenGL_COMPRESSED_TEXTURE_FORMATS );
    QUERY->add_svar( QUERY, "int", "CLAMP_TO_BORDER", TRUE, (void *)&Chuck_OpenGL_CLAMP_TO_BORDER );
    QUERY->add_svar( QUERY, "int", "CLIENT_ACTIVE_TEXTURE", TRUE, (void *)&Chuck_OpenGL_CLIENT_ACTIVE_TEXTURE );
    QUERY->add_svar( QUERY, "int", "MAX_TEXTURE_UNITS", TRUE, (void *)&Chuck_OpenGL_MAX_TEXTURE_UNITS );
    QUERY->add_svar( QUERY, "int", "TRANSPOSE_MODELVIEW_MATRIX", TRUE, (void *)&Chuck_OpenGL_TRANSPOSE_MODELVIEW_MATRIX );
    QUERY->add_svar( QUERY, "int", "TRANSPOSE_PROJECTION_MATRIX", TRUE, (void *)&Chuck_OpenGL_TRANSPOSE_PROJECTION_MATRIX );
    QUERY->add_svar( QUERY, "int", "TRANSPOSE_TEXTURE_MATRIX", TRUE, (void *)&Chuck_OpenGL_TRANSPOSE_TEXTURE_MATRIX );
    QUERY->add_svar( QUERY, "int", "TRANSPOSE_COLOR_MATRIX", TRUE, (void *)&Chuck_OpenGL_TRANSPOSE_COLOR_MATRIX );
    QUERY->add_svar( QUERY, "int", "MULTISAMPLE_BIT", TRUE, (void *)&Chuck_OpenGL_MULTISAMPLE_BIT );
    QUERY->add_svar( QUERY, "int", "NORMAL_MAP", TRUE, (void *)&Chuck_OpenGL_NORMAL_MAP );
    QUERY->add_svar( QUERY, "int", "REFLECTION_MAP", TRUE, (void *)&Chuck_OpenGL_REFLECTION_MAP );
    QUERY->add_svar( QUERY, "int", "COMPRESSED_ALPHA", TRUE, (void *)&Chuck_OpenGL_COMPRESSED_ALPHA );
    QUERY->add_svar( QUERY, "int", "COMPRESSED_LUMINANCE", TRUE, (void *)&Chuck_OpenGL_COMPRESSED_LUMINANCE );
    QUERY->add_svar( QUERY, "int", "COMPRESSED_LUMINANCE_ALPHA", TRUE, (void *)&Chuck_OpenGL_COMPRESSED_LUMINANCE_ALPHA );
    QUERY->add_svar( QUERY, "int", "COMPRESSED_INTENSITY", TRUE, (void *)&Chuck_OpenGL_COMPRESSED_INTENSITY );
    QUERY->add_svar( QUERY, "int", "COMBINE", TRUE, (void *)&Chuck_OpenGL_COMBINE );
    QUERY->add_svar( QUERY, "int", "COMBINE_RGB", TRUE, (void *)&Chuck_OpenGL_COMBINE_RGB );
    QUERY->add_svar( QUERY, "int", "COMBINE_ALPHA", TRUE, (void *)&Chuck_OpenGL_COMBINE_ALPHA );
    QUERY->add_svar( QUERY, "int", "SOURCE0_RGB", TRUE, (void *)&Chuck_OpenGL_SOURCE0_RGB );
    QUERY->add_svar( QUERY, "int", "SOURCE1_RGB", TRUE, (void *)&Chuck_OpenGL_SOURCE1_RGB );
    QUERY->add_svar( QUERY, "int", "SOURCE2_RGB", TRUE, (void *)&Chuck_OpenGL_SOURCE2_RGB );
    QUERY->add_svar( QUERY, "int", "SOURCE0_ALPHA", TRUE, (void *)&Chuck_OpenGL_SOURCE0_ALPHA );
    QUERY->add_svar( QUERY, "int", "SOURCE1_ALPHA", TRUE, (void *)&Chuck_OpenGL_SOURCE1_ALPHA );
    QUERY->add_svar( QUERY, "int", "SOURCE2_ALPHA", TRUE, (void *)&Chuck_OpenGL_SOURCE2_ALPHA );
    QUERY->add_svar( QUERY, "int", "OPERAND0_RGB", TRUE, (void *)&Chuck_OpenGL_OPERAND0_RGB );
    QUERY->add_svar( QUERY, "int", "OPERAND1_RGB", TRUE, (void *)&Chuck_OpenGL_OPERAND1_RGB );
    QUERY->add_svar( QUERY, "int", "OPERAND2_RGB", TRUE, (void *)&Chuck_OpenGL_OPERAND2_RGB );
    QUERY->add_svar( QUERY, "int", "OPERAND0_ALPHA", TRUE, (void *)&Chuck_OpenGL_OPERAND0_ALPHA );
    QUERY->add_svar( QUERY, "int", "OPERAND1_ALPHA", TRUE, (void *)&Chuck_OpenGL_OPERAND1_ALPHA );
    QUERY->add_svar( QUERY, "int", "OPERAND2_ALPHA", TRUE, (void *)&Chuck_OpenGL_OPERAND2_ALPHA );
    QUERY->add_svar( QUERY, "int", "RGB_SCALE", TRUE, (void *)&Chuck_OpenGL_RGB_SCALE );
    QUERY->add_svar( QUERY, "int", "ADD_SIGNED", TRUE, (void *)&Chuck_OpenGL_ADD_SIGNED );
    QUERY->add_svar( QUERY, "int", "INTERPOLATE", TRUE, (void *)&Chuck_OpenGL_INTERPOLATE );
    QUERY->add_svar( QUERY, "int", "SUBTRACT", TRUE, (void *)&Chuck_OpenGL_SUBTRACT );
    QUERY->add_svar( QUERY, "int", "CONSTANT", TRUE, (void *)&Chuck_OpenGL_CONSTANT );
    QUERY->add_svar( QUERY, "int", "PRIMARY_COLOR", TRUE, (void *)&Chuck_OpenGL_PRIMARY_COLOR );
    QUERY->add_svar( QUERY, "int", "PREVIOUS", TRUE, (void *)&Chuck_OpenGL_PREVIOUS );
    QUERY->add_svar( QUERY, "int", "DOT3_RGB", TRUE, (void *)&Chuck_OpenGL_DOT3_RGB );
    QUERY->add_svar( QUERY, "int", "DOT3_RGBA", TRUE, (void *)&Chuck_OpenGL_DOT3_RGBA );

    QUERY->add_mfun(QUERY, Chuck_OpenGL_ActiveTexture, "void", "ActiveTexture");
    QUERY->add_arg(QUERY, "int", "texture");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SampleCoverage, "void", "SampleCoverage");
    QUERY->add_arg(QUERY, "float", "value");
    QUERY->add_arg(QUERY, "int", "invert");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CompressedTexImage3D, "void", "CompressedTexImage3D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "internalformat");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "depth");
    QUERY->add_arg(QUERY, "int", "border");
    QUERY->add_arg(QUERY, "int", "imageSize");
    QUERY->add_arg(QUERY, "Object", "data");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CompressedTexImage2D, "void", "CompressedTexImage2D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "internalformat");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "border");
    QUERY->add_arg(QUERY, "int", "imageSize");
    QUERY->add_arg(QUERY, "Object", "data");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CompressedTexImage1D, "void", "CompressedTexImage1D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "internalformat");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "border");
    QUERY->add_arg(QUERY, "int", "imageSize");
    QUERY->add_arg(QUERY, "Object", "data");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CompressedTexSubImage3D, "void", "CompressedTexSubImage3D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "xoffset");
    QUERY->add_arg(QUERY, "int", "yoffset");
    QUERY->add_arg(QUERY, "int", "zoffset");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "depth");
    QUERY->add_arg(QUERY, "int", "format");
    QUERY->add_arg(QUERY, "int", "imageSize");
    QUERY->add_arg(QUERY, "Object", "data");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CompressedTexSubImage2D, "void", "CompressedTexSubImage2D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "xoffset");
    QUERY->add_arg(QUERY, "int", "yoffset");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "height");
    QUERY->add_arg(QUERY, "int", "format");
    QUERY->add_arg(QUERY, "int", "imageSize");
    QUERY->add_arg(QUERY, "Object", "data");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CompressedTexSubImage1D, "void", "CompressedTexSubImage1D");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "int", "xoffset");
    QUERY->add_arg(QUERY, "int", "width");
    QUERY->add_arg(QUERY, "int", "format");
    QUERY->add_arg(QUERY, "int", "imageSize");
    QUERY->add_arg(QUERY, "Object", "data");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetCompressedTexImage, "void", "GetCompressedTexImage");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "level");
    QUERY->add_arg(QUERY, "Object", "img");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ClientActiveTexture, "void", "ClientActiveTexture");
    QUERY->add_arg(QUERY, "int", "texture");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord1d, "void", "MultiTexCoord1d");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float", "s");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord1dv, "void", "MultiTexCoord1dv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord1f, "void", "MultiTexCoord1f");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float", "s");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord1fv, "void", "MultiTexCoord1fv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord1i, "void", "MultiTexCoord1i");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "s");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord1iv, "void", "MultiTexCoord1iv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord1s, "void", "MultiTexCoord1s");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "s");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord1sv, "void", "MultiTexCoord1sv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord2d, "void", "MultiTexCoord2d");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float", "s");
    QUERY->add_arg(QUERY, "float", "t");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord2dv, "void", "MultiTexCoord2dv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord2f, "void", "MultiTexCoord2f");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float", "s");
    QUERY->add_arg(QUERY, "float", "t");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord2fv, "void", "MultiTexCoord2fv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord2i, "void", "MultiTexCoord2i");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "s");
    QUERY->add_arg(QUERY, "int", "t");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord2iv, "void", "MultiTexCoord2iv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord2s, "void", "MultiTexCoord2s");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "s");
    QUERY->add_arg(QUERY, "int", "t");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord2sv, "void", "MultiTexCoord2sv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord3d, "void", "MultiTexCoord3d");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float", "s");
    QUERY->add_arg(QUERY, "float", "t");
    QUERY->add_arg(QUERY, "float", "r");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord3dv, "void", "MultiTexCoord3dv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord3f, "void", "MultiTexCoord3f");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float", "s");
    QUERY->add_arg(QUERY, "float", "t");
    QUERY->add_arg(QUERY, "float", "r");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord3fv, "void", "MultiTexCoord3fv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord3i, "void", "MultiTexCoord3i");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "s");
    QUERY->add_arg(QUERY, "int", "t");
    QUERY->add_arg(QUERY, "int", "r");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord3iv, "void", "MultiTexCoord3iv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord3s, "void", "MultiTexCoord3s");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "s");
    QUERY->add_arg(QUERY, "int", "t");
    QUERY->add_arg(QUERY, "int", "r");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord3sv, "void", "MultiTexCoord3sv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord4d, "void", "MultiTexCoord4d");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float", "s");
    QUERY->add_arg(QUERY, "float", "t");
    QUERY->add_arg(QUERY, "float", "r");
    QUERY->add_arg(QUERY, "float", "q");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord4dv, "void", "MultiTexCoord4dv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord4f, "void", "MultiTexCoord4f");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float", "s");
    QUERY->add_arg(QUERY, "float", "t");
    QUERY->add_arg(QUERY, "float", "r");
    QUERY->add_arg(QUERY, "float", "q");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord4fv, "void", "MultiTexCoord4fv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord4i, "void", "MultiTexCoord4i");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "s");
    QUERY->add_arg(QUERY, "int", "t");
    QUERY->add_arg(QUERY, "int", "r");
    QUERY->add_arg(QUERY, "int", "q");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord4iv, "void", "MultiTexCoord4iv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord4s, "void", "MultiTexCoord4s");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "s");
    QUERY->add_arg(QUERY, "int", "t");
    QUERY->add_arg(QUERY, "int", "r");
    QUERY->add_arg(QUERY, "int", "q");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiTexCoord4sv, "void", "MultiTexCoord4sv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_LoadTransposeMatrixf, "void", "LoadTransposeMatrixf");
    QUERY->add_arg(QUERY, "float[]", "m");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_LoadTransposeMatrixd, "void", "LoadTransposeMatrixd");
    QUERY->add_arg(QUERY, "float[]", "m");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultTransposeMatrixf, "void", "MultTransposeMatrixf");
    QUERY->add_arg(QUERY, "float[]", "m");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultTransposeMatrixd, "void", "MultTransposeMatrixd");
    QUERY->add_arg(QUERY, "float[]", "m");

    QUERY->add_svar( QUERY, "int", "BLEND_DST_RGB", TRUE, (void *)&Chuck_OpenGL_BLEND_DST_RGB );
    QUERY->add_svar( QUERY, "int", "BLEND_SRC_RGB", TRUE, (void *)&Chuck_OpenGL_BLEND_SRC_RGB );
    QUERY->add_svar( QUERY, "int", "BLEND_DST_ALPHA", TRUE, (void *)&Chuck_OpenGL_BLEND_DST_ALPHA );
    QUERY->add_svar( QUERY, "int", "BLEND_SRC_ALPHA", TRUE, (void *)&Chuck_OpenGL_BLEND_SRC_ALPHA );
    QUERY->add_svar( QUERY, "int", "POINT_FADE_THRESHOLD_SIZE", TRUE, (void *)&Chuck_OpenGL_POINT_FADE_THRESHOLD_SIZE );
    QUERY->add_svar( QUERY, "int", "DEPTH_COMPONENT16", TRUE, (void *)&Chuck_OpenGL_DEPTH_COMPONENT16 );
    QUERY->add_svar( QUERY, "int", "DEPTH_COMPONENT24", TRUE, (void *)&Chuck_OpenGL_DEPTH_COMPONENT24 );
    QUERY->add_svar( QUERY, "int", "DEPTH_COMPONENT32", TRUE, (void *)&Chuck_OpenGL_DEPTH_COMPONENT32 );
    QUERY->add_svar( QUERY, "int", "MIRRORED_REPEAT", TRUE, (void *)&Chuck_OpenGL_MIRRORED_REPEAT );
    QUERY->add_svar( QUERY, "int", "MAX_TEXTURE_LOD_BIAS", TRUE, (void *)&Chuck_OpenGL_MAX_TEXTURE_LOD_BIAS );
    QUERY->add_svar( QUERY, "int", "TEXTURE_LOD_BIAS", TRUE, (void *)&Chuck_OpenGL_TEXTURE_LOD_BIAS );
    QUERY->add_svar( QUERY, "int", "INCR_WRAP", TRUE, (void *)&Chuck_OpenGL_INCR_WRAP );
    QUERY->add_svar( QUERY, "int", "DECR_WRAP", TRUE, (void *)&Chuck_OpenGL_DECR_WRAP );
    QUERY->add_svar( QUERY, "int", "TEXTURE_DEPTH_SIZE", TRUE, (void *)&Chuck_OpenGL_TEXTURE_DEPTH_SIZE );
    QUERY->add_svar( QUERY, "int", "TEXTURE_COMPARE_MODE", TRUE, (void *)&Chuck_OpenGL_TEXTURE_COMPARE_MODE );
    QUERY->add_svar( QUERY, "int", "TEXTURE_COMPARE_FUNC", TRUE, (void *)&Chuck_OpenGL_TEXTURE_COMPARE_FUNC );
    QUERY->add_svar( QUERY, "int", "POINT_SIZE_MIN", TRUE, (void *)&Chuck_OpenGL_POINT_SIZE_MIN );
    QUERY->add_svar( QUERY, "int", "POINT_SIZE_MAX", TRUE, (void *)&Chuck_OpenGL_POINT_SIZE_MAX );
    QUERY->add_svar( QUERY, "int", "POINT_DISTANCE_ATTENUATION", TRUE, (void *)&Chuck_OpenGL_POINT_DISTANCE_ATTENUATION );
    QUERY->add_svar( QUERY, "int", "GENERATE_MIPMAP", TRUE, (void *)&Chuck_OpenGL_GENERATE_MIPMAP );
    QUERY->add_svar( QUERY, "int", "GENERATE_MIPMAP_HINT", TRUE, (void *)&Chuck_OpenGL_GENERATE_MIPMAP_HINT );
    QUERY->add_svar( QUERY, "int", "FOG_COORDINATE_SOURCE", TRUE, (void *)&Chuck_OpenGL_FOG_COORDINATE_SOURCE );
    QUERY->add_svar( QUERY, "int", "FOG_COORDINATE", TRUE, (void *)&Chuck_OpenGL_FOG_COORDINATE );
    QUERY->add_svar( QUERY, "int", "FRAGMENT_DEPTH", TRUE, (void *)&Chuck_OpenGL_FRAGMENT_DEPTH );
    QUERY->add_svar( QUERY, "int", "CURRENT_FOG_COORDINATE", TRUE, (void *)&Chuck_OpenGL_CURRENT_FOG_COORDINATE );
    QUERY->add_svar( QUERY, "int", "FOG_COORDINATE_ARRAY_TYPE", TRUE, (void *)&Chuck_OpenGL_FOG_COORDINATE_ARRAY_TYPE );
    QUERY->add_svar( QUERY, "int", "FOG_COORDINATE_ARRAY_STRIDE", TRUE, (void *)&Chuck_OpenGL_FOG_COORDINATE_ARRAY_STRIDE );
    QUERY->add_svar( QUERY, "int", "FOG_COORDINATE_ARRAY_POINTER", TRUE, (void *)&Chuck_OpenGL_FOG_COORDINATE_ARRAY_POINTER );
    QUERY->add_svar( QUERY, "int", "FOG_COORDINATE_ARRAY", TRUE, (void *)&Chuck_OpenGL_FOG_COORDINATE_ARRAY );
    QUERY->add_svar( QUERY, "int", "COLOR_SUM", TRUE, (void *)&Chuck_OpenGL_COLOR_SUM );
    QUERY->add_svar( QUERY, "int", "CURRENT_SECONDARY_COLOR", TRUE, (void *)&Chuck_OpenGL_CURRENT_SECONDARY_COLOR );
    QUERY->add_svar( QUERY, "int", "SECONDARY_COLOR_ARRAY_SIZE", TRUE, (void *)&Chuck_OpenGL_SECONDARY_COLOR_ARRAY_SIZE );
    QUERY->add_svar( QUERY, "int", "SECONDARY_COLOR_ARRAY_TYPE", TRUE, (void *)&Chuck_OpenGL_SECONDARY_COLOR_ARRAY_TYPE );
    QUERY->add_svar( QUERY, "int", "SECONDARY_COLOR_ARRAY_STRIDE", TRUE, (void *)&Chuck_OpenGL_SECONDARY_COLOR_ARRAY_STRIDE );
    QUERY->add_svar( QUERY, "int", "SECONDARY_COLOR_ARRAY_POINTER", TRUE, (void *)&Chuck_OpenGL_SECONDARY_COLOR_ARRAY_POINTER );
    QUERY->add_svar( QUERY, "int", "SECONDARY_COLOR_ARRAY", TRUE, (void *)&Chuck_OpenGL_SECONDARY_COLOR_ARRAY );
    QUERY->add_svar( QUERY, "int", "TEXTURE_FILTER_CONTROL", TRUE, (void *)&Chuck_OpenGL_TEXTURE_FILTER_CONTROL );
    QUERY->add_svar( QUERY, "int", "DEPTH_TEXTURE_MODE", TRUE, (void *)&Chuck_OpenGL_DEPTH_TEXTURE_MODE );
    QUERY->add_svar( QUERY, "int", "COMPARE_R_TO_TEXTURE", TRUE, (void *)&Chuck_OpenGL_COMPARE_R_TO_TEXTURE );

    QUERY->add_mfun(QUERY, Chuck_OpenGL_BlendFuncSeparate, "void", "BlendFuncSeparate");
    QUERY->add_arg(QUERY, "int", "sfactorRGB");
    QUERY->add_arg(QUERY, "int", "dfactorRGB");
    QUERY->add_arg(QUERY, "int", "sfactorAlpha");
    QUERY->add_arg(QUERY, "int", "dfactorAlpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_MultiDrawArrays, "void", "MultiDrawArrays");
    QUERY->add_arg(QUERY, "int", "mode");
    QUERY->add_arg(QUERY, "int[]", "first");
    QUERY->add_arg(QUERY, "int[]", "count");
    QUERY->add_arg(QUERY, "int", "drawcount");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PointParameterf, "void", "PointParameterf");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PointParameterfv, "void", "PointParameterfv");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PointParameteri, "void", "PointParameteri");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int", "param");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_PointParameteriv, "void", "PointParameteriv");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_FogCoordf, "void", "FogCoordf");
    QUERY->add_arg(QUERY, "float", "coord");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_FogCoordfv, "void", "FogCoordfv");
    QUERY->add_arg(QUERY, "float[]", "coord");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_FogCoordd, "void", "FogCoordd");
    QUERY->add_arg(QUERY, "float", "coord");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_FogCoorddv, "void", "FogCoorddv");
    QUERY->add_arg(QUERY, "float[]", "coord");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_FogCoordPointer, "void", "FogCoordPointer");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "int", "stride");
    QUERY->add_arg(QUERY, "Object", "pointer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SecondaryColor3b, "void", "SecondaryColor3b");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SecondaryColor3bv, "void", "SecondaryColor3bv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SecondaryColor3d, "void", "SecondaryColor3d");
    QUERY->add_arg(QUERY, "float", "red");
    QUERY->add_arg(QUERY, "float", "green");
    QUERY->add_arg(QUERY, "float", "blue");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SecondaryColor3dv, "void", "SecondaryColor3dv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SecondaryColor3f, "void", "SecondaryColor3f");
    QUERY->add_arg(QUERY, "float", "red");
    QUERY->add_arg(QUERY, "float", "green");
    QUERY->add_arg(QUERY, "float", "blue");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SecondaryColor3fv, "void", "SecondaryColor3fv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SecondaryColor3i, "void", "SecondaryColor3i");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SecondaryColor3iv, "void", "SecondaryColor3iv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SecondaryColor3s, "void", "SecondaryColor3s");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SecondaryColor3sv, "void", "SecondaryColor3sv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SecondaryColor3ub, "void", "SecondaryColor3ub");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SecondaryColor3ubv, "void", "SecondaryColor3ubv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SecondaryColor3ui, "void", "SecondaryColor3ui");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SecondaryColor3uiv, "void", "SecondaryColor3uiv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SecondaryColor3us, "void", "SecondaryColor3us");
    QUERY->add_arg(QUERY, "int", "red");
    QUERY->add_arg(QUERY, "int", "green");
    QUERY->add_arg(QUERY, "int", "blue");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SecondaryColor3usv, "void", "SecondaryColor3usv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_SecondaryColorPointer, "void", "SecondaryColorPointer");
    QUERY->add_arg(QUERY, "int", "size");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "int", "stride");
    QUERY->add_arg(QUERY, "Object", "pointer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_WindowPos2d, "void", "WindowPos2d");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_WindowPos2dv, "void", "WindowPos2dv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_WindowPos2f, "void", "WindowPos2f");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_WindowPos2fv, "void", "WindowPos2fv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_WindowPos2i, "void", "WindowPos2i");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_WindowPos2iv, "void", "WindowPos2iv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_WindowPos2s, "void", "WindowPos2s");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_WindowPos2sv, "void", "WindowPos2sv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_WindowPos3d, "void", "WindowPos3d");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_WindowPos3dv, "void", "WindowPos3dv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_WindowPos3f, "void", "WindowPos3f");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_WindowPos3fv, "void", "WindowPos3fv");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_WindowPos3i, "void", "WindowPos3i");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_WindowPos3iv, "void", "WindowPos3iv");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_WindowPos3s, "void", "WindowPos3s");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_WindowPos3sv, "void", "WindowPos3sv");
    QUERY->add_arg(QUERY, "int[]", "v");

    QUERY->add_svar( QUERY, "int", "FUNC_ADD", TRUE, (void *)&Chuck_OpenGL_FUNC_ADD );
    QUERY->add_svar( QUERY, "int", "FUNC_SUBTRACT", TRUE, (void *)&Chuck_OpenGL_FUNC_SUBTRACT );
    QUERY->add_svar( QUERY, "int", "FUNC_REVERSE_SUBTRACT", TRUE, (void *)&Chuck_OpenGL_FUNC_REVERSE_SUBTRACT );
    QUERY->add_svar( QUERY, "int", "MIN", TRUE, (void *)&Chuck_OpenGL_MIN );
    QUERY->add_svar( QUERY, "int", "MAX", TRUE, (void *)&Chuck_OpenGL_MAX );
    QUERY->add_svar( QUERY, "int", "CONSTANT_COLOR", TRUE, (void *)&Chuck_OpenGL_CONSTANT_COLOR );
    QUERY->add_svar( QUERY, "int", "ONE_MINUS_CONSTANT_COLOR", TRUE, (void *)&Chuck_OpenGL_ONE_MINUS_CONSTANT_COLOR );
    QUERY->add_svar( QUERY, "int", "CONSTANT_ALPHA", TRUE, (void *)&Chuck_OpenGL_CONSTANT_ALPHA );
    QUERY->add_svar( QUERY, "int", "ONE_MINUS_CONSTANT_ALPHA", TRUE, (void *)&Chuck_OpenGL_ONE_MINUS_CONSTANT_ALPHA );

    QUERY->add_mfun(QUERY, Chuck_OpenGL_BlendColor, "void", "BlendColor");
    QUERY->add_arg(QUERY, "float", "red");
    QUERY->add_arg(QUERY, "float", "green");
    QUERY->add_arg(QUERY, "float", "blue");
    QUERY->add_arg(QUERY, "float", "alpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_BlendEquation, "void", "BlendEquation");
    QUERY->add_arg(QUERY, "int", "mode");

    QUERY->add_svar( QUERY, "int", "BUFFER_SIZE", TRUE, (void *)&Chuck_OpenGL_BUFFER_SIZE );
    QUERY->add_svar( QUERY, "int", "BUFFER_USAGE", TRUE, (void *)&Chuck_OpenGL_BUFFER_USAGE );
    QUERY->add_svar( QUERY, "int", "QUERY_COUNTER_BITS", TRUE, (void *)&Chuck_OpenGL_QUERY_COUNTER_BITS );
    QUERY->add_svar( QUERY, "int", "CURRENT_QUERY", TRUE, (void *)&Chuck_OpenGL_CURRENT_QUERY );
    QUERY->add_svar( QUERY, "int", "QUERY_RESULT", TRUE, (void *)&Chuck_OpenGL_QUERY_RESULT );
    QUERY->add_svar( QUERY, "int", "QUERY_RESULT_AVAILABLE", TRUE, (void *)&Chuck_OpenGL_QUERY_RESULT_AVAILABLE );
    QUERY->add_svar( QUERY, "int", "ARRAY_BUFFER", TRUE, (void *)&Chuck_OpenGL_ARRAY_BUFFER );
    QUERY->add_svar( QUERY, "int", "ELEMENT_ARRAY_BUFFER", TRUE, (void *)&Chuck_OpenGL_ELEMENT_ARRAY_BUFFER );
    QUERY->add_svar( QUERY, "int", "ARRAY_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_ARRAY_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "ELEMENT_ARRAY_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_ELEMENT_ARRAY_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "VERTEX_ATTRIB_ARRAY_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "READ_ONLY", TRUE, (void *)&Chuck_OpenGL_READ_ONLY );
    QUERY->add_svar( QUERY, "int", "WRITE_ONLY", TRUE, (void *)&Chuck_OpenGL_WRITE_ONLY );
    QUERY->add_svar( QUERY, "int", "READ_WRITE", TRUE, (void *)&Chuck_OpenGL_READ_WRITE );
    QUERY->add_svar( QUERY, "int", "BUFFER_ACCESS", TRUE, (void *)&Chuck_OpenGL_BUFFER_ACCESS );
    QUERY->add_svar( QUERY, "int", "BUFFER_MAPPED", TRUE, (void *)&Chuck_OpenGL_BUFFER_MAPPED );
    QUERY->add_svar( QUERY, "int", "BUFFER_MAP_POINTER", TRUE, (void *)&Chuck_OpenGL_BUFFER_MAP_POINTER );
    QUERY->add_svar( QUERY, "int", "STREAM_DRAW", TRUE, (void *)&Chuck_OpenGL_STREAM_DRAW );
    QUERY->add_svar( QUERY, "int", "STREAM_READ", TRUE, (void *)&Chuck_OpenGL_STREAM_READ );
    QUERY->add_svar( QUERY, "int", "STREAM_COPY", TRUE, (void *)&Chuck_OpenGL_STREAM_COPY );
    QUERY->add_svar( QUERY, "int", "STATIC_DRAW", TRUE, (void *)&Chuck_OpenGL_STATIC_DRAW );
    QUERY->add_svar( QUERY, "int", "STATIC_READ", TRUE, (void *)&Chuck_OpenGL_STATIC_READ );
    QUERY->add_svar( QUERY, "int", "STATIC_COPY", TRUE, (void *)&Chuck_OpenGL_STATIC_COPY );
    QUERY->add_svar( QUERY, "int", "DYNAMIC_DRAW", TRUE, (void *)&Chuck_OpenGL_DYNAMIC_DRAW );
    QUERY->add_svar( QUERY, "int", "DYNAMIC_READ", TRUE, (void *)&Chuck_OpenGL_DYNAMIC_READ );
    QUERY->add_svar( QUERY, "int", "DYNAMIC_COPY", TRUE, (void *)&Chuck_OpenGL_DYNAMIC_COPY );
    QUERY->add_svar( QUERY, "int", "SAMPLES_PASSED", TRUE, (void *)&Chuck_OpenGL_SAMPLES_PASSED );
    QUERY->add_svar( QUERY, "int", "SRC1_ALPHA", TRUE, (void *)&Chuck_OpenGL_SRC1_ALPHA );
    QUERY->add_svar( QUERY, "int", "VERTEX_ARRAY_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_VERTEX_ARRAY_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "NORMAL_ARRAY_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_NORMAL_ARRAY_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "COLOR_ARRAY_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_COLOR_ARRAY_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "INDEX_ARRAY_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_INDEX_ARRAY_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "TEXTURE_COORD_ARRAY_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_TEXTURE_COORD_ARRAY_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "EDGE_FLAG_ARRAY_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_EDGE_FLAG_ARRAY_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "SECONDARY_COLOR_ARRAY_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "FOG_COORDINATE_ARRAY_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_FOG_COORDINATE_ARRAY_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "WEIGHT_ARRAY_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_WEIGHT_ARRAY_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "FOG_COORD_SRC", TRUE, (void *)&Chuck_OpenGL_FOG_COORD_SRC );
    QUERY->add_svar( QUERY, "int", "FOG_COORD", TRUE, (void *)&Chuck_OpenGL_FOG_COORD );
    QUERY->add_svar( QUERY, "int", "CURRENT_FOG_COORD", TRUE, (void *)&Chuck_OpenGL_CURRENT_FOG_COORD );
    QUERY->add_svar( QUERY, "int", "FOG_COORD_ARRAY_TYPE", TRUE, (void *)&Chuck_OpenGL_FOG_COORD_ARRAY_TYPE );
    QUERY->add_svar( QUERY, "int", "FOG_COORD_ARRAY_STRIDE", TRUE, (void *)&Chuck_OpenGL_FOG_COORD_ARRAY_STRIDE );
    QUERY->add_svar( QUERY, "int", "FOG_COORD_ARRAY_POINTER", TRUE, (void *)&Chuck_OpenGL_FOG_COORD_ARRAY_POINTER );
    QUERY->add_svar( QUERY, "int", "FOG_COORD_ARRAY", TRUE, (void *)&Chuck_OpenGL_FOG_COORD_ARRAY );
    QUERY->add_svar( QUERY, "int", "FOG_COORD_ARRAY_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_FOG_COORD_ARRAY_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "SRC0_RGB", TRUE, (void *)&Chuck_OpenGL_SRC0_RGB );
    QUERY->add_svar( QUERY, "int", "SRC1_RGB", TRUE, (void *)&Chuck_OpenGL_SRC1_RGB );
    QUERY->add_svar( QUERY, "int", "SRC2_RGB", TRUE, (void *)&Chuck_OpenGL_SRC2_RGB );
    QUERY->add_svar( QUERY, "int", "SRC0_ALPHA", TRUE, (void *)&Chuck_OpenGL_SRC0_ALPHA );
    QUERY->add_svar( QUERY, "int", "SRC2_ALPHA", TRUE, (void *)&Chuck_OpenGL_SRC2_ALPHA );

    QUERY->add_mfun(QUERY, Chuck_OpenGL_GenQueries, "void", "GenQueries");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int[]", "ids");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DeleteQueries, "void", "DeleteQueries");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int[]", "ids");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_IsQuery, "int", "IsQuery");
    QUERY->add_arg(QUERY, "int", "id");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_BeginQuery, "void", "BeginQuery");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "id");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EndQuery, "void", "EndQuery");
    QUERY->add_arg(QUERY, "int", "target");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetQueryiv, "void", "GetQueryiv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetQueryObjectiv, "void", "GetQueryObjectiv");
    QUERY->add_arg(QUERY, "int", "id");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetQueryObjectuiv, "void", "GetQueryObjectuiv");
    QUERY->add_arg(QUERY, "int", "id");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_BindBuffer, "void", "BindBuffer");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "buffer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DeleteBuffers, "void", "DeleteBuffers");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int[]", "buffers");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GenBuffers, "void", "GenBuffers");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int[]", "buffers");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_IsBuffer, "int", "IsBuffer");
    QUERY->add_arg(QUERY, "int", "buffer");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_UnmapBuffer, "int", "UnmapBuffer");
    QUERY->add_arg(QUERY, "int", "target");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetBufferParameteriv, "void", "GetBufferParameteriv");
    QUERY->add_arg(QUERY, "int", "target");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");

    QUERY->add_svar( QUERY, "int", "BLEND_EQUATION_RGB", TRUE, (void *)&Chuck_OpenGL_BLEND_EQUATION_RGB );
    QUERY->add_svar( QUERY, "int", "VERTEX_ATTRIB_ARRAY_ENABLED", TRUE, (void *)&Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_ENABLED );
    QUERY->add_svar( QUERY, "int", "VERTEX_ATTRIB_ARRAY_SIZE", TRUE, (void *)&Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_SIZE );
    QUERY->add_svar( QUERY, "int", "VERTEX_ATTRIB_ARRAY_STRIDE", TRUE, (void *)&Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_STRIDE );
    QUERY->add_svar( QUERY, "int", "VERTEX_ATTRIB_ARRAY_TYPE", TRUE, (void *)&Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_TYPE );
    QUERY->add_svar( QUERY, "int", "CURRENT_VERTEX_ATTRIB", TRUE, (void *)&Chuck_OpenGL_CURRENT_VERTEX_ATTRIB );
    QUERY->add_svar( QUERY, "int", "VERTEX_PROGRAM_POINT_SIZE", TRUE, (void *)&Chuck_OpenGL_VERTEX_PROGRAM_POINT_SIZE );
    QUERY->add_svar( QUERY, "int", "VERTEX_ATTRIB_ARRAY_POINTER", TRUE, (void *)&Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_POINTER );
    QUERY->add_svar( QUERY, "int", "STENCIL_BACK_FUNC", TRUE, (void *)&Chuck_OpenGL_STENCIL_BACK_FUNC );
    QUERY->add_svar( QUERY, "int", "STENCIL_BACK_FAIL", TRUE, (void *)&Chuck_OpenGL_STENCIL_BACK_FAIL );
    QUERY->add_svar( QUERY, "int", "STENCIL_BACK_PASS_DEPTH_FAIL", TRUE, (void *)&Chuck_OpenGL_STENCIL_BACK_PASS_DEPTH_FAIL );
    QUERY->add_svar( QUERY, "int", "STENCIL_BACK_PASS_DEPTH_PASS", TRUE, (void *)&Chuck_OpenGL_STENCIL_BACK_PASS_DEPTH_PASS );
    QUERY->add_svar( QUERY, "int", "MAX_DRAW_BUFFERS", TRUE, (void *)&Chuck_OpenGL_MAX_DRAW_BUFFERS );
    QUERY->add_svar( QUERY, "int", "DRAW_BUFFER0", TRUE, (void *)&Chuck_OpenGL_DRAW_BUFFER0 );
    QUERY->add_svar( QUERY, "int", "DRAW_BUFFER1", TRUE, (void *)&Chuck_OpenGL_DRAW_BUFFER1 );
    QUERY->add_svar( QUERY, "int", "DRAW_BUFFER2", TRUE, (void *)&Chuck_OpenGL_DRAW_BUFFER2 );
    QUERY->add_svar( QUERY, "int", "DRAW_BUFFER3", TRUE, (void *)&Chuck_OpenGL_DRAW_BUFFER3 );
    QUERY->add_svar( QUERY, "int", "DRAW_BUFFER4", TRUE, (void *)&Chuck_OpenGL_DRAW_BUFFER4 );
    QUERY->add_svar( QUERY, "int", "DRAW_BUFFER5", TRUE, (void *)&Chuck_OpenGL_DRAW_BUFFER5 );
    QUERY->add_svar( QUERY, "int", "DRAW_BUFFER6", TRUE, (void *)&Chuck_OpenGL_DRAW_BUFFER6 );
    QUERY->add_svar( QUERY, "int", "DRAW_BUFFER7", TRUE, (void *)&Chuck_OpenGL_DRAW_BUFFER7 );
    QUERY->add_svar( QUERY, "int", "DRAW_BUFFER8", TRUE, (void *)&Chuck_OpenGL_DRAW_BUFFER8 );
    QUERY->add_svar( QUERY, "int", "DRAW_BUFFER9", TRUE, (void *)&Chuck_OpenGL_DRAW_BUFFER9 );
    QUERY->add_svar( QUERY, "int", "DRAW_BUFFER10", TRUE, (void *)&Chuck_OpenGL_DRAW_BUFFER10 );
    QUERY->add_svar( QUERY, "int", "DRAW_BUFFER11", TRUE, (void *)&Chuck_OpenGL_DRAW_BUFFER11 );
    QUERY->add_svar( QUERY, "int", "DRAW_BUFFER12", TRUE, (void *)&Chuck_OpenGL_DRAW_BUFFER12 );
    QUERY->add_svar( QUERY, "int", "DRAW_BUFFER13", TRUE, (void *)&Chuck_OpenGL_DRAW_BUFFER13 );
    QUERY->add_svar( QUERY, "int", "DRAW_BUFFER14", TRUE, (void *)&Chuck_OpenGL_DRAW_BUFFER14 );
    QUERY->add_svar( QUERY, "int", "DRAW_BUFFER15", TRUE, (void *)&Chuck_OpenGL_DRAW_BUFFER15 );
    QUERY->add_svar( QUERY, "int", "BLEND_EQUATION_ALPHA", TRUE, (void *)&Chuck_OpenGL_BLEND_EQUATION_ALPHA );
    QUERY->add_svar( QUERY, "int", "MAX_VERTEX_ATTRIBS", TRUE, (void *)&Chuck_OpenGL_MAX_VERTEX_ATTRIBS );
    QUERY->add_svar( QUERY, "int", "VERTEX_ATTRIB_ARRAY_NORMALIZED", TRUE, (void *)&Chuck_OpenGL_VERTEX_ATTRIB_ARRAY_NORMALIZED );
    QUERY->add_svar( QUERY, "int", "MAX_TEXTURE_IMAGE_UNITS", TRUE, (void *)&Chuck_OpenGL_MAX_TEXTURE_IMAGE_UNITS );
    QUERY->add_svar( QUERY, "int", "FRAGMENT_SHADER", TRUE, (void *)&Chuck_OpenGL_FRAGMENT_SHADER );
    QUERY->add_svar( QUERY, "int", "VERTEX_SHADER", TRUE, (void *)&Chuck_OpenGL_VERTEX_SHADER );
    QUERY->add_svar( QUERY, "int", "MAX_FRAGMENT_UNIFORM_COMPONENTS", TRUE, (void *)&Chuck_OpenGL_MAX_FRAGMENT_UNIFORM_COMPONENTS );
    QUERY->add_svar( QUERY, "int", "MAX_VERTEX_UNIFORM_COMPONENTS", TRUE, (void *)&Chuck_OpenGL_MAX_VERTEX_UNIFORM_COMPONENTS );
    QUERY->add_svar( QUERY, "int", "MAX_VARYING_FLOATS", TRUE, (void *)&Chuck_OpenGL_MAX_VARYING_FLOATS );
    QUERY->add_svar( QUERY, "int", "MAX_VERTEX_TEXTURE_IMAGE_UNITS", TRUE, (void *)&Chuck_OpenGL_MAX_VERTEX_TEXTURE_IMAGE_UNITS );
    QUERY->add_svar( QUERY, "int", "MAX_COMBINED_TEXTURE_IMAGE_UNITS", TRUE, (void *)&Chuck_OpenGL_MAX_COMBINED_TEXTURE_IMAGE_UNITS );
    QUERY->add_svar( QUERY, "int", "SHADER_TYPE", TRUE, (void *)&Chuck_OpenGL_SHADER_TYPE );
    QUERY->add_svar( QUERY, "int", "FLOAT_VEC2", TRUE, (void *)&Chuck_OpenGL_FLOAT_VEC2 );
    QUERY->add_svar( QUERY, "int", "FLOAT_VEC3", TRUE, (void *)&Chuck_OpenGL_FLOAT_VEC3 );
    QUERY->add_svar( QUERY, "int", "FLOAT_VEC4", TRUE, (void *)&Chuck_OpenGL_FLOAT_VEC4 );
    QUERY->add_svar( QUERY, "int", "INT_VEC2", TRUE, (void *)&Chuck_OpenGL_INT_VEC2 );
    QUERY->add_svar( QUERY, "int", "INT_VEC3", TRUE, (void *)&Chuck_OpenGL_INT_VEC3 );
    QUERY->add_svar( QUERY, "int", "INT_VEC4", TRUE, (void *)&Chuck_OpenGL_INT_VEC4 );
    QUERY->add_svar( QUERY, "int", "BOOL", TRUE, (void *)&Chuck_OpenGL_BOOL );
    QUERY->add_svar( QUERY, "int", "BOOL_VEC2", TRUE, (void *)&Chuck_OpenGL_BOOL_VEC2 );
    QUERY->add_svar( QUERY, "int", "BOOL_VEC3", TRUE, (void *)&Chuck_OpenGL_BOOL_VEC3 );
    QUERY->add_svar( QUERY, "int", "BOOL_VEC4", TRUE, (void *)&Chuck_OpenGL_BOOL_VEC4 );
    QUERY->add_svar( QUERY, "int", "FLOAT_MAT2", TRUE, (void *)&Chuck_OpenGL_FLOAT_MAT2 );
    QUERY->add_svar( QUERY, "int", "FLOAT_MAT3", TRUE, (void *)&Chuck_OpenGL_FLOAT_MAT3 );
    QUERY->add_svar( QUERY, "int", "FLOAT_MAT4", TRUE, (void *)&Chuck_OpenGL_FLOAT_MAT4 );
    QUERY->add_svar( QUERY, "int", "SAMPLER_1D", TRUE, (void *)&Chuck_OpenGL_SAMPLER_1D );
    QUERY->add_svar( QUERY, "int", "SAMPLER_2D", TRUE, (void *)&Chuck_OpenGL_SAMPLER_2D );
    QUERY->add_svar( QUERY, "int", "SAMPLER_3D", TRUE, (void *)&Chuck_OpenGL_SAMPLER_3D );
    QUERY->add_svar( QUERY, "int", "SAMPLER_CUBE", TRUE, (void *)&Chuck_OpenGL_SAMPLER_CUBE );
    QUERY->add_svar( QUERY, "int", "SAMPLER_1D_SHADOW", TRUE, (void *)&Chuck_OpenGL_SAMPLER_1D_SHADOW );
    QUERY->add_svar( QUERY, "int", "SAMPLER_2D_SHADOW", TRUE, (void *)&Chuck_OpenGL_SAMPLER_2D_SHADOW );
    QUERY->add_svar( QUERY, "int", "DELETE_STATUS", TRUE, (void *)&Chuck_OpenGL_DELETE_STATUS );
    QUERY->add_svar( QUERY, "int", "COMPILE_STATUS", TRUE, (void *)&Chuck_OpenGL_COMPILE_STATUS );
    QUERY->add_svar( QUERY, "int", "LINK_STATUS", TRUE, (void *)&Chuck_OpenGL_LINK_STATUS );
    QUERY->add_svar( QUERY, "int", "VALIDATE_STATUS", TRUE, (void *)&Chuck_OpenGL_VALIDATE_STATUS );
    QUERY->add_svar( QUERY, "int", "INFO_LOG_LENGTH", TRUE, (void *)&Chuck_OpenGL_INFO_LOG_LENGTH );
    QUERY->add_svar( QUERY, "int", "ATTACHED_SHADERS", TRUE, (void *)&Chuck_OpenGL_ATTACHED_SHADERS );
    QUERY->add_svar( QUERY, "int", "ACTIVE_UNIFORMS", TRUE, (void *)&Chuck_OpenGL_ACTIVE_UNIFORMS );
    QUERY->add_svar( QUERY, "int", "ACTIVE_UNIFORM_MAX_LENGTH", TRUE, (void *)&Chuck_OpenGL_ACTIVE_UNIFORM_MAX_LENGTH );
    QUERY->add_svar( QUERY, "int", "SHADER_SOURCE_LENGTH", TRUE, (void *)&Chuck_OpenGL_SHADER_SOURCE_LENGTH );
    QUERY->add_svar( QUERY, "int", "ACTIVE_ATTRIBUTES", TRUE, (void *)&Chuck_OpenGL_ACTIVE_ATTRIBUTES );
    QUERY->add_svar( QUERY, "int", "ACTIVE_ATTRIBUTE_MAX_LENGTH", TRUE, (void *)&Chuck_OpenGL_ACTIVE_ATTRIBUTE_MAX_LENGTH );
    QUERY->add_svar( QUERY, "int", "FRAGMENT_SHADER_DERIVATIVE_HINT", TRUE, (void *)&Chuck_OpenGL_FRAGMENT_SHADER_DERIVATIVE_HINT );
    QUERY->add_svar( QUERY, "int", "SHADING_LANGUAGE_VERSION", TRUE, (void *)&Chuck_OpenGL_SHADING_LANGUAGE_VERSION );
    QUERY->add_svar( QUERY, "int", "CURRENT_PROGRAM", TRUE, (void *)&Chuck_OpenGL_CURRENT_PROGRAM );
    QUERY->add_svar( QUERY, "int", "POINT_SPRITE_COORD_ORIGIN", TRUE, (void *)&Chuck_OpenGL_POINT_SPRITE_COORD_ORIGIN );
    QUERY->add_svar( QUERY, "int", "LOWER_LEFT", TRUE, (void *)&Chuck_OpenGL_LOWER_LEFT );
    QUERY->add_svar( QUERY, "int", "UPPER_LEFT", TRUE, (void *)&Chuck_OpenGL_UPPER_LEFT );
    QUERY->add_svar( QUERY, "int", "STENCIL_BACK_REF", TRUE, (void *)&Chuck_OpenGL_STENCIL_BACK_REF );
    QUERY->add_svar( QUERY, "int", "STENCIL_BACK_VALUE_MASK", TRUE, (void *)&Chuck_OpenGL_STENCIL_BACK_VALUE_MASK );
    QUERY->add_svar( QUERY, "int", "STENCIL_BACK_WRITEMASK", TRUE, (void *)&Chuck_OpenGL_STENCIL_BACK_WRITEMASK );
    QUERY->add_svar( QUERY, "int", "VERTEX_PROGRAM_TWO_SIDE", TRUE, (void *)&Chuck_OpenGL_VERTEX_PROGRAM_TWO_SIDE );
    QUERY->add_svar( QUERY, "int", "POINT_SPRITE", TRUE, (void *)&Chuck_OpenGL_POINT_SPRITE );
    QUERY->add_svar( QUERY, "int", "COORD_REPLACE", TRUE, (void *)&Chuck_OpenGL_COORD_REPLACE );
    QUERY->add_svar( QUERY, "int", "MAX_TEXTURE_COORDS", TRUE, (void *)&Chuck_OpenGL_MAX_TEXTURE_COORDS );

    QUERY->add_mfun(QUERY, Chuck_OpenGL_BlendEquationSeparate, "void", "BlendEquationSeparate");
    QUERY->add_arg(QUERY, "int", "modeRGB");
    QUERY->add_arg(QUERY, "int", "modeAlpha");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DrawBuffers, "void", "DrawBuffers");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->add_arg(QUERY, "int[]", "bufs");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_StencilOpSeparate, "void", "StencilOpSeparate");
    QUERY->add_arg(QUERY, "int", "face");
    QUERY->add_arg(QUERY, "int", "sfail");
    QUERY->add_arg(QUERY, "int", "dpfail");
    QUERY->add_arg(QUERY, "int", "dppass");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_StencilFuncSeparate, "void", "StencilFuncSeparate");
    QUERY->add_arg(QUERY, "int", "face");
    QUERY->add_arg(QUERY, "int", "func");
    QUERY->add_arg(QUERY, "int", "ref");
    QUERY->add_arg(QUERY, "int", "mask");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_StencilMaskSeparate, "void", "StencilMaskSeparate");
    QUERY->add_arg(QUERY, "int", "face");
    QUERY->add_arg(QUERY, "int", "mask");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_AttachShader, "void", "AttachShader");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "shader");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_BindAttribLocation, "void", "BindAttribLocation");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int[]", "name");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CompileShader, "void", "CompileShader");
    QUERY->add_arg(QUERY, "int", "shader");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CreateProgram, "int", "CreateProgram");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_CreateShader, "int", "CreateShader");
    QUERY->add_arg(QUERY, "int", "type");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DeleteProgram, "void", "DeleteProgram");
    QUERY->add_arg(QUERY, "int", "program");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DeleteShader, "void", "DeleteShader");
    QUERY->add_arg(QUERY, "int", "shader");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DetachShader, "void", "DetachShader");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "shader");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_DisableVertexAttribArray, "void", "DisableVertexAttribArray");
    QUERY->add_arg(QUERY, "int", "index");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_EnableVertexAttribArray, "void", "EnableVertexAttribArray");
    QUERY->add_arg(QUERY, "int", "index");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetActiveAttrib, "void", "GetActiveAttrib");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int", "bufSize");
    QUERY->add_arg(QUERY, "int[]", "length");
    QUERY->add_arg(QUERY, "int[]", "size");
    QUERY->add_arg(QUERY, "int[]", "type");
    QUERY->add_arg(QUERY, "int[]", "name");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetActiveUniform, "void", "GetActiveUniform");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int", "bufSize");
    QUERY->add_arg(QUERY, "int[]", "length");
    QUERY->add_arg(QUERY, "int[]", "size");
    QUERY->add_arg(QUERY, "int[]", "type");
    QUERY->add_arg(QUERY, "int[]", "name");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetAttachedShaders, "void", "GetAttachedShaders");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "maxCount");
    QUERY->add_arg(QUERY, "int[]", "count");
    QUERY->add_arg(QUERY, "int[]", "shaders");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetAttribLocation, "int", "GetAttribLocation");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int[]", "name");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetProgramiv, "void", "GetProgramiv");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetProgramInfoLog, "void", "GetProgramInfoLog");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "bufSize");
    QUERY->add_arg(QUERY, "int[]", "length");
    QUERY->add_arg(QUERY, "int[]", "infoLog");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetShaderiv, "void", "GetShaderiv");
    QUERY->add_arg(QUERY, "int", "shader");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetShaderInfoLog, "void", "GetShaderInfoLog");
    QUERY->add_arg(QUERY, "int", "shader");
    QUERY->add_arg(QUERY, "int", "bufSize");
    QUERY->add_arg(QUERY, "int[]", "length");
    QUERY->add_arg(QUERY, "int[]", "infoLog");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetShaderSource, "void", "GetShaderSource");
    QUERY->add_arg(QUERY, "int", "shader");
    QUERY->add_arg(QUERY, "int", "bufSize");
    QUERY->add_arg(QUERY, "int[]", "length");
    QUERY->add_arg(QUERY, "int[]", "source");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetUniformLocation, "int", "GetUniformLocation");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int[]", "name");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetUniformfv, "void", "GetUniformfv");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetUniformiv, "void", "GetUniformiv");
    QUERY->add_arg(QUERY, "int", "program");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetVertexAttribdv, "void", "GetVertexAttribdv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetVertexAttribfv, "void", "GetVertexAttribfv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "float[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_GetVertexAttribiv, "void", "GetVertexAttribiv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int", "pname");
    QUERY->add_arg(QUERY, "int[]", "params");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_IsProgram, "int", "IsProgram");
    QUERY->add_arg(QUERY, "int", "program");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_IsShader, "int", "IsShader");
    QUERY->add_arg(QUERY, "int", "shader");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_LinkProgram, "void", "LinkProgram");
    QUERY->add_arg(QUERY, "int", "program");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_UseProgram, "void", "UseProgram");
    QUERY->add_arg(QUERY, "int", "program");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform1f, "void", "Uniform1f");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "float", "v0");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform2f, "void", "Uniform2f");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "float", "v0");
    QUERY->add_arg(QUERY, "float", "v1");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform3f, "void", "Uniform3f");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "float", "v0");
    QUERY->add_arg(QUERY, "float", "v1");
    QUERY->add_arg(QUERY, "float", "v2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform4f, "void", "Uniform4f");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "float", "v0");
    QUERY->add_arg(QUERY, "float", "v1");
    QUERY->add_arg(QUERY, "float", "v2");
    QUERY->add_arg(QUERY, "float", "v3");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform1i, "void", "Uniform1i");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "v0");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform2i, "void", "Uniform2i");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "v0");
    QUERY->add_arg(QUERY, "int", "v1");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform3i, "void", "Uniform3i");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "v0");
    QUERY->add_arg(QUERY, "int", "v1");
    QUERY->add_arg(QUERY, "int", "v2");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform4i, "void", "Uniform4i");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "v0");
    QUERY->add_arg(QUERY, "int", "v1");
    QUERY->add_arg(QUERY, "int", "v2");
    QUERY->add_arg(QUERY, "int", "v3");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform1fv, "void", "Uniform1fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform2fv, "void", "Uniform2fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform3fv, "void", "Uniform3fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform4fv, "void", "Uniform4fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform1iv, "void", "Uniform1iv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform2iv, "void", "Uniform2iv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform3iv, "void", "Uniform3iv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_Uniform4iv, "void", "Uniform4iv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_UniformMatrix2fv, "void", "UniformMatrix2fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int", "transpose");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_UniformMatrix3fv, "void", "UniformMatrix3fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int", "transpose");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_UniformMatrix4fv, "void", "UniformMatrix4fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int", "transpose");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_ValidateProgram, "void", "ValidateProgram");
    QUERY->add_arg(QUERY, "int", "program");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib1d, "void", "VertexAttrib1d");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float", "x");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib1dv, "void", "VertexAttrib1dv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib1f, "void", "VertexAttrib1f");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float", "x");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib1fv, "void", "VertexAttrib1fv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib1s, "void", "VertexAttrib1s");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int", "x");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib1sv, "void", "VertexAttrib1sv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib2d, "void", "VertexAttrib2d");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib2dv, "void", "VertexAttrib2dv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib2f, "void", "VertexAttrib2f");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib2fv, "void", "VertexAttrib2fv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib2s, "void", "VertexAttrib2s");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib2sv, "void", "VertexAttrib2sv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib3d, "void", "VertexAttrib3d");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib3dv, "void", "VertexAttrib3dv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib3f, "void", "VertexAttrib3f");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib3fv, "void", "VertexAttrib3fv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib3s, "void", "VertexAttrib3s");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "z");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib3sv, "void", "VertexAttrib3sv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4Nbv, "void", "VertexAttrib4Nbv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4Niv, "void", "VertexAttrib4Niv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4Nsv, "void", "VertexAttrib4Nsv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4Nub, "void", "VertexAttrib4Nub");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "z");
    QUERY->add_arg(QUERY, "int", "w");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4Nubv, "void", "VertexAttrib4Nubv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4Nuiv, "void", "VertexAttrib4Nuiv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4Nusv, "void", "VertexAttrib4Nusv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4bv, "void", "VertexAttrib4bv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4d, "void", "VertexAttrib4d");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");
    QUERY->add_arg(QUERY, "float", "w");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4dv, "void", "VertexAttrib4dv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4f, "void", "VertexAttrib4f");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float", "x");
    QUERY->add_arg(QUERY, "float", "y");
    QUERY->add_arg(QUERY, "float", "z");
    QUERY->add_arg(QUERY, "float", "w");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4fv, "void", "VertexAttrib4fv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "float[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4iv, "void", "VertexAttrib4iv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4s, "void", "VertexAttrib4s");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int", "x");
    QUERY->add_arg(QUERY, "int", "y");
    QUERY->add_arg(QUERY, "int", "z");
    QUERY->add_arg(QUERY, "int", "w");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4sv, "void", "VertexAttrib4sv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4ubv, "void", "VertexAttrib4ubv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4uiv, "void", "VertexAttrib4uiv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttrib4usv, "void", "VertexAttrib4usv");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int[]", "v");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_VertexAttribPointer, "void", "VertexAttribPointer");
    QUERY->add_arg(QUERY, "int", "index");
    QUERY->add_arg(QUERY, "int", "size");
    QUERY->add_arg(QUERY, "int", "type");
    QUERY->add_arg(QUERY, "int", "normalized");
    QUERY->add_arg(QUERY, "int", "stride");
    QUERY->add_arg(QUERY, "Object", "pointer");

    QUERY->add_svar( QUERY, "int", "PIXEL_PACK_BUFFER", TRUE, (void *)&Chuck_OpenGL_PIXEL_PACK_BUFFER );
    QUERY->add_svar( QUERY, "int", "PIXEL_UNPACK_BUFFER", TRUE, (void *)&Chuck_OpenGL_PIXEL_UNPACK_BUFFER );
    QUERY->add_svar( QUERY, "int", "PIXEL_PACK_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_PIXEL_PACK_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "PIXEL_UNPACK_BUFFER_BINDING", TRUE, (void *)&Chuck_OpenGL_PIXEL_UNPACK_BUFFER_BINDING );
    QUERY->add_svar( QUERY, "int", "FLOAT_MAT2x3", TRUE, (void *)&Chuck_OpenGL_FLOAT_MAT2x3 );
    QUERY->add_svar( QUERY, "int", "FLOAT_MAT2x4", TRUE, (void *)&Chuck_OpenGL_FLOAT_MAT2x4 );
    QUERY->add_svar( QUERY, "int", "FLOAT_MAT3x2", TRUE, (void *)&Chuck_OpenGL_FLOAT_MAT3x2 );
    QUERY->add_svar( QUERY, "int", "FLOAT_MAT3x4", TRUE, (void *)&Chuck_OpenGL_FLOAT_MAT3x4 );
    QUERY->add_svar( QUERY, "int", "FLOAT_MAT4x2", TRUE, (void *)&Chuck_OpenGL_FLOAT_MAT4x2 );
    QUERY->add_svar( QUERY, "int", "FLOAT_MAT4x3", TRUE, (void *)&Chuck_OpenGL_FLOAT_MAT4x3 );
    QUERY->add_svar( QUERY, "int", "SRGB", TRUE, (void *)&Chuck_OpenGL_SRGB );
    QUERY->add_svar( QUERY, "int", "SRGB8", TRUE, (void *)&Chuck_OpenGL_SRGB8 );
    QUERY->add_svar( QUERY, "int", "SRGB_ALPHA", TRUE, (void *)&Chuck_OpenGL_SRGB_ALPHA );
    QUERY->add_svar( QUERY, "int", "SRGB8_ALPHA8", TRUE, (void *)&Chuck_OpenGL_SRGB8_ALPHA8 );
    QUERY->add_svar( QUERY, "int", "COMPRESSED_SRGB", TRUE, (void *)&Chuck_OpenGL_COMPRESSED_SRGB );
    QUERY->add_svar( QUERY, "int", "COMPRESSED_SRGB_ALPHA", TRUE, (void *)&Chuck_OpenGL_COMPRESSED_SRGB_ALPHA );
    QUERY->add_svar( QUERY, "int", "CURRENT_RASTER_SECONDARY_COLOR", TRUE, (void *)&Chuck_OpenGL_CURRENT_RASTER_SECONDARY_COLOR );
    QUERY->add_svar( QUERY, "int", "SLUMINANCE_ALPHA", TRUE, (void *)&Chuck_OpenGL_SLUMINANCE_ALPHA );
    QUERY->add_svar( QUERY, "int", "SLUMINANCE8_ALPHA8", TRUE, (void *)&Chuck_OpenGL_SLUMINANCE8_ALPHA8 );
    QUERY->add_svar( QUERY, "int", "SLUMINANCE", TRUE, (void *)&Chuck_OpenGL_SLUMINANCE );
    QUERY->add_svar( QUERY, "int", "SLUMINANCE8", TRUE, (void *)&Chuck_OpenGL_SLUMINANCE8 );
    QUERY->add_svar( QUERY, "int", "COMPRESSED_SLUMINANCE", TRUE, (void *)&Chuck_OpenGL_COMPRESSED_SLUMINANCE );
    QUERY->add_svar( QUERY, "int", "COMPRESSED_SLUMINANCE_ALPHA", TRUE, (void *)&Chuck_OpenGL_COMPRESSED_SLUMINANCE_ALPHA );

    QUERY->add_mfun(QUERY, Chuck_OpenGL_UniformMatrix2x3fv, "void", "UniformMatrix2x3fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int", "transpose");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_UniformMatrix3x2fv, "void", "UniformMatrix3x2fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int", "transpose");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_UniformMatrix2x4fv, "void", "UniformMatrix2x4fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int", "transpose");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_UniformMatrix4x2fv, "void", "UniformMatrix4x2fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int", "transpose");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_UniformMatrix3x4fv, "void", "UniformMatrix3x4fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int", "transpose");
    QUERY->add_arg(QUERY, "float[]", "value");


    QUERY->add_mfun(QUERY, Chuck_OpenGL_UniformMatrix4x3fv, "void", "UniformMatrix4x3fv");
    QUERY->add_arg(QUERY, "int", "location");
    QUERY->add_arg(QUERY, "int", "count");
    QUERY->add_arg(QUERY, "int", "transpose");
    QUERY->add_arg(QUERY, "float[]", "value");


    
    QUERY->end_class(QUERY);
    
    return TRUE;
}

