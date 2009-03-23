/****************************************************************************
 **
 ** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
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
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
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

#include "qmacdefines_mac.h"
#ifdef QT_MAC_USE_COCOA

#import <private/qcocoaapplicationdelegate_mac_p.h>
#import <private/qcocoamenuloader_mac_p.h>
#include <private/qapplication_p.h>
#include <private/qt_mac_p.h>
#include <private/qt_cocoa_helpers_mac_p.h>
#include <private/qdesktopwidget_mac_p.h>
#include <qevent.h>
#include <qapplication.h>

QT_BEGIN_NAMESPACE
extern void onApplicationChangedActivation(bool); // qapplication_mac.mm
QT_END_NAMESPACE

QT_FORWARD_DECLARE_CLASS(QDesktopWidgetImplementation)
QT_USE_NAMESPACE

static QT_MANGLE_NAMESPACE(QCocoaApplicationDelegate) *sharedCocoaApplicationDelegate = nil;

static void cleanupCocoaApplicationDelegate()
{
    [sharedCocoaApplicationDelegate release];
}

@implementation QT_MANGLE_NAMESPACE(QCocoaApplicationDelegate)

- (id)init
{
    self = [super init];
    return self;
}

- (void)dealloc
{
    sharedCocoaApplicationDelegate = nil;
    [dockMenu release];
    [qtMenuLoader release];
    if (reflectionDelegate) {
        [NSApp setDelegate:reflectionDelegate];
        [reflectionDelegate release];
    }
    [super dealloc];
}

+ (id)allocWithZone:(NSZone *)zone
{
    @synchronized(self) {
        if (sharedCocoaApplicationDelegate == nil) {
            sharedCocoaApplicationDelegate = [super allocWithZone:zone];
            return sharedCocoaApplicationDelegate;
            qAddPostRoutine(cleanupCocoaApplicationDelegate);
        }
    }
    return nil;
}

+ (QT_MANGLE_NAMESPACE(QCocoaApplicationDelegate)*)sharedDelegate
{
    @synchronized(self) {
        if (sharedCocoaApplicationDelegate == nil)
            [[self alloc] init];
    }
    return [[sharedCocoaApplicationDelegate retain] autorelease];
}

- (void)setDockMenu:(NSMenu*)newMenu
{
    [newMenu retain];
    [dockMenu release];
    dockMenu = newMenu;
}

- (NSMenu *)applicationDockMenu
{
    return [[dockMenu retain] autorelease];
}

- (QApplicationPrivate *)qAppPrivate
{
    return qtPrivate;
}

- (void)setQtPrivate:(QApplicationPrivate *)value
{
    qtPrivate = value;
}

- (void)setMenuLoader:(QT_MANGLE_NAMESPACE(QCocoaMenuLoader) *)menuLoader
{
    [menuLoader retain];
    [qtMenuLoader release];
    qtMenuLoader = menuLoader;
}

- (QT_MANGLE_NAMESPACE(QCocoaMenuLoader) *)menuLoader;
{
    return [[qtMenuLoader retain] autorelease];
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender
{
    Q_UNUSED(sender);
    // The reflection delegate gets precedence
    NSApplicationTerminateReply reply = NSTerminateCancel;
    if (reflectionDelegate
        && [reflectionDelegate respondsToSelector:@selector(applicationShouldTerminate:)]) {
        return [reflectionDelegate applicationShouldTerminate:sender];
    }

    if (qtPrivate->canQuit()) {
        reply = NSTerminateNow;
        if (!startedQuit) {
            startedQuit = true;
            qAppInstance()->quit();
            startedQuit = false;
        }
    }
    return reply;
}

- (void)application:(NSApplication *)sender openFiles:(NSArray *)filenames
{
    unsigned int ix;
    for( ix = 0; ix < [filenames count]; ix++) {
        NSString *fileName = [filenames objectAtIndex:ix];
        qApp->postEvent(qApp, new QFileOpenEvent(QCFString::toQString((CFStringRef)fileName)));
    }

    if (reflectionDelegate &&
        [reflectionDelegate respondsToSelector:@selector(application:openFiles:)])
        [reflectionDelegate application:sender openFiles:filenames];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    // If we have a reflection delegate, that will get to call the shots.
    if (reflectionDelegate
        && [reflectionDelegate respondsToSelector:
                            @selector(applicationShouldTerminateAfterLastWindowClosed:)])
        return [reflectionDelegate applicationShouldTerminateAfterLastWindowClosed:sender];
    return NO; // Someday qApp->quitOnLastWindowClosed(); when QApp and NSApp work closer together.
}


- (void)applicationDidBecomeActive:(NSNotification *)notification
{
    if (reflectionDelegate
        && [reflectionDelegate respondsToSelector:@selector(applicationDidBecomeActive:)])
        [reflectionDelegate applicationDidBecomeActive:notification];
    onApplicationChangedActivation(true);
}

- (void)applicationDidResignActive:(NSNotification *)notification;
{
    if (reflectionDelegate
        && [reflectionDelegate respondsToSelector:@selector(applicationDidResignActive:)])
        [reflectionDelegate applicationDidResignActive:notification];
    onApplicationChangedActivation(false);
}

class QDesktopWidgetImplementation;
- (void)applicationDidChangeScreenParameters:(NSNotification *)notification
{
    Q_UNUSED(notification);
    QDesktopWidgetImplementation::instance()->onResize();
}

- (void)setReflectionDelegate:(NSObject *)oldDelegate
{
    [oldDelegate retain];
    [reflectionDelegate release];
    reflectionDelegate = oldDelegate;
}

- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector
{
    NSMethodSignature *result = [super methodSignatureForSelector:aSelector];
    if (!result && reflectionDelegate) {
        result = [reflectionDelegate methodSignatureForSelector:aSelector];
    }
    return result;
}

- (BOOL)respondsToSelector:(SEL)aSelector
{
    BOOL result = [super respondsToSelector:aSelector];
    if (!result && reflectionDelegate)
        result = [reflectionDelegate respondsToSelector:aSelector];
    return result;
}

- (void)forwardInvocation:(NSInvocation *)invocation
{
    SEL invocationSelector = [invocation selector];
    if (reflectionDelegate && [reflectionDelegate respondsToSelector:invocationSelector])
        [invocation invokeWithTarget:reflectionDelegate];
    else
        [self doesNotRecognizeSelector:invocationSelector];
}

@end
#endif
