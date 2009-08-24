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
#include <QStringList>
#include <qtest.h>

class tst_QStringList: public QObject
{
    Q_OBJECT
private slots:
    void join() const;
    void join_data() const;

private:
    static QStringList populate(const unsigned int count,
                                const QString &unit);
};

QStringList tst_QStringList::populate(const unsigned int count,
                                      const QString &unit)
{
    QStringList retval;

    for(unsigned int i = 0; i < count; ++i)
        retval.append(unit);

    return retval;
}

void tst_QStringList::join() const
{
    QFETCH(QStringList, input);
    QFETCH(QString, separator);

    QBENCHMARK {
        input.join(separator);
    }
}

void tst_QStringList::join_data() const
{
    QTest::addColumn<QStringList>("input");
    QTest::addColumn<QString>("separator");

    QTest::newRow("")
        << populate(100, QLatin1String("unit"))
        << QString();

    QTest::newRow("")
        << populate(1000, QLatin1String("unit"))
        << QString();

    QTest::newRow("")
        << populate(10000, QLatin1String("unit"))
        << QString();

    QTest::newRow("")
        << populate(100000, QLatin1String("unit"))
        << QString();
}

QTEST_MAIN(tst_QStringList)

#include "main.moc"
