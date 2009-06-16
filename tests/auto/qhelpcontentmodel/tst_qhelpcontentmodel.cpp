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
** contact the sales department at http://www.qtsoftware.com/contact.
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QtTest/QtTest>

#ifndef QT_NO_BUILD_TOOLS

#include <QtCore/QThread>
#include <QtCore/QUrl>
#include <QtCore/QFileInfo>

#include <QtHelp/QHelpEngine>
#include <QtHelp/QHelpContentWidget>

class SignalWaiter : public QThread
{
    Q_OBJECT

public:
    SignalWaiter();
    void run();

public slots:
    void stopWaiting();

private:
    bool stop;
};

SignalWaiter::SignalWaiter()
{
    stop = false;
}

void SignalWaiter::run()
{
    while (!stop)
        msleep(500);
    stop = false;
}

void SignalWaiter::stopWaiting()
{
    stop = true;
}


class tst_QHelpContentModel : public QObject
{
    Q_OBJECT

private slots:
    void init();

    void setupContents();
    void contentItemAt();

private:
    QString m_colFile;
};

void tst_QHelpContentModel::init()
{
    // defined in profile
    QString path = QLatin1String(SRCDIR);

    m_colFile = path + QLatin1String("/data/col.qhc");
    if (QFile::exists(m_colFile))
        QDir::current().remove(m_colFile);
    if (!QFile::copy(path + "/data/collection.qhc", m_colFile))
        QFAIL("Cannot copy file!");
    QFile f(m_colFile);
    f.setPermissions(QFile::WriteUser|QFile::ReadUser);
}

void tst_QHelpContentModel::setupContents()
{
    QHelpEngine h(m_colFile, 0);
    QHelpContentModel *m = h.contentModel();
    SignalWaiter w;
    connect(m, SIGNAL(contentsCreated()),
        &w, SLOT(stopWaiting()));
    w.start();
    h.setupData();
    int i = 0;
    while (w.isRunning() && i++ < 10)
        QTest::qWait(500);

    QCOMPARE(h.currentFilter(), QString("unfiltered"));
    QCOMPARE(m->rowCount(), 4);

    w.start();
    h.setCurrentFilter("Custom Filter 1");
    i = 0;
    while (w.isRunning() && i++ < 10)
        QTest::qWait(500);

     QCOMPARE(m->rowCount(), 1);
}

void tst_QHelpContentModel::contentItemAt()
{
    QHelpEngine h(m_colFile, 0);
    QHelpContentModel *m = h.contentModel();
    SignalWaiter w;
    connect(m, SIGNAL(contentsCreated()),
        &w, SLOT(stopWaiting()));
    w.start();
    h.setupData();
    int i = 0;
    while (w.isRunning() && i++ < 10)
        QTest::qWait(500);

    QCOMPARE(h.currentFilter(), QString("unfiltered"));

    QModelIndex root = m->index(0, 0);
    if (!root.isValid())
        QFAIL("Cannot retrieve root item!");
    QHelpContentItem *item = m->contentItemAt(root);
    if (!item)
        QFAIL("Cannot retrieve content item!");
    QCOMPARE(item->title(), QString("qmake Manual"));

    item = m->contentItemAt(m->index(4, 0, root));
    QCOMPARE(item->title(), QString("qmake Concepts"));

    item = m->contentItemAt(m->index(3, 0));
    QCOMPARE(item->title(), QString("Fancy Manual"));

    w.start();
    h.setCurrentFilter("Custom Filter 1");
    i = 0;
    while (w.isRunning() && i++ < 10)
        QTest::qWait(500);

    item = m->contentItemAt(m->index(0, 0));
    QCOMPARE(item->title(), QString("Test Manual"));
}

QTEST_MAIN(tst_QHelpContentModel)
#include "tst_qhelpcontentmodel.moc"

#else // QT_NO_BUILD_TOOLS
QTEST_NOOP_MAIN
#endif
