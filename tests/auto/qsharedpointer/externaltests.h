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


#ifndef QTEST_EXTERNAL_TESTS_H
#define QTEST_EXTERNAL_TESTS_H

#include <QList>
#include <QByteArray>

QT_BEGIN_NAMESPACE
namespace QTest {
    class QExternalTestPrivate;
    class QExternalTest
    {
    public:
        QExternalTest();
        ~QExternalTest();

        enum Stage {
            FileStage,
            QmakeStage,
            CompilationStage,
            LinkStage,
            RunStage
        };

        enum QtModule {
            QtCore      = 0x0001,
            QtGui       = 0x0002,
            QtNetwork   = 0x0004,
            QtXml       = 0x0008,
            QtXmlPatterns=0x0010,
            QtOpenGL    = 0x0020,
            QtSql       = 0x0040,
            Qt3Support  = 0x0080,
            QtSvg       = 0x0100,
            QtScript    = 0x0200,
            QtTest      = 0x0400,
            QtDBus      = 0x0800,
            QtWebKit    = 0x1000,
            Phonon      = 0x2000 // odd man out
        };
        Q_DECLARE_FLAGS(QtModules, QtModule)

        enum ApplicationType {
            AutoApplication,
            Applicationless,
            QCoreApplication,
            QApplicationTty,
            QApplicationGuiClient,
            QApplicationGuiServer
        };

        bool isDebugMode() const;
        void setDebugMode(bool enable);

        QList<QByteArray> qmakeSettings() const;
        void setQmakeSettings(const QList<QByteArray> &settings);

        QtModules qtModules() const;
        void setQtModules(QtModules modules);

        ApplicationType applicationType() const;
        void setApplicationType(ApplicationType type);

        QByteArray programHeader() const;
        void setProgramHeader(const QByteArray &header);

        // execution:
        bool tryCompile(const QByteArray &body);
        bool tryLink(const QByteArray &body);
        bool tryRun(const QByteArray &body);
        bool tryCompileFail(const QByteArray &body);
        bool tryLinkFail(const QByteArray &body);
        bool tryRunFail(const QByteArray &body);

        Stage failedStage() const;
        int exitCode() const;
        QByteArray fullProgramSource() const;
        QByteArray standardOutput() const;
        QByteArray standardError() const;

        QString errorReport() const;

    private:
        QExternalTestPrivate * const d;
    };

    Q_DECLARE_OPERATORS_FOR_FLAGS(QExternalTest::QtModules)
}
QT_END_NAMESPACE

#endif
