#ifndef oxygenshadowhelper_h
#define oxygenshadowhelper_h

//////////////////////////////////////////////////////////////////////////////
// oxygenshadowhelper.h
// handle shadow pixmaps passed to window manager via X property
// -------------------
//
// Copyright (c) 2010 Hugo Pereira Da Costa <hugo@oxygen-icons.org>
//
// Loosely inspired (and largely rewritten) from BeSpin style
// Copyright (C) 2007 Thomas Luebking <thomas.luebking@web.de>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////

#include "oxygentileset.h"

#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtCore/QSet>

#ifdef Q_WS_X11
#include <X11/Xdefs.h>
#endif

namespace Oxygen
{

    //! forward declaration
    class ShadowCache;
    class Helper;

    //! handle shadow pixmaps passed to window manager via X property
    class ShadowHelper: public QObject
    {

        Q_OBJECT

        public:

        //! constructor
        ShadowHelper( QObject*, Helper& );

        //! destructor
        virtual ~ShadowHelper( void );

        //! register widget
        bool registerWidget( QWidget* );

        //! unregister widget
        void unregisterWidget( QWidget* );

        //! reload config
        void reloadConfig( void );

        protected slots:

        //! unregister widget
        void objectDeleted( QObject* );

        protected:

        //! shadow cache
        const ShadowCache& shadowCache( void ) const
        { return *_shadowCache; }

        //! shadow cache
        ShadowCache& shadowCache( void )
        { return *_shadowCache; }

        //! install shadow X11 property on given widget
        /*!
        shadow atom and property specification available at
        http://community.kde.org/KWin/Shadow
        */
        bool installX11Shadows( QWidget* ) const;

        //! install shadow X11 property on given widget
        /*!
        shadow atom and property specification available at
        http://community.kde.org/KWin/Shadow
        */
        void uninstallX11Shadows( QWidget* ) const;

        private:

        //! cache
        ShadowCache* _shadowCache;

        //! set of registered widgets
        QSet<QWidget*> _widgets;

        //! shadow
        TileSet _shadows;

        //! shadow size
        int _shadowSize;

        #ifdef Q_WS_X11
        //! shadow atom
        Atom _atom;
        #endif

    };

}

#endif