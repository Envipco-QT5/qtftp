/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Designer of the Qt Toolkit.
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

#include <QtGui/QAction>
#include "view3d_tool.h"

QView3DTool::QView3DTool(QDesignerFormWindowInterface *formWindow, QObject *parent)
    :  QDesignerFormWindowToolInterface(parent)
{
    m_action = new QAction(tr("3DView"), this);
    m_formWindow = formWindow;
}

QDesignerFormEditorInterface *QView3DTool::core() const
{
    return m_formWindow->core();
}

QDesignerFormWindowInterface *QView3DTool::formWindow() const
{
    return m_formWindow;
}

QWidget *QView3DTool::editor() const
{
    if (m_editor == 0)
        m_editor = new QView3D(formWindow(), 0);

    return m_editor;
}

QAction *QView3DTool::action() const
{
    return m_action;
}

void QView3DTool::activated()
{
    if (m_editor != 0)
        m_editor->updateForm();
}

void QView3DTool::deactivated()
{
}

bool QView3DTool::handleEvent(QWidget*, QWidget*, QEvent*)
{
    return false;
}
