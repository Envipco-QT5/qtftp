/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtNetwork module of the Qt Toolkit.
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
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
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

//#define QNETWORKDISKCACHE_DEBUG

#include "qnetworkdiskcache.h"
#include "qnetworkdiskcache_p.h"

#include <qfile.h>
#include <qdir.h>
#include <qdatetime.h>
#include <qdiriterator.h>
#include <qcryptographichash.h>
#include <qurl.h>

#include <qdebug.h>

#define CACHE_PREFIX  QLatin1String("cache_")
#define CACHE_POSTFIX QLatin1String(".cache")
#define MAX_COMPRESSION_SIZE (1024 * 1024 * 3)

QT_BEGIN_NAMESPACE

/*!
    \class QNetworkDiskCache
    \since 4.5
    \inmodule QtNetwork

    \brief The QNetworkDiskCache class provides a very basic disk cache.

    QNetworkDiskCache stores each url in its own file inside of the
    cacheDirectory using QDataStream.  Files with a text MimeType
    are compressed using qCompress.  Each cache file starts with "cache_"
    and ends in ".cache".  Data is written to disk only in insert()
    and updateMetaData().

    Currently you can not share the same cache files with more then
    one disk cache.

    QNetworkDiskCache by default limits the amount of space that the cache will
    use on the system to 50MB.

    Note you have to set the cache directory before it will work.
*/

/*!
    Creates a new disk cache. The \a parent argument is passed to
    QAbstractNetworkCache's constructor.
 */
QNetworkDiskCache::QNetworkDiskCache(QObject *parent)
    : QAbstractNetworkCache(*new QNetworkDiskCachePrivate, parent)
{
}

/*!
    Destroys the cache object.  This does not clear the disk cache.
 */
QNetworkDiskCache::~QNetworkDiskCache()
{
    Q_D(QNetworkDiskCache);
    QHashIterator<QIODevice*, QCacheItem*> it(d->inserting);
    while (it.hasNext()) {
        it.next();
        delete it.value();
    }
}

/*!
    Returns the location where cached files will be stored.
*/
QString QNetworkDiskCache::cacheDirectory() const
{
    Q_D(const QNetworkDiskCache);
    return d->cacheDirectory;
}

/*!
    Sets the directory where cached files will be stored to \a cacheDir

    QNetworkDiskCache will create this directory if it does not exists.

    Prepared cache items will be stored in the new cache directory when
    they are inserted.

    \sa QDesktopServices::CacheLocation
*/
void QNetworkDiskCache::setCacheDirectory(const QString &cacheDir)
{
#if defined(QNETWORKDISKCACHE_DEBUG)
    qDebug() << "QNetworkDiskCache::setCacheDirectory()" << cacheDir;
#endif
    Q_D(QNetworkDiskCache);
    if (cacheDir.isEmpty())
        return;
    d->cacheDirectory = cacheDir;
    QDir dir(d->cacheDirectory);
    d->cacheDirectory = dir.absolutePath();
    if (!d->cacheDirectory.endsWith(QLatin1Char('/')))
        d->cacheDirectory += QLatin1Char('/');
}

/*!
    \reimp
*/
qint64 QNetworkDiskCache::cacheSize() const
{
#if defined(QNETWORKDISKCACHE_DEBUG)
    qDebug() << "QNetworkDiskCache::cacheSize()";
#endif
    Q_D(const QNetworkDiskCache);
    if (d->cacheDirectory.isEmpty())
        return 0;
    if (d->currentCacheSize < 0) {
        QNetworkDiskCache *that = const_cast<QNetworkDiskCache*>(this);
        that->d_func()->currentCacheSize = that->expire();
    }
    return d->currentCacheSize;
}

/*!
    \reimp
*/
QIODevice *QNetworkDiskCache::prepare(const QNetworkCacheMetaData &metaData)
{
#if defined(QNETWORKDISKCACHE_DEBUG)
    qDebug() << "QNetworkDiskCache::prepare()" << metaData.url();
#endif
    Q_D(QNetworkDiskCache);
    if (!metaData.isValid() || !metaData.url().isValid() || !metaData.saveToDisk())
        return 0;

    if (d->cacheDirectory.isEmpty()) {
        qWarning() << "QNetworkDiskCache::prepare() The cache directory is not set";
        return 0;
    }

    foreach (QNetworkCacheMetaData::RawHeader header, metaData.rawHeaders()) {
        if (header.first.toLower() == "content-length") {
            qint64 size = header.second.toInt();
            if (size > (maximumCacheSize() * 3)/4)
                return 0;
            break;
        }
    }

    QCacheItem *cacheItem = new QCacheItem;
    cacheItem->metaData = metaData;

    QIODevice *device = 0;
    if (cacheItem->canCompress()) {
        cacheItem->data.open(QBuffer::ReadWrite);
        device = &(cacheItem->data);
    } else {
        QString templateName = d->tmpCacheFileName();
        cacheItem->file = new QTemporaryFile(templateName, &cacheItem->data);
        if (!cacheItem->file->open()) {
            qWarning() << "QNetworkDiskCache::prepare() unable to open temporary file";
            delete cacheItem;
            return 0;
        }
        cacheItem->writeHeader(cacheItem->file);
        device = cacheItem->file;
    }
    d->inserting[device] = cacheItem;
    return device;
}

/*!
    \reimp
*/
void QNetworkDiskCache::insert(QIODevice *device)
{
#if defined(QNETWORKDISKCACHE_DEBUG)
    qDebug() << "QNetworkDiskCache::insert()" << device;
#endif
    Q_D(QNetworkDiskCache);
    QHash<QIODevice*, QCacheItem*>::iterator it = d->inserting.find(device);
    if (it == d->inserting.end()) {
        qWarning() << "QNetworkDiskCache::insert() called on a device we don't know about" << device;
        return;
    }

    d->storeItem(it.value());
    delete it.value();
    d->inserting.erase(it);
}

void QNetworkDiskCachePrivate::storeItem(QCacheItem *cacheItem)
{
    Q_Q(QNetworkDiskCache);
    Q_ASSERT(cacheItem->metaData.saveToDisk());

    QString fileName = cacheFileName(cacheItem->metaData.url());
    Q_ASSERT(!fileName.isEmpty());

    if (QFile::exists(fileName)) {
        if (!QFile::remove(fileName)) {
            qWarning() << "QNetworkDiskCache: couldn't remove the cache file " << fileName;
            return;
        }
    }

    if (currentCacheSize > 0)
        currentCacheSize += 1024 + cacheItem->size();
    currentCacheSize = q->expire();
    if (!cacheItem->file) {
        QString templateName = tmpCacheFileName();
        cacheItem->file = new QTemporaryFile(templateName, &cacheItem->data);
        if (cacheItem->file->open()) {
            cacheItem->writeHeader(cacheItem->file);
            cacheItem->writeCompressedData(cacheItem->file);
        }
    }

    if (cacheItem->file
        && cacheItem->file->isOpen()
        && cacheItem->file->error() == QFile::NoError) {
        cacheItem->file->setAutoRemove(false);
        // ### use atomic rename rather then remove & rename
        if (cacheItem->file->rename(fileName))
            currentCacheSize += cacheItem->file->size();
        else
            cacheItem->file->setAutoRemove(true);
    }
    if (cacheItem->metaData.url() == lastItem.metaData.url())
        lastItem.reset();
}

/*!
    \reimp
*/
bool QNetworkDiskCache::remove(const QUrl &url)
{
#if defined(QNETWORKDISKCACHE_DEBUG)
    qDebug() << "QNetworkDiskCache::remove()" << url;
#endif
    Q_D(QNetworkDiskCache);

    // remove is also used to cancel insertions, not a common operation
    QHashIterator<QIODevice*, QCacheItem*> it(d->inserting);
    while (it.hasNext()) {
        it.next();
        QCacheItem *item = it.value();
        if (item && item->metaData.url() == url) {
            delete item;
            d->inserting.remove(it.key());
            return true;
        }
    }

    if (d->lastItem.metaData.url() == url)
        d->lastItem.reset();
    return d->removeFile(d->cacheFileName(url));
}

/*!
    Put all of the misc file removing into one function to be extra safe
 */
bool QNetworkDiskCachePrivate::removeFile(const QString &file)
{
#if defined(QNETWORKDISKCACHE_DEBUG)
    qDebug() << "QNetworkDiskCache::removFile()" << file;
#endif
    if (file.isEmpty())
        return false;
    QFileInfo info(file);
    QString fileName = info.fileName();
    if (!fileName.endsWith(CACHE_POSTFIX) || !fileName.startsWith(CACHE_PREFIX))
        return false;
    qint64 size = info.size();
    if (QFile::remove(file)) {
        currentCacheSize -= size;
        return true;
    }
    return false;
}

/*!
    \reimp
*/
QNetworkCacheMetaData QNetworkDiskCache::metaData(const QUrl &url)
{
#if defined(QNETWORKDISKCACHE_DEBUG)
    qDebug() << "QNetworkDiskCache::metaData()" << url;
#endif
    Q_D(QNetworkDiskCache);
    if (d->lastItem.metaData.url() == url)
        return d->lastItem.metaData;
    return fileMetaData(d->cacheFileName(url));
}

/*!
    Returns the QNetworkCacheMetaData for the cache file \a fileName.

    If \a fileName is not a cache file QNetworkCacheMetaData will be invalid.
 */
QNetworkCacheMetaData QNetworkDiskCache::fileMetaData(const QString &fileName) const
{
#if defined(QNETWORKDISKCACHE_DEBUG)
    qDebug() << "QNetworkDiskCache::fileMetaData()" << fileName;
#endif
    Q_D(const QNetworkDiskCache);
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return QNetworkCacheMetaData();
    if (!d->lastItem.read(&file, false)) {
        file.close();
        QNetworkDiskCachePrivate *that = const_cast<QNetworkDiskCachePrivate*>(d);
        that->removeFile(fileName);
    }
    return d->lastItem.metaData;
}

/*!
    \reimp
*/
QIODevice *QNetworkDiskCache::data(const QUrl &url)
{
#if defined(QNETWORKDISKCACHE_DEBUG)
    qDebug() << "QNetworkDiskCache::data()" << url;
#endif
    Q_D(QNetworkDiskCache);
    QBuffer *buffer = 0;
    if (!url.isValid())
        return buffer;
    if (d->lastItem.metaData.url() == url && d->lastItem.data.isOpen()) {
        buffer = new QBuffer;
        buffer->setData(d->lastItem.data.data());
    } else {
        QFile *file = new QFile(d->cacheFileName(url));
        if (!file->open(QFile::ReadOnly | QIODevice::Unbuffered)) {
            delete file;
            return 0;
        }
        if (!d->lastItem.read(file, true)) {
            file->close();
            remove(url);
            delete file;
            return 0;
        }
        if (d->lastItem.data.isOpen()) {
            // compressed
            buffer = new QBuffer;
            buffer->setData(d->lastItem.data.data());
            delete file;
        } else {
            buffer = new QBuffer;
            // ### verify that QFile uses the fd size and not the file name
            qint64 size = file->size() - file->pos();
            const uchar *p = 0;
#ifndef Q_OS_WINCE
            p = file->map(file->pos(), size);
#endif
            if (p) {
                file->setParent(buffer);
                buffer->setData((const char *)p, size);
            } else {
                buffer->setData(file->readAll());
                delete file;
            }
        }
    }
    buffer->open(QBuffer::ReadOnly);
    return buffer;
}

/*!
    \reimp
*/
void QNetworkDiskCache::updateMetaData(const QNetworkCacheMetaData &metaData)
{
#if defined(QNETWORKDISKCACHE_DEBUG)
    qDebug() << "QNetworkDiskCache::updateMetaData()" << metaData.url();
#endif
    QUrl url = metaData.url();
    QIODevice *oldDevice = data(url);
    if (!oldDevice) {
#if defined(QNETWORKDISKCACHE_DEBUG)
        qDebug() << "QNetworkDiskCache::updateMetaData(), no device!";
#endif
        return;
    }

    QIODevice *newDevice = prepare(metaData);
    if (!newDevice) {
#if defined(QNETWORKDISKCACHE_DEBUG)
        qDebug() << "QNetworkDiskCache::updateMetaData(), no new device!" << url;
#endif
        return;
    }
    char data[1024];
    while (!oldDevice->atEnd()) {
        qint64 s = oldDevice->read(data, 1024);
        newDevice->write(data, s);
    }
    delete oldDevice;
    insert(newDevice);
}

/*!
    Returns the current maximum size for the disk cache.

    \sa setMaximumCacheSize()
 */
qint64 QNetworkDiskCache::maximumCacheSize() const
{
    Q_D(const QNetworkDiskCache);
    return d->maximumCacheSize;
}

/*!
    Sets the maximum size of the disk cache to be \a size.

    If the new size is smaller then the current cache size then the cache will call expire().

    \sa maximumCacheSize()
 */
void QNetworkDiskCache::setMaximumCacheSize(qint64 size)
{
    Q_D(QNetworkDiskCache);
    bool expireCache = (size < d->maximumCacheSize);
    d->maximumCacheSize = size;
    if (expireCache)
        d->currentCacheSize = expire();
}

/*!
    Cleans the cache so that its size is under the maximum cache size.
    Returns the current size of the cache.

    When the current size of the cache is greater than the maximumCacheSize()
    older cache files are removed until the total size is less then 90% of
    maximumCacheSize() starting with the oldest ones first using the file
    creation date to determine how old a cache file is.

    Subclasses can reimplement this function to change the order that cache
    files are removed taking into account information in the application
    knows about that QNetworkDiskCache does not, for example the number of times
    a cache is accessed.

    Note: cacheSize() calls expire if the current cache size is unknown.

    \sa maximumCacheSize(), fileMetaData()
 */
qint64 QNetworkDiskCache::expire()
{
    Q_D(QNetworkDiskCache);
    if (d->currentCacheSize >= 0 && d->currentCacheSize < maximumCacheSize())
        return d->currentCacheSize;

    if (cacheDirectory().isEmpty()) {
        qWarning() << "QNetworkDiskCache::expire() The cache directory is not set";
        return 0;
    }

    QDir::Filters filters = QDir::AllDirs | QDir:: Files | QDir::NoDotAndDotDot;
    QDirIterator it(cacheDirectory(), filters, QDirIterator::Subdirectories);

    QMultiMap<QDateTime, QString> cacheItems;
    qint64 totalSize = 0;
    while (it.hasNext()) {
        QString path = it.next();
        QFileInfo info = it.fileInfo();
        QString fileName = info.fileName();
        if (fileName.endsWith(CACHE_POSTFIX) && fileName.startsWith(CACHE_PREFIX)) {
            cacheItems.insert(info.created(), path);
            totalSize += info.size();
        }
    }

    int removedFiles = 0;
    qint64 goal = (maximumCacheSize() * 9) / 10;
    QMultiMap<QDateTime, QString>::const_iterator i = cacheItems.constBegin();
    while (i != cacheItems.constEnd()) {
        if (totalSize < goal)
            break;
        QString name = i.value();
        QFile file(name);
        qint64 size = file.size();
        file.remove();
        totalSize -= size;
        ++removedFiles;
        ++i;
    }
#if defined(QNETWORKDISKCACHE_DEBUG)
    if (removedFiles > 0) {
        qDebug() << "QNetworkDiskCache::expire()"
                << "Removed:" << removedFiles
                << "Kept:" << cacheItems.count() - removedFiles;
    }
#endif
    if (removedFiles > 0)
        d->lastItem.reset();
    return totalSize;
}

/*!
    \reimp
*/
void QNetworkDiskCache::clear()
{
#if defined(QNETWORKDISKCACHE_DEBUG)
    qDebug() << "QNetworkDiskCache::clear()";
#endif
    Q_D(QNetworkDiskCache);
    qint64 size = d->maximumCacheSize;
    d->maximumCacheSize = 0;
    d->currentCacheSize = expire();
    d->maximumCacheSize = size;
}

QByteArray QNetworkDiskCachePrivate::generateId(const QUrl &url) const
{
    QUrl cleanUrl = url;
    cleanUrl.setPassword(QString());
    cleanUrl.setFragment(QString());

    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(cleanUrl.toEncoded());
    return hash.result().toHex();
}

QString QNetworkDiskCachePrivate::tmpCacheFileName() const
{
    QDir dir;
    dir.mkpath(cacheDirectory + QLatin1String("prepared/"));
    return cacheDirectory + QLatin1String("prepared/") + CACHE_PREFIX + QLatin1String("XXXXXX") + CACHE_POSTFIX;
}

QString QNetworkDiskCachePrivate::cacheFileName(const QUrl &url) const
{
    if (!url.isValid())
        return QString();
    QString directory = cacheDirectory + url.scheme() + QLatin1Char('/');
    if (!QFile::exists(directory)) {
        // ### make a static QDir function for this...
        QDir dir;
        dir.mkpath(directory);
    }

    QString fileName = CACHE_PREFIX + QLatin1String(generateId(url)) + CACHE_POSTFIX;
    return  directory + fileName;
}

/*!
    We compress small text and JavaScript files.
 */
bool QCacheItem::canCompress() const
{
    bool sizeOk = false;
    bool typeOk = false;
    foreach (QNetworkCacheMetaData::RawHeader header, metaData.rawHeaders()) {
        if (header.first.toLower() == "content-length") {
            qint64 size = header.second.toLongLong();
            if (size > MAX_COMPRESSION_SIZE)
                return false;
            else
                sizeOk = true;
        }

        if (header.first.toLower() == "content-type") {
            QByteArray type = header.second;
            if (type.startsWith("text/")
                    || (type.startsWith("application/")
                        && (type.endsWith("javascript") || type.endsWith("ecmascript"))))
                typeOk = true;
            else
                return false;
        }
        if (sizeOk && typeOk)
            return true;
    }
    return false;
}

enum
{
    CacheMagic = 0xe8,
    CurrentCacheVersion = 7
};

void QCacheItem::writeHeader(QFile *device) const
{
    QDataStream out(device);

    out << qint32(CacheMagic);
    out << qint32(CurrentCacheVersion);
    out << metaData;
    bool compressed = canCompress();
    out << compressed;
}

void QCacheItem::writeCompressedData(QFile *device) const
{
    QDataStream out(device);

    out << qCompress(data.data());
}

/*!
    Returns false if the file is a cache file,
    but is an older version and should be removed otherwise true.
 */
bool QCacheItem::read(QFile *device, bool readData)
{
    reset();

    QDataStream in(device);

    qint32 marker;
    qint32 v;
    in >> marker;
    in >> v;
    if (marker != CacheMagic)
        return true;

    // If the cache magic is correct, but the version is not we should remove it
    if (v != CurrentCacheVersion)
        return false;

    bool compressed;
    QByteArray dataBA;
    in >> metaData;
    in >> compressed;
    if (readData && compressed) {
        in >> dataBA;
        data.setData(qUncompress(dataBA));
        data.open(QBuffer::ReadOnly);
    }
    return metaData.isValid();
}

QT_END_NAMESPACE
