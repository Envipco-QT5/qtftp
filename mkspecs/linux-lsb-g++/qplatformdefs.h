/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the qmake spec of the Qt Toolkit.
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

#ifndef QPLATFORMDEFS_H
#define QPLATFORMDEFS_H

// Get Qt defines/settings

#include "qglobal.h"

// Set any POSIX/XOPEN defines at the top of this file to turn on specific APIs

// 1) need to reset default environment if _BSD_SOURCE is defined
// 2) need to specify POSIX thread interfaces explicitly in glibc 2.0
// 3) it seems older glibc need this to include the X/Open stuff
#ifndef _GNU_SOURCE
#  define _GNU_SOURCE
#endif

#include <unistd.h>


// We are hot - unistd.h should have turned on the specific APIs we requested

#include <features.h>
#include <pthread.h>
#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <signal.h>
#include <dlfcn.h>
#include <time.h>

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <netinet/in.h>
#ifndef QT_NO_IPV6IFNAME
#include <net/if.h>
#endif

// LSB 3.1 defines htonl and friends here
#include <arpa/inet.h>

#ifdef QT_LARGEFILE_SUPPORT
#define QT_STATBUF              struct stat64
#define QT_STATBUF4TSTAT        struct stat64
#define QT_STAT                 ::stat64
#define QT_FSTAT                ::fstat64
#define QT_LSTAT                ::lstat64
#define QT_OPEN                 ::open64
#define QT_TRUNCATE             ::truncate64
#define QT_FTRUNCATE            ::ftruncate64
#define QT_LSEEK                ::lseek64
#else
#define QT_STATBUF              struct stat
#define QT_STATBUF4TSTAT        struct stat
#define QT_STAT                 ::stat
#define QT_FSTAT                ::fstat
#define QT_LSTAT                ::lstat
#define QT_OPEN                 ::open
#define QT_TRUNCATE             ::truncate
#define QT_FTRUNCATE            ::ftruncate
#define QT_LSEEK                ::lseek
#endif

#ifdef QT_LARGEFILE_SUPPORT
#define QT_FOPEN                ::fopen64
#define QT_FSEEK                ::fseeko64
#define QT_FTELL                ::ftello64
#define QT_FGETPOS              ::fgetpos64
#define QT_FSETPOS              ::fsetpos64
#define QT_FPOS_T               fpos64_t
#define QT_OFF_T                off64_t
#else
#define QT_FOPEN                ::fopen
#define QT_FSEEK                ::fseek
#define QT_FTELL                ::ftell
#define QT_FGETPOS              ::fgetpos
#define QT_FSETPOS              ::fsetpos
#define QT_FPOS_T               fpos_t
#define QT_OFF_T                long
#endif

#define QT_STAT_REG		S_IFREG
#define QT_STAT_DIR		S_IFDIR
#define QT_STAT_MASK		S_IFMT
#define QT_STAT_LNK		S_IFLNK
#define QT_SOCKET_CONNECT	::connect
#define QT_SOCKET_BIND		::bind
#define QT_SOCKET_BIND		::bind
#define QT_FILENO		fileno
#define QT_CLOSE		::close
#define QT_READ			::read
#define QT_WRITE		::write
#define QT_ACCESS		::access
#define QT_GETCWD		::getcwd
#define QT_CHDIR		::chdir
#define QT_MKDIR		::mkdir
#define QT_RMDIR		::rmdir
#define QT_OPEN_LARGEFILE       0
#define QT_OPEN_RDONLY		O_RDONLY
#define QT_OPEN_WRONLY		O_WRONLY
#define QT_OPEN_RDWR		O_RDWR
#define QT_OPEN_CREAT		O_CREAT
#define QT_OPEN_TRUNC		O_TRUNC
#define QT_OPEN_APPEND		O_APPEND

#define QT_SIGNAL_RETTYPE	void
#define QT_SIGNAL_ARGS		int
#define QT_SIGNAL_IGNORE	SIG_IGN

#ifndef SIOCGIFBRDADDR
#  define SIOCGIFBRDADDR 0x8919
#endif

#if defined(__GLIBC__) && (__GLIBC__ >= 2)
#define QT_SOCKLEN_T		socklen_t
#else
#define QT_SOCKLEN_T		int
#endif

#if defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE >= 500)
#define QT_SNPRINTF		::snprintf
#define QT_VSNPRINTF		::vsnprintf
#endif


#endif // QPLATFORMDEFS_H
