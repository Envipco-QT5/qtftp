/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
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
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include <private/qabstractpagesetupdialog_p.h>

#ifndef QT_NO_PRINTDIALOG

QT_BEGIN_NAMESPACE

// hack
class QPageSetupDialogPrivate : public QAbstractPageSetupDialogPrivate
{
};

/*!
    \enum QPageSetupDialog::PageSetupDialogOption
    \since 4.4

    Used to specify options to the page setup dialog

    This value is obsolete and does nothing since Qt 4.5:

    \value DontUseSheet In previous versions of Qt, exec() the page setup dialog
    would create a sheet by default if the dialog was given a parent.
    This is no longer supported in Qt 4.5.  If you want to use sheets, use
    QPageSetupDialog::open() instead.

    \omitvalue None
    \omitvalue OwnsPrinter
*/

/*!
    Sets the given \a option to be enabled if \a on is true;
    otherwise, clears the given \a option.

    \sa options, testOption()
*/
void QPageSetupDialog::setOption(PageSetupDialogOption option, bool on)
{
    Q_D(QPageSetupDialog);
    if (!(d->opts & option) != !on)
        setOptions(d->opts ^ option);
}

/*!
    Returns true if the given \a option is enabled; otherwise, returns
    false.

    \sa options, setOption()
*/
bool QPageSetupDialog::testOption(PageSetupDialogOption option) const
{
    Q_D(const QPageSetupDialog);
    return (d->opts & option) != 0;
}

/*!
    \property QPageSetupDialog::options
    \brief the various options that affect the look and feel of the dialog
    \since 4.5

    By default, all options are disabled.

    Options should be set before showing the dialog. Setting them while the
    dialog is visible is not guaranteed to have an immediate effect on the
    dialog (depending on the option and on the platform).

    \sa setOption(), testOption()
*/
void QPageSetupDialog::setOptions(PageSetupDialogOptions options)
{
    Q_D(QPageSetupDialog);

    PageSetupDialogOptions changed = (options ^ d->opts);
    if (!changed)
        return;

    d->opts = options;
}

QPageSetupDialog::PageSetupDialogOptions QPageSetupDialog::options() const
{
    Q_D(const QPageSetupDialog);
    return d->opts;
}

/*!
    \obsolete

    Use setOption(\a option, true) instead.
*/
void QPageSetupDialog::addEnabledOption(PageSetupDialogOption option)
{
    setOption(option, true);
}

/*!
    \obsolete

    Use setOptions(\a options) instead.
*/
void QPageSetupDialog::setEnabledOptions(PageSetupDialogOptions options)
{
    setOptions(options);
}

/*!
    \obsolete

    Use options() instead.
*/
QPageSetupDialog::PageSetupDialogOptions QPageSetupDialog::enabledOptions() const
{
    return options();
}

/*!
    \obsolete

    Use testOption(\a option) instead.
*/
bool QPageSetupDialog::isOptionEnabled(PageSetupDialogOption option) const
{
    return testOption(option);
}

/*!
    \overload
    \since 4.5

    Opens the dialog and connects its accepted() signal to the slot specified
    by \a receiver and \a member.

    The signal will be disconnected from the slot when the dialog is closed.
*/
void QPageSetupDialog::open(QObject *receiver, const char *member)
{
    Q_D(QPageSetupDialog);
    connect(this, SIGNAL(accepted()), receiver, member);
    d->receiverToDisconnectOnClose = receiver;
    d->memberToDisconnectOnClose = member;
    QDialog::open();
}

#if defined(Q_WS_MAC) || defined(Q_OS_WIN)
/*! \fn void QPageSetupDialog::setVisible(bool visible)
    \reimp
*/
#endif

QT_END_NAMESPACE

#endif
