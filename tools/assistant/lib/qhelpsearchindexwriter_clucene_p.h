/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Assistant of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
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
** additional rights.  These rights are described in the Nokia Qt LGPL
** Exception version 1.1, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QHELPSEARCHINDEXWRITERCLUCENE_H
#define QHELPSEARCHINDEXWRITERCLUCENE_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API. It exists for the convenience
// of the help generator tools. This header file may change from version
// to version without notice, or even be removed.
//
// We mean it.
//

#include "qhelpenginecore.h"
#include "fulltextsearch/qanalyzer_p.h"

#include <QtCore/QUrl>
#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <QtCore/QStringList>
#include <QtCore/QWaitCondition>

QT_BEGIN_NAMESPACE

class QCLuceneIndexWriter;

namespace qt {
    namespace fulltextsearch {
        namespace clucene {

class QHelpSearchIndexWriter : public QThread
{
    Q_OBJECT

public:
    QHelpSearchIndexWriter();
    ~QHelpSearchIndexWriter();

    void cancelIndexing();
    void updateIndex(const QString &collectionFile,
        const QString &indexFilesFolder, bool reindex);
    void optimizeIndex();

signals:
    void indexingStarted();
    void indexingFinished();

private:
    void run();

    bool addDocuments(const QList<QUrl> docFiles, const QHelpEngineCore &engine,
        const QStringList &attributes, const QString &namespaceName,
        QCLuceneIndexWriter *writer, QCLuceneAnalyzer &analyzer);
    void removeDocuments(const QString &indexPath, const QString &namespaceName);

    bool writeIndexMap(QHelpEngineCore& engine,
        const QMap<QString, QDateTime>& indexMap);

    QList<QUrl> indexableFiles(QHelpEngineCore *helpEngine,
        const QString &namespaceName, const QStringList &attributes) const;

private:
    QMutex mutex;
    QWaitCondition waitCondition;

    bool m_cancel;
    bool m_reindex;
    QString m_collectionFile;
    QString m_indexFilesFolder;
};

        }   // namespace clucene
    }   // namespace fulltextsearch
}   // namespace clucene

QT_END_NAMESPACE

#endif  // QHELPSEARCHINDEXWRITERCLUCENE_H
