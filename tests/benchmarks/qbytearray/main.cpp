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
#include <QDebug>
#include <QIODevice>
#include <QFile>
#include <QString>

#include <qtest.h>


class tst_qbytearray : public QObject
{
    Q_OBJECT
private slots:
    void append();
    void append_data();
};


void tst_qbytearray::append_data()
{
    QTest::addColumn<int>("size");
    QTest::newRow("1")         << int(1);
    QTest::newRow("10")        << int(10);
    QTest::newRow("100")       << int(100);
    QTest::newRow("1000")      << int(1000);
    QTest::newRow("10000")     << int(10000);
    QTest::newRow("100000")    << int(100000);
    QTest::newRow("1000000")   << int(1000000);
    QTest::newRow("10000000")  << int(10000000);
    QTest::newRow("100000000") << int(100000000);
}

void tst_qbytearray::append()
{
    QFETCH(int, size);

    QByteArray ba;
    QBENCHMARK {
        QByteArray ba2(size, 'x');
        ba.append(ba2);
        ba.clear();
    }
}


QTEST_MAIN(tst_qbytearray)

#include "main.moc"
