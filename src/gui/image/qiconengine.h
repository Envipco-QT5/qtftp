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

#ifndef QICONENGINE_H
#define QICONENGINE_H

#include <QtCore/qglobal.h>
#include <QtCore/qlist.h>
#include <QtGui/qicon.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

class Q_GUI_EXPORT QIconEngine
{
public:
    virtual ~QIconEngine();
    virtual void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) = 0;
    virtual QSize actualSize(const QSize &size, QIcon::Mode mode, QIcon::State state);
    virtual QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state);

    virtual void addPixmap(const QPixmap &pixmap, QIcon::Mode mode, QIcon::State state);
    virtual void addFile(const QString &fileName, const QSize &size, QIcon::Mode mode, QIcon::State state);

#if 0
    virtual int frameCount(QIcon::Mode fromMode, QIcon::State fromState, QIcon::Mode toMode, QIcon::State toState);
    virtual void paintFrame(QPainter *painter, const QRect &rect, int frameNumber, QIcon::Mode fromMode, QIcon::State fromState, QIcon::Mode toMode, QIcon::State toState);
#endif
};

// ### Qt 5: move the below into QIconEngine
class Q_GUI_EXPORT QIconEngineV2 : public QIconEngine
{
public:
    virtual QString key() const;
    virtual QIconEngineV2 *clone() const;
    virtual bool read(QDataStream &in);
    virtual bool write(QDataStream &out) const;
    virtual void virtual_hook(int id, void *data);

public:
    enum IconEngineHook { AvailableSizesHook = 1 };

    struct AvailableSizesArgument
    {
        QIcon::Mode mode;
        QIcon::State state;
        QList<QSize> sizes;
    };

    // ### Qt 5: make this function const and virtual.
    QList<QSize> availableSizes(QIcon::Mode mode = QIcon::Normal,
                                QIcon::State state = QIcon::Off);
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // QICONENGINE_H
