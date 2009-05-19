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

#include <qcoreapplication.h>
#include <qdebug.h>
#include <qdir.h>
#include <qfileinfo.h>
#include <qregexp.h>
#include <qstringlist.h>

#include "../network-settings.h"



//TESTED_CLASS=
//TESTED_FILES=

class tst_QDir : public QObject
{
Q_OBJECT

public:
    tst_QDir();
    virtual ~tst_QDir();

private slots:
    void getSetCheck();
    void construction();

    void setPath_data();
    void setPath();

    void entryList_data();
    void entryList();

    void entryListSimple_data();
    void entryListSimple();

    void entryListWithSymLinks();

    void mkdir_data();
    void mkdir();

    void rmdir_data();
    void rmdir();

    void exists_data();
    void exists();

    void isRelativePath_data();
    void isRelativePath();

    void canonicalPath_data();
    void canonicalPath();

    void current_data();
    void current();

    void cd_data();
    void cd();

    void setNameFilters_data();
    void setNameFilters();

    void cleanPath_data();
    void cleanPath();

    void compare();
    void QDir_default();

    void filePath_data();
    void filePath();

    void absoluteFilePath_data();
    void absoluteFilePath();

    void absolutePath_data();
    void absolutePath();

    void relativeFilePath_data();
    void relativeFilePath();

    void remove();
    void rename();

    void exists2_data();
    void exists2();

    void dirName_data();
    void dirName();

    void operator_eq();

    void dotAndDotDot();
#ifdef QT3_SUPPORT
    void matchAllDirs();
#endif
    void homePath();
    void tempPath();
    void rootPath();

    void nativeSeparators();

    void searchPaths();
    void searchPaths_data();

    void entryListWithSearchPaths();

    void longFileName_data();
    void longFileName();
};

// Testing get/set functions
void tst_QDir::getSetCheck()
{
    QDir obj1;
    // Filters QDir::filter()
    // void QDir::setFilter(Filters)
    obj1.setFilter(QDir::Filters(QDir::Dirs));
    QCOMPARE(QDir::Filters(QDir::Dirs), obj1.filter());
    obj1.setFilter(QDir::Filters(QDir::Dirs | QDir::Files));
    QCOMPARE(QDir::Filters(QDir::Dirs | QDir::Files), obj1.filter());
    obj1.setFilter(QDir::Filters(QDir::NoFilter));
    QCOMPARE(QDir::Filters(QDir::NoFilter), obj1.filter());

    // SortFlags QDir::sorting()
    // void QDir::setSorting(SortFlags)
    obj1.setSorting(QDir::SortFlags(QDir::Name));
    QCOMPARE(QDir::SortFlags(QDir::Name), obj1.sorting());
    obj1.setSorting(QDir::SortFlags(QDir::Name | QDir::IgnoreCase));
    QCOMPARE(QDir::SortFlags(QDir::Name | QDir::IgnoreCase), obj1.sorting());
    obj1.setSorting(QDir::SortFlags(QDir::NoSort));
    QCOMPARE(QDir::SortFlags(QDir::NoSort), obj1.sorting());
}

tst_QDir::tst_QDir()
{
}

tst_QDir::~tst_QDir()
{

}

void tst_QDir::construction()
{
    QFileInfo myFileInfo("/machine/share/dir1/file1");
    QDir myDir(myFileInfo.absoluteDir()); // this asserted
    QCOMPARE(myFileInfo.absoluteDir().absolutePath(), myDir.absolutePath());
}

void tst_QDir::setPath_data()
{
    QTest::addColumn<QString>("dir1");
    QTest::addColumn<QString>("dir2");

    QTest::newRow("data0") << QString(".") << QString("..");
#if defined(Q_WS_WIN) && !defined(Q_OS_WINCE)
    QTest::newRow("data1") << QString("c:/") << QDir::currentPath();
#endif
}

void tst_QDir::setPath()
{
    QFETCH(QString, dir1);
    QFETCH(QString, dir2);

    QDir shared;
    QDir qDir1(dir1);
    QStringList entries1 = qDir1.entryList();
    shared.setPath(dir1);
    QCOMPARE(shared.entryList(), entries1);

    QDir qDir2(dir2);
    QStringList entries2 = qDir2.entryList();
    shared.setPath(dir2);
    QCOMPARE(shared.entryList(), entries2);
}

void tst_QDir::mkdir_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<bool>("recurse");

    QStringList dirs;
    dirs << QDir::currentPath() + "/testdir/one/two/three"
         << QDir::currentPath() + "/testdir/two"
         << QDir::currentPath() + "/testdir/two/three";
    QTest::newRow("data0") << dirs.at(0) << true;
    QTest::newRow("data1") << dirs.at(1) << false;
    QTest::newRow("data2") << dirs.at(2) << false;

    // Ensure that none of these directories already exist
    QDir dir;
    for (int i = 0; i < dirs.count(); ++i)
        dir.rmpath(dirs.at(i));
}

void tst_QDir::mkdir()
{
    QFETCH(QString, path);
    QFETCH(bool, recurse);

    QDir dir;
    dir.rmdir(path);
    if (recurse)
        QVERIFY(dir.mkpath(path));
    else
        QVERIFY(dir.mkdir(path));

    //make sure it really exists (ie that mkdir returns the right value)
    QFileInfo fi(path);
    QVERIFY(fi.exists() && fi.isDir());
}

void tst_QDir::rmdir_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<bool>("recurse");

    QTest::newRow("data0") << QDir::currentPath() + "/testdir/one/two/three" << true;
    QTest::newRow("data1") << QDir::currentPath() + "/testdir/two/three" << false;
    QTest::newRow("data2") << QDir::currentPath() + "/testdir/two" << false;
}

void tst_QDir::rmdir()
{
    QFETCH(QString, path);
    QFETCH(bool, recurse);

    QDir dir;
    if (recurse)
        QVERIFY(dir.rmpath(path));
    else
        QVERIFY(dir.rmdir(path));

    //make sure it really doesn't exist (ie that rmdir returns the right value)
    QFileInfo fi(path);
    QVERIFY(!fi.exists());
}

void tst_QDir::exists_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<bool>("expected");

    QTest::newRow("data0") << QDir::currentPath() << true;
    QTest::newRow("data0.1") << QDir::currentPath() + "/" << true;
    QTest::newRow("data1") << QString("/I/Do_not_expect_this_path_to_exist/") << false;
    QTest::newRow("resource0") << QString(":/tst_qdir/") << true;
    QTest::newRow("resource1") << QString(":/I/Do_not_expect_this_resource_to_exist/") << false;

    QTest::newRow("simple dir") << SRCDIR "resources" << true;
    QTest::newRow("simple dir with slash") << SRCDIR "resources/" << true;
#if defined(Q_OS_WIN) && !defined(Q_OS_WINCE)
    QTest::newRow("unc 1") << "//" + QtNetworkSettings::winServerName() << true;
    QTest::newRow("unc 2") << "//"  + QtNetworkSettings::winServerName() + "/" << true;
    QTest::newRow("unc 3") << "//"  + QtNetworkSettings::winServerName() + "/testshare" << true;
    QTest::newRow("unc 4") << "//"  + QtNetworkSettings::winServerName() + "/testshare/" << true;
    QTest::newRow("unc 5") << "//"  + QtNetworkSettings::winServerName() + "/testshare/tmp" << true;
    QTest::newRow("unc 6") << "//"  + QtNetworkSettings::winServerName() + "/testshare/tmp/" << true;
    QTest::newRow("unc 7") << "//"  + QtNetworkSettings::winServerName() + "/testshare/adirthatshouldnotexist" << false;
    QTest::newRow("unc 8") << "//"  + QtNetworkSettings::winServerName() + "/asharethatshouldnotexist" << false;
    QTest::newRow("unc 9") << "//ahostthatshouldnotexist" << false;

    QTest::newRow("This drive should exist") <<  "C:/" << true;
    // find a non-existing drive and check if it does not exist
    QFileInfoList drives = QFSFileEngine::drives();
    QStringList driveLetters;
    for (int i = 0; i < drives.count(); ++i) {
        driveLetters+=drives.at(i).absoluteFilePath();
    }
    char drive = 'Z';
    QString driv;
    do {
        driv = QString::fromAscii("%1:/").arg(drive);
        if (!driveLetters.contains(driv)) break;
        --drive;
    } while (drive >= 'A');
    if (drive >= 'A') {
        QTest::newRow("This drive should not exist") <<  driv << false;
    }
#endif
}

void tst_QDir::exists()
{
    QFETCH(QString, path);
    QFETCH(bool, expected);

    QDir dir(path);
    QCOMPARE(dir.exists(), expected);
}

void tst_QDir::isRelativePath_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<bool>("relative");

    QTest::newRow("data0") << "../somedir" << true;
#if defined(Q_WS_WIN) && !defined(Q_OS_WINCE)
    QTest::newRow("data1") << "C:/sOmedir" << false;
#endif
    QTest::newRow("data2") << "somedir" << true;
    QTest::newRow("data3") << "/somedir" << false;
}

void tst_QDir::isRelativePath()
{
    QFETCH(QString, path);
    QFETCH(bool, relative);

    QCOMPARE(QDir::isRelativePath(path),relative);
}


void tst_QDir::QDir_default()
{
    //default constructor QDir();
    QDir dir; // according to documentation should be currentDirPath
    QCOMPARE(dir.absolutePath(), QDir::currentPath());
}

void tst_QDir::compare()
{
    // operator==
    QDir dir;
    dir.makeAbsolute();
    QVERIFY(dir == QDir::currentPath());
}

void tst_QDir::entryList_data()
{
    QTest::addColumn<QString>("dirName"); // relative from current path or abs
    QTest::addColumn<QStringList>("nameFilters");
    QTest::addColumn<int>("filterspec");
    QTest::addColumn<int>("sortspec");
    QTest::addColumn<QStringList>("expected");
    QTest::newRow("spaces1") << SRCDIR "testdir/spaces" << QStringList("*. bar")
			  << (int)(QDir::NoFilter) << (int)(QDir::NoSort)
			  << QStringList("foo. bar"); // notice how spaces5 works
    QTest::newRow("spaces2") << SRCDIR "testdir/spaces" << QStringList("*.bar")
			  << (int)(QDir::NoFilter) << (int)(QDir::NoSort)
			  << QStringList("foo.bar");
    QTest::newRow("spaces3") << SRCDIR "testdir/spaces" << QStringList("foo.*")
			  << (int)(QDir::NoFilter) << (int)(QDir::NoSort)
			  << QString("foo. bar,foo.bar").split(',');
    QTest::newRow("files1")  << SRCDIR "testdir/dir" << QString("*r.cpp *.pro").split(" ")
			  << (int)(QDir::NoFilter) << (int)(QDir::NoSort)
			  << QString("qdir.pro,qrc_qdir.cpp,tst_qdir.cpp").split(',');
    QTest::newRow("testdir1")  << SRCDIR "testdir" << QStringList()
			  << (int)(QDir::AllDirs) << (int)(QDir::NoSort)
			  << QString(".,..,dir,spaces").split(',');
// #### this test uses filenames that cannot be represented on all filesystems we test, in
// particular HFS+ on the Mac. When checking out the files with perforce it silently ignores the
// error that it cannot represent the file names stored in the repository and the test fails. That
// is why the test is marked as 'skip' for the mac. When checking out the files with git on the mac
// the error of not being able to represent the files stored in the repository is not silently
// ignored but git reports an error. The test only tried to prevent QDir from _hanging_ when listing
// the directory.
//    QTest::newRow("unprintablenames")  << SRCDIR "unprintablenames" << QStringList("*")
//			  << (int)(QDir::NoFilter) << (int)(QDir::NoSort)
//			  << QString(".,..").split(",");
    QTest::newRow("resources1") << QString(":/tst_qdir/resources/entryList") << QStringList("*.data")
                             << (int)(QDir::NoFilter) << (int)(QDir::NoSort)
                             << QString("file1.data,file2.data,file3.data").split(',');
    QTest::newRow("resources2") << QString(":/tst_qdir/resources/entryList") << QStringList("*.data")
                             << (int)(QDir::Files) << (int)(QDir::NoSort)
                             << QString("file1.data,file2.data,file3.data").split(',');

    QTest::newRow("nofilter") << SRCDIR "entrylist/" << QStringList("*")
                              << int(QDir::NoFilter) << int(QDir::Name)
                              << QString(".,..,directory,file,linktodirectory.lnk,linktofile.lnk,writable").split(',');
    QTest::newRow("QDir::AllEntries") << SRCDIR "entrylist/" << QStringList("*")
                              << int(QDir::AllEntries) << int(QDir::Name)
                              << QString(".,..,directory,file,linktodirectory.lnk,linktofile.lnk,writable").split(',');
    QTest::newRow("QDir::Files") << SRCDIR "entrylist/" << QStringList("*")
                                 << int(QDir::Files) << int(QDir::Name)
                                 << QString("file,linktofile.lnk,writable").split(',');
    QTest::newRow("QDir::Dirs") << SRCDIR "entrylist/" << QStringList("*")
                                << int(QDir::Dirs) << int(QDir::Name)
                                << QString(".,..,directory,linktodirectory.lnk").split(',');
    QTest::newRow("QDir::Dirs | QDir::NoDotAndDotDot") << SRCDIR "entrylist/" << QStringList("*")
                                                       << int(QDir::Dirs | QDir::NoDotAndDotDot) << int(QDir::Name)
                                << QString("directory,linktodirectory.lnk").split(',');
    QTest::newRow("QDir::AllDirs") << SRCDIR "entrylist/" << QStringList("*")
                                   << int(QDir::AllDirs) << int(QDir::Name)
                                   << QString(".,..,directory,linktodirectory.lnk").split(',');
    QTest::newRow("QDir::AllDirs | QDir::Dirs") << SRCDIR "entrylist/" << QStringList("*")
                                                << int(QDir::AllDirs | QDir::Dirs) << int(QDir::Name)
                                                << QString(".,..,directory,linktodirectory.lnk").split(',');
    QTest::newRow("QDir::AllDirs | QDir::Files") << SRCDIR "entrylist/" << QStringList("*")
                                                 << int(QDir::AllDirs | QDir::Files) << int(QDir::Name)
                                                 << QString(".,..,directory,file,linktodirectory.lnk,linktofile.lnk,writable").split(',');
    QTest::newRow("QDir::AllEntries | QDir::NoSymLinks") << SRCDIR "entrylist/" << QStringList("*")
                                      << int(QDir::AllEntries | QDir::NoSymLinks) << int(QDir::Name)
                                      << QString(".,..,directory,file,writable").split(',');
    QTest::newRow("QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot") << SRCDIR "entrylist/" << QStringList("*")
                                      << int(QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot) << int(QDir::Name)
                                      << QString("directory,file,writable").split(',');
    QTest::newRow("QDir::Files | QDir::NoSymLinks") << SRCDIR "entrylist/" << QStringList("*")
                                                    << int(QDir::Files | QDir::NoSymLinks) << int(QDir::Name)
                                                    << QString("file,writable").split(',');
    QTest::newRow("QDir::Dirs | QDir::NoSymLinks") << SRCDIR "entrylist/" << QStringList("*")
                                                   << int(QDir::Dirs | QDir::NoSymLinks) << int(QDir::Name)
                                                   << QString(".,..,directory").split(',');
    QTest::newRow("QDir::Drives | QDir::Files | QDir::NoDotAndDotDot") << SRCDIR "entrylist/" << QStringList("*")
                                                   << int(QDir::Drives | QDir::Files | QDir::NoDotAndDotDot) << int(QDir::Name)
                                                   << QString("file,linktofile.lnk,writable").split(',');
    QTest::newRow("QDir::System") << SRCDIR "entrylist/" << QStringList("*")
                                  << int(QDir::System) << int(QDir::Name)
                                  << QStringList("brokenlink.lnk");
    QTest::newRow("QDir::Hidden") << SRCDIR "entrylist/" << QStringList("*")
                                  << int(QDir::Hidden) << int(QDir::Name)
                                  << QStringList();
    QTest::newRow("QDir::System | QDir::Hidden") << SRCDIR "entrylist/" << QStringList("*")
                                  << int(QDir::System | QDir::Hidden) << int(QDir::Name)
                                  << QStringList("brokenlink.lnk");
    QTest::newRow("QDir::AllDirs | QDir::NoSymLinks") << SRCDIR "entrylist/" << QStringList("*")
                                                      << int(QDir::AllDirs | QDir::NoSymLinks) << int(QDir::Name)
                                                      << QString(".,..,directory").split(',');
#ifdef QT3_SUPPORT
    QTest::newRow("QDir::All | QDir::Hidden | QDir::System") << SRCDIR "entrylist/" << QStringList("*")
                                  << int(QDir::All | QDir::Hidden | QDir::System) << int(QDir::Name)
                                  << QString(".,..,brokenlink.lnk,directory,file,linktodirectory.lnk,linktofile.lnk,writable").split(',');
    QTest::newRow("QDir::All | QDir::Readable") << SRCDIR "entrylist/" << QStringList("*")
                                  << int(QDir::All | QDir::Readable) << int(QDir::Name)
                                                << QString(".,..,directory,file,linktodirectory.lnk,linktofile.lnk,writable").split(',');
    QTest::newRow("QDir::All | QDir::Writable") << SRCDIR "entrylist/" << QStringList("*")
                                  << int(QDir::All | QDir::Writable) << int(QDir::Name)
                                  << QString(".,..,directory,linktodirectory.lnk,writable").split(',');
#else
    QTest::newRow("QDir::AllEntries | QDir::Hidden | QDir::System") << SRCDIR "entrylist/" << QStringList("*")
                                  << int(QDir::AllEntries | QDir::Hidden | QDir::System) << int(QDir::Name)
                                  << QString(".,..,brokenlink.lnk,directory,file,linktodirectory.lnk,linktofile.lnk,writable").split(',');
    QTest::newRow("QDir::AllEntries | QDir::Readable") << SRCDIR "entrylist/" << QStringList("*")
                                  << int(QDir::AllEntries | QDir::Readable) << int(QDir::Name)
                                                << QString(".,..,directory,file,linktodirectory.lnk,linktofile.lnk,writable").split(',');
    QTest::newRow("QDir::AllEntries | QDir::Writable") << SRCDIR "entrylist/" << QStringList("*")
                                  << int(QDir::AllEntries | QDir::Writable) << int(QDir::Name)
                                  << QString(".,..,directory,linktodirectory.lnk,writable").split(',');
#endif
    QTest::newRow("Namefilters b*") << SRCDIR "entrylist/" << QStringList("d*")
                                  << int(QDir::NoFilter) << int(QDir::Name)
                                  << QString("directory").split(',');
    QTest::newRow("Namefilters f*") << SRCDIR "entrylist/" << QStringList("f*")
                                  << int(QDir::NoFilter) << int(QDir::Name)
                                  << QString("file").split(',');
    QTest::newRow("Namefilters link*") << SRCDIR "entrylist/" << QStringList("link*")
                                  << int(QDir::NoFilter) << int(QDir::Name)
                                  << QString("linktodirectory.lnk,linktofile.lnk").split(',');
    QTest::newRow("Namefilters *to*") << SRCDIR "entrylist/" << QStringList("*to*")
                                  << int(QDir::NoFilter) << int(QDir::Name)
                                  << QString("directory,linktodirectory.lnk,linktofile.lnk").split(',');
    QTest::newRow("Sorting QDir::Name") << SRCDIR "entrylist/" << QStringList("*")
                                  << int(QDir::NoFilter) << int(QDir::Name)
                                  << QString(".,..,directory,file,linktodirectory.lnk,linktofile.lnk,writable").split(',');
    QTest::newRow("Sorting QDir::Name | QDir::Reversed") << SRCDIR "entrylist/" << QStringList("*")
                                  << int(QDir::NoFilter) << int(QDir::Name | QDir::Reversed)
                                  << QString("writable,linktofile.lnk,linktodirectory.lnk,file,directory,..,.").split(',');
    QTest::newRow("Sorting QDir::Type") << SRCDIR "types/" << QStringList("*")
                                  << int(QDir::NoFilter) << int(QDir::Type)
                                  << QString(".,..,a,b,c,d,e,f,a.a,b.a,c.a,d.a,e.a,f.a,a.b,b.b,c.b,d.b,e.b,f.b,a.c,b.c,c.c,d.c,e.c,f.c").split(',');
    QTest::newRow("Sorting QDir::Type | QDir::Reversed") << SRCDIR "types/" << QStringList("*")
                                  << int(QDir::NoFilter) << int(QDir::Type | QDir::Reversed)
                                  << QString("f.c,e.c,d.c,c.c,b.c,a.c,f.b,e.b,d.b,c.b,b.b,a.b,f.a,e.a,d.a,c.a,b.a,a.a,f,e,d,c,b,a,..,.").split(',');
    QTest::newRow("Sorting QDir::Type | QDir::DirsLast") << SRCDIR "types/" << QStringList("*")
                                  << int(QDir::NoFilter) << int(QDir::Type | QDir::DirsLast)
                                  << QString("a,b,c,a.a,b.a,c.a,a.b,b.b,c.b,a.c,b.c,c.c,.,..,d,e,f,d.a,e.a,f.a,d.b,e.b,f.b,d.c,e.c,f.c").split(',');
    QTest::newRow("Sorting QDir::Type | QDir::DirsFirst") << SRCDIR "types/" << QStringList("*")
                                  << int(QDir::NoFilter) << int(QDir::Type | QDir::DirsFirst)
                                  << QString(".,..,d,e,f,d.a,e.a,f.a,d.b,e.b,f.b,d.c,e.c,f.c,a,b,c,a.a,b.a,c.a,a.b,b.b,c.b,a.c,b.c,c.c").split(',');
    QTest::newRow("Sorting QDir::Size") << SRCDIR "types/" << QStringList("*")
                                  << int(QDir::AllEntries|QDir::NoDotAndDotDot) << int(QDir::Size | QDir::DirsFirst)
                                  << QString("d,d.a,d.b,d.c,e,e.a,e.b,e.c,f,f.a,f.b,f.c,c.a,c.b,c.c,b.a,b.c,b.b,a.c,a.b,a.a,a,b,c").split(',');
    QTest::newRow("Sorting QDir::Size | QDir::Reversed") << SRCDIR "types/" << QStringList("*")
                                  << int(QDir::AllEntries|QDir::NoDotAndDotDot) << int(QDir::Size | QDir::Reversed | QDir::DirsLast)
                                  << QString("c,b,a,a.a,a.b,a.c,b.b,b.c,b.a,c.c,c.b,c.a,f.c,f.b,f.a,f,e.c,e.b,e.a,e,d.c,d.b,d.a,d").split(',');
}

void tst_QDir::entryList()
{
    QFETCH(QString, dirName);
    QFETCH(QStringList, nameFilters);
    QFETCH(int, filterspec);
    QFETCH(int, sortspec);
    QFETCH(QStringList, expected);

    QFile(SRCDIR "entrylist/writable").open(QIODevice::ReadWrite);
    QFile(SRCDIR "entrylist/file").setPermissions(QFile::ReadOwner | QFile::ReadUser);
    QFile::remove(SRCDIR "entrylist/linktofile");
    QFile::remove(SRCDIR "entrylist/linktodirectory");
    QFile::remove(SRCDIR "entrylist/linktofile.lnk");
    QFile::remove(SRCDIR "entrylist/linktodirectory.lnk");
    QFile::remove(SRCDIR "entrylist/brokenlink.lnk");
    QFile::remove(SRCDIR "entrylist/brokenlink");

	// WinCE does not have . and .. in the directory listing
#ifdef Q_OS_WINCE
	expected.removeAll(".");
	expected.removeAll("..");
#endif

#ifdef Q_OS_WIN
    // ### Sadly, this is a platform difference right now.
    QFile::link(SRCDIR "entryList/file", SRCDIR "entrylist/linktofile.lnk");
    QFile::link(SRCDIR "entryList/directory", SRCDIR "entrylist/linktodirectory.lnk");
    QFile::link(SRCDIR "entryList/nothing", SRCDIR "entrylist/brokenlink.lnk");
#else
    QFile::link("file", SRCDIR "entrylist/linktofile.lnk");
    QFile::link("directory", SRCDIR "entrylist/linktodirectory.lnk");
    QFile::link("nothing", SRCDIR "entrylist/brokenlink.lnk");
#endif

#ifdef Q_WS_MAC
    if (qstrcmp(QTest::currentDataTag(), "unprintablenames") == 0)
        QSKIP("p4 doesn't sync the files with the unprintable names properly on Mac",SkipSingle);
#endif
    QDir dir(dirName);
    QVERIFY(dir.exists());

    QStringList actual = dir.entryList(nameFilters, (QDir::Filters)filterspec,
                                       (QDir::SortFlags)sortspec);

    int max = qMin(actual.count(), expected.count());

    if (qstrcmp(QTest::currentDataTag(), "unprintablenames") == 0) {
        // The purpose of this entry is to check that QDir doesn't
        // lock up. The actual result depends on the file system.
        return;
    }

    for (int i=0; i<max; ++i)
        QCOMPARE(actual[i], expected[i]);

    QCOMPARE(actual.count(), expected.count());

    QFile::remove(SRCDIR "entrylist/writable");
    QFile::remove(SRCDIR "entrylist/linktofile");
    QFile::remove(SRCDIR "entrylist/linktodirectory");
    QFile::remove(SRCDIR "entrylist/linktofile.lnk");
    QFile::remove(SRCDIR "entrylist/linktodirectory.lnk");
    QFile::remove(SRCDIR "entrylist/brokenlink.lnk");
    QFile::remove(SRCDIR "entrylist/brokenlink");
}

void tst_QDir::entryListSimple_data()
{
    QTest::addColumn<QString>("dirName");
    QTest::addColumn<int>("countMin");

    QTest::newRow("data2") << "do_not_expect_this_path_to_exist/" << 0;
#if defined(Q_OS_WINCE)
    QTest::newRow("simple dir") << SRCDIR "resources" << 0;
    QTest::newRow("simple dir with slash") << SRCDIR "resources/" << 0;
#else
    QTest::newRow("simple dir") << SRCDIR "resources" << 2;
    QTest::newRow("simple dir with slash") << SRCDIR "resources/" << 2;
#endif

#if defined(Q_OS_WIN) && !defined(Q_OS_WINCE)
    QTest::newRow("unc 1") << "//"  + QtNetworkSettings::winServerName() << 2;
    QTest::newRow("unc 2") << "//"  + QtNetworkSettings::winServerName() + "/" << 2;
    QTest::newRow("unc 3") << "//"  + QtNetworkSettings::winServerName() + "/testshare" << 2;
    QTest::newRow("unc 4") << "//"  + QtNetworkSettings::winServerName() + "/testshare/" << 2;
    QTest::newRow("unc 5") << "//"  + QtNetworkSettings::winServerName() + "/testshare/tmp" << 2;
    QTest::newRow("unc 6") << "//"  + QtNetworkSettings::winServerName() + "/testshare/tmp/" << 2;
    QTest::newRow("unc 7") << "//"  + QtNetworkSettings::winServerName() + "/testshare/adirthatshouldnotexist" << 0;
    QTest::newRow("unc 8") << "//"  + QtNetworkSettings::winServerName() + "/asharethatshouldnotexist" << 0;
    QTest::newRow("unc 9") << "//ahostthatshouldnotexist" << 0;
#endif
}

void tst_QDir::entryListSimple()
{
    QFETCH(QString, dirName);
    QFETCH(int, countMin);

    QDir dir(dirName);
    QStringList actual = dir.entryList();
    QVERIFY(actual.count() >= countMin);
}

void tst_QDir::entryListWithSymLinks()
{
    QFile::remove("myLinkToDir.lnk");
    QFile::remove("myLinkToFile.lnk");
    QFile::remove("testfile.cpp");
    QDir dir;
    dir.mkdir("myDir");
    QFile("testfile.cpp").open(QIODevice::WriteOnly);
    QVERIFY(QFile::link("myDir", "myLinkToDir.lnk"));
    QVERIFY(QFile::link("testfile.cpp", "myLinkToFile.lnk"));

    {
        QStringList entryList = QDir().entryList();
        QVERIFY(entryList.contains("myDir"));
        QVERIFY(entryList.contains("myLinkToDir.lnk"));
        QVERIFY(entryList.contains("myLinkToFile.lnk"));
    }
    {
        QStringList entryList = QDir().entryList(QDir::Dirs);
        QVERIFY(entryList.contains("myDir"));
        QVERIFY(entryList.contains("myLinkToDir.lnk"));
        QVERIFY(!entryList.contains("myLinkToFile.lnk"));
    }
    {
        QStringList entryList = QDir().entryList(QDir::Dirs | QDir::NoSymLinks);
        QVERIFY(entryList.contains("myDir"));
        QVERIFY(!entryList.contains("myLinkToDir.lnk"));
        QVERIFY(!entryList.contains("myLinkToFile.lnk"));
    }

    QFile::remove("myLinkToDir.lnk");
    QFile::remove("myLinkToFile.lnk");
    QFile::remove("testfile.cpp");
    dir.rmdir("myDir");
}

void tst_QDir::canonicalPath_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<QString>("canonicalPath");
    QString appPath = SRCDIR;
    if (appPath.isEmpty())
        appPath = QCoreApplication::instance()->applicationDirPath();
    else
        appPath.chop(1);        // remove the ending slash

#if defined Q_WS_WIN
    if (appPath.endsWith("release", Qt::CaseInsensitive) || appPath.endsWith("debug", Qt::CaseInsensitive)) {
        QDir appDir(appPath);
        QVERIFY(appDir.cdUp());
        appPath = appDir.absolutePath();
    }
#endif

	QTest::newRow("relative") << "." << appPath;
    QTest::newRow("relativeSubDir") << "./testData/../testData" << appPath + "/testData";

#ifndef Q_WS_WIN
    QTest::newRow("absPath") << appPath + "/testData/../testData" << appPath + "/testData";
#else
    QTest::newRow("absPath") << appPath + "\\testData\\..\\testData" << appPath + "/testData";
#endif
    QTest::newRow("nonexistant") << "testd" << QString();
}

void tst_QDir::canonicalPath()
{
    QDir srcPath;
    if (strlen(SRCDIR) > 0)
        srcPath = QDir(SRCDIR);
    else
        srcPath = QDir(".");
    if (srcPath.absolutePath() != srcPath.canonicalPath())
        QSKIP("This test does not work if this directory path consists of symlinks.", SkipAll);

    QString oldpwd = QDir::currentPath();
    QDir::setCurrent(srcPath.absolutePath());

    QFETCH(QString, path);
    QFETCH(QString, canonicalPath);

    QDir dir(path);
#ifdef Q_OS_WIN
    QCOMPARE(dir.canonicalPath().toLower(), canonicalPath.toLower());
#else
    QCOMPARE(dir.canonicalPath(), canonicalPath);
#endif

    QDir::setCurrent(oldpwd);
}

void tst_QDir::current_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<QString>("currentDir");
    QString appPath = SRCDIR;
    if (appPath.isEmpty())
        appPath = QCoreApplication::instance()->applicationDirPath();
    else
        appPath.chop(1);        // remove the ending slash
#if defined Q_WS_WIN
	if (appPath.endsWith("release", Qt::CaseInsensitive))
		appPath = appPath.left(appPath.length()-8);
    else if (appPath.endsWith("debug", Qt::CaseInsensitive))
		appPath = appPath.left(appPath.length()-6);
#endif

    QTest::newRow("startup") << QString() << appPath;
    QTest::newRow("relPath") << "testData" << appPath + "/testData";
#ifndef Q_WS_WIN
    QTest::newRow("absPath") << appPath + "/testData" << appPath + "/testData";
#else
    QTest::newRow("absPath") << appPath + "\\testData" << appPath + "/testData";
#endif
    QTest::newRow("nonexistant") << "testd" << QString();

    QTest::newRow("parent") << ".." << appPath.left(appPath.lastIndexOf('/'));
}

void tst_QDir::current()
{
    QString oldDir = QDir::currentPath();
    QString appPath = SRCDIR;
    if (appPath.isEmpty())
        appPath = QCoreApplication::instance()->applicationDirPath();
    QDir::setCurrent(appPath);
    QFETCH(QString, path);
    QFETCH(QString, currentDir);

    if (!path.isEmpty()) {
        bool b = QDir::setCurrent(path);
        // If path is non existant, then setCurrent should be false (currentDir is empty in testData)
        QVERIFY(b == !currentDir.isEmpty());
    }
    if (!currentDir.isEmpty()) {
        QDir newCurrent = QDir::current();
        QDir::setCurrent(oldDir);
#ifdef Q_OS_WIN
	QCOMPARE(newCurrent.absolutePath().toLower(), currentDir.toLower());
#else
	QCOMPARE(newCurrent.absolutePath(), currentDir);
#endif
    }

    QDir::setCurrent(oldDir);
}

void tst_QDir::cd_data()
{
    QTest::addColumn<QString>("startDir");
    QTest::addColumn<QString>("cdDir");
    QTest::addColumn<bool>("successExpected");
    QTest::addColumn<QString>("newDir");

    QString appPath = QDir::currentPath();
	int index = appPath.lastIndexOf("/");
	QTest::newRow("cdUp") << QDir::currentPath() << ".." << true << appPath.left(index==0?1:index);
    QTest::newRow("noChange") << QDir::currentPath() << "." << true << appPath;
#ifdef Q_OS_WIN // on windows QDir::root() is usually c:/ but cd "/" will not force it to be root
    QTest::newRow("absolute") << QDir::currentPath() << "/" << true << "/";
#else
    QTest::newRow("absolute") << QDir::currentPath() << "/" << true << QDir::root().absolutePath();
#endif
    QTest::newRow("non existant") << "." << "../anonexistingdir" << false << QDir::currentPath();
    QTest::newRow("self") << "." << (QString("../") + QFileInfo(QDir::currentPath()).fileName()) << true << QDir::currentPath();
    QTest::newRow("file") << "." << "qdir.pro" << false << "";
}

void tst_QDir::cd()
{
    QFETCH(QString, startDir);
    QFETCH(QString, cdDir);
    QFETCH(bool, successExpected);
    QFETCH(QString, newDir);

    QDir d = startDir;
    QCOMPARE(d.cd(cdDir), successExpected);
    if (successExpected)
        QCOMPARE(d.absolutePath(), newDir);
}

void tst_QDir::setNameFilters_data()
{
    // Effectively copied from entryList2() test

    QTest::addColumn<QString>("dirName"); // relative from current path or abs
    QTest::addColumn<QStringList>("nameFilters");
    QTest::addColumn<QStringList>("expected");

    QString appPath = SRCDIR;
    if (appPath.isEmpty())
        appPath = QCoreApplication::instance()->applicationDirPath();
    if (!appPath.endsWith("/"))
        appPath.append("/");

    QTest::newRow("spaces1") << appPath + "testdir/spaces" << QStringList("*. bar")
                          << QStringList("foo. bar");
    QTest::newRow("spaces2") << appPath + "testdir/spaces" << QStringList("*.bar")
			              << QStringList("foo.bar");
    QTest::newRow("spaces3") << appPath + "testdir/spaces" << QStringList("foo.*")
			  			  << QString("foo. bar,foo.bar").split(",");
    QTest::newRow("files1")  << appPath + "testdir/dir" << QString("*r.cpp *.pro").split(" ")
						  << QString("qdir.pro,qrc_qdir.cpp,tst_qdir.cpp").split(",");
    QTest::newRow("resources1") << QString(":/tst_qdir/resources/entryList") << QStringList("*.data")
                             << QString("file1.data,file2.data,file3.data").split(',');
}

void tst_QDir::setNameFilters()
{
    QFETCH(QString, dirName);
    QFETCH(QStringList, nameFilters);
    QFETCH(QStringList, expected);

    QDir dir(dirName);
    QVERIFY(dir.exists());

    dir.setNameFilters(nameFilters);
    QStringList actual = dir.entryList();
    int max = qMin(actual.count(), expected.count());

    for (int i=0; i<max; ++i)
        QCOMPARE(actual[i], expected[i]);
    QCOMPARE(actual.count(), expected.count());
}

void
tst_QDir::cleanPath_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<QString>("expected");

    QTest::newRow("data0") << "/Users/sam/troll/qt4.0//.." << "/Users/sam/troll";
    QTest::newRow("data1") << "/Users/sam////troll/qt4.0//.." << "/Users/sam/troll";
    QTest::newRow("data2") << "/" << "/";
    QTest::newRow("data3") << QDir::cleanPath("../.") << "..";
    QTest::newRow("data4") << QDir::cleanPath("../..") << "../..";
#if !defined(Q_OS_WINCE)
#if defined Q_OS_WIN
    QTest::newRow("data5") << "d:\\a\\bc\\def\\.." << "d:/a/bc";
    QTest::newRow("data6") << "d:\\a\\bc\\def\\../../.." << "d:/";
#else
    QTest::newRow("data5") << "d:\\a\\bc\\def\\.." << "d:\\a\\bc\\def\\..";
    QTest::newRow("data6") << "d:\\a\\bc\\def\\../../.." << "d:\\a\\bc\\def\\../../..";
#endif
#endif
    QTest::newRow("data7") << ".//file1.txt" << "file1.txt";
    QTest::newRow("data8") << "/foo/bar/..//file1.txt" << "/foo/file1.txt";
    QTest::newRow("data9") << "//" << "/";
}


void
tst_QDir::cleanPath()
{
    QFETCH(QString, path);
    QFETCH(QString, expected);
    QString cleaned = QDir::cleanPath(path);
    QCOMPARE(cleaned, expected);
}

void tst_QDir::absoluteFilePath_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<QString>("expectedFilePath");

    QTest::newRow("0") << "/etc" << "/passwd" << "/passwd";
    QTest::newRow("1") << "/etc" << "passwd" << "/etc/passwd";
    QTest::newRow("2") << "/" << "passwd" << "/passwd";
    QTest::newRow("3") << "relative" << "path" << QDir::currentPath() + "/relative/path";
    QTest::newRow("4") << "" << "" << QDir::currentPath();
}

void tst_QDir::absoluteFilePath()
{
    QFETCH(QString, path);
    QFETCH(QString, fileName);
    QFETCH(QString, expectedFilePath);

    QDir dir(path);
    QString absFilePath = dir.absoluteFilePath(fileName);
    QCOMPARE(absFilePath, expectedFilePath);
}

void tst_QDir::absolutePath_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<QString>("expectedPath");

    QTest::newRow("0") << "/machine/share/dir1" << "/machine/share/dir1";
#if defined(Q_OS_WIN) && !defined(Q_OS_WINCE)
    QTest::newRow("1") << "\\machine\\share\\dir1" << "/machine/share/dir1";
    QTest::newRow("2") << "//machine/share/dir1" << "//machine/share/dir1";
    QTest::newRow("3") << "\\\\machine\\share\\dir1" << "//machine/share/dir1";
    QTest::newRow("4") << "c:/machine/share/dir1" << "c:/machine/share/dir1";
    QTest::newRow("5") << "c:\\machine\\share\\dir1" << "c:/machine/share/dir1";
#endif
}

void tst_QDir::absolutePath()
{
    QFETCH(QString, path);
    QFETCH(QString, expectedPath);

    QDir dir(path);
    QCOMPARE(dir.absolutePath(), expectedPath);
}

void tst_QDir::relativeFilePath_data()
{
    QTest::addColumn<QString>("dir");
    QTest::addColumn<QString>("path");
    QTest::addColumn<QString>("expected");

    QTest::newRow("0") << "/foo/bar" << "ding.txt" << "ding.txt";
    QTest::newRow("1") << "/foo/bar" << "ding/dong.txt"    << "ding/dong.txt";
    QTest::newRow("2") << "/foo/bar" << "../ding/dong.txt" << "../ding/dong.txt";

    QTest::newRow("3") << "/foo/bar" << "/foo/bar/ding.txt" << "ding.txt";
    QTest::newRow("4") << "/foo/bar/" << "/foo/bar/ding/dong.txt" << "ding/dong.txt";
    QTest::newRow("5") << "/foo/bar/" << "/ding/dong.txt" << "../../ding/dong.txt";

    QTest::newRow("6") << "/" << "/ding/dong.txt" << "ding/dong.txt";
    QTest::newRow("7") << "/" << "/ding/" << "ding";
    QTest::newRow("8") << "/" << "/ding//" << "ding";
    QTest::newRow("9") << "/" << "/ding/../dong" << "dong";
    QTest::newRow("10") << "/" << "/ding/../../../../dong" << "../../../dong";

    QTest::newRow("11") << "" << "" << "";

#if defined(Q_OS_WIN) && !defined(Q_OS_WINCE)
    QTest::newRow("12") << "C:/foo/bar" << "ding" << "ding";
    QTest::newRow("13") << "C:/foo/bar" << "C:/ding/dong" << "../../ding/dong";
    QTest::newRow("14") << "C:/foo/bar" << "/ding/dong" << "../../ding/dong";
    QTest::newRow("15") << "C:/foo/bar" << "D:/ding/dong" << "D:/ding/dong";
    QTest::newRow("16") << "C:" << "C:/ding/dong" << "ding/dong";
    QTest::newRow("16") << "C:/" << "C:/ding/dong" << "ding/dong";
    QTest::newRow("17") << "C:" << "C:" << "";
    QTest::newRow("18") << "C:/" << "C:" << "";
    QTest::newRow("19") << "C:" << "C:/" << "";
    QTest::newRow("20") << "C:/" << "C:/" << "";
    QTest::newRow("17") << "C:" << "C:file.txt" << "file.txt";
    QTest::newRow("18") << "C:/" << "C:file.txt" << "file.txt";
    QTest::newRow("19") << "C:" << "C:/file.txt" << "file.txt";
    QTest::newRow("20") << "C:/" << "C:/file.txt" << "file.txt";
    QTest::newRow("21") << "C:" << "D:" << "D:";
    QTest::newRow("22") << "C:" << "D:/" << "D:/";
    QTest::newRow("23") << "C:/" << "D:" << "D:";
    QTest::newRow("24") << "C:/" << "D:/" << "D:/";
    QTest::newRow("25") << "C:/foo/bar" << "//anotherHost/foo/bar" << "//anotherHost/foo/bar";
    QTest::newRow("26") << "//anotherHost/foo" << "//anotherHost/foo/bar" << "bar";
    QTest::newRow("27") << "//anotherHost/foo" << "bar" << "bar";
    QTest::newRow("28") << "//anotherHost/foo" << "C:/foo/bar" << "C:/foo/bar";
#endif
}

void tst_QDir::relativeFilePath()
{
    QFETCH(QString, dir);
    QFETCH(QString, path);
    QFETCH(QString, expected);

    QCOMPARE(QDir(dir).relativeFilePath(path), expected);
}

void tst_QDir::filePath_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<QString>("expectedFilePath");

    QTest::newRow("0") << "/etc" << "/passwd" << "/passwd";
    QTest::newRow("1") << "/etc" << "passwd" << "/etc/passwd";
    QTest::newRow("2") << "/" << "passwd" << "/passwd";
    QTest::newRow("3") << "relative" << "path" << "relative/path";
    QTest::newRow("4") << "" << "" << ".";
}

void tst_QDir::filePath()
{
    QFETCH(QString, path);
    QFETCH(QString, fileName);
    QFETCH(QString, expectedFilePath);

    QDir dir(path);
    QString absFilePath = dir.filePath(fileName);
    QCOMPARE(absFilePath, expectedFilePath);
}

void tst_QDir::remove()
{
    QFile f("remove-test");
    f.open(QIODevice::WriteOnly);
    f.close();
    QDir dir;
    QVERIFY(dir.remove("remove-test"));
    QVERIFY(!dir.remove("/remove-test"));
}

void tst_QDir::rename()
{
    QFile f("rename-test");
    f.open(QIODevice::WriteOnly);
    f.close();
    QDir dir;
    QVERIFY(dir.rename("rename-test", "rename-test-renamed"));
    QVERIFY(dir.rename("rename-test-renamed", "rename-test"));
#if defined(Q_OS_MAC)
    QVERIFY(!dir.rename("rename-test", "/etc/rename-test-renamed"));
#elif !defined(Q_OS_WIN) // on windows this is possible maybe make the test a bit better
    QVERIFY(!dir.rename("rename-test", "/rename-test-renamed"));
#endif
    QVERIFY(dir.remove("rename-test"));
}

void tst_QDir::exists2_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<bool>("exists");

    QTest::newRow("0") << "." << true;
    QTest::newRow("1") << "/" << true;
    QTest::newRow("2") << "" << false;
    QTest::newRow("3") << "testData" << true;
    QTest::newRow("4") << "/testData" << false;
    QTest::newRow("5") << "tst_qdir.cpp" << true;
    QTest::newRow("6") << "/resources.cpp" << false;
}

void tst_QDir::exists2()
{
    QFETCH(QString, path);
    QFETCH(bool, exists);

    QString oldpwd = QDir::currentPath();
    if (strlen(SRCDIR) > 0)
        QDir::setCurrent(SRCDIR);

    if (path.isEmpty())
        QTest::ignoreMessage(QtWarningMsg, "QDir::exists: Empty or null file name");

    QDir dir;
    if (exists)
        QVERIFY(dir.exists(path));
    else
        QVERIFY(!dir.exists(path));

    QDir::setCurrent(oldpwd);
}

void tst_QDir::dirName_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<QString>("dirName");

    QTest::newRow("slash0") << "c:/winnt/system32" << "system32";
    QTest::newRow("slash1") << "/winnt/system32" << "system32";
    QTest::newRow("slash2") << "c:/winnt/system32/kernel32.dll" << "kernel32.dll";
#ifdef Q_OS_WIN
    QTest::newRow("bslash0") << "c:\\winnt\\system32" << "system32";
    QTest::newRow("bslash1") << "\\winnt\\system32" << "system32";
    QTest::newRow("bslash2") << "c:\\winnt\\system32\\kernel32.dll" << "kernel32.dll";
#endif
}

void tst_QDir::dirName()
{
    QFETCH(QString, path);
    QFETCH(QString, dirName);

    QDir dir(path);
    QCOMPARE(dir.dirName(), dirName);
}

void tst_QDir::operator_eq()
{
    QDir dir1(".");
    dir1 = dir1;
    dir1.setPath("..");
}

void tst_QDir::dotAndDotDot()
{
#ifdef Q_OS_WINCE
	QSKIP("WinCE does not have . nor ..", SkipAll);
#endif
    QDir dir(QString(SRCDIR "testdir/"));
    QStringList entryList = dir.entryList(QDir::Dirs);
    QCOMPARE(entryList, QStringList() << QString(".") << QString("..") << QString("dir") << QString("spaces"));
    entryList = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    QCOMPARE(entryList, QStringList() << QString("dir") << QString("spaces"));
}

#ifdef QT3_SUPPORT
/*
    Tets that the setMatchAllDirs setting survies a call to setFilter.
*/
void tst_QDir::matchAllDirs()
{
    QDir dir("/");
    dir.setMatchAllDirs(true);
    dir.setNameFilters(QStringList() << "*.foo");
    dir.setFilter(QDir::Hidden);
    QVERIFY(dir.matchAllDirs());
    QVERIFY(dir.entryList().count() > 0);
    dir.setMatchAllDirs(false);
    dir.setFilter(QDir::Hidden);
    QVERIFY(dir.matchAllDirs() == false);
    QCOMPARE(dir.entryList().count(), 0);

}
#endif

void tst_QDir::homePath()
{
    QDir homeDir = QDir::home();
    QString strHome = QDir::homePath();

    // docs say that homePath() is an absolute path
    QCOMPARE(strHome, homeDir.absolutePath());
    QVERIFY(QDir::isAbsolutePath(strHome));

#ifdef Q_OS_UNIX
    if (strHome.length() > 1)      // root dir = "/"
        QVERIFY(!strHome.endsWith('/'));
#elif defined(Q_OS_WIN)
    if (strHome.length() > 3)      // root dir = "c:/"; "//" is not really valid...
        QVERIFY(!strHome.endsWith('/'));
#endif

    QStringList entries = homeDir.entryList();
    for (int i = 0; i < entries.count(); ++i) {
        QFileInfo fi(QDir::homePath() + "/" + entries[i]);
        QCOMPARE(fi.exists(), true);
    }
}

void tst_QDir::tempPath()
{
    QDir dir = QDir::temp();
    QString path = QDir::tempPath();

    // docs say that tempPath() is an absolute path
    QCOMPARE(path, dir.absolutePath());
    QVERIFY(QDir::isAbsolutePath(path));

#ifdef Q_OS_UNIX
    if (path.length() > 1)      // root dir = "/"
        QVERIFY(!path.endsWith('/'));
#elif defined(Q_OS_WIN)
    if (path.length() > 3)      // root dir = "c:/"; "//" is not really valid...
        QVERIFY(!path.endsWith('/'));
#endif
}

void tst_QDir::rootPath()
{
    QDir dir = QDir::root();
    QString path = QDir::rootPath();

    // docs say that tempPath() is an absolute path
    QCOMPARE(path, dir.absolutePath());
    QVERIFY(QDir::isAbsolutePath(path));

#ifdef Q_OS_UNIX
    QCOMPARE(path, QString("/"));
#endif
}

void tst_QDir::nativeSeparators()
{
#ifdef Q_OS_WIN
    QCOMPARE(QDir::toNativeSeparators(QLatin1String("/")), QString("\\"));
    QCOMPARE(QDir::toNativeSeparators(QLatin1String("\\")), QString("\\"));
    QCOMPARE(QDir::fromNativeSeparators(QLatin1String("/")), QString("/"));
    QCOMPARE(QDir::fromNativeSeparators(QLatin1String("\\")), QString("/"));
#else
    QCOMPARE(QDir::toNativeSeparators(QLatin1String("/")), QString("/"));
    QCOMPARE(QDir::toNativeSeparators(QLatin1String("\\")), QString("\\"));
    QCOMPARE(QDir::fromNativeSeparators(QLatin1String("/")), QString("/"));
    QCOMPARE(QDir::fromNativeSeparators(QLatin1String("\\")), QString("\\"));
#endif
}

void tst_QDir::searchPaths_data()
{
    QTest::addColumn<QString>("filename");
    QTest::addColumn<QString>("searchPathPrefixes");
    QTest::addColumn<QString>("searchPaths");
    QTest::addColumn<QString>("expectedAbsolutePath");

    QString srcdir = SRCDIR;
    if (srcdir.isEmpty())
        srcdir = QDir::currentPath();
    else
        srcdir.chop(1);         // remove ending slash
    QString searchDir = srcdir + "/searchdir";

    // sanity
    QTest::newRow("nopath") << "picker.png" << QString() << QString() << QString();
    QTest::newRow("emptysearchpath") << "subdir1/picker.png" << QString() << QString() << QString();
    QTest::newRow("searchpathwithoutprefix") << SRCDIR "searchdir/subdir1/picker.png" << QString("searchpath") << QString("searchdir") << (searchDir+"/subdir1/picker.png");

    // new
    QTest::newRow("novalidsearchpath") << "searchpath:subdir1/picker.png" << QString() << QString() << QString();
    QTest::newRow("invalidsearchpath") << "searchpath:subdir1/picker.png" << QString("invalid") << QString("invalid") << QString();
    QTest::newRow("onlyvalidsearchpath") << "searchpath:subdir1/picker.png" << QString("searchpath") << QString(SRCDIR "searchdir") << (searchDir+"/subdir1/picker.png");
    QTest::newRow("validandinvalidsearchpath") << "searchpath:subdir1/picker.png" << QString("invalid;searchpath") << QString("invalid;" SRCDIR "searchdir") << (searchDir+"/subdir1/picker.png");
    QTest::newRow("precedence1") << "searchpath:picker.png" << QString("invalid;searchpath") << QString("invalid;" SRCDIR "searchdir/subdir1," SRCDIR "searchdir/subdir2") << (searchDir+"/subdir1/picker.png");
    QTest::newRow("precedence2") << "searchpath:picker.png" << QString("invalid;searchpath") << QString("invalid;" SRCDIR "searchdir/subdir2," SRCDIR "searchdir/subdir1") << (searchDir+"/subdir2/picker.png");
    QTest::newRow("precedence3") << "searchpath2:picker.png" << QString("searchpath1;searchpath2") << QString(SRCDIR "searchdir/subdir1;" SRCDIR "searchdir/subdir2") << (searchDir+"/subdir2/picker.png");

    // re
}

void tst_QDir::searchPaths()
{
    QFETCH(QString, filename);
    QFETCH(QString, searchPathPrefixes);
    QStringList searchPathPrefixList = searchPathPrefixes.split(";", QString::SkipEmptyParts);
    QFETCH(QString, searchPaths);
    QStringList searchPathsList = searchPaths.split(";", QString::SkipEmptyParts);
    QFETCH(QString, expectedAbsolutePath);
    bool exists = !expectedAbsolutePath.isEmpty();

    for (int i = 0; i < searchPathPrefixList.count(); ++i) {
        QDir::setSearchPaths(searchPathPrefixList.at(i), searchPathsList.at(i).split(","));
    }
    for (int i = 0; i < searchPathPrefixList.count(); ++i) {
        QVERIFY(QDir::searchPaths(searchPathPrefixList.at(i)) == searchPathsList.at(i).split(","));
    }

    QCOMPARE(QFile(filename).exists(), exists);
    QCOMPARE(QFileInfo(filename).exists(), exists);

    if (exists) {
        QCOMPARE(QFileInfo(filename).absoluteFilePath(), expectedAbsolutePath);
    }

    for (int i = 0; i < searchPathPrefixList.count(); ++i) {
        QDir::setSearchPaths(searchPathPrefixList.at(i), QStringList());
    }
    for (int i = 0; i < searchPathPrefixList.count(); ++i) {
        QVERIFY(QDir::searchPaths(searchPathPrefixList.at(i)).isEmpty());
    }
}

void tst_QDir::entryListWithSearchPaths()
{
    QDir realDir(":/tst_qdir/resources/entryList");
    QVERIFY(realDir.exists());
    QVERIFY(!realDir.entryList().isEmpty());
    QVERIFY(realDir.entryList().contains("file3.data"));

    QDir::setSearchPaths("searchpath", QStringList(":/tst_qdir/resources"));
    QDir dir("searchpath:entryList/");
    QCOMPARE(dir.path(), QString(":/tst_qdir/resources/entryList"));
    QVERIFY(dir.exists());
    QStringList entryList = dir.entryList();
    QVERIFY(entryList.contains("file3.data"));
}

void tst_QDir::longFileName_data()
{
    QTest::addColumn<int>("length");

    QTest::newRow("128") << 128;
    QTest::newRow("256") << 256;
    QTest::newRow("512") << 512;
    QTest::newRow("1024") << 1024;
    QTest::newRow("2048") << 2048;
    QTest::newRow("4096") << 4096;
}

void tst_QDir::longFileName()
{
    QFETCH(int, length);

    QString fileName(length, QLatin1Char('a'));
    fileName += QLatin1String(".txt");

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly))
        QSKIP("Cannot create long file names", SkipAll);

    QFile file2(fileName);
    QVERIFY(file2.open(QFile::ReadOnly));

    QVERIFY(QDir().entryList().contains(fileName));

    file.close();
    file2.close();

    QFile::remove(fileName);
}

QTEST_MAIN(tst_QDir)
#include "tst_qdir.moc"

