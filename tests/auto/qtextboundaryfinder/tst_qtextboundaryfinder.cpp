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

#include <qtextboundaryfinder.h>
#include <qfile.h>
#include <qdebug.h>

//TESTED_CLASS=
//TESTED_FILES=gui/text/qtextlayout.h corelib/tools/qtextboundaryfinder.cpp

class tst_QTextBoundaryFinder : public QObject
{
    Q_OBJECT

public:
    tst_QTextBoundaryFinder();
    virtual ~tst_QTextBoundaryFinder();


public slots:
    void init();
    void cleanup();
private slots:
    void graphemeBoundaries();
    void wordBoundaries();
    void sentenceBoundaries();
    void isAtWordStart();
    void fastConstructor();
    void isAtBoundaryLine();
};

tst_QTextBoundaryFinder::tst_QTextBoundaryFinder()
{
}

tst_QTextBoundaryFinder::~tst_QTextBoundaryFinder()
{
}

void tst_QTextBoundaryFinder::init()
{
#ifndef Q_OS_IRIX
    QDir::setCurrent(SRCDIR);
#endif
}

void tst_QTextBoundaryFinder::cleanup()
{
}

void tst_QTextBoundaryFinder::graphemeBoundaries()
{
    QFile file("data/GraphemeBreakTest.txt");
    file.open(QFile::ReadOnly);

    int lines = 0;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (line.startsWith('#'))
            continue;

        lines++;
        QString test = QString::fromUtf8(line);
        int hash = test.indexOf('#');
        if (hash > 0)
            test = test.left(hash);
        test = test.simplified();
        test = test.replace(QLatin1String(" "), QString());

        QList<int> breakPositions;
        QString testString;
        int pos = 0;
        int strPos = 0;
        while (pos < test.length()) {
            if (test.at(pos).unicode() == 0xf7)
                breakPositions.append(strPos);
            else
                Q_ASSERT(test.at(pos).unicode() == 0xd7);
            ++pos;
            if (pos < test.length()) {
                Q_ASSERT(pos < test.length() - 4);
                QString hex = test.mid(pos, 4);
                bool ok = true;
                testString.append(QChar(hex.toInt(&ok, 16)));
                Q_ASSERT(ok);
                pos += 4;
            }
            ++strPos;
        }

        QTextBoundaryFinder finder(QTextBoundaryFinder::Grapheme, testString);
        for (int i = 0; i < breakPositions.size(); ++i) {
            QCOMPARE(finder.position(), breakPositions.at(i));
            finder.toNextBoundary();
        }
        QCOMPARE(finder.toNextBoundary(), -1);

        for (int i = 0; i < testString.length(); ++i) {
            finder.setPosition(i);
            QCOMPARE(finder.isAtBoundary(), breakPositions.contains(i) == true);
        }
    }
    QCOMPARE(lines, 100); // to see it actually found the file and all.
}

void tst_QTextBoundaryFinder::wordBoundaries()
{
    QFile file("data/WordBreakTest.txt");
    file.open(QFile::ReadOnly);

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (line.startsWith('#'))
            continue;

        QString test = QString::fromUtf8(line);
        int hash = test.indexOf('#');
        if (hash > 0)
            test = test.left(hash);
        test = test.simplified();
        test = test.replace(QLatin1String(" "), QString());

        QList<int> breakPositions;
        QString testString;
        int pos = 0;
        int strPos = 0;
        while (pos < test.length()) {
            if (test.at(pos).unicode() == 0xf7)
                breakPositions.append(strPos);
            else
                Q_ASSERT(test.at(pos).unicode() == 0xd7);
            ++pos;
            if (pos < test.length()) {
                Q_ASSERT(pos < test.length() - 4);
                QString hex = test.mid(pos, 4);
                bool ok = true;
                testString.append(QChar(hex.toInt(&ok, 16)));
                Q_ASSERT(ok);
                pos += 4;
            }
            ++strPos;
        }

        QTextBoundaryFinder finder(QTextBoundaryFinder::Word, testString);
        for (int i = 0; i < breakPositions.size(); ++i) {
            QCOMPARE(finder.position(), breakPositions.at(i));
            finder.toNextBoundary();
        }
        QCOMPARE(finder.toNextBoundary(), -1);

        for (int i = 0; i < testString.length(); ++i) {
            finder.setPosition(i);
            QCOMPARE(finder.isAtBoundary(), breakPositions.contains(i) == true);
        }
    }
}

void tst_QTextBoundaryFinder::sentenceBoundaries()
{
    QFile file("data/SentenceBreakTest.txt");
    file.open(QFile::ReadOnly);

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (line.startsWith('#'))
            continue;

        QString test = QString::fromUtf8(line);
        int hash = test.indexOf('#');
        if (hash > 0)
            test = test.left(hash);
        test = test.simplified();
        test = test.replace(QLatin1String(" "), QString());

        QList<int> breakPositions;
        QString testString;
        int pos = 0;
        int strPos = 0;
        while (pos < test.length()) {
            if (test.at(pos).unicode() == 0xf7)
                breakPositions.append(strPos);
            else
                Q_ASSERT(test.at(pos).unicode() == 0xd7);
            ++pos;
            if (pos < test.length()) {
                Q_ASSERT(pos < test.length() - 4);
                QString hex = test.mid(pos, 4);
                bool ok = true;
                testString.append(QChar(hex.toInt(&ok, 16)));
                Q_ASSERT(ok);
                pos += 4;
            }
            ++strPos;
        }

        QTextBoundaryFinder finder(QTextBoundaryFinder::Sentence, testString);
        for (int i = 0; i < breakPositions.size(); ++i) {
            QCOMPARE(finder.position(), breakPositions.at(i));
            finder.toNextBoundary();
        }
        QCOMPARE(finder.toNextBoundary(), -1);

        for (int i = 0; i < testString.length(); ++i) {
            finder.setPosition(i);
            QCOMPARE(finder.isAtBoundary(), breakPositions.contains(i) == true);
        }
    }
}

void tst_QTextBoundaryFinder::isAtWordStart()
{
    QString txt("The quick brown fox jumped over $the lazy. dog  ");
    QList<int> start, end;
    start << 0 << 4 << 10 << 16 << 20 << 27 << 32 << 33 << 37 << 41 << 43;
    end << 3 << 9 << 15 << 19 << 26 << 31 << 33 << 36 << 41 << 42 << 46;
    QTextBoundaryFinder finder(QTextBoundaryFinder::Word, txt);
    for(int i=0; i < txt.length(); ++i) {
        finder.setPosition(i);
        QTextBoundaryFinder::BoundaryReasons r = finder.boundaryReasons();
        // qDebug() << i << r;
        QCOMPARE((r & QTextBoundaryFinder::StartWord) != 0, start.contains(i) == true);
        QCOMPARE((r & QTextBoundaryFinder::EndWord) != 0, end.contains(i) == true);
    }
}

void tst_QTextBoundaryFinder::fastConstructor()
{
    QString text("Hello World");
    QTextBoundaryFinder finder(QTextBoundaryFinder::Word, text.constData(), text.length(), /*buffer*/0, /*buffer size*/0);
    QVERIFY(finder.boundaryReasons() == QTextBoundaryFinder::StartWord);

    finder.toNextBoundary();
    QCOMPARE(finder.position(), 5);
    QVERIFY(finder.boundaryReasons() == QTextBoundaryFinder::EndWord);

    finder.toNextBoundary();
    QCOMPARE(finder.position(), 6);
    QVERIFY(finder.boundaryReasons() == QTextBoundaryFinder::StartWord);

    finder.toNextBoundary();
    QCOMPARE(finder.position(), text.length());
    QVERIFY(finder.boundaryReasons() == QTextBoundaryFinder::EndWord);

    finder.toNextBoundary();
    QVERIFY(finder.boundaryReasons() == QTextBoundaryFinder::NotAtBoundary);
    QCOMPARE(finder.position(), -1);
}

void tst_QTextBoundaryFinder::isAtBoundaryLine()
{
    // idx          0       1       2       3       4       5
    // break?       -       -       -       +       -       +
    QChar s[] = { 0x0061, 0x00AD, 0x0062, 0x0009, 0x0063, 0x0064 };
    QString text(s, sizeof(s)/sizeof(s[0]));
    qDebug() << "text = " << text << ", length = " << text.length();
    QTextBoundaryFinder finder(QTextBoundaryFinder::Line, text.constData(), text.length(), /*buffer*/0, /*buffer size*/0);
    finder.setPosition(0);
    QVERIFY(!finder.isAtBoundary());
    finder.setPosition(1);
    QVERIFY(!finder.isAtBoundary());
    finder.setPosition(2);
    QVERIFY(!finder.isAtBoundary());
    finder.setPosition(3);
    QVERIFY(finder.isAtBoundary());
    finder.setPosition(4);
    QVERIFY(!finder.isAtBoundary());
    finder.setPosition(5);
    QVERIFY(finder.isAtBoundary());
}

QTEST_MAIN(tst_QTextBoundaryFinder)
#include "tst_qtextboundaryfinder.moc"
