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

#include "qmacdefines_mac.h"
#include "qapplication.h"
#ifdef QT_MAC_USE_COCOA
#import <private/qcocoamenu_mac_p.h>
#import <private/qcocoamenuloader_mac_p.h>
#include <private/qt_cocoa_helpers_mac_p.h>
#include <private/qapplication_p.h>

#include <QtGui/QMenu>

QT_FORWARD_DECLARE_CLASS(QAction)
QT_FORWARD_DECLARE_CLASS(QWidget)
QT_FORWARD_DECLARE_CLASS(QApplication)

QT_BEGIN_NAMESPACE
extern bool qt_sendSpontaneousEvent(QObject*, QEvent*); //qapplication.cpp
QT_END_NAMESPACE

@implementation QT_MANGLE_NAMESPACE(QCocoaMenu)

- (id)initWithQMenu:(QMenu*)menu
{
    self = [super init];
    if (self) {
        qmenu = menu;
        [self setAutoenablesItems:NO];
        [self setDelegate:self];
    }
    return self;
}

- (void)menu:(NSMenu*)menu willHighlightItem:(NSMenuItem*)item;
{
    Q_UNUSED(menu);

    if (!item) {
        // ### According to the docs everything will be highlighted. Not sure what we should do in
        // Qt, so just return.
        return;
    }

    if (QAction *action = reinterpret_cast<QAction *>([item tag]))
        action->activate(QAction::Hover);
}

- (void)menuWillOpen:(NSMenu*)menu;
{
    while (QWidget *popup
                = QApplication::activePopupWidget())
        popup->close();
    qt_mac_emit_menuSignals(((QT_MANGLE_NAMESPACE(QCocoaMenu) *)menu)->qmenu, true);
}

- (void)menuWillClose:(NSMenu*)menu;
{
    qt_mac_emit_menuSignals(((QT_MANGLE_NAMESPACE(QCocoaMenu) *)menu)->qmenu, false);
}

- (BOOL)hasShortcut:(NSMenu *)menu forKey:(NSString *)key forModifiers:(NSUInteger)modifier
  whichItem:(NSMenuItem**)outItem
{
    for (NSMenuItem *item in [menu itemArray]) {
        if (![item isEnabled] || [item isHidden] || [item isSeparatorItem])
            continue;
        if ([item hasSubmenu]) {
            if ([self hasShortcut:[item submenu]
                           forKey:key
                     forModifiers:modifier whichItem:outItem]) {
                if (outItem)
                    *outItem = item;
                return YES;
            }
        }
        NSString *menuKey = [item keyEquivalent];
        if (menuKey && NSOrderedSame == [menuKey compare:key]
            && (modifier == [item keyEquivalentModifierMask])) {
            if (outItem)
                *outItem = item;
            return YES;
        }
    }
    if (outItem)
        *outItem = 0;
    return NO;
}

- (BOOL)menuHasKeyEquivalent:(NSMenu *)menu forEvent:(NSEvent *)event target:(id *)target action:(SEL *)action
{
    // Check if the menu actually has a keysequence defined for this key event.
    // If it does, then we will first send the key sequence to the QWidget that has focus
    // since (in Qt's eyes) it needs to a chance at the key event first. If the widget
    // accepts the key event, we then return YES, but set the target and action to be nil,
    // which means that the action should not be triggered, and instead dispatch the event ourselves.
    // In every other case we return NO, which means that Cocoa can do as it pleases
    // (i.e., fire the menu action).
    NSMenuItem *whichItem;
    if ([self hasShortcut:menu
                   forKey:[event characters]
             forModifiers:([event modifierFlags] & NSDeviceIndependentModifierFlagsMask)
                 whichItem:&whichItem]) {
        QWidget *widget = 0;
        QAction *qaction = 0;
        if (whichItem && [whichItem tag]) {
            qaction = reinterpret_cast<QAction *>([whichItem tag]);
        }
        if (qApp->activePopupWidget())
            widget = (qApp->activePopupWidget()->focusWidget() ?
                      qApp->activePopupWidget()->focusWidget() : qApp->activePopupWidget());
        else if (QApplicationPrivate::focus_widget)
            widget = QApplicationPrivate::focus_widget;
        if (qaction && widget) {
            int key = qaction->shortcut();
            QKeyEvent accel_ev(QEvent::ShortcutOverride, (key & (~Qt::KeyboardModifierMask)),
                               Qt::KeyboardModifiers(key & Qt::KeyboardModifierMask));
            accel_ev.ignore();
            qt_sendSpontaneousEvent(widget, &accel_ev);
            if (accel_ev.isAccepted()) {
                if (qt_dispatchKeyEvent(event, widget)) {
                    *target = nil;
                    *action = nil;
                    return YES;
                }
            }
        }
    }
    return NO;
}

@end

QT_BEGIN_NAMESPACE
extern int qt_mac_menus_open_count; // qmenu_mac.mm

void qt_mac_emit_menuSignals(QMenu *menu, bool show)
{
    if (!menu)
        return;
    int delta;
    if (show) {
        emit menu->aboutToShow();
        delta = 1;
    } else {
        emit menu->aboutToHide();
        delta = -1;
    }
    qt_mac_menus_open_count += delta;
}
QT_END_NAMESPACE

#endif
