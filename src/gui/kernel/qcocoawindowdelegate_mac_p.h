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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qmacdefines_mac.h"

#ifdef QT_MAC_USE_COCOA
#import <Cocoa/Cocoa.h>

QT_BEGIN_NAMESPACE
template <class Key, class T> class QHash;
QT_END_NAMESPACE
using QT_PREPEND_NAMESPACE(QHash);
QT_FORWARD_DECLARE_CLASS(QWidget)
QT_FORWARD_DECLARE_CLASS(QSize)
QT_FORWARD_DECLARE_CLASS(QWidgetData)

#if MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_5
@protocol NSWindowDelegate <NSObject>
- (NSSize)windowWillResize:(NSWindow *)window toSize:(NSSize)proposedFrameSize;
- (void)windowDidMiniaturize:(NSNotification*)notification;
- (void)windowDidResize:(NSNotification *)notification;
- (NSRect)windowWillUseStandardFrame:(NSWindow *)window defaultFrame:(NSRect)defaultFrame;
- (void)windowDidMove:(NSNotification *)notification;
- (BOOL)windowShouldClose:(id)window;
- (void)windowDidDeminiaturize:(NSNotification *)notification;
- (void)windowDidBecomeMain:(NSNotification*)notification;
- (void)windowDidResignMain:(NSNotification*)notification;
- (void)windowDidBecomeKey:(NSNotification*)notification;
- (void)windowDidResignKey:(NSNotification*)notification;
@end

@protocol NSDrawerDelegate <NSObject>
- (NSSize)drawerWillResizeContents:(NSDrawer *)sender toSize:(NSSize)contentSize;
@end

#endif



@interface QT_MANGLE_NAMESPACE(QCocoaWindowDelegate) : NSObject<NSWindowDelegate, NSDrawerDelegate> {
    QHash<NSWindow *, QWidget *> *m_windowHash;
    QHash<NSDrawer *, QWidget *> *m_drawerHash;
}
+ (QT_MANGLE_NAMESPACE(QCocoaWindowDelegate)*)sharedDelegate;
- (void)becomeDelegteForWindow:(NSWindow *)window  widget:(QWidget *)widget;
- (void)resignDelegateForWindow:(NSWindow *)window;
- (void)becomeDelegateForDrawer:(NSDrawer *)drawer widget:(QWidget *)widget;
- (void)resignDelegateForDrawer:(NSDrawer *)drawer;
- (void)dumpMaximizedStateforWidget:(QWidget*)qwidget window:(NSWindow *)window;
- (void)syncSizeForWidget:(QWidget *)qwidget
        toSize:(const QSize &)newSize
        fromSize:(const QSize &)oldSize;
- (NSSize)closestAcceptableSizeForWidget:(QWidget *)qwidget
        window:(NSWindow *)window withNewSize:(NSSize)proposedSize;
- (QWidget *)qt_qwidgetForWindow:(NSWindow *)window;
@end
#endif
