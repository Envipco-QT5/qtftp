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


#include <QtTest/QtTest>
#include <qsharedmemory.h>

//TESTED_CLASS=
//TESTED_FILES=

#define EXISTING_SHARE "existing"
#define EXISTING_SIZE 1024

Q_DECLARE_METATYPE(QSharedMemory::SharedMemoryError);
Q_DECLARE_METATYPE(QSharedMemory::AccessMode);

class tst_QSharedMemory : public QObject
{
    Q_OBJECT

public:
    tst_QSharedMemory();
    virtual ~tst_QSharedMemory();

public Q_SLOTS:
    void init();
    void cleanup();

private slots:
    // basics
    void constructor();
    void key_data();
    void key();
    void create_data();
    void create();
    void attach_data();
    void attach();
    void lock();

    // custom edge cases
    void removeWhileAttached();
    void emptyMemory();
    void readOnly();

    // basics all together
    void simpleProducerConsumer_data();
    void simpleProducerConsumer();
    void simpleDoubleProducerConsumer();

    // with threads
    void simpleThreadedProducerConsumer_data();
    void simpleThreadedProducerConsumer();

    // with processes
    void simpleProcessProducerConsumer_data();
    void simpleProcessProducerConsumer();

    // extreme cases
    void useTooMuchMemory();
    void attachTooMuch();

protected:
    int remove(const QString &key);

    QString rememberKey(const QString &key)
    {
        if (key == EXISTING_SHARE)
            return key;
        if (!keys.contains(key)) {
            keys.append(key);
            remove(key);
        }
        return key;
    }

    QStringList keys;
    QList<QSharedMemory*> jail;
    QSharedMemory *existingSharedMemory;
};

tst_QSharedMemory::tst_QSharedMemory() : existingSharedMemory(0)
{
}

tst_QSharedMemory::~tst_QSharedMemory()
{
}

void tst_QSharedMemory::init()
{
    existingSharedMemory = new QSharedMemory(EXISTING_SHARE);
    if (!existingSharedMemory->create(EXISTING_SIZE)) {
        QVERIFY(existingSharedMemory->error() == QSharedMemory::AlreadyExists);
    }
}

void tst_QSharedMemory::cleanup()
{
    delete existingSharedMemory;
    qDeleteAll(jail.begin(), jail.end());
    jail.clear();

    keys.append(EXISTING_SHARE);
    for (int i = 0; i < keys.count(); ++i) {
        QSharedMemory sm(keys.at(i));
        if (!sm.create(1024)) {
            //if(sm.error() != QSharedMemory::KeyError)
            //    qWarning() << "test cleanup: remove failed:" << keys.at(i) << sm.error() << sm.errorString();
            sm.attach();
            sm.detach();
            remove(keys.at(i));
        }
    }
}

#ifndef Q_OS_WIN
#include "private/qsharedmemory_p.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#endif

int tst_QSharedMemory::remove(const QString &key)
{
#ifndef Q_OS_WIN
    // On unix the shared memory might exists from a previously failed test
    // or segfault, remove it it does
    if (key.isEmpty())
        return -1;

    // ftok requires that an actual file exists somewhere
    QString fileName = QSharedMemoryPrivate::makePlatformSafeKey(key);
    if (!QFile::exists(fileName)) {
        //qDebug() << "exits failed";
        return -2;
    }

    int unix_key = ftok(fileName.toLatin1().constData(), 'Q');
    if (-1 == unix_key) {
        qDebug() << "ftok failed";
        return -3;
    }

    int id = shmget(unix_key, 0, 0660);
    if (-1 == id) {
        qDebug() << "shmget failed";
        return -4;
    }

    struct shmid_ds shmid_ds;
    if (-1 == shmctl(id, IPC_RMID, &shmid_ds)) {
        qDebug() << "shmctl failed";
        return -5;
    }
    return QFile::remove(fileName);
#else
    Q_UNUSED(key);
    return 0;
#endif
}

/*!
    Tests the default values
 */
void tst_QSharedMemory::constructor()
{
    QSharedMemory sm;
    QCOMPARE(sm.key(), QString());
    QVERIFY(!sm.isAttached());
    QVERIFY(sm.data() == 0);
    QCOMPARE(sm.size(), 0);
    QCOMPARE(sm.error(), QSharedMemory::NoError);
    QVERIFY(sm.errorString() == QString());
}

void tst_QSharedMemory::key_data()
{
    QTest::addColumn<QString>("constructorKey");
    QTest::addColumn<QString>("setKey");

    QTest::newRow("null, null") << QString() << QString();
    QTest::newRow("null, one") << QString() << QString("one");
    QTest::newRow("one, two") << QString("one") << QString("two");
    QTest::newRow("invalid") << QString("o/e") << QString("t/o");
}

/*!
    Basic key testing
 */
void tst_QSharedMemory::key()
{
    QFETCH(QString, constructorKey);
    QFETCH(QString, setKey);

    QSharedMemory sm(constructorKey);
    QCOMPARE(sm.key(), constructorKey);
    sm.setKey(setKey);
    QCOMPARE(sm.key(), setKey);
    QCOMPARE(sm.isAttached(), false);

    QCOMPARE(sm.error(), QSharedMemory::NoError);
    QVERIFY(sm.errorString() == QString());
    QVERIFY(sm.data() == 0);
    QCOMPARE(sm.size(), 0);

    QCOMPARE(sm.detach(), false);
}

void tst_QSharedMemory::create_data()
{
    QTest::addColumn<QString>("key");
    QTest::addColumn<int>("size");
    QTest::addColumn<bool>("canCreate");
    QTest::addColumn<QSharedMemory::SharedMemoryError>("error");

    QTest::newRow("null key") << QString() << 1024
        << false << QSharedMemory::LockError;
    QTest::newRow("-1 size") << QString("negsize") << -1
        << false << QSharedMemory::InvalidSize;
    QTest::newRow("nor size") << QString("norsize") << 1024
        << true << QSharedMemory::NoError;
    QTest::newRow("already exists") << QString(EXISTING_SHARE) << EXISTING_SIZE
        << false << QSharedMemory::AlreadyExists;
}

/*!
    Basic create testing
 */
void tst_QSharedMemory::create()
{
    QFETCH(QString, key);
    QFETCH(int, size);
    QFETCH(bool, canCreate);
    QFETCH(QSharedMemory::SharedMemoryError, error);

    QSharedMemory sm(rememberKey(key));
    QCOMPARE(sm.create(size), canCreate);
    if(sm.error() != error)
        qDebug() << sm.errorString();
    QCOMPARE(sm.key(), key);
    if (canCreate) {
        QVERIFY(sm.errorString() == QString());
        QVERIFY(sm.data() != 0);
        QVERIFY(sm.size() != 0);
    } else {
        QVERIFY(sm.data() == 0);
        QVERIFY(sm.errorString() != QString());
    }
}

void tst_QSharedMemory::attach_data()
{
    QTest::addColumn<QString>("key");
    QTest::addColumn<bool>("exists");
    QTest::addColumn<QSharedMemory::SharedMemoryError>("error");

    QTest::newRow("null key") << QString() << false << QSharedMemory::LockError;
    QTest::newRow("doesn't exists") << QString("doesntexists") << false << QSharedMemory::NotFound;
    QTest::newRow("already exists") << QString(EXISTING_SHARE) << true << QSharedMemory::NoError;
}

/*!
    Basic attach/detach testing
 */
void tst_QSharedMemory::attach()
{
    QFETCH(QString, key);
    QFETCH(bool, exists);
    QFETCH(QSharedMemory::SharedMemoryError, error);
#ifdef Q_OS_HPUX
    if (QLatin1String(QTest::currentDataTag()) == QLatin1String("already exists")) {
        QSKIP("HPUX doesn't allow for multiple attaches per process", SkipSingle);
    }
#endif
    QSharedMemory sm(key);
    QCOMPARE(sm.attach(), exists);
    QCOMPARE(sm.isAttached(), exists);
    QCOMPARE(sm.error(), error);
    QCOMPARE(sm.key(), key);
    if (exists) {
        QVERIFY(sm.data() != 0);
        QVERIFY(sm.size() != 0);
        QCOMPARE(sm.errorString(), QString());
        QVERIFY(sm.detach());
        // Make sure detach doesn't screw up something and we can't re-attach.
        QVERIFY(sm.attach());
        QVERIFY(sm.detach());
        QCOMPARE(sm.size(), 0);
        QVERIFY(sm.data() == 0);
    } else {
        QVERIFY(sm.data() == 0);
        QVERIFY(sm.size() == 0);
        QVERIFY(sm.errorString() != QString());
        QVERIFY(!sm.detach());
    }
}

void tst_QSharedMemory::lock()
{
    QSharedMemory shm;
    QVERIFY(!shm.lock());
    QCOMPARE(shm.error(), QSharedMemory::LockError);

    shm.setKey(QLatin1String("qsharedmemory"));

    QVERIFY(!shm.lock());
    QCOMPARE(shm.error(), QSharedMemory::LockError);

    QVERIFY(shm.create(100));
    QVERIFY(shm.lock());
    QTest::ignoreMessage(QtWarningMsg, "QSharedMemory::lock: already locked");
    QVERIFY(shm.lock());
    // don't lock forever
}

/*!
    Other shared memory are allowed to be attached after we remove,
    but new shared memory are not allowed to attach after a remove.
 */
void tst_QSharedMemory::removeWhileAttached()
{
#ifdef Q_OS_HPUX
    QSKIP("HPUX doesn't allow for multiple attaches per process", SkipAll);
#endif
    rememberKey("one");

    // attach 1
    QSharedMemory *smOne = new QSharedMemory(QLatin1String("one"));
    QVERIFY(smOne->create(1024));
    QVERIFY(smOne->isAttached());

    // attach 2
    QSharedMemory *smTwo = new QSharedMemory(QLatin1String("one"));
    QVERIFY(smTwo->attach());
    QVERIFY(smTwo->isAttached());

    // detach 1 and remove, remove one first to catch another error.
    delete smOne;
    delete smTwo;

    // three shouldn't be able to attach
    QSharedMemory smThree(QLatin1String("one"));
    QVERIFY(!smThree.attach());
    QCOMPARE(smThree.error(), QSharedMemory::NotFound);
}

/*!
    The memory should be set to 0 after created.
 */
void tst_QSharedMemory::emptyMemory()
{
    QSharedMemory sm(rememberKey(QLatin1String("voidland")));
    int size = 1024;
    QVERIFY(sm.create(size, QSharedMemory::ReadOnly));
    char *get = (char*)sm.data();
    char null = 0;
    for (int i = 0; i < size; ++i)
        QCOMPARE(get[i], null);
}

/*!
    Verify that attach with ReadOnly is actually read only
    by writing to data and causing a segfault.
*/
void tst_QSharedMemory::readOnly()
{
#ifdef Q_OS_WIN
    QSKIP("This test opens a crash dialog on Windows", SkipSingle);
#endif
    QString program = "./lackey/lackey";
    QStringList arguments;
    rememberKey("readonly_segfault");
    arguments << SRCDIR "lackey/scripts/readonly_segfault.js";

    // ### on windows disable the popup somehow
    QProcess p;
    p.start(program, arguments);
    p.setProcessChannelMode(QProcess::ForwardedChannels);
    p.waitForFinished();
    QCOMPARE(p.error(), QProcess::Crashed);
}

/*!
    Keep making shared memory until the kernel stops us.
 */
void tst_QSharedMemory::useTooMuchMemory()
{
#ifdef Q_OS_LINUX
    bool success = true;
    int count = 0;
    while (success) {
        QString key = QString("maxmemorytest_%1").arg(count++);
        QSharedMemory *sm = new QSharedMemory(rememberKey(key));
        QVERIFY(sm);
        jail.append(sm);
        int size = 32768 * 1024;
        success = sm->create(size);
        if (!success && sm->error() == QSharedMemory::AlreadyExists) {
            // left over from a crash, clean it up
            sm->attach();
            sm->detach();
            success = sm->create(size);
        }

        if (!success) {
            QVERIFY(!sm->isAttached());
            QCOMPARE(sm->key(), key);
            QCOMPARE(sm->size(), 0);
            QVERIFY(sm->data() == 0);
            if (sm->error() != QSharedMemory::OutOfResources)
                qDebug() << sm->error() << sm->errorString();
            // ### Linux wont return OutOfResources if there are not enough semaphores to use.
            QVERIFY(sm->error() == QSharedMemory::OutOfResources
                    || sm->error() == QSharedMemory::LockError);
            QVERIFY(sm->errorString() != QString());
            QVERIFY(!sm->attach());
            QVERIFY(!sm->detach());
        } else {
            QVERIFY(sm->isAttached());
        }
    }
#endif
}

/*!
    Create one shared memory (government) and see how many other shared memories (wars) we can
    attach before the system runs out of resources.
 */
void tst_QSharedMemory::attachTooMuch()
{
    QSKIP("disabled", SkipAll);
#ifdef Q_OS_HPUX
    QSKIP("HPUX doesn't allow for multiple attaches per process", SkipAll);
#endif
#ifdef Q_OS_WINCE
    QSKIP("This nearly kills the system itself, so skip for Qt/WinCE", SkipAll);
#endif
    QSharedMemory government(rememberKey("government"));
    QVERIFY(government.create(1024));
    while (true) {
        QSharedMemory *war = new QSharedMemory(government.key());
        QVERIFY(war);
        jail.append(war);
        if (!war->attach()) {
            QVERIFY(!war->isAttached());
            QCOMPARE(war->key(), government.key());
            QCOMPARE(war->size(), 0);
            QVERIFY(war->data() == 0);
            QCOMPARE(war->error(), QSharedMemory::OutOfResources);
            QVERIFY(war->errorString() != QString());
            QVERIFY(!war->detach());
            break;
        } else {
            QVERIFY(war->isAttached());
        }
    }
}

void tst_QSharedMemory::simpleProducerConsumer_data()
{
    QTest::addColumn<QSharedMemory::AccessMode>("mode");

    QTest::newRow("readonly") << QSharedMemory::ReadOnly;
    QTest::newRow("readwrite") << QSharedMemory::ReadWrite;
}

/*!
    The basic consumer producer that rounds out the basic testing.
    If this fails then any muli-threading/process might fail (but be
    harder to debug)

    This doesn't require nor test any locking system.
 */
void tst_QSharedMemory::simpleProducerConsumer()
{
#ifdef Q_OS_HPUX
    QSKIP("HPUX doesn't allow for multiple attaches per process", SkipAll);
#endif
    QFETCH(QSharedMemory::AccessMode, mode);

    rememberKey(QLatin1String("market"));
    QSharedMemory producer(QLatin1String("market"));
    QSharedMemory consumer(QLatin1String("market"));
    int size = 512;
    QVERIFY(producer.create(size));
    QVERIFY(consumer.attach(mode));

    char *put = (char*)producer.data();
    char *get = (char*)consumer.data();
    // On Windows CE you always have ReadWrite access. Thus
    // ViewMapOfFile returns the same pointer
#ifndef Q_OS_WINCE
    QVERIFY(put != get);
#endif
    for (int i = 0; i < size; ++i) {
        put[i] = 'Q';
        QCOMPARE(get[i], 'Q');
    }
    QVERIFY(consumer.detach());
}

void tst_QSharedMemory::simpleDoubleProducerConsumer()
{
#ifdef Q_OS_HPUX
    QSKIP("HPUX doesn't allow for multiple attaches per process", SkipAll);
#endif
    rememberKey(QLatin1String("market"));
    QSharedMemory producer(QLatin1String("market"));
    int size = 512;
    QVERIFY(producer.create(size));
    QVERIFY(producer.detach());
    QVERIFY(producer.create(size));

    {
        QSharedMemory consumer(QLatin1String("market"));
        QVERIFY(consumer.attach());
    }
}

class Consumer : public QThread
{

public:
    void run()
    {
        QSharedMemory consumer(QLatin1String("market"));
        while (!consumer.attach()) {
            if (consumer.error() != QSharedMemory::NotFound)
                qDebug() << "consumer: failed to connect" << consumer.error() << consumer.errorString();
            QVERIFY(consumer.error() == QSharedMemory::NotFound || consumer.error() == QSharedMemory::KeyError);
            QTest::qWait(1);
        }

        char *memory = (char*)consumer.data();

        int i = 0;
        while (true) {
            if(!consumer.lock())
                break;
            if (memory[0] == 'Q')
                memory[0] = ++i;
            if (memory[0] == 'E') {
                memory[1]++;
                QVERIFY(consumer.unlock());
                break;
            }
            QVERIFY(consumer.unlock());
            QTest::qWait(1);
        }

        QVERIFY(consumer.detach());
    }
};

class Producer : public QThread
{

public:
    void run()
    {
        QSharedMemory producer(QLatin1String("market"));
        int size = 1024;
        if (!producer.create(size)) {
            // left over from a crash...
            if (producer.error() == QSharedMemory::AlreadyExists) {
                producer.attach();
                producer.detach();
                QVERIFY(producer.create(size));
            }
        }
        QVERIFY(producer.isAttached());
        char *memory = (char*)producer.data();
        memory[1] = '0';
        QTime timer;
        timer.start();
        int i = 0;
        while (i < 5 && timer.elapsed() < 5000) {
            QVERIFY(producer.lock());
            if (memory[0] == 'Q') {
                QVERIFY(producer.unlock());
                QTest::qWait(1);
                continue;
            }
            ++i;
            memory[0] = 'Q';
            QVERIFY(producer.unlock());
            QTest::qWait(1);
        }

        // tell everyone to quit
        QVERIFY(producer.lock());
        memory[0] = 'E';
        QVERIFY(producer.unlock());
    }
private:

};

void tst_QSharedMemory::simpleThreadedProducerConsumer_data()
{
    QTest::addColumn<bool>("producerIsThread");
    QTest::addColumn<int>("threads");
    for (int i = 0; i < 5; ++i) {
        QTest::newRow("1 consumer, producer is thread") << true << 1;
        QTest::newRow("1 consumer, producer is this") << false << 1;
        QTest::newRow("5 consumers, producer is thread") << true << 5;
        QTest::newRow("5 consumers, producer is this") << false << 5;
    }
}

/*!
    The basic producer/consumer, but this time using threads.
 */
void tst_QSharedMemory::simpleThreadedProducerConsumer()
{
    QFETCH(bool, producerIsThread);
    QFETCH(int, threads);
    rememberKey(QLatin1String("market"));

#if defined Q_OS_HPUX && defined __ia64
    QSKIP("This test locks up on gravlaks.troll.no", SkipSingle);
#endif

    Producer p;
    if (producerIsThread)
        p.start();

    QList<Consumer*> consumers;
    for (int i = 0; i < threads; ++i) {
        consumers.append(new Consumer());
        consumers.last()->start();
    }

    if (!producerIsThread)
        p.run();

    p.wait(5000);
    while (!consumers.isEmpty()) {
        QVERIFY(consumers.first()->wait(5000));
        delete consumers.takeFirst();
    }
}

void tst_QSharedMemory::simpleProcessProducerConsumer_data()
{
    QTest::addColumn<int>("processes");
    int tries = 10;
#ifdef Q_OS_WIN
    tries = 5;
#endif
    for (int i = 0; i < tries; ++i) {
        QTest::newRow("1 process") << 1;
        QTest::newRow("5 processes") << 5;
    }
}

/*!
    Create external processes that produce and consume.
 */
void tst_QSharedMemory::simpleProcessProducerConsumer()
{
    QFETCH(int, processes);

    rememberKey("market");

#ifndef Q_OS_WINCE
    QStringList arguments = QStringList() << SRCDIR "lackey/scripts/producer.js";
#else
    QStringList arguments = QStringList() << QFileInfo(SRCDIR "lackey/scripts/producer.js").absoluteFilePath();
#endif
    QProcess producer;
    producer.setProcessChannelMode(QProcess::ForwardedChannels);
    producer.start("./lackey/lackey", arguments);
    producer.waitForStarted();

    QList<QProcess*> consumers;
    for (int i = 0; i < processes; ++i) {
#ifndef Q_OS_WINCE
        QStringList arguments = QStringList() << SRCDIR  "lackey/scripts/consumer.js";
#else
        QStringList arguments = QStringList() << QFileInfo(SRCDIR "lackey/scripts/consumer.js").absoluteFilePath();
#endif
        QProcess *p = new QProcess;
        p->setProcessChannelMode(QProcess::ForwardedChannels);
        consumers.append(p);
        p->start("./lackey/lackey", arguments);
    }

    producer.waitForFinished(5000);

    bool consumerFailed = false;

    while (!consumers.isEmpty()) {
        consumers.first()->waitForFinished(1000);
        if (consumers.first()->exitStatus() != QProcess::NormalExit ||
            consumers.first()->exitCode() != 0) {
                consumerFailed = true;
            }
        delete consumers.takeFirst();
    }
    QCOMPARE(consumerFailed, false);
}

QTEST_MAIN(tst_QSharedMemory)
#include "tst_qsharedmemory.moc"

