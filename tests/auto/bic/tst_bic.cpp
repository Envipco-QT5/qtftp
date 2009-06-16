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


#include <QtCore/QtCore>
#include <QtTest/QtTest>

#include "qbic.h"

#include <stdlib.h>

class tst_Bic: public QObject
{
    Q_OBJECT

public:
    tst_Bic();
    QBic::Info getCurrentInfo(const QString &libName);

private slots:
    void initTestCase_data();
    void initTestCase();

    void sizesAndVTables_data();
    void sizesAndVTables();

private:
    QBic bic;
};

typedef QPair<QString, QString> QStringPair;

tst_Bic::tst_Bic()
{
    bic.addBlacklistedClass(QLatin1String("std::*"));
    bic.addBlacklistedClass(QLatin1String("qIsNull*"));
    bic.addBlacklistedClass(QLatin1String("_*"));
    bic.addBlacklistedClass(QLatin1String("<anonymous*"));

    /* some system stuff we don't care for */
    bic.addBlacklistedClass(QLatin1String("timespec"));
    bic.addBlacklistedClass(QLatin1String("itimerspec"));
    bic.addBlacklistedClass(QLatin1String("sched_param"));
    bic.addBlacklistedClass(QLatin1String("timeval"));
    bic.addBlacklistedClass(QLatin1String("drand"));
    bic.addBlacklistedClass(QLatin1String("lconv"));
    bic.addBlacklistedClass(QLatin1String("random"));
    bic.addBlacklistedClass(QLatin1String("wait"));
    bic.addBlacklistedClass(QLatin1String("tm"));
    bic.addBlacklistedClass(QLatin1String("sigcontext"));
    bic.addBlacklistedClass(QLatin1String("ucontext"));
    bic.addBlacklistedClass(QLatin1String("ucontext64"));
    bic.addBlacklistedClass(QLatin1String("sigaltstack"));

    /* QtOpenGL includes qt_windows.h, and some SDKs dont have these structs present */
    bic.addBlacklistedClass(QLatin1String("tagTITLEBARINFO"));

    /* some bug in gcc also reported template instanciations */
    bic.addBlacklistedClass(QLatin1String("QTypeInfo<*>"));
    bic.addBlacklistedClass(QLatin1String("QMetaTypeId<*>"));
    bic.addBlacklistedClass(QLatin1String("QVector<QGradientStop>*"));
    bic.addBlacklistedClass(QLatin1String("QMap<*>::iterator"));
    bic.addBlacklistedClass(QLatin1String("QMap<*>::Node"));

    /* this guy is never instantiated, just for compile-time checking */
    bic.addBlacklistedClass(QLatin1String("QMap<*>::PayloadNode"));

    /* QFileEngine was removed in 4.1 */
    bic.addBlacklistedClass(QLatin1String("QFileEngine"));
    bic.addBlacklistedClass(QLatin1String("QFileEngineHandler"));
    bic.addBlacklistedClass(QLatin1String("QFlags<QFileEngine::FileFlag>"));

    /* Private classes */
    bic.addBlacklistedClass(QLatin1String("QBrushData"));
    bic.addBlacklistedClass(QLatin1String("QObjectData"));
    bic.addBlacklistedClass(QLatin1String("QAtomic"));
    bic.addBlacklistedClass(QLatin1String("QBasicAtomic"));

    /* Jambi-related classes in Designer */
    bic.addBlacklistedClass(QLatin1String("QDesignerLanguageExtension"));

    /* Harald says it's undocumented and private :) */
    bic.addBlacklistedClass(QLatin1String("QAccessibleInterfaceEx"));
    bic.addBlacklistedClass(QLatin1String("QAccessibleObjectEx"));
    bic.addBlacklistedClass(QLatin1String("QAccessibleWidgetEx"));

    /* This structure is semi-private and should never shrink */
    bic.addBlacklistedClass(QLatin1String("QVFbHeader"));
}

void tst_Bic::initTestCase_data()
{
    QTest::addColumn<QString>("libName");

    QTest::newRow("QtCore") << "QtCore";
    QTest::newRow("QtGui") << "QtGui";
    QTest::newRow("QtScript") << "QtScript";
    QTest::newRow("QtSql") << "QtSql";
    QTest::newRow("QtSvg") << "QtSvg";
    QTest::newRow("QtNetwork") << "QtNetwork";
    QTest::newRow("QtOpenGL") << "QtOpenGL";
    QTest::newRow("QtXml") << "QtXml";
    QTest::newRow("QtXmlPatterns") << "QtXmlPatterns";
    QTest::newRow("Qt3Support") << "Qt3Support";
    QTest::newRow("QtTest") << "QtTest";
    QTest::newRow("QtDBus") << "QtDBus";
    QTest::newRow("QtDesigner") << "QtDesigner";
}

void tst_Bic::initTestCase()
{
    QString qtDir = QString::fromLocal8Bit(getenv("QTDIR"));
    QVERIFY2(!qtDir.isEmpty(), "This test needs $QTDIR");

    if (qgetenv("PATH").contains("teambuilder"))
        QTest::qWarn("This test might not work with teambuilder, consider switching it off.");
}

void tst_Bic::sizesAndVTables_data()
{
#if !defined(Q_CC_GNU) || defined(Q_CC_INTEL)
    QSKIP("Test not implemented for this compiler/platform", SkipAll);
#else

    int major = QT_VERSION >> 16;
    if (major != 4) {
        QFAIL("This test is for Qt 4");
    }
    int minor = (QT_VERSION & 0x00FF00) >> 8;
    int patch = (QT_VERSION & 0x0000FF);

    // Test every Qt 4 version up to this minor version.
    typedef QPair<QString,bool> VersionPair;
    QList<VersionPair> versions;
    for (int i = 0; i <= minor; ++i) {
        bool isPatchRelease = (i == minor && patch);
        versions << qMakePair(QString("%1.%2").arg(major).arg(i), isPatchRelease);
    }

    QString arch;
#if defined Q_OS_LINUX && defined Q_WS_X11
# if defined(__powerpc__) && !defined(__powerpc64__)
    arch = "linux-gcc-ppc32";
# elif defined(__amd64__)
    arch = "linux-gcc-amd64";
# elif defined(__i386__)
    arch = "linux-gcc-ia32";
# endif
#elif defined Q_OS_AIX
    if (sizeof(void*) == 4) {
        arch = "aix-gcc-power32";
    }
#elif defined Q_OS_MAC && defined(__powerpc__)
    arch = "macx-gcc-ppc32";
#elif defined Q_OS_MAC && defined(__i386__)
    arch = "macx-gcc-ia32";
#elif defined Q_OS_WIN && defined Q_CC_GNU
    arch = "win32-gcc-ia32";
#endif

    if (arch.isEmpty())
        QSKIP("No reference files found for this arch", SkipAll);

    QTest::addColumn<QString>("oldLib");
    QTest::addColumn<bool>("isPatchRelease");

    foreach (VersionPair const& version, versions) {
        QString archFileName = QString("data/%3.%1.0.%2.txt").arg(version.first).arg(arch);
        QTest::newRow(qPrintable(version.first)) << archFileName << version.second;
    }
#endif
}

QBic::Info tst_Bic::getCurrentInfo(const QString &libName)
{
    QTemporaryFile tmpQFile;
    tmpQFile.open();
    QString tmpFileName = tmpQFile.fileName();

    QByteArray tmpFileContents = "#include<" + libName.toLatin1() + "/" + libName.toLatin1() + ">\n";
    tmpQFile.write(tmpFileContents);
    tmpQFile.flush();

    QString qtDir = QString::fromLocal8Bit(getenv("QTDIR"));
#ifdef Q_OS_WIN
    qtDir.replace('\\', '/');
#endif
    QString compilerName = "g++";

    QStringList args;
    args << "-c"
         << "-I" + qtDir + "/include"
#ifndef Q_OS_WIN
         << "-I/usr/X11R6/include/"
#endif
         << "-DQT_NO_STL" << "-DQT3_SUPPORT"
         << "-xc++"
#if !defined(Q_OS_AIX) && !defined(Q_OS_WIN)
         << "-o" << "/dev/null"
#endif
         << "-fdump-class-hierarchy"
         << tmpFileName;

    QProcess proc;
    proc.start(compilerName, args, QIODevice::ReadOnly);
    if (!proc.waitForFinished(6000000)) {
        qWarning() << "gcc didn't finish" << proc.errorString();
        return QBic::Info();
    }
    if (proc.exitCode() != 0) {
        qWarning() << "gcc returned with" << proc.exitCode();
        return QBic::Info();
    }

    QString errs = QString::fromLocal8Bit(proc.readAllStandardError().constData());
    if (!errs.isEmpty()) {
        qDebug() << "Arguments:" << args << "Warnings:" << errs;
        return QBic::Info();
    }

    QString resultFileName = QFileInfo(tmpQFile).fileName();
    static const char *suffixes[] = { ".t01.class", ".class", ".002t.class", 0 };
    for (const char **p = suffixes; true; ++p) {
        if (!p) {
            // we didn't find the file
            qFatal("GCC didn't produce the expected intermediary files. Please update this test!");
            return QBic::Info();
        }

        QString check = resultFileName + *p;
        if (!QFile::exists(check))
            continue;

        resultFileName = check;
        break;
    }
    QBic::Info inf = bic.parseFile(resultFileName);

    QFile::remove(resultFileName);
    tmpQFile.close();

    return inf;
}

void tst_Bic::sizesAndVTables()
{
#if !defined(Q_CC_GNU) || defined(Q_CC_INTEL)
    QSKIP("Test not implemented for this compiler/platform", SkipAll);
#else

    QFETCH_GLOBAL(QString, libName);
    QFETCH(QString, oldLib);
    QFETCH(bool, isPatchRelease);

    bool isFailed = false;

    if (oldLib.isEmpty() || !QFile::exists(oldLib.arg(libName)))
        QSKIP("No platform spec found for this platform/version.", SkipSingle);

    const QBic::Info oldLibInfo = bic.parseFile(oldLib.arg(libName));
    QVERIFY(!oldLibInfo.classVTables.isEmpty());

    const QBic::Info currentLibInfo = getCurrentInfo(libName);
    QVERIFY(!currentLibInfo.classVTables.isEmpty());

    QBic::VTableDiff diff = bic.diffVTables(oldLibInfo, currentLibInfo);

    if (!diff.removedVTables.isEmpty()) {
        qWarning() << "VTables for the following classes were removed" << diff.removedVTables;
        isFailed = true;
    }

    if (!diff.modifiedVTables.isEmpty()) {
        foreach(QStringPair entry, diff.modifiedVTables)
            qWarning() << "modified VTable:\n    Old: " << entry.first
                       << "\n    New: " << entry.second;
        isFailed = true;
    }

    if (isPatchRelease && !diff.addedVTables.isEmpty()) {
        qWarning() << "VTables for the following classes were added in a patch release:"
                   << diff.addedVTables;
        isFailed = true;
    }

    if (isPatchRelease && !diff.reimpMethods.isEmpty()) {
        foreach(QStringPair entry, diff.reimpMethods)
            qWarning() << "reimplemented virtual in patch release:\n    Old: " << entry.first
                       << "\n    New: " << entry.second;
        isFailed = true;
    }

    QBic::SizeDiff sizeDiff = bic.diffSizes(oldLibInfo, currentLibInfo);
    if (!sizeDiff.mismatch.isEmpty()) {
        foreach (QString className, sizeDiff.mismatch)
            qWarning() << "size mismatch for" << className
                       << "old" << oldLibInfo.classSizes.value(className)
                       << "new" << currentLibInfo.classSizes.value(className);
        isFailed = true;
    }

#ifdef Q_CC_MINGW
    /**
     * These symbols are from Windows' imm.h header, and is available
     * conditionally depending on the value of the WINVER define. We pull
     * them out since they're not relevant to the testing done.
     */
    sizeDiff.removed.removeAll(QLatin1String("tagIMECHARPOSITION"));
    sizeDiff.removed.removeAll(QLatin1String("tagRECONVERTSTRING"));
#endif

    if (!sizeDiff.removed.isEmpty()) {
        qWarning() << "the following classes were removed:" << sizeDiff.removed;
        isFailed = true;
    }

    if (isPatchRelease && !sizeDiff.added.isEmpty()) {
        qWarning() << "the following classes were added in a patch release:" << sizeDiff.added;
        isFailed = true;
    }

    if (isFailed)
        QFAIL("Test failed, read warnings above.");
#endif
}

QTEST_APPLESS_MAIN(tst_Bic)

#include "tst_bic.moc"

