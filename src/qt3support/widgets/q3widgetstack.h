/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt3Support module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
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
** additional rights.  These rights are described in the Nokia Qt LGPL
** Exception version 1.1, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef Q3WIDGETSTACK_H
#define Q3WIDGETSTACK_H

#include <Qt3Support/q3frame.h>
#include <Qt3Support/q3intdict.h>
#include <Qt3Support/q3ptrdict.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Qt3SupportLight)

class Q3WidgetStackPrivate;


class Q_COMPAT_EXPORT Q3WidgetStack: public Q3Frame
{
    Q_OBJECT
public:
    Q3WidgetStack(QWidget* parent, const char* name=0, Qt::WindowFlags f=0);

    ~Q3WidgetStack();

    int addWidget(QWidget *, int = -1);
    void removeWidget(QWidget *);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;
    void setVisible(bool visible);

    QWidget * widget(int) const;
    int id(QWidget *) const;

    QWidget * visibleWidget() const;

    void setFrameRect(const QRect &);

Q_SIGNALS:
    void aboutToShow(int);
    void aboutToShow(QWidget *);

public Q_SLOTS:
    void raiseWidget(int);
    void raiseWidget(QWidget *);

protected:
    void frameChanged();
    void resizeEvent(QResizeEvent *);
    bool event(QEvent* e);

    virtual void setChildGeometries();
    void childEvent(QChildEvent *);

private:
    void init();

    Q3WidgetStackPrivate * d;
    Q3IntDict<QWidget> * dict;
    Q3PtrDict<QWidget> * focusWidgets;
    QWidget * topWidget;
    QWidget * invisible;

    Q_DISABLE_COPY(Q3WidgetStack)
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // Q3WIDGETSTACK_H
