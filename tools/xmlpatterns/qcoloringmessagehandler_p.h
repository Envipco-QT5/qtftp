/****************************************************************************
 * ** * ** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
 * **
 * ** This file is part of the Patternist project on Trolltech Labs.  * **
 * ** $QT_BEGIN_LICENSE:LGPL$
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
 * **
 * ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * **
 * ****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Patternist_ColoringMessageHandler_h
#define Patternist_ColoringMessageHandler_h

#include <QHash>

#include "qcoloroutput_p.h"
#include "qabstractmessagehandler.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    class ColoringMessageHandler : public QAbstractMessageHandler
                                 , private ColorOutput
    {
    public:
        ColoringMessageHandler(QObject *parent = 0);

    protected:
        virtual void handleMessage(QtMsgType type,
                                   const QString &description,
                                   const QUrl &identifier,
                                   const QSourceLocation &sourceLocation);

    private:
        QString colorifyDescription(const QString &in) const;

        enum ColorType
        {
            RunningText,
            Location,
            ErrorCode,
            Keyword,
            Data
        };

        QHash<QString, ColorType> m_classToColor;
    };
}

QT_END_NAMESPACE

QT_END_HEADER

#endif
