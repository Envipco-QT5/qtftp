/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
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
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/


#include <QtTest/QtTest>

#if !defined(QMAKE_CROSS_COMPILED) && defined(QT3_SUPPORT)

#include <qdir.h>
#include <qprocess.h>


#include "testcompiler.h"

#include <stdlib.h>

//TESTED_CLASS=
//TESTED_FILES=corelib/tools/qlocale.h corelib/tools/qlocale.cpp

class tst_qmake : public QObject
{
    Q_OBJECT

public:
    tst_qmake();
    virtual ~tst_qmake();


public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
private slots:
    void simple_app();
    void simple_lib();
    void simple_dll();
    void subdirs();
    void functions();
    void operators();
    void variables();
    void func_export();
    void func_variables();
    void comments();
    void duplicateLibraryEntries();
    void export_across_file_boundaries();
    void include_dir();
    void install_files();
    void install_depends();
    void quotedfilenames();
    void prompt();
    void one_space();
    void findMocs();
    void findDeps();
#ifndef Q_OS_WIN
    // Test requires make
    void bundle_spaces();
#endif

private:
    TestCompiler test_compiler;
    QString base_path;
};

tst_qmake::tst_qmake()
{
    QString cmd = QString("qmake \"QT_VERSION=%1\"").arg(QT_VERSION);
#ifdef Q_CC_MSVC
    test_compiler.setBaseCommands( "nmake", cmd, FALSE );
#elif defined(Q_CC_MINGW)
    test_compiler.setBaseCommands( "mingw32-make", cmd, FALSE );
#elif defined(Q_OS_WIN) && defined(Q_CC_GNU)
    test_compiler.setBaseCommands( "mmmake", cmd, FALSE );
#else
    test_compiler.setBaseCommands( "make", cmd, FALSE );
#endif
    QDir dir;
    base_path = dir.currentDirPath();
}

tst_qmake::~tst_qmake()
{

}

void tst_qmake::initTestCase()
{
}

void tst_qmake::cleanupTestCase()
{
}

void tst_qmake::init()
{
}

void tst_qmake::cleanup()
{
}

void tst_qmake::simple_app()
{
    QString workDir = base_path + "/testdata/simple_app";

    QVERIFY( test_compiler.qmake( workDir, "simple_app" ));
    QVERIFY( test_compiler.make( workDir ));
    QVERIFY( test_compiler.exists( workDir, "simple_app", Exe, "1.0.0" ));
    QVERIFY( test_compiler.makeClean( workDir ));
    QVERIFY( test_compiler.exists( workDir, "simple_app", Exe, "1.0.0" )); // Should still exist after a make clean
    QVERIFY( test_compiler.makeDistClean( workDir ));
    QVERIFY( !test_compiler.exists( workDir, "simple_app", Exe, "1.0.0" )); // Should not exist after a make distclean
    QVERIFY( test_compiler.removeMakefile( workDir ) );
}

void tst_qmake::simple_dll()
{
    QString workDir = base_path + "/testdata/simple_dll";

    QDir D;
    D.remove( workDir + "/Makefile");
    QVERIFY( test_compiler.qmake( workDir, "simple_dll" ));
    QVERIFY( test_compiler.make( workDir ));
    QVERIFY( test_compiler.exists( workDir, "simple_dll", Dll, "1.0.0" ));
    QVERIFY( test_compiler.makeClean( workDir ));
    QVERIFY( test_compiler.exists( workDir, "simple_dll", Dll, "1.0.0" )); // Should still exist after a make clean
    QVERIFY( test_compiler.makeDistClean( workDir ));
    QVERIFY( !test_compiler.exists( workDir, "simple_dll", Dll, "1.0.0" )); // Should not exist after a make distclean
    QVERIFY( test_compiler.removeMakefile( workDir ) );
}

void tst_qmake::simple_lib()
{
    QString workDir = base_path + "/testdata/simple_lib";

    QDir D;
    D.remove( workDir + "/Makefile");
    QVERIFY( test_compiler.qmake( workDir, "simple_lib" ));
    QVERIFY( test_compiler.make( workDir ));
    QVERIFY( test_compiler.exists( workDir, "simple_lib", Lib, "1.0.0" ));
    QVERIFY( test_compiler.makeClean( workDir ));
    QVERIFY( test_compiler.exists( workDir, "simple_lib", Lib, "1.0.0" )); // Should still exist after a make clean
    QVERIFY( test_compiler.makeDistClean( workDir ));
    QVERIFY( !test_compiler.exists( workDir, "simple_lib", Lib, "1.0.0" )); // Should not exist after a make distclean
    QVERIFY( test_compiler.removeMakefile( workDir ) );
}

void tst_qmake::subdirs()
{
    QString workDir = base_path + "/testdata/subdirs";

    QDir D;
    D.remove( workDir + "/simple_app/Makefile");
    D.remove( workDir + "/simple_dll/Makefile");
    QVERIFY( test_compiler.qmake( workDir, "subdirs" ));
    QVERIFY( test_compiler.make( workDir ));
    QVERIFY( test_compiler.exists( workDir + "/simple_app", "simple_app", Exe, "1.0.0" ));
    QVERIFY( test_compiler.exists( workDir + "/simple_dll", "simple_dll", Dll, "1.0.0" ));
    QVERIFY( test_compiler.makeClean( workDir ));
    // Should still exist after a make clean
    QVERIFY( test_compiler.exists( workDir + "/simple_app", "simple_app", Exe, "1.0.0" ));
    QVERIFY( test_compiler.exists( workDir + "/simple_dll", "simple_dll", Dll, "1.0.0" ));
    // Since subdirs templates do not have a make dist clean, we should clean up ourselves
    // properly
    QVERIFY( test_compiler.makeDistClean( workDir ));
    QVERIFY( test_compiler.removeMakefile( workDir ) );
}

void tst_qmake::functions()
{
    QString workDir = base_path + "/testdata/functions";
    QVERIFY( test_compiler.qmake( workDir, "functions" ));
}

void tst_qmake::operators()
{
    QString workDir = base_path + "/testdata/operators";
    QVERIFY( test_compiler.qmake( workDir, "operators" ));
}

void tst_qmake::variables()
{
    QString workDir = base_path + "/testdata/variables";
    QVERIFY(test_compiler.qmake( workDir, "variables" ));
}

void tst_qmake::func_export()
{
    QString workDir = base_path + "/testdata/func_export";
    QVERIFY(test_compiler.qmake( workDir, "func_export" ));
}

void tst_qmake::func_variables()
{
    QString workDir = base_path + "/testdata/func_variables";
    QVERIFY(test_compiler.qmake( workDir, "func_variables" ));
}

void tst_qmake::comments()
{
    QString workDir = base_path + "/testdata/comments";
    QVERIFY(test_compiler.qmake( workDir, "comments" ));
}

void tst_qmake::duplicateLibraryEntries()
{
    QVERIFY(true);
    /* TODO: this test does not work as the problem it tests doesn't happen
    until after the parsing of the pro-file and thus has to be tested
    by parsing the Makefile. This is not doable with the current
    testcompiler framework and has as such been put on hold.

    QString workDir = base_path + "/testdata/duplicateLibraryEntries";
    QVERIFY(test_compiler.qmake(workDir, "duplicateLibraryEntries")); */
}

void tst_qmake::export_across_file_boundaries()
{
    // This relies on features so we need to set the QMAKEFEATURES environment variable
	putenv("QMAKEFEATURES=.");
    QString workDir = base_path + "/testdata/export_across_file_boundaries";
    QVERIFY( test_compiler.qmake( workDir, "foo" ));
	putenv("QMAKEFEATURES=");
}

void tst_qmake::include_dir()
{
    QString workDir = base_path + "/testdata/include_dir";
    QVERIFY( test_compiler.qmake( workDir, "foo" ));
    QVERIFY( test_compiler.make( workDir ));
    QVERIFY( test_compiler.exists( workDir, "foo", Exe, "1.0.0" ));
    QVERIFY( test_compiler.makeDistClean( workDir ));

    QString buildDir = base_path + "/testdata/include_dir_build";
    QVERIFY( test_compiler.qmake( workDir, "foo", buildDir ));
    QVERIFY( test_compiler.make( buildDir ));
    QVERIFY( test_compiler.exists( buildDir, "foo", Exe, "1.0.0" ));
    QVERIFY( test_compiler.makeDistClean( buildDir ));
}

void tst_qmake::install_files()
{
    QString workDir = base_path + "/testdata/shadow_files";
    QVERIFY( test_compiler.qmake( workDir, "foo" ));
    QVERIFY( test_compiler.make( workDir ));
    QVERIFY( test_compiler.exists( workDir, "foo", Exe, "1.0.0" ));
    QVERIFY( test_compiler.make( workDir, "install" ));
    QVERIFY( test_compiler.exists( workDir + "/dist", "foo", Exe, "1.0.0" ));
    QVERIFY( test_compiler.exists( workDir + "/dist", "test.txt", Plain, "1.0.0" ));
    QVERIFY( test_compiler.make( workDir, "uninstall" ));
    QVERIFY( test_compiler.makeDistClean( workDir ));

    QString buildDir = base_path + "/testdata/shadow_files_build";
    QVERIFY( test_compiler.qmake( workDir, "foo", buildDir ));
    QVERIFY( test_compiler.make( buildDir ));
    QVERIFY( test_compiler.exists( buildDir, "foo", Exe, "1.0.0" ));
    QVERIFY( test_compiler.make( buildDir, "install" ));
    QVERIFY( test_compiler.exists( workDir + "/dist", "foo", Exe, "1.0.0" ));
    QVERIFY( test_compiler.exists( workDir + "/dist", "test.txt", Plain, "1.0.0" ));
    QVERIFY( test_compiler.exists( workDir + "/dist", "foo.bar", Plain, "1.0.0" ));
    QVERIFY( test_compiler.make( buildDir, "uninstall" ));
    QVERIFY( test_compiler.makeDistClean( buildDir ));
}

void tst_qmake::install_depends()
{
    QString workDir = base_path + "/testdata/install_depends";
    QVERIFY( test_compiler.qmake( workDir, "foo" ));
    QVERIFY( test_compiler.make( workDir ));
    QVERIFY( test_compiler.exists( workDir, "foo", Exe, "1.0.0" ));
    QVERIFY( test_compiler.make( workDir, "install" ));
    QVERIFY( test_compiler.exists( workDir + "/dist", "foo", Exe, "1.0.0" ));
    QVERIFY( test_compiler.exists( workDir + "/dist", "test1", Plain, "1.0.0" ));
    QVERIFY( test_compiler.exists( workDir + "/dist", "test2", Plain, "1.0.0" ));
    QVERIFY( test_compiler.make( workDir, "uninstall" ));
    QVERIFY( test_compiler.makeDistClean( workDir ));
}
void tst_qmake::quotedfilenames()
{
    QString workDir = base_path + "/testdata/quotedfilenames";
    QVERIFY( test_compiler.qmake( workDir, "quotedfilenames" ));
    QVERIFY( test_compiler.makeClean( workDir ));
    QVERIFY( test_compiler.make( workDir ));
    QVERIFY( test_compiler.exists( workDir, "quotedfilenames", Exe, "1.0.0" ));
}

void tst_qmake::prompt()
{
#if 0
    QProcess qmake;
    qmake.setReadChannelMode(QProcess::MergedChannels);
    qmake.setWorkingDirectory(QLatin1String("testdata/prompt"));
    qmake.start(QLatin1String("qmake CONFIG-=debug_and_release CONFIG-=debug CONFIG+=release"),
                QIODevice::Text | QIODevice::ReadWrite);
    QVERIFY(qmake.waitForStarted(20000));
    QByteArray read = qmake.readAll();
    qDebug() << read;
    QCOMPARE(read, QByteArray("Project PROMPT: Prompteroo? "));
    qmake.write("promptetiprompt\n");
    QVERIFY(qmake.waitForFinished(20000));
#endif
}

void tst_qmake::one_space()
{
    QString workDir = base_path + "/testdata/one_space";

    QVERIFY( test_compiler.qmake( workDir, "one_space" ));
    QVERIFY( test_compiler.make( workDir ));
    QVERIFY( test_compiler.exists( workDir, "one space", Exe, "1.0.0" ));
    QVERIFY( test_compiler.makeClean( workDir ));
    QVERIFY( test_compiler.exists( workDir, "one space", Exe, "1.0.0" )); // Should still exist after a make clean
    QVERIFY( test_compiler.makeDistClean( workDir ));
    QVERIFY( !test_compiler.exists( workDir, "one space", Exe, "1.0.0" )); // Should not exist after a make distclean
    QVERIFY( test_compiler.removeMakefile( workDir ) );
}

void tst_qmake::findMocs()
{
    QString workDir = base_path + "/testdata/findMocs";

    QVERIFY( test_compiler.qmake(workDir, "findMocs") );
    QVERIFY( test_compiler.make(workDir) );
    QVERIFY( test_compiler.exists(workDir, "findMocs", Exe, "1.0.0" ) );
    QVERIFY( test_compiler.makeClean(workDir) );
    QVERIFY( test_compiler.exists(workDir, "findMocs", Exe, "1.0.0" ) );
    QVERIFY( test_compiler.makeDistClean(workDir ) );
    QVERIFY( !test_compiler.exists(workDir, "findMocs", Exe, "1.0.0" ) );
    QVERIFY( test_compiler.removeMakefile(workDir) );
}

void tst_qmake::findDeps()
{
    QString workDir = base_path + "/testdata/findDeps";

    QVERIFY( test_compiler.qmake(workDir, "findDeps") );
    QVERIFY( test_compiler.make(workDir) );
    QVERIFY( test_compiler.exists(workDir, "findDeps", Exe, "1.0.0" ) );
    QVERIFY( test_compiler.makeClean(workDir) );
    QVERIFY( test_compiler.exists(workDir, "findDeps", Exe, "1.0.0" ) );
    QVERIFY( test_compiler.makeDistClean(workDir ) );
    QVERIFY( !test_compiler.exists(workDir, "findDeps", Exe, "1.0.0" ) );
    QVERIFY( test_compiler.removeMakefile(workDir) );
}

struct TempFile
    : QFile
{
    TempFile(QString filename)
        : QFile(filename)
    {
    }

    ~TempFile()
    {
        if (this->exists())
            this->remove();
    }
};

#ifndef Q_OS_WIN
void tst_qmake::bundle_spaces()
{
    QString workDir = base_path + "/testdata/bundle-spaces";

    // We set up alternate commands here, to make sure we're testing Mac
    // Bundles and since this might be the wrong output we rely on dry-running
    // make (-n).

    TestCompiler local_tc;
    local_tc.setBaseCommands("make -n", "qmake -macx -spec macx-g++", FALSE);

    QVERIFY( local_tc.qmake(workDir, "bundle-spaces") );

    TempFile non_existing_file(workDir + "/non-existing file");
    QVERIFY( !non_existing_file.exists() );

    // Make fails: no rule to make "non-existing file"
    QVERIFY( !local_tc.make(workDir) );

    QVERIFY( non_existing_file.open(QIODevice::WriteOnly) );
    QVERIFY( non_existing_file.exists() );

    // Aha!
    QVERIFY( local_tc.make(workDir) );

    // Cleanup
    QVERIFY( non_existing_file.remove() );
    QVERIFY( !non_existing_file.exists() );
    QVERIFY( local_tc.removeMakefile(workDir) );
}
#endif // Q_OS_WIN

QTEST_MAIN(tst_qmake)
#include "tst_qmake.moc"

#else // QMAKE_CROSS_COMPILED
QTEST_NOOP_MAIN
#endif
