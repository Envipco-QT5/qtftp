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
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtTest/QtTest>
#ifndef QT_NO_DBUS
#include <QtDBus>

#define TEST_INTERFACE_NAME "com.trolltech.QtDBus.MyObject"

class MyObject : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.trolltech.QtDBus.MyObject")

public:
    MyObject(QObject* parent =0)
        : QDBusAbstractAdaptor(parent)
    {}

public slots:
    QStringList returnFoo() const
    { return QStringList() << QString::fromLatin1("foo"); }

    void returnError(const QDBusMessage &msg) const
    {
        msg.setDelayedReply(true);
        QDBusConnection::sessionBus().send(msg.createErrorReply("dbuspendingcall_error", ""));
    }
};

class tst_QDBusPendingCall: public QObject
{
    Q_OBJECT

public:
    tst_QDBusPendingCall();

public Q_SLOTS:
    void callback(const QStringList &list);
    void errorCallback(const QDBusError &error);
    void finished(QDBusPendingCallWatcher *call);
    void makeCall();

private Q_SLOTS:
    void initTestCase();
    void waitForFinished();
    void waitForFinished_error();
//    void setReplyCallback();
    void watcher();
    void watcher_error();
    void watcher_waitForFinished();
    void watcher_waitForFinished_alreadyFinished();
    void watcher_waitForFinished_alreadyFinished_eventLoop();
    void watcher_waitForFinished_error();
    void callInsideWaitForFinished();

    void callWithCallback_localLoop();
    void callWithCallback_localLoop_errorReply();

private:
    QDBusPendingCall sendMessage();
    QDBusPendingCall sendError();

    QDBusConnection conn;

    enum { CallbackCalled, ErrorCallbackCalled, FinishCalled, MakeCallCalled };
    int slotCalled;
    int callCount;
    QStringList callbackArgument;
    QDBusError errorArgument;
    QDBusPendingCallWatcher *watchArgument;
    MyObject *obj;
};

tst_QDBusPendingCall::tst_QDBusPendingCall()
    : conn(QDBusConnection::sessionBus())
    , obj(new MyObject(this))
{
}

void tst_QDBusPendingCall::finished(QDBusPendingCallWatcher *call)
{
    slotCalled = FinishCalled;
    ++callCount;
    watchArgument = call;
    QTestEventLoop::instance().exitLoop();
}

void tst_QDBusPendingCall::callback(const QStringList &list)
{
    slotCalled = CallbackCalled;
    ++callCount;
    callbackArgument = list;
    QTestEventLoop::instance().exitLoop();
}

void tst_QDBusPendingCall::errorCallback(const QDBusError &error)
{
    slotCalled = ErrorCallbackCalled;
    ++callCount;
    errorArgument = error;
    QTestEventLoop::instance().exitLoop();
}

void tst_QDBusPendingCall::makeCall()
{
    // make an external call to D-Bus to make sure we haven't left any locks
    slotCalled = MakeCallCalled;
    ++callCount;

    sendMessage().waitForFinished();
}

void tst_QDBusPendingCall::initTestCase()
{
    QVERIFY(conn.isConnected());
    QVERIFY(conn.registerObject("/", this));
}

QDBusPendingCall tst_QDBusPendingCall::sendMessage()
{
    QDBusMessage msg = QDBusMessage::createMethodCall("org.freedesktop.DBus",
                                                      "/",
                                                      "org.freedesktop.DBus",
                                                      "ListNames");
    return conn.asyncCall(msg);
}

QDBusPendingCall tst_QDBusPendingCall::sendError()
{
    QDBusMessage msg = QDBusMessage::createMethodCall("org.freedesktop.DBus",
                                                      "/",
                                                      "org.freedesktop.DBus",
                                                      "ThisNameWontExist");
    return conn.asyncCall(msg);
}

void tst_QDBusPendingCall::waitForFinished()
{
    QDBusPendingCall ac = sendMessage();
    QVERIFY(!ac.isFinished());
    QVERIFY(!ac.isError());
    QVERIFY(ac.reply().type() == QDBusMessage::InvalidMessage);

    ac.waitForFinished();
    QVERIFY(ac.isFinished());
    QVERIFY(!ac.isError());

    const QDBusMessage reply = ac.reply();
    QVERIFY(reply.type() == QDBusMessage::ReplyMessage);
    QCOMPARE(reply.signature(), QString("as"));

    const QVariantList args = ac.reply().arguments();
    QCOMPARE(args.count(), 1);

    const QVariant &arg = args.at(0);
    QCOMPARE(arg.type(), QVariant::StringList);
    QVERIFY(arg.toStringList().contains(conn.baseService()));
}

void tst_QDBusPendingCall::waitForFinished_error()
{
    QDBusPendingCall ac = sendError();
    QVERIFY(!ac.isFinished());
    QVERIFY(!ac.isError());
    QVERIFY(ac.reply().type() == QDBusMessage::InvalidMessage);

    ac.waitForFinished();
    QVERIFY(ac.isFinished());
    QVERIFY(ac.isError());

    QDBusError error = ac.error();
    QVERIFY(error.isValid());
    QCOMPARE(error.name(), QString("org.freedesktop.DBus.Error.UnknownMethod"));
    QCOMPARE(error.type(), QDBusError::UnknownMethod);
}

void tst_QDBusPendingCall::callWithCallback_localLoop()
{
    // Verify that a callback actually gets called when the call is dispatched locally.
    QDBusInterface iface(QDBusConnection::sessionBus().baseService(), QLatin1String("/"),
                         TEST_INTERFACE_NAME);
    QVERIFY(iface.isValid());

    QVERIFY(iface.callWithCallback("returnFoo", QVariantList(), this, SLOT(callback(QStringList))));

    // May be called synchronously or asynchronously...
    if (callbackArgument != (QStringList() << QString::fromLatin1("foo"))) {
        QTestEventLoop::instance().enterLoop(2);
        QVERIFY(!QTestEventLoop::instance().timeout());
    }

    QCOMPARE(callbackArgument, QStringList() << QString::fromLatin1("foo"));
}

void tst_QDBusPendingCall::callWithCallback_localLoop_errorReply()
{
    // Verify that an error callback actually gets called when the call is
    // dispatched locally and the called method returns an error

    QDBusInterface iface(QDBusConnection::sessionBus().baseService(), QLatin1String("/"),
                         TEST_INTERFACE_NAME);
    QVERIFY(iface.isValid());

    callbackArgument.clear();

    QVERIFY(iface.callWithCallback("returnError", QVariantList(), this,
        SLOT(callback(QStringList)), SLOT(errorCallback(QDBusError))));

    // May be called synchronously or asynchronously...
    if (errorArgument.name() != "dbuspendingcall_error") {
        QTestEventLoop::instance().enterLoop(2);
        QVERIFY(!QTestEventLoop::instance().timeout());
    }

    QCOMPARE(errorArgument.name(), QString::fromLatin1("dbuspendingcall_error"));
    QVERIFY(callbackArgument.isEmpty());
}

#if 0
// This function was removed from the public API
void tst_QDBusPendingCall::setReplyCallback()
{
    QDBusPendingCall ac = sendMessage();
    QVERIFY(!ac.isFinished());
    QVERIFY(!ac.isError());
    QVERIFY(ac.reply().type() == QDBusMessage::InvalidMessage);

    callCount = 0;
    callbackArgument.clear();
    QVERIFY(ac.setReplyCallback(this, SLOT(callback(const QStringList &))));
    QVERIFY(callCount == 0);
    QVERIFY(callbackArgument.isEmpty());

    QTestEventLoop::instance().enterLoop(2);
    QVERIFY(!QTestEventLoop::instance().timeout());

    QVERIFY(ac.isFinished());
    QVERIFY(!ac.isError());

    QCOMPARE(callCount, 1);
    QCOMPARE(slotCalled, (int)CallbackCalled);
    QVERIFY(!callbackArgument.isEmpty());
    QVERIFY(callbackArgument.contains(conn.baseService()));

    const QVariantList args = ac.reply().arguments();
    QVERIFY(!args.isEmpty());
    QCOMPARE(args.at(0).toStringList(), callbackArgument);
}
#endif

void tst_QDBusPendingCall::watcher()
{
    QDBusPendingCall ac = sendMessage();
    QVERIFY(!ac.isFinished());
    QVERIFY(!ac.isError());
    QVERIFY(ac.reply().type() == QDBusMessage::InvalidMessage);

    callCount = 0;
    watchArgument = 0;

    QDBusPendingCallWatcher watch(ac);
    connect(&watch, SIGNAL(finished(QDBusPendingCallWatcher*)),
            SLOT(finished(QDBusPendingCallWatcher*)));

    QTestEventLoop::instance().enterLoop(2);
    QVERIFY(!QTestEventLoop::instance().timeout());

    QVERIFY(ac.isFinished());
    QVERIFY(!ac.isError());

    QCOMPARE(callCount, 1);
    QCOMPARE(slotCalled, (int)FinishCalled);
    QCOMPARE(watchArgument, &watch);
    QVERIFY(!watch.isError());

    const QVariantList args2 = ac.reply().arguments();
    QVERIFY(!args2.isEmpty());
    QVERIFY(args2.at(0).toStringList().contains(conn.baseService()));
}

void tst_QDBusPendingCall::watcher_error()
{
    QDBusPendingCall ac = sendError();
    QVERIFY(!ac.isFinished());
    QVERIFY(!ac.isError());
    QVERIFY(ac.reply().type() == QDBusMessage::InvalidMessage);

    callCount = 0;
    watchArgument = 0;

    QDBusPendingCallWatcher watch(ac);
    connect(&watch, SIGNAL(finished(QDBusPendingCallWatcher*)),
            SLOT(finished(QDBusPendingCallWatcher*)));

    QTestEventLoop::instance().enterLoop(2);
    QVERIFY(!QTestEventLoop::instance().timeout());

    QVERIFY(ac.isFinished());
    QVERIFY(ac.isError());

    QCOMPARE(callCount, 1);
    QCOMPARE(slotCalled, (int)FinishCalled);
    QCOMPARE(watchArgument, &watch);

    QVERIFY(watch.isError());
    QVERIFY(watch.error().isValid());
}

void tst_QDBusPendingCall::watcher_waitForFinished()
{
    QDBusPendingCall ac = sendMessage();
    QVERIFY(!ac.isFinished());
    QVERIFY(!ac.isError());
    QVERIFY(ac.reply().type() == QDBusMessage::InvalidMessage);

    callCount = 0;
    watchArgument = 0;

    QDBusPendingCallWatcher watch(ac);
    connect(&watch, SIGNAL(finished(QDBusPendingCallWatcher*)),
            SLOT(finished(QDBusPendingCallWatcher*)));

    watch.waitForFinished();

    QVERIFY(ac.isFinished());
    QVERIFY(!ac.isError());

    QCOMPARE(callCount, 1);
    QCOMPARE(slotCalled, (int)FinishCalled);
    QCOMPARE(watchArgument, &watch);
    QVERIFY(!watch.isError());

    const QVariantList args2 = ac.reply().arguments();
    QVERIFY(!args2.isEmpty());
    QVERIFY(args2.at(0).toStringList().contains(conn.baseService()));
}

void tst_QDBusPendingCall::watcher_waitForFinished_alreadyFinished()
{
    QDBusPendingCall ac = sendMessage();
    QVERIFY(!ac.isFinished());
    QVERIFY(!ac.isError());
    QVERIFY(ac.reply().type() == QDBusMessage::InvalidMessage);

    ac.waitForFinished();
    QVERIFY(ac.isFinished());
    QVERIFY(!ac.isError());

    callCount = 0;
    watchArgument = 0;

    // create a watcher on an already-finished reply
    QDBusPendingCallWatcher watch(ac);
    connect(&watch, SIGNAL(finished(QDBusPendingCallWatcher*)),
            SLOT(finished(QDBusPendingCallWatcher*)));

    watch.waitForFinished();

    QVERIFY(ac.isFinished());
    QVERIFY(!ac.isError());

    QCOMPARE(callCount, 1);
    QCOMPARE(slotCalled, (int)FinishCalled);
    QCOMPARE(watchArgument, &watch);
    QVERIFY(!watch.isError());

    const QVariantList args2 = ac.reply().arguments();
    QVERIFY(!args2.isEmpty());
    QVERIFY(args2.at(0).toStringList().contains(conn.baseService()));
}

void tst_QDBusPendingCall::watcher_waitForFinished_alreadyFinished_eventLoop()
{
    QDBusPendingCall ac = sendMessage();
    QVERIFY(!ac.isFinished());
    QVERIFY(!ac.isError());
    QVERIFY(ac.reply().type() == QDBusMessage::InvalidMessage);

    ac.waitForFinished();
    QVERIFY(ac.isFinished());
    QVERIFY(!ac.isError());

    callCount = 0;
    watchArgument = 0;

    // create a watcher on an already-finished reply
    QDBusPendingCallWatcher watch(ac);
    connect(&watch, SIGNAL(finished(QDBusPendingCallWatcher*)),
            SLOT(finished(QDBusPendingCallWatcher*)));
    connect(&watch, SIGNAL(finished(QDBusPendingCallWatcher*)),
            &QTestEventLoop::instance(), SLOT(exitLoop()));

    QTestEventLoop::instance().enterLoop(1);
    QVERIFY(!QTestEventLoop::instance().timeout());

    QVERIFY(ac.isFinished());
    QVERIFY(!ac.isError());

    QCOMPARE(callCount, 1);
    QCOMPARE(slotCalled, (int)FinishCalled);
    QCOMPARE(watchArgument, &watch);
    QVERIFY(!watch.isError());

    const QVariantList args2 = ac.reply().arguments();
    QVERIFY(!args2.isEmpty());
    QVERIFY(args2.at(0).toStringList().contains(conn.baseService()));
}

void tst_QDBusPendingCall::watcher_waitForFinished_error()
{
    QDBusPendingCall ac = sendError();
    QVERIFY(!ac.isFinished());
    QVERIFY(!ac.isError());
    QVERIFY(ac.reply().type() == QDBusMessage::InvalidMessage);

    callCount = 0;
    watchArgument = 0;

    QDBusPendingCallWatcher watch(ac);
    connect(&watch, SIGNAL(finished(QDBusPendingCallWatcher*)),
            SLOT(finished(QDBusPendingCallWatcher*)));

    watch.waitForFinished();

    QVERIFY(ac.isFinished());
    QVERIFY(ac.isError());

    QCOMPARE(callCount, 1);
    QCOMPARE(slotCalled, (int)FinishCalled);
    QCOMPARE(watchArgument, &watch);

    QVERIFY(watch.isError());
    QVERIFY(watch.error().isValid());
}

void tst_QDBusPendingCall::callInsideWaitForFinished()
{
    QDBusPendingCall ac = sendMessage();
    QDBusPendingCallWatcher watch(ac);

    callCount = 0;

    connect(&watch, SIGNAL(finished(QDBusPendingCallWatcher*)),
            SLOT(makeCall()));

    watch.waitForFinished();

    QCOMPARE(callCount, 1);
    QCOMPARE(slotCalled, (int)MakeCallCalled);
    QVERIFY(!watch.isError());

    const QVariantList args2 = ac.reply().arguments();
    QVERIFY(!args2.isEmpty());
    QVERIFY(args2.at(0).toStringList().contains(conn.baseService()));
}

QTEST_MAIN(tst_QDBusPendingCall)
#include "tst_qdbuspendingcall.moc"
#else
QTEST_NOOP_MAIN
#endif
