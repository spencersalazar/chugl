/*----------------------------------------------------------------------------
 ChucK Concurrent, On-the-fly Audio Programming Language
 Compiler and Virtual Machine
 
 Copyright (c) 2004 Ge Wang and Perry R. Cook.  All rights reserved.
 http://chuck.cs.princeton.edu/
 http://soundlab.cs.princeton.edu/
 
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

//-----------------------------------------------------------------------------
// file: chuck_ui_qt.cpp
// desc: ui boilerplate for QT 
//
// author: Spencer Salazar (spencer@ccrma.stanford.edu)
// date: October 2014
//-----------------------------------------------------------------------------

#include "chuck_ui.h"
#include "chuck_ui_qt.h"

#include "chuck_vm.h"
#include "chuck_globals.h"
#include "chuck_errmsg.h"
#include "util_icon.h"

#include <QApplication>


mAApplicationDelegate::mAApplicationDelegate() : QObject(NULL)
{
    connect(this, SIGNAL(processSynchronous(mAMainThreadProcessor *)), this, SLOT(process(mAMainThreadProcessor *)), Qt::BlockingQueuedConnection);
    connect(this, SIGNAL(processAsynchronous(mAMainThreadProcessor *)), this, SLOT(process(mAMainThreadProcessor *)), Qt::QueuedConnection);
}

mAApplicationDelegate::~mAApplicationDelegate() { }


void mAApplicationDelegate::aboutToQuit()
{
    // termination of vm will cause application exit
    if(g_vm) g_vm->shutdown();
}

void mAApplicationDelegate::process(mAMainThreadProcessor *proc)
{
    proc->execute();
}



struct Chuck_UI_Manager::platform_data
{
    platform_data() : m_app(NULL), m_appDelegate(NULL) { }
    
    QApplication *m_app;
    mAApplicationDelegate *m_appDelegate;
};


static Chuck_UI_Manager * g_ui_manager = NULL;

Chuck_UI_Manager * Chuck_UI_Manager::instance()
{
    if(g_ui_manager == NULL)
        g_ui_manager = new Chuck_UI_Manager;
    return g_ui_manager;
}

Chuck_UI_Manager::Chuck_UI_Manager() : m_platformData(new platform_data)
{
    init();
}

void Chuck_UI_Manager::init()
{
    m_hasStarted = false;
    m_doStart = false;
    m_doShutdown = false;
    m_hasMainThreadInit = false;
    m_hookActivated = false;
    m_hook = NULL;
}

void Chuck_UI_Manager::main_thread_init()
{
    if(false) // TODO is main thread?
    {
        EM_error3("chuck_ui: attempt to call main_thread_init from non-main thread!");
        return;
    }
    
    if(m_hasMainThreadInit)
        return;
    
    EM_log(CK_LOG_INFO, "chuck_ui: initializing on main-thread");
    
    m_hasMainThreadInit = true;
    
    platform_mainThreadInit();
}

void Chuck_UI_Manager::run()
{
    while( !m_doStart && !m_doShutdown )
    {
        // TODO: semaphore?
        usleep(10000);
    }
    
    if( m_doShutdown )
        return;
    
    main_thread_init();
    
    m_hasStarted = true;
    m_doStart = false;
    
    EM_log(CK_LOG_INFO, "running chuck_ui");
    
    platform_run();
    
    m_hook->deactivate(m_hook);
}


void Chuck_UI_Manager::start()
{
    if( !m_hookActivated )
    {
        m_hook->activate(m_hook);
        m_hookActivated = true;
    }
    
    if( !m_hasStarted )
    {
        // if main thread
        if(platform_isMainThread())
            main_thread_init();
        
        m_doStart = true;
    }
}

void Chuck_UI_Manager::shutdown()
{
    m_doShutdown = true;
    
    if( m_hasStarted || m_doStart )
    {
        platform_shutdown();
    }
}


void Chuck_UI_Manager::platform_mainThreadInit()
{
    int argc = 1;
    char *argv = "chuck";
    
    QApplication *app = new QApplication(argc, &argv);
    
    m_platformData->m_app = app;
    
    mAApplicationDelegate *appDelegate = new mAApplicationDelegate;
    m_platformData->m_appDelegate = appDelegate;
    QObject::connect(app, SIGNAL(aboutToQuit()), appDelegate, SLOT(aboutToQuit()));
}

void Chuck_UI_Manager::platform_run()
{
    m_platformData->m_app->exec();
}

void Chuck_UI_Manager::platform_shutdown()
{
    m_platformData->m_app->quit();
}

bool Chuck_UI_Manager::platform_isMainThread()
{
    // HACK: assume main thread if ChucK is processing 0th sample code
    return g_vm->shreduler()->now_system == 0;
}


