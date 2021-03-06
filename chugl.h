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

#ifndef CHUGL_H
#define CHUGL_H

#include "chuck_dl.h"
#include "chuck_def.h"

#include "glplat.h"

#include <list>

using namespace std;


class ixPointer;


/*-----------------------------------------------------------------------------
 chugl_array_data_base
 chugl_array_data

 Used to store allocated vector data in between multiple calls to GL, e.g. for 
 glVertexPointer, glTexCoordPointer, etc. Arrays stored in this way are deleted
 every time the GL context is unlocked. 
-----------------------------------------------------------------------------*/

#include "boost/scoped_array.hpp"

class chugl_array_data_base
{
public:
    chugl_array_data_base() { }
    virtual ~chugl_array_data_base() { }
};

template<typename T>
class chugl_array_data : public chugl_array_data_base
{
public:
    chugl_array_data(T *data = NULL) : m_data(data) { }
    virtual ~chugl_array_data() { }
    
    void set(T *data) { m_data.reset(data); }
    
private:
    boost::scoped_array<T> m_data;
};


class chugl
{
public:
    
    static chugl *platformMake(); // defined for subclass/platform
    static chugl *mainChugl();
    
    chugl();
    virtual ~chugl();
        
    t_CKBOOL good() const { return m_good; }
    
    virtual void openWindow(t_CKFLOAT width, t_CKFLOAT height) = 0;
    virtual void openFullscreen() = 0;
    virtual t_CKBOOL isOpen() = 0;
    
    // virtual void lock() = 0;
    // virtual void unlock() = 0;
    // t_CKBOOL locked() const { return m_lock > 0; }
    
    void enter();
    void exit();
    
    t_CKFLOAT windowWidth() const { return m_windowWidth; }
    t_CKFLOAT windowHeight() const { return m_windowHeight; }
    
    template<typename T>
    void scheduleDataForCleanup(T *data)
    {
        m_cleanupData.push_back(new chugl_array_data<T>(data));
    }
    
    void scheduleArrayForCleanup(Chuck_Array *array)
    {
        m_cleanupArray.push_back(array);
    }
    
    void setPointer(ixPointer *pointer);
    ixPointer *pointer();
    
    virtual void hideCursor() = 0;
    virtual void showCursor() = 0;
    
    
protected:
    void cleanupArrayData();
    
    virtual void backendEnter() = 0;
    virtual void backendExit() = 0;
    virtual void platformEnter() = 0;
    virtual void platformExit() = 0;
    virtual t_CKBOOL isMainThread() = 0;
    
    void (*m_Chuck_UI_Manager_init)();
    void (*m_Chuck_UI_Manager_start)();
    t_CKINT m_lock;
    t_CKBOOL m_enter;
    t_CKBOOL m_enterMainThread;
    t_CKBOOL m_good;
    t_CKFLOAT m_windowWidth, m_windowHeight;
    
    ixPointer *m_pointer;
    
    list<chugl_array_data_base *> m_cleanupData;
    list<Chuck_Array *> m_cleanupArray;
    
private:
    static chugl *s_mainChugl;
};


class chugl_image
{
public:
    static chugl_image *platformMake(); // defined for subclass/platform
    
    chugl_image();
    virtual ~chugl_image();
    
    virtual t_CKBOOL load(const std::string &filepath) = 0;
    virtual t_CKBOOL unload() = 0;
    
    GLuint tex() { return m_tex; }
    
protected:
    
    GLuint m_tex;
};


#endif // CHUGL_H

