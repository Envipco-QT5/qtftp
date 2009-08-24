/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the either Technology Preview License Agreement or the
** Beta Release License Agreement.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://qt.nokia.com/contact.
** $QT_END_LICENSE$
**
****************************************************************************/

/****************************************************************************
**
** Copyright (c) 2007-2008, Apple, Inc.
**
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**
**   * Redistributions of source code must retain the above copyright notice,
**     this list of conditions and the following disclaimer.
**
**   * Redistributions in binary form must reproduce the above copyright notice,
**     this list of conditions and the following disclaimer in the documentation
**     and/or other materials provided with the distribution.
**
**   * Neither the name of Apple, Inc. nor the names of its contributors
**     may be used to endorse or promote products derived from this software
**     without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
** CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of qapplication_*.cpp, qwidget*.cpp, qcolor_x11.cpp, qfiledialog.cpp
// and many other.  This header file may change from version to version
// without notice, or even be removed.
//
// We mean it.
//

#include <private/qt_mac_p.h>

#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qwidget.h>
#include <qevent.h>
#include <qhash.h>
#include <qlabel.h>
#include <qpointer.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qstylepainter.h>
#include <qtimer.h>
#include <qtooltip.h>
#include <private/qeffects_p.h>
#include <qtextdocument.h>
#include <qdebug.h>
#include <qpoint.h>
#include "private/qt_mac_p.h"

struct HIContentBorderMetrics;

#ifdef Q_WS_MAC32
typedef struct _NSPoint NSPoint; // Just redefine here so I don't have to pull in all of Cocoa.
#else
typedef struct CGPoint NSPoint;
#endif

QT_BEGIN_NAMESPACE
Qt::MouseButtons qt_mac_get_buttons(int buttons);
Qt::MouseButton qt_mac_get_button(EventMouseButton button);
void macWindowFade(void * /*OSWindowRef*/ window, float durationSeconds = 0);
bool macWindowIsTextured(void * /*OSWindowRef*/ window);
void macWindowToolbarShow(const QWidget *widget, bool show );
void macWindowToolbarSet( void * /*OSWindowRef*/ window, void* toolbarRef );
bool macWindowToolbarVisible( void * /*OSWindowRef*/ window );
void macWindowSetHasShadow( void * /*OSWindowRef*/ window, bool hasShadow );
void macWindowFlush(void * /*OSWindowRef*/ window);
void qt_mac_updateContentBorderMetricts(void * /*OSWindowRef */window, const ::HIContentBorderMetrics &metrics);
void * /*NSImage */qt_mac_create_nsimage(const QPixmap &pm);
void qt_mac_update_mouseTracking(QWidget *widget);
OSStatus qt_mac_drawCGImage(CGContextRef cg, const CGRect *inbounds, CGImageRef);
bool qt_mac_checkForNativeSizeGrip(const QWidget *widget);
void qt_dispatchTabletProximityEvent(void * /*NSEvent * */ tabletEvent);
#ifdef QT_MAC_USE_COCOA
bool qt_dispatchKeyEventWithCocoa(void * /*NSEvent * */ keyEvent, QWidget *widgetToGetEvent);
#endif
bool qt_dispatchKeyEvent(void * /*NSEvent * */ keyEvent, QWidget *widgetToGetEvent);
void qt_dispatchModifiersChanged(void * /*NSEvent * */flagsChangedEvent, QWidget *widgetToGetEvent);
void qt_mac_dispatchNCMouseMessage(void */* NSWindow* */eventWindow, void */* NSEvent* */mouseEvent, 
                                   QWidget *widgetToGetEvent, bool &leftButtonIsRightButton);
bool qt_mac_handleMouseEvent(void * /*QCocoaView * */view, void * /*NSEvent * */event, QEvent::Type eventType, Qt::MouseButton button);
bool qt_mac_handleTabletEvent(void * /*QCocoaView * */view, void * /*NSEvent * */event);
inline QApplication *qAppInstance() { return static_cast<QApplication *>(QCoreApplication::instance()); }
struct ::TabletProximityRec;
void qt_dispatchTabletProximityEvent(const ::TabletProximityRec &proxRec);
Qt::KeyboardModifiers qt_cocoaModifiers2QtModifiers(ulong modifierFlags);
Qt::KeyboardModifiers qt_cocoaDragOperation2QtModifiers(uint dragOperations);
inline int flipYCoordinate(int y)
{
    return QApplication::desktop()->screenGeometry(0).height() - y;    
}

inline qreal flipYCoordinate(qreal y)
{
    return QApplication::desktop()->screenGeometry(0).height() - y;
}

QPointF flipPoint(const NSPoint &p);
NSPoint flipPoint(const QPoint &p);
NSPoint flipPoint(const QPointF &p);

QStringList qt_mac_NSArrayToQStringList(void *nsarray);
void *qt_mac_QStringListToNSMutableArrayVoid(const QStringList &list);

void qt_syncCocoaTitleBarButtons(OSWindowRef window, QWidget *widgetForWindow);

#ifdef __OBJC__
inline NSMutableArray *qt_mac_QStringListToNSMutableArray(const QStringList &qstrlist)
{ return reinterpret_cast<NSMutableArray *>(qt_mac_QStringListToNSMutableArrayVoid(qstrlist)); }

inline QString qt_mac_NSStringToQString(const NSString *nsstr)
{ return QCFString::toQString(reinterpret_cast<const CFStringRef>(nsstr)); }

inline NSString *qt_mac_QStringToNSString(const QString &qstr)
{ return [reinterpret_cast<const NSString *>(QCFString::toCFStringRef(qstr)) autorelease]; }
#endif

QT_END_NAMESPACE
