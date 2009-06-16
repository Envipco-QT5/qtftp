/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
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
** contact the sales department at http://www.qtsoftware.com/contact.
** $QT_END_LICENSE$
**
****************************************************************************/


#include <QtTest/QtTest>

#ifdef QTEST_XMLPATTERNS
#include <QtCore/QTextCodec>
#include <QtXmlPatterns/QXmlSerializer>
#include <QtXmlPatterns/QXmlQuery>

#include "../qxmlquery/MessageSilencer.h"

/*!
 \class tst_QXmlSerializer
 \internal
 \since 4.4
 \brief Tests QSourceLocation

 */
class tst_QXmlSerializer : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void constructorTriggerWarnings() const;
    void objectSize() const;
    void constCorrectness() const;
    void setCodec() const;
    void codec() const;
    void outputDevice() const;
    void serializationError() const;
    void serializationError_data() const;
    void cleanUpTestCase() const;
};

void tst_QXmlSerializer::constructorTriggerWarnings() const
{
    QXmlQuery query;

    QTest::ignoreMessage(QtWarningMsg, "outputDevice cannot be null.");
    QXmlSerializer(query, 0);

    QTest::ignoreMessage(QtWarningMsg, "outputDevice must be opened in write mode.");
    QBuffer buffer;
    QXmlSerializer(query, &buffer);
}

void tst_QXmlSerializer::constCorrectness() const
{
    QXmlQuery query;
    QFile file(QLatin1String("dummy.xml"));
    file.open(QIODevice::WriteOnly);
    const QXmlSerializer serializer(query, &file);
    /* These functions must be const. */

    serializer.outputDevice();
    serializer.codec();
}

void tst_QXmlSerializer::objectSize() const
{
    QCOMPARE(sizeof(QXmlSerializer), sizeof(QAbstractXmlReceiver));
}

void tst_QXmlSerializer::setCodec() const
{
    QFile file(QLatin1String("dummy.xml"));
    file.open(QIODevice::WriteOnly);

    /* Ensure we can take a const pointer. */
    {
        QXmlQuery query;
        QXmlSerializer serializer(query, &file);
        serializer.setCodec(const_cast<const QTextCodec *>(QTextCodec::codecForName("UTF-8")));
    }

    /* Check that setting the codec has effect. */
    {
        QXmlQuery query;
        QXmlSerializer serializer(query, &file);
        serializer.setCodec(const_cast<const QTextCodec *>(QTextCodec::codecForName("UTF-16")));
        QCOMPARE(serializer.codec()->name(), QTextCodec::codecForName("UTF-16")->name());

        /* Set it back. */
        serializer.setCodec(const_cast<const QTextCodec *>(QTextCodec::codecForName("UTF-8")));
        QCOMPARE(serializer.codec()->name(), QTextCodec::codecForName("UTF-8")->name());
    }
}

void tst_QXmlSerializer::codec() const
{
    QFile file(QLatin1String("dummy.xml"));
    file.open(QIODevice::WriteOnly);

    /* Check default value. */
    {
        const QXmlQuery query;
        const QXmlSerializer serializer(query, &file);
        QCOMPARE(serializer.codec()->name(), QTextCodec::codecForName("UTF-8")->name());
    }
}

void tst_QXmlSerializer::outputDevice() const
{
    QFile file(QLatin1String("dummy.xml"));
    file.open(QIODevice::WriteOnly);

    /* Check default value. */
    {
        const QXmlQuery query;
        const QXmlSerializer serializer(query, &file);
        QCOMPARE(serializer.outputDevice(), &file);
    }
}

void tst_QXmlSerializer::serializationError() const
{
    QFETCH(QString, queryString);
    QXmlQuery query;
    MessageSilencer silencer;
    query.setMessageHandler(&silencer);
    
    query.setQuery(queryString);

    QByteArray output;
    QBuffer buffer(&output);
    QVERIFY(buffer.open(QIODevice::WriteOnly));
    QVERIFY(query.isValid());

    QXmlSerializer serializer(query, &buffer);

    QEXPECT_FAIL("Two top elements", "Bug, this is not checked for", Continue);
    QVERIFY(!query.evaluateTo(&serializer));
}

void tst_QXmlSerializer::serializationError_data() const
{
    QTest::addColumn<QString>("queryString");

    QTest::newRow("Two top elements")
        << QString::fromLatin1("<e/>, <e/>");

    QTest::newRow("An attribute")
        << QString::fromLatin1("attribute name {'foo'}");
}

void tst_QXmlSerializer::cleanUpTestCase() const
{
    QVERIFY(QFile::remove(QLatin1String("dummy.xml")));
}

QTEST_MAIN(tst_QXmlSerializer)

#include "tst_qxmlserializer.moc"
#else
QTEST_NOOP_MAIN
#endif

// vim: et:ts=4:sw=4:sts=4
