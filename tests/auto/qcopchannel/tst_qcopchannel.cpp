/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
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
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/


#include <QtTest/QtTest>

#ifdef Q_WS_QWS

//TESTED_CLASS=
//TESTED_FILES=

#include <QCopChannel>
#include <QProcess>

class tst_QCopChannel : public QObject
{
    Q_OBJECT

public:
    tst_QCopChannel() {}
    virtual ~tst_QCopChannel() {}

private slots:
    void channel();
    void isRegistered();
    void sendreceivemp();
    void sendreceivesp();
protected:
    void testSend(const QString& channel, const QString& msg, const QByteArray& data=QByteArray());
};

class tst_SendQCopProcess : public QProcess
{
    Q_OBJECT
public:
    tst_SendQCopProcess( QObject* par )
	: QProcess( par )
    {
    }

signals:
    void messageSent();
};

void tst_QCopChannel::channel()
{
    QCopChannel channel1("channel1");
    QCOMPARE(channel1.channel(), QString("channel1"));
}

void tst_QCopChannel::isRegistered()
{
    QVERIFY(!QCopChannel::isRegistered("foo"));

    const QString channelName("registered/channel");
    QCopChannel *channel = new QCopChannel(channelName);
    QVERIFY(QCopChannel::isRegistered(channelName));

    delete channel;
    QVERIFY(!QCopChannel::isRegistered(channelName));
}

void tst_QCopChannel::sendreceivemp()
{
    const QString channelName("tst_QcopChannel::send()");
    QCopChannel *channel = new QCopChannel(channelName);
    QSignalSpy spy(channel, SIGNAL(received(const QString&, const QByteArray&)));

    testSend("foo", "msg");
    QApplication::processEvents();
    QCOMPARE(spy.count(), 0);

    testSend(channelName, "msg", "data");
    QApplication::processEvents();
    QCOMPARE(spy.count(), 1);

    QList<QVariant> args = spy.takeFirst();
    QCOMPARE(args.at(0).toString(), QString("msg"));
    QCOMPARE(args.at(1).toByteArray(), QByteArray("data"));

    QCOMPARE(spy.count(), 0);

    delete channel;
    testSend(channelName, "msg2");
    QApplication::processEvents();
    QCOMPARE(spy.count(), 0);
}

void tst_QCopChannel::sendreceivesp()
{
    const QString channelName("tst_QcopChannel::send()");
    QCopChannel *channel = new QCopChannel(channelName);
    QSignalSpy spy(channel, SIGNAL(received(const QString&, const QByteArray&)));
    QCopChannel::send("foo", "msg");
    QApplication::processEvents();
    QCOMPARE(spy.count(), 0);
    QCopChannel::send(channelName, "msg", "data");
    QApplication::processEvents();
    QCOMPARE(spy.count(), 1);

    QList<QVariant> args = spy.takeFirst();
    QCOMPARE(args.at(0).toString(), QString("msg"));
    QCOMPARE(args.at(1).toByteArray(), QByteArray("data"));

    QCOMPARE(spy.count(), 0);

    delete channel;
    QCopChannel::send(channelName, "msg2");
    QApplication::processEvents();
    QCOMPARE(spy.count(), 0);
}

void tst_QCopChannel::testSend( const QString& channel, const QString& msg, const QByteArray& data )
{
    QProcess proc;
    QStringList args;
    args << channel << msg;
    if( !data.isEmpty() )
	args << data;
    proc.start( "testSend/testSend", args );

    QTest::qWait(100);

    QVERIFY(proc.state() == QProcess::NotRunning || proc.waitForFinished());
    QCOMPARE(proc.exitStatus(), QProcess::NormalExit);
    QVERIFY(proc.readAll() == "done"); // sanity check
}

QTEST_MAIN(tst_QCopChannel)

#include "tst_qcopchannel.moc"

#else // Q_WS_QWS
QTEST_NOOP_MAIN
#endif
