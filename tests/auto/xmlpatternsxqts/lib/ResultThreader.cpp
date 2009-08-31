/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
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

#include <QEventLoop>

#include "ResultThreader.h"

using namespace QPatternistSDK;

ResultThreader::ResultThreader(QEventLoop &ev,
                               QFile *file,
                               const Type t,
                               QObject *p) : QThread(p)
                                           , m_file(file)
                                           , m_type(t)
                                           , m_eventLoop(ev)
{
    Q_ASSERT_X(p,       Q_FUNC_INFO, "Should have a parent");
    Q_ASSERT_X(file,    Q_FUNC_INFO, "Should have a valid file");
    Q_ASSERT(m_type == Baseline || m_type == Result);
}

void ResultThreader::run()
{
    QXmlSimpleReader reader;
    reader.setContentHandler(this);

    QXmlInputSource source(m_file);
    reader.parse(source);
    m_file->close();
}

ResultThreader::Type ResultThreader::type() const
{
    return m_type;
}

// vim: et:ts=4:sw=4:sts=4
