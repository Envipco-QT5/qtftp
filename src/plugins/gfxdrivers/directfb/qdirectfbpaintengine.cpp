/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the plugins of the Qt Toolkit.
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
** contact the sales department at http://www.qtsoftware.com/contact.
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qdirectfbpaintengine.h"

#ifndef QT_NO_DIRECTFB

#include "qdirectfbwindowsurface.h"
#include "qdirectfbscreen.h"
#include "qdirectfbpixmap.h"
#include <directfb.h>
#include <qtransform.h>
#include <qvarlengtharray.h>
#include <qcache.h>
#include <qmath.h>
#include <private/qpixmapdata_p.h>
#include <private/qpixmap_raster_p.h>

class SurfaceCache;
class QDirectFBPaintEnginePrivate : public QRasterPaintEnginePrivate
{
public:
    enum TransformationTypeFlags {
        Matrix_NegativeScale = 0x100,
        Matrix_RectsUnsupported = (QTransform::TxRotate|QTransform::TxShear|QTransform::TxProject),
        Matrix_BlitsUnsupported = (Matrix_NegativeScale|Matrix_RectsUnsupported)
    };

    enum CompositionModeStatus {
        PorterDuff_None = 0x0,
        PorterDuff_SupportedBlits = 0x1,
        PorterDuff_SupportedPrimitives = 0x2
    };

    QDirectFBPaintEnginePrivate(QDirectFBPaintEngine *p);
    ~QDirectFBPaintEnginePrivate();

    inline void setTransform(const QTransform &transforma);
    inline void setPen(const QPen &pen);
    inline void setCompositionMode(QPainter::CompositionMode mode);
    inline void setRenderHints(QPainter::RenderHints hints);

    inline void setDFBColor(const QColor &color);

    inline void lock();
    inline void unlock();

    inline bool dfbCanHandleClip(const QRect &rect) const;
    inline bool dfbCanHandleClip(const QRectF &rect) const;
    inline bool dfbCanHandleClip() const;
    inline bool isSimpleBrush(const QBrush &brush) const;

    void drawTiledPixmap(const QRectF &dest, const QPixmap &pixmap, const QPointF &pos);
    void blit(const QRectF &dest, IDirectFBSurface *surface, const QRectF &src);

    inline void updateClip();
    virtual void systemStateChanged();

    static IDirectFBSurface *getSurface(const QImage &img, bool *release);

#ifdef QT_DIRECTFB_IMAGECACHE
    static inline int cacheCost(const QImage &img) { return img.width() * img.height() * img.depth() / 8; }
#endif

    void prepareForBlit(bool alpha);
private:
    IDirectFBSurface *surface;

    bool antialiased;
    bool simplePen;

    uint transformationType; // this is QTransform::type() + Matrix_NegativeScale if qMin(transform.m11(), transform.m22()) < 0

    SurfaceCache *surfaceCache;

    IDirectFB *fb;

    quint8 opacity;

    bool dirtyClip;
    bool dfbHandledClip;
    bool ignoreSystemClip;
    QDirectFBPaintDevice *dfbDevice;
    uint compositionModeStatus;

    QDirectFBPaintEngine *q;
    QRect currentClip;
    friend class QDirectFBPaintEngine;
};

class SurfaceCache
{
public:
    SurfaceCache() : surface(0), buffer(0), bufsize(0) {}
    ~SurfaceCache() { clear(); }
    IDirectFBSurface *getSurface(const uint *buf, int size);
    void clear();
private:
    IDirectFBSurface *surface;
    uint *buffer;
    int bufsize;
};


#ifdef QT_DIRECTFB_IMAGECACHE
#include <private/qimage_p.h>
struct CachedImage
{
    IDirectFBSurface *surface;
    ~CachedImage()
    {
        if (surface && QDirectFBScreen::instance()) {
            QDirectFBScreen::instance()->releaseDFBSurface(surface);
        }
    }
};
static QCache<qint64, CachedImage> imageCache(4*1024*1024); // 4 MB
#endif

#if defined QT_DIRECTFB_WARN_ON_RASTERFALLBACKS || defined QT_DIRECTFB_DISABLE_RASTERFALLBACKS
#define VOID_ARG() static_cast<bool>(false)
enum PaintOperation {
    DRAW_RECTS = 0x0001, DRAW_LINES = 0x0002, DRAW_IMAGE = 0x0004,
    DRAW_PIXMAP = 0x0008, DRAW_TILED_PIXMAP = 0x0010, STROKE_PATH = 0x0020,
    DRAW_PATH = 0x0040, DRAW_POINTS = 0x0080, DRAW_ELLIPSE = 0x0100,
    DRAW_POLYGON = 0x0200, DRAW_TEXT = 0x0400, FILL_PATH = 0x0800,
    FILL_RECT = 0x1000, DRAW_COLORSPANS = 0x2000, ALL = 0xffff
};
#endif

#ifdef QT_DIRECTFB_WARN_ON_RASTERFALLBACKS
template <typename device, typename T1, typename T2, typename T3>
static void rasterFallbackWarn(const char *msg, const char *func, const device *dev,
                               uint transformationType, bool simplePen,
                               bool dfbHandledClip, uint compositionModeStatus,
                               const char *nameOne, const T1 &one,
                               const char *nameTwo, const T2 &two,
                               const char *nameThree, const T3 &three);
#endif

#if defined QT_DIRECTFB_WARN_ON_RASTERFALLBACKS && defined QT_DIRECTFB_DISABLE_RASTERFALLBACKS
#define RASTERFALLBACK(op, one, two, three)                             \
    if (op & (QT_DIRECTFB_WARN_ON_RASTERFALLBACKS))                     \
        rasterFallbackWarn("Disabled raster engine operation",          \
                           __FUNCTION__, state()->painter->device(),    \
                           d_func()->transformationType,                \
                           d_func()->simplePen,                         \
                           d_func()->dfbCanHandleClip(),                \
                           d_func()->compositionModeStatus,             \
                           #one, one, #two, two, #three, three);        \
    if (op & (QT_DIRECTFB_DISABLE_RASTERFALLBACKS))                     \
        return;
#elif defined QT_DIRECTFB_DISABLE_RASTERFALLBACKS
#define RASTERFALLBACK(op, one, two, three)             \
    if (op & (QT_DIRECTFB_DISABLE_RASTERFALLBACKS))     \
        return;
#elif defined QT_DIRECTFB_WARN_ON_RASTERFALLBACKS
#define RASTERFALLBACK(op, one, two, three)                             \
    if (op & (QT_DIRECTFB_WARN_ON_RASTERFALLBACKS))                     \
        rasterFallbackWarn("Falling back to raster engine for",         \
                           __FUNCTION__, state()->painter->device(),    \
                           d_func()->transformationType,                \
                           d_func()->simplePen,                         \
                           d_func()->dfbCanHandleClip(),                \
                           d_func()->compositionModeStatus,             \
                           #one, one, #two, two, #three, three);
#else
#define RASTERFALLBACK(op, one, two, three)
#endif


template <class T>
static inline void drawLines(const T *lines, int n, const QTransform &transform, IDirectFBSurface *surface);
template <class T>
static inline void fillRects(const T *rects, int n, const QTransform &transform, IDirectFBSurface *surface);
template <class T>
static inline void drawRects(const T *rects, int n, const QTransform &transform, IDirectFBSurface *surface);

QDirectFBPaintEngine::QDirectFBPaintEngine(QPaintDevice *device)
    : QRasterPaintEngine(*(new QDirectFBPaintEnginePrivate(this)), device)
{
}

QDirectFBPaintEngine::~QDirectFBPaintEngine()
{
}

bool QDirectFBPaintEngine::begin(QPaintDevice *device)
{
    Q_D(QDirectFBPaintEngine);
    if (device->devType() == QInternal::CustomRaster) {
        d->dfbDevice = static_cast<QDirectFBPaintDevice*>(device);
    } else if (device->devType() == QInternal::Pixmap) {
        QPixmapData *data = static_cast<QPixmap*>(device)->pixmapData();
        Q_ASSERT(data->classId() == QPixmapData::DirectFBClass);
        QDirectFBPixmapData *dfbPixmapData = static_cast<QDirectFBPixmapData*>(data);
        d->dfbDevice = static_cast<QDirectFBPaintDevice*>(dfbPixmapData);
    }

    if (d->dfbDevice)
        d->surface = d->dfbDevice->directFBSurface();

    if (!d->surface) {
        qFatal("QDirectFBPaintEngine used on an invalid device: 0x%x",
               device->devType());
    }

    d->prepare(d->dfbDevice);
    d->setCompositionMode(state()->composition_mode);

    return QRasterPaintEngine::begin(device);
}

bool QDirectFBPaintEngine::end()
{
    Q_D(QDirectFBPaintEngine);
    d->unlock();
    d->dfbDevice = 0;
#if (Q_DIRECTFB_VERSION >= 0x010000)
    d->surface->ReleaseSource(d->surface);
#endif
    d->currentClip = QRect();
    d->surface->SetClip(d->surface, NULL);
    d->surface = 0;
    return QRasterPaintEngine::end();
}

void QDirectFBPaintEngine::clipEnabledChanged()
{
    Q_D(QDirectFBPaintEngine);
    d->dirtyClip = true;
    QRasterPaintEngine::clipEnabledChanged();
}

void QDirectFBPaintEngine::penChanged()
{
    Q_D(QDirectFBPaintEngine);
    d->setPen(state()->pen);

    QRasterPaintEngine::penChanged();
}

void QDirectFBPaintEngine::opacityChanged()
{
    Q_D(QDirectFBPaintEngine);
    d->opacity = quint8(state()->opacity * 255);
    QRasterPaintEngine::opacityChanged();
}

void QDirectFBPaintEngine::compositionModeChanged()
{
    Q_D(QDirectFBPaintEngine);
    d->setCompositionMode(state()->compositionMode());
    QRasterPaintEngine::compositionModeChanged();
}

void QDirectFBPaintEngine::renderHintsChanged()
{
    Q_D(QDirectFBPaintEngine);
    d->setRenderHints(state()->renderHints);
    QRasterPaintEngine::renderHintsChanged();
}

void QDirectFBPaintEngine::transformChanged()
{
    Q_D(QDirectFBPaintEngine);
    d->setTransform(state()->matrix);
    QRasterPaintEngine::transformChanged();
}

void QDirectFBPaintEngine::setState(QPainterState *state)
{
    Q_D(QDirectFBPaintEngine);
    QRasterPaintEngine::setState(state);
    d->dirtyClip = true;
    d->setPen(state->pen);
    d->opacity = quint8(state->opacity * 255);
    d->setCompositionMode(state->compositionMode());
    d->setTransform(state->transform());
    d->setRenderHints(state->renderHints);
}

void QDirectFBPaintEngine::clip(const QVectorPath &path, Qt::ClipOperation op)
{
    Q_D(QDirectFBPaintEngine);
    d->dirtyClip = true;
    QRasterPaintEngine::clip(path, op);
}

void QDirectFBPaintEngine::clip(const QRect &rect, Qt::ClipOperation op)
{
    Q_D(QDirectFBPaintEngine);
    d->dirtyClip = true;
    QRasterPaintEngine::clip(rect, op);
}

void QDirectFBPaintEngine::drawRects(const QRect *rects, int rectCount)
{
    Q_D(QDirectFBPaintEngine);
    d->updateClip();
    const QBrush &brush = state()->brush;
    if (!(d->compositionModeStatus & QDirectFBPaintEnginePrivate::PorterDuff_SupportedPrimitives)
        || (d->transformationType & QDirectFBPaintEnginePrivate::Matrix_RectsUnsupported)
        || !d->simplePen
        || !d->dfbCanHandleClip()
        || !d->isSimpleBrush(brush)) {
        RASTERFALLBACK(DRAW_RECTS, rectCount, VOID_ARG(), VOID_ARG());
        d->lock();
        QRasterPaintEngine::drawRects(rects, rectCount);
        return;
    }

    d->unlock();

    if (brush != Qt::NoBrush) {
        d->setDFBColor(brush.color());
        ::fillRects<QRect>(rects, rectCount, state()->matrix, d->surface);
    }
    const QPen &pen = state()->pen;
    if (pen != Qt::NoPen) {
        d->setDFBColor(pen.color());
        ::drawRects<QRect>(rects, rectCount, state()->matrix, d->surface);
    }
}

void QDirectFBPaintEngine::drawRects(const QRectF *rects, int rectCount)
{
    Q_D(QDirectFBPaintEngine);
    d->updateClip();
    const QBrush &brush = state()->brush;
    if (!(d->compositionModeStatus & QDirectFBPaintEnginePrivate::PorterDuff_SupportedPrimitives)
        || (d->transformationType & QDirectFBPaintEnginePrivate::Matrix_RectsUnsupported)
        || !d->simplePen
        || !d->dfbCanHandleClip()
        || !d->isSimpleBrush(brush)) {
        RASTERFALLBACK(DRAW_RECTS, rectCount, VOID_ARG(), VOID_ARG());
        d->lock();
        QRasterPaintEngine::drawRects(rects, rectCount);
        return;
    }

    d->unlock();

    if (brush != Qt::NoBrush) {
        d->setDFBColor(brush.color());
        ::fillRects<QRectF>(rects, rectCount, state()->matrix, d->surface);
    }
    const QPen &pen = state()->pen;
    if (pen != Qt::NoPen) {
        d->setDFBColor(pen.color());
        ::drawRects<QRectF>(rects, rectCount, state()->matrix, d->surface);
    }
}

void QDirectFBPaintEngine::drawLines(const QLine *lines, int lineCount)
{
    Q_D(QDirectFBPaintEngine);
    d->updateClip();
    if (!(d->compositionModeStatus & QDirectFBPaintEnginePrivate::PorterDuff_SupportedPrimitives)
        || !d->simplePen
        || !d->dfbCanHandleClip()) {
        RASTERFALLBACK(DRAW_LINES, lineCount, VOID_ARG(), VOID_ARG());
        d->lock();
        QRasterPaintEngine::drawLines(lines, lineCount);
        return;
    }

    const QPen &pen = state()->pen;
    if (pen != Qt::NoPen) {
        d->unlock();
        d->setDFBColor(pen.color());
        ::drawLines<QLine>(lines, lineCount, state()->matrix, d->surface);
    }
}

void QDirectFBPaintEngine::drawLines(const QLineF *lines, int lineCount)
{
    Q_D(QDirectFBPaintEngine);
    d->updateClip();
    if (!(d->compositionModeStatus & QDirectFBPaintEnginePrivate::PorterDuff_SupportedPrimitives)
        || !d->simplePen
        || !d->dfbCanHandleClip()) {
        RASTERFALLBACK(DRAW_LINES, lineCount, VOID_ARG(), VOID_ARG());
        d->lock();
        QRasterPaintEngine::drawLines(lines, lineCount);
        return;
    }

    const QPen &pen = state()->pen;
    if (pen != Qt::NoPen) {
        d->unlock();
        d->setDFBColor(pen.color());
        ::drawLines<QLineF>(lines, lineCount, state()->matrix, d->surface);
    }
}

void QDirectFBPaintEngine::drawImage(const QRectF &r, const QImage &image,
                                     const QRectF &sr,
                                     Qt::ImageConversionFlags flags)
{
    Q_D(QDirectFBPaintEngine);
    Q_UNUSED(flags);

    /*  This is hard to read. The way it works is like this:

    - If you do not have support for preallocated surfaces and do not use an
    image cache we always fall back to raster engine.

    - If it's rotated/sheared/mirrored (negative scale) or we can't
    clip it we fall back to raster engine.

    - If we don't cache the image, but we do have support for
    preallocated surfaces we fall back to the raster engine if the
    image is in a format DirectFB can't handle.

    - If we do cache the image but don't have support for preallocated
    images and the cost of caching the image (bytes used) is higher
    than the max image cache size we fall back to raster engine.
    */

    d->updateClip();
#if !defined QT_NO_DIRECTFB_PREALLOCATED || defined QT_DIRECTFB_IMAGECACHE
    if (!(d->compositionModeStatus & QDirectFBPaintEnginePrivate::PorterDuff_SupportedBlits)
        || (d->transformationType & QDirectFBPaintEnginePrivate::Matrix_BlitsUnsupported)
        || !d->dfbCanHandleClip(r)
#ifndef QT_DIRECTFB_IMAGECACHE
        || QDirectFBScreen::getSurfacePixelFormat(image.format()) == DSPF_UNKNOWN
#elif defined QT_NO_DIRECTFB_PREALLOCATED
        || QDirectFBPaintEnginePrivate::cacheCost(image) > imageCache.maxCost()
#endif
        )
#endif
    {
        RASTERFALLBACK(DRAW_IMAGE, r, image.size(), sr);
        d->lock();
        QRasterPaintEngine::drawImage(r, image, sr, flags);
        return;
    }
#if !defined QT_NO_DIRECTFB_PREALLOCATED || defined QT_DIRECTFB_IMAGECACHE
    d->unlock();
    bool release;
    IDirectFBSurface *imgSurface = d->getSurface(image, &release);
    d->prepareForBlit(QDirectFBScreen::hasAlpha(imgSurface));
    d->blit(r, imgSurface, sr);
    if (release) {
#if (Q_DIRECTFB_VERSION >= 0x010000)
        d->surface->ReleaseSource(d->surface);
#endif
        imgSurface->Release(imgSurface);
    }
#endif
}

void QDirectFBPaintEngine::drawImage(const QPointF &p, const QImage &img)
{
    drawImage(QRectF(p, img.size()), img, img.rect());
}

void QDirectFBPaintEngine::drawPixmap(const QRectF &r, const QPixmap &pixmap,
                                      const QRectF &sr)
{
    Q_D(QDirectFBPaintEngine);
    d->updateClip();

    if (pixmap.pixmapData()->classId() != QPixmapData::DirectFBClass) {
        RASTERFALLBACK(DRAW_PIXMAP, r, pixmap.size(), sr);
        d->lock();
        QRasterPaintEngine::drawPixmap(r, pixmap, sr);
    } else if (!(d->compositionModeStatus & QDirectFBPaintEnginePrivate::PorterDuff_SupportedBlits)
               || (d->transformationType & QDirectFBPaintEnginePrivate::Matrix_BlitsUnsupported)
               || !d->dfbCanHandleClip(r)) {
        RASTERFALLBACK(DRAW_PIXMAP, r, pixmap.size(), sr);
        const QImage *img = static_cast<QDirectFBPixmapData*>(pixmap.pixmapData())->buffer(DSLF_READ);
        d->lock();
        QRasterPaintEngine::drawImage(r, *img, sr);
    } else {
        d->unlock();
        d->prepareForBlit(pixmap.hasAlphaChannel());
        QPixmapData *data = pixmap.pixmapData();
        Q_ASSERT(data->classId() == QPixmapData::DirectFBClass);
        QDirectFBPixmapData *dfbData = static_cast<QDirectFBPixmapData*>(data);
        dfbData->unlockDirectFB();
        IDirectFBSurface *s = dfbData->directFBSurface();
        d->blit(r, s, sr);
    }
}

void QDirectFBPaintEngine::drawPixmap(const QPointF &p, const QPixmap &pm)
{
    drawPixmap(QRectF(p, pm.size()), pm, pm.rect());
}

void QDirectFBPaintEngine::drawTiledPixmap(const QRectF &r,
                                           const QPixmap &pixmap,
                                           const QPointF &offset)
{
    Q_D(QDirectFBPaintEngine);
    d->updateClip();
    if (pixmap.pixmapData()->classId() != QPixmapData::DirectFBClass) {
        RASTERFALLBACK(DRAW_TILED_PIXMAP, r, pixmap.size(), offset);
        d->lock();
        QRasterPaintEngine::drawTiledPixmap(r, pixmap, offset);
    } else if (!(d->compositionModeStatus & QDirectFBPaintEnginePrivate::PorterDuff_SupportedBlits)
               || (d->transformationType & QDirectFBPaintEnginePrivate::Matrix_BlitsUnsupported)
               || !d->dfbCanHandleClip(r)) {
        RASTERFALLBACK(DRAW_TILED_PIXMAP, r, pixmap.size(), offset);
        const QImage *img = static_cast<QDirectFBPixmapData*>(pixmap.pixmapData())->buffer(DSLF_READ);
        d->lock();
        QRasterPixmapData *data = new QRasterPixmapData(QPixmapData::PixmapType);
        data->fromImage(*img, Qt::AutoColor);
        const QPixmap pix(data);
        QRasterPaintEngine::drawTiledPixmap(r, pix, offset);
    } else {
        d->unlock();
        d->drawTiledPixmap(r, pixmap, offset);
    }
}


void QDirectFBPaintEngine::stroke(const QVectorPath &path, const QPen &pen)
{
    RASTERFALLBACK(STROKE_PATH, path, VOID_ARG(), VOID_ARG());
    Q_D(QDirectFBPaintEngine);
    d->lock();
    QRasterPaintEngine::stroke(path, pen);
}

void QDirectFBPaintEngine::drawPath(const QPainterPath &path)
{
    RASTERFALLBACK(DRAW_PATH, path, VOID_ARG(), VOID_ARG());
    Q_D(QDirectFBPaintEngine);
    d->lock();
    QRasterPaintEngine::drawPath(path);
}

void QDirectFBPaintEngine::drawPoints(const QPointF *points, int pointCount)
{
    RASTERFALLBACK(DRAW_POINTS, pointCount, VOID_ARG(), VOID_ARG());
    Q_D(QDirectFBPaintEngine);
    d->lock();
    QRasterPaintEngine::drawPoints(points, pointCount);
}

void QDirectFBPaintEngine::drawPoints(const QPoint *points, int pointCount)
{
    RASTERFALLBACK(DRAW_POINTS, pointCount, VOID_ARG(), VOID_ARG());
    Q_D(QDirectFBPaintEngine);
    d->lock();
    QRasterPaintEngine::drawPoints(points, pointCount);
}

void QDirectFBPaintEngine::drawEllipse(const QRectF &rect)
{
    RASTERFALLBACK(DRAW_ELLIPSE, rect, VOID_ARG(), VOID_ARG());
    Q_D(QDirectFBPaintEngine);
    d->lock();
    QRasterPaintEngine::drawEllipse(rect);
}

void QDirectFBPaintEngine::drawPolygon(const QPointF *points, int pointCount,
                                       PolygonDrawMode mode)
{
    RASTERFALLBACK(DRAW_POLYGON, pointCount, mode, VOID_ARG());
    Q_D(QDirectFBPaintEngine);
    d->lock();
    QRasterPaintEngine::drawPolygon(points, pointCount, mode);
}

void QDirectFBPaintEngine::drawPolygon(const QPoint *points, int pointCount,
                                       PolygonDrawMode mode)
{
    RASTERFALLBACK(DRAW_POLYGON, pointCount, mode, VOID_ARG());
    Q_D(QDirectFBPaintEngine);
    d->lock();
    QRasterPaintEngine::drawPolygon(points, pointCount, mode);
}

void QDirectFBPaintEngine::drawTextItem(const QPointF &p,
                                        const QTextItem &textItem)
{
    RASTERFALLBACK(DRAW_TEXT, p, textItem.text(), VOID_ARG());
    Q_D(QDirectFBPaintEngine);
    d->lock();
    QRasterPaintEngine::drawTextItem(p, textItem);
}

void QDirectFBPaintEngine::fill(const QVectorPath &path, const QBrush &brush)
{
    if (brush.style() == Qt::NoBrush)
        return;
    RASTERFALLBACK(FILL_PATH, path, brush, VOID_ARG());
    Q_D(QDirectFBPaintEngine);
    d->lock();
    QRasterPaintEngine::fill(path, brush);
}


void QDirectFBPaintEngine::fillRect(const QRectF &rect, const QBrush &brush)
{
    Q_D(QDirectFBPaintEngine);
    if (brush.style() == Qt::NoBrush)
        return;
    d->updateClip();
    if (d->dfbCanHandleClip(rect)) {
        switch (brush.style()) {
        case Qt::SolidPattern: {
            if (!(d->compositionModeStatus & QDirectFBPaintEnginePrivate::PorterDuff_SupportedPrimitives)
                || (d->transformationType & QDirectFBPaintEnginePrivate::Matrix_RectsUnsupported)) {
                break;
            }
            const QColor color = brush.color();
            if (!color.isValid())
                return;
            d->unlock();
            d->setDFBColor(color);
            const QRect r = state()->matrix.mapRect(rect).toRect();
            d->surface->FillRectangle(d->surface, r.x(), r.y(),
                                      r.width(), r.height());
            return; }
        case Qt::TexturePattern: {
            if (!(d->compositionModeStatus & QDirectFBPaintEnginePrivate::PorterDuff_SupportedBlits)
                || (d->transformationType & QDirectFBPaintEnginePrivate::Matrix_BlitsUnsupported)) {
                break;
            }

            const QPixmap texture = brush.texture();
            if (texture.pixmapData()->classId() != QPixmapData::DirectFBClass)
                break;

            d->unlock();
            d->drawTiledPixmap(rect, texture, rect.topLeft() - state()->brushOrigin);
            return; }
        default:
            break;
        }
    }
    RASTERFALLBACK(FILL_RECT, rect, brush, VOID_ARG());
    d->lock();
    QRasterPaintEngine::fillRect(rect, brush);
}

void QDirectFBPaintEngine::fillRect(const QRectF &rect, const QColor &color)
{
    if (!color.isValid())
        return;
    Q_D(QDirectFBPaintEngine);
    d->updateClip();
    if (!(d->compositionModeStatus & QDirectFBPaintEnginePrivate::PorterDuff_SupportedPrimitives)
        || (d->transformationType & QDirectFBPaintEnginePrivate::Matrix_RectsUnsupported)
        || !d->dfbCanHandleClip()) {
        RASTERFALLBACK(FILL_RECT, rect, color, VOID_ARG());
        d->lock();
        QRasterPaintEngine::fillRect(rect, color);
    } else {
        d->unlock();
        d->setDFBColor(color);
        const QRect r = state()->matrix.mapRect(rect).toRect();
        d->surface->FillRectangle(d->surface, r.x(), r.y(),
                                  r.width(), r.height());
    }
}

void QDirectFBPaintEngine::drawBufferSpan(const uint *buffer, int bufsize,
                                          int x, int y, int length,
                                          uint const_alpha)
{
    Q_D(QDirectFBPaintEngine);
    IDirectFBSurface *src = d->surfaceCache->getSurface(buffer, bufsize);
    // ### how does this play with setDFBColor
    src->SetColor(src, 0, 0, 0, const_alpha);
    const DFBRectangle rect = { 0, 0, length, 1 };
    d->surface->Blit(d->surface, src, &rect, x, y);
}

#ifdef QT_DIRECTFB_IMAGECACHE
static void cachedImageCleanupHook(qint64 key)
{
    delete imageCache.take(key);
}
void QDirectFBPaintEngine::initImageCache(int size)
{
    Q_ASSERT(size >= 0);
    imageCache.setMaxCost(size);
    typedef void (*_qt_image_cleanup_hook_64)(qint64);
    extern Q_GUI_EXPORT _qt_image_cleanup_hook_64 qt_image_cleanup_hook_64;
    qt_image_cleanup_hook_64 = ::cachedImageCleanupHook;
}

#endif // QT_DIRECTFB_IMAGECACHE

// ---- QDirectFBPaintEnginePrivate ----


QDirectFBPaintEnginePrivate::QDirectFBPaintEnginePrivate(QDirectFBPaintEngine *p)
    : surface(0), antialiased(false), simplePen(false),
      transformationType(0), opacity(255), dirtyClip(true),
      dfbHandledClip(false), dfbDevice(0),
      compositionModeStatus(0), q(p)
{
    fb = QDirectFBScreen::instance()->dfb();
    ignoreSystemClip = QDirectFBScreen::instance()->directFBFlags() & QDirectFBScreen::IgnoreSystemClip;
    surfaceCache = new SurfaceCache;
}

QDirectFBPaintEnginePrivate::~QDirectFBPaintEnginePrivate()
{
    delete surfaceCache;
}

bool QDirectFBPaintEnginePrivate::dfbCanHandleClip(const QRect &) const
{
    // TODO: Check to see if DirectFB can handle the clip for the given rect
    return dfbHandledClip;
}

bool QDirectFBPaintEnginePrivate::dfbCanHandleClip(const QRectF &) const
{
    // TODO: Check to see if DirectFB can handle the clip for the given rect
    return dfbHandledClip;
}

bool QDirectFBPaintEnginePrivate::dfbCanHandleClip() const
{
    return dfbHandledClip;
}

bool QDirectFBPaintEnginePrivate::isSimpleBrush(const QBrush &brush) const
{
    return (brush.style() == Qt::NoBrush) || (brush.style() == Qt::SolidPattern && !antialiased);
}

void QDirectFBPaintEnginePrivate::lock()
{
    // We will potentially get a new pointer to the buffer after a
    // lock so we need to call the base implementation of prepare so
    // it updates its rasterBuffer to point to the new buffer address.
    Q_ASSERT(dfbDevice);
    if (dfbDevice->lockFlags() != (DSLF_WRITE|DSLF_READ)) {
        dfbDevice->lockDirectFB(DSLF_READ|DSLF_WRITE);
        prepare(dfbDevice);
    }
}

void QDirectFBPaintEnginePrivate::unlock()
{
    Q_ASSERT(dfbDevice);
    dfbDevice->unlockDirectFB();
}

void QDirectFBPaintEnginePrivate::setTransform(const QTransform &transform)
{
    transformationType = transform.type();
    if (qMin(transform.m11(), transform.m22()) < 0) {
        transformationType |= QDirectFBPaintEnginePrivate::Matrix_NegativeScale;
    }
    setPen(q->state()->pen);
}

void QDirectFBPaintEnginePrivate::setPen(const QPen &pen)
{
    if (pen.style() == Qt::NoPen) {
        simplePen = true;
    } else if (pen.style() == Qt::SolidLine
               && !antialiased
               && pen.brush().style() == Qt::SolidPattern
               && pen.widthF() <= 1.0
               && (transformationType < QTransform::TxScale || pen.isCosmetic())) {
        simplePen = true;
    } else {
        simplePen = false;
    }
}

void QDirectFBPaintEnginePrivate::setCompositionMode(QPainter::CompositionMode mode)
{
    if (!surface)
        return;
    compositionModeStatus = PorterDuff_SupportedBlits;
    switch (mode) {
    case QPainter::CompositionMode_Clear:
        surface->SetPorterDuff(surface, DSPD_CLEAR);
        break;
    case QPainter::CompositionMode_Source:
        surface->SetPorterDuff(surface, DSPD_SRC);
        break;
    case QPainter::CompositionMode_SourceOver:
        compositionModeStatus |= PorterDuff_SupportedPrimitives;
        surface->SetPorterDuff(surface, DSPD_SRC_OVER);
        break;
    case QPainter::CompositionMode_DestinationOver:
        surface->SetPorterDuff(surface, DSPD_DST_OVER);
        break;
    case QPainter::CompositionMode_SourceIn:
        surface->SetPorterDuff(surface, DSPD_SRC_IN);
        break;
    case QPainter::CompositionMode_DestinationIn:
        surface->SetPorterDuff(surface, DSPD_DST_IN);
        break;
    case QPainter::CompositionMode_SourceOut:
        surface->SetPorterDuff(surface, DSPD_SRC_OUT);
        break;
    case QPainter::CompositionMode_DestinationOut:
        surface->SetPorterDuff(surface, DSPD_DST_OUT);
        break;
    case QPainter::CompositionMode_SourceAtop:
        surface->SetPorterDuff(surface, DSPD_SRC_ATOP);
        break;
    case QPainter::CompositionMode_DestinationAtop:
        surface->SetPorterDuff(surface, DSPD_DST_ATOP);
        break;
    case QPainter::CompositionMode_Plus:
        surface->SetPorterDuff(surface, DSPD_ADD);
        break;
    case QPainter::CompositionMode_Xor:
        surface->SetPorterDuff(surface, DSPD_XOR);
        break;
    default:
        compositionModeStatus = 0;
        break;
    }
}

void QDirectFBPaintEnginePrivate::setRenderHints(QPainter::RenderHints hints)
{
    const bool old = antialiased;
    antialiased = bool(hints & QPainter::Antialiasing);
    if (old != antialiased) {
        setPen(q->state()->pen);
    }
}

void QDirectFBPaintEnginePrivate::prepareForBlit(bool alpha)
{
    quint32 blittingFlags = alpha ? DSBLIT_BLEND_ALPHACHANNEL : DSBLIT_NOFX;
    if (opacity != 255) {
        blittingFlags |= DSBLIT_BLEND_COLORALPHA;
    }
    surface->SetColor(surface, 0xff, 0xff, 0xff, opacity);
    surface->SetBlittingFlags(surface, DFBSurfaceBlittingFlags(blittingFlags));
}

static inline uint ALPHA_MUL(uint x, uint a)
{
    uint t = x * a;
    t = ((t + (t >> 8) + 0x80) >> 8) & 0xff;
    return t;
}

void QDirectFBPaintEnginePrivate::setDFBColor(const QColor &color)
{
    Q_ASSERT(surface);
    const quint8 alpha = (opacity == 255 ?
                          color.alpha() : ALPHA_MUL(color.alpha(), opacity));
    surface->SetColor(surface, color.red(), color.green(), color.blue(), alpha);
    surface->SetPorterDuff(surface, DSPD_NONE);
    surface->SetDrawingFlags(surface, alpha == 255 ? DSDRAW_NOFX : DSDRAW_BLEND);
}

IDirectFBSurface *QDirectFBPaintEnginePrivate::getSurface(const QImage &img, bool *release)
{
#ifndef QT_DIRECTFB_IMAGECACHE
    *release = true;
    return QDirectFBScreen::instance()->createDFBSurface(img, QDirectFBScreen::DontTrackSurface);
#else
    const qint64 key = img.cacheKey();
    *release = false;
    if (imageCache.contains(key)) {
        return imageCache[key]->surface;
    }

    const int cost = cacheCost(img);
    const bool cache = cost <= imageCache.maxCost();
    QDirectFBScreen *screen = QDirectFBScreen::instance();
    const QImage::Format format = (img.format() == screen->alphaPixmapFormat() || QDirectFBPixmapData::hasAlphaChannel(img)
                                   ? screen->alphaPixmapFormat() : screen->pixelFormat());

    IDirectFBSurface *surface = screen->copyToDFBSurface(img, format,
                                                         cache
                                                         ? QDirectFBScreen::TrackSurface
                                                         : QDirectFBScreen::DontTrackSurface);
    if (cache) {
        CachedImage *cachedImage = new CachedImage;
        const_cast<QImage&>(img).data_ptr()->is_cached = true;
        cachedImage->surface = surface;
        imageCache.insert(key, cachedImage, cost);
    } else {
        *release = true;
    }
    return surface;
#endif
}


void QDirectFBPaintEnginePrivate::blit(const QRectF &dest, IDirectFBSurface *s, const QRectF &src)
{
    const QRect sr = src.toRect();
    const QRect dr = q->state()->matrix.mapRect(dest).toRect();
    if (dr.isEmpty())
        return;
    const DFBRectangle sRect = { sr.x(), sr.y(), sr.width(), sr.height() };
    DFBResult result;

    if (dr.size() == sr.size()) {
        result = surface->Blit(surface, s, &sRect, dr.x(), dr.y());
    } else {
        const DFBRectangle dRect = { dr.x(), dr.y(), dr.width(), dr.height() };
        result = surface->StretchBlit(surface, s, &sRect, &dRect);
    }
    if (result != DFB_OK)
        DirectFBError("QDirectFBPaintEngine::drawPixmap()", result);
}

static inline qreal fixCoord(qreal rect_pos, qreal pixmapSize, qreal offset)
{
    qreal pos = rect_pos - offset;
    while (pos > rect_pos)
        pos -= pixmapSize;
    while (pos + pixmapSize < rect_pos)
        pos += pixmapSize;
    return pos;
}

void QDirectFBPaintEnginePrivate::drawTiledPixmap(const QRectF &dest, const QPixmap &pixmap, const QPointF &off)
{
    Q_ASSERT(!dirtyClip);
    Q_ASSERT(!(transformationType & Matrix_BlitsUnsupported));
    const QTransform &transform = q->state()->matrix;
    const QRect destinationRect = transform.mapRect(dest).toRect().normalized();
    QRect newClip = destinationRect;
    if (!currentClip.isEmpty())
        newClip &= currentClip;

    if (newClip.isNull())
        return;

    const DFBRegion clip = {
        newClip.x(),
        newClip.y(),
        newClip.x() + newClip.width() - 1,
        newClip.y() + newClip.height() - 1
    };
    surface->SetClip(surface, &clip);

    QPointF offset = off;
    Q_ASSERT(transform.type() <= QTransform::TxScale);
    prepareForBlit(pixmap.hasAlphaChannel());
    QPixmapData *data = pixmap.pixmapData();
    Q_ASSERT(data->classId() == QPixmapData::DirectFBClass);
    QDirectFBPixmapData *dfbData = static_cast<QDirectFBPixmapData*>(data);
    dfbData->unlockDirectFB();
    const QSize pixmapSize = dfbData->size();
    IDirectFBSurface *sourceSurface = dfbData->directFBSurface();
    if (transform.isScaling()) {
        Q_ASSERT(qMin(transform.m11(), transform.m22()) >= 0);
        offset.rx() *= transform.m11();
        offset.ry() *= transform.m22();

        const QSizeF mappedSize(pixmapSize.width() * transform.m11(), pixmapSize.height() * transform.m22());
        qreal y = ::fixCoord(destinationRect.y(), mappedSize.height(), offset.y());
        const qreal startX = ::fixCoord(destinationRect.x(), mappedSize.width(), offset.x());
        while (y <= destinationRect.bottom()) {
            qreal x = startX;
            while (x <= destinationRect.right()) {
                const DFBRectangle destination = { qRound(x), qRound(y), mappedSize.width(), mappedSize.height() };
                surface->StretchBlit(surface, sourceSurface, 0, &destination);
                x += mappedSize.width();
            }
            y += mappedSize.height();
        }
    } else {
        qreal y = ::fixCoord(destinationRect.y(), pixmapSize.height(), offset.y());
        const qreal startX = ::fixCoord(destinationRect.x(), pixmapSize.width(), offset.x());
        int horizontal = qMax(1, destinationRect.width() / pixmapSize.width()) + 1;
        if (startX != destinationRect.x())
            ++horizontal;
        int vertical = qMax(1, destinationRect.height() / pixmapSize.height()) + 1;
        if (y != destinationRect.y())
            ++vertical;

        const int maxCount = (vertical * horizontal);
        QVarLengthArray<DFBRectangle, 16> sourceRects(maxCount);
        QVarLengthArray<DFBPoint, 16> points(maxCount);

        int i = 0;
        while (y <= destinationRect.bottom()) {
            Q_ASSERT(i < maxCount);
            qreal x = startX;
            while (x <= destinationRect.right()) {
                points[i].x = qRound(x);
                points[i].y = qRound(y);
                sourceRects[i].x = 0;
                sourceRects[i].y = 0;
                sourceRects[i].w = int(pixmapSize.width());
                sourceRects[i].h = int(pixmapSize.height());
                x += pixmapSize.width();
                ++i;
            }
            y += pixmapSize.height();
        }
        surface->BatchBlit(surface, sourceSurface, sourceRects.constData(), points.constData(), i);
    }

    if (currentClip.isEmpty()) {
        surface->SetClip(surface, 0);
    } else {
        const DFBRegion clip = {
            currentClip.x(),
            currentClip.y(),
            currentClip.x() + currentClip.width(),
            currentClip.y() + currentClip.height()
        };
        surface->SetClip(surface, &clip);
    }
}

void QDirectFBPaintEnginePrivate::updateClip()
{
    if (!dirtyClip)
        return;

    currentClip = QRect();
    const QClipData *clipData = clip();
    if (!clipData || !clipData->enabled) {
        surface->SetClip(surface, NULL);
        dfbHandledClip = true;
    } else if (clipData->hasRectClip) {
        const DFBRegion r = {
            clipData->clipRect.x(),
            clipData->clipRect.y(),
            clipData->clipRect.x() + clipData->clipRect.width(),
            clipData->clipRect.y() + clipData->clipRect.height()
        };
        surface->SetClip(surface, &r);
        currentClip = clipData->clipRect.normalized();
        // ### is this guaranteed to always be normalized?
        dfbHandledClip = true;
    } else if (clipData->hasRegionClip && ignoreSystemClip && clipData->clipRegion == systemClip) {
        dfbHandledClip = true;
    } else {
        dfbHandledClip = false;
    }

    dirtyClip = false;
}

void QDirectFBPaintEnginePrivate::systemStateChanged()
{
    dirtyClip = true;
    QRasterPaintEnginePrivate::systemStateChanged();
}

IDirectFBSurface *SurfaceCache::getSurface(const uint *buf, int size)
{
    if (buffer == buf && bufsize == size)
        return surface;

    clear();

    const DFBSurfaceDescription description = QDirectFBScreen::getSurfaceDescription(buf, size);
    surface = QDirectFBScreen::instance()->createDFBSurface(description, QDirectFBScreen::TrackSurface);
    if (!surface)
        qWarning("QDirectFBPaintEngine: SurfaceCache: Unable to create surface");

    buffer = const_cast<uint*>(buf);
    bufsize = size;

    return surface;
}

void SurfaceCache::clear()
{
    if (surface && QDirectFBScreen::instance())
        QDirectFBScreen::instance()->releaseDFBSurface(surface);
    surface = 0;
    buffer = 0;
    bufsize = 0;
}


static inline QRect mapRect(const QTransform &transform, const QRect &rect) { return transform.mapRect(rect); }
static inline QRect mapRect(const QTransform &transform, const QRectF &rect) { return transform.mapRect(rect).toRect(); }
static inline QLine map(const QTransform &transform, const QLine &line) { return transform.map(line); }
static inline QLine map(const QTransform &transform, const QLineF &line) { return transform.map(line).toLine(); }
template <class T>
static inline void drawLines(const T *lines, int n, const QTransform &transform, IDirectFBSurface *surface)
{
    if (n == 1) {
        const QLine l = ::map(transform, lines[0]);
        surface->DrawLine(surface, l.x1(), l.y1(), l.x2(), l.y2());
    } else {
        QVarLengthArray<DFBRegion, 32> lineArray(n);
        for (int i=0; i<n; ++i) {
            const QLine l = ::map(transform, lines[i]);
            lineArray[i].x1 = l.x1();
            lineArray[i].y1 = l.y1();
            lineArray[i].x2 = l.x2();
            lineArray[i].y2 = l.y2();
        }
        surface->DrawLines(surface, lineArray.constData(), n);
    }
}

template <class T>
static inline void fillRects(const T *rects, int n, const QTransform &transform, IDirectFBSurface *surface)
{
    if (n == 1) {
        const QRect r = ::mapRect(transform, rects[0]);
        surface->FillRectangle(surface, r.x(), r.y(), r.width(), r.height());
    } else {
        QVarLengthArray<DFBRectangle, 32> rectArray(n);
        for (int i=0; i<n; ++i) {
            const QRect r = ::mapRect(transform, rects[i]);
            rectArray[i].x = r.x();
            rectArray[i].y = r.y();
            rectArray[i].w = r.width();
            rectArray[i].h = r.height();
        }
        surface->FillRectangles(surface, rectArray.constData(), n);
    }
}

template <class T>
static inline void drawRects(const T *rects, int n, const QTransform &transform, IDirectFBSurface *surface)
{
    for (int i=0; i<n; ++i) {
        const QRect r = ::mapRect(transform, rects[i]);
        surface->DrawRectangle(surface, r.x(), r.y(), r.width(), r.height());
    }
}

#ifdef QT_DIRECTFB_WARN_ON_RASTERFALLBACKS
template <typename T> inline const T *ptr(const T &t) { return &t; }
template <> inline const bool* ptr<bool>(const bool &) { return 0; }
template <typename device, typename T1, typename T2, typename T3>
static void rasterFallbackWarn(const char *msg, const char *func, const device *dev,
                               uint transformationType, bool simplePen,
                               bool dfbHandledClip, uint compositionModeStatus,
                               const char *nameOne, const T1 &one,
                               const char *nameTwo, const T2 &two,
                               const char *nameThree, const T3 &three)
{
    QString out;
    QDebug dbg(&out);
    dbg << msg << (QByteArray(func) + "()")  << "painting on";
    if (dev->devType() == QInternal::Widget) {
        dbg << static_cast<const QWidget*>(dev);
    } else {
        dbg << dev << "of type" << dev->devType();
    }

    dbg << QString("transformationType 0x%1").arg(transformationType, 3, 16, QLatin1Char('0'))
        << "simplePen" << simplePen
        << "dfbHandledClip" << dfbHandledClip
        << "compositionModeStatus" << compositionModeStatus;

    const T1 *t1 = ptr(one);
    const T2 *t2 = ptr(two);
    const T3 *t3 = ptr(three);

    if (t1) {
        dbg << nameOne << *t1;
        if (t2) {
            dbg << nameTwo << *t2;
            if (t3) {
                dbg << nameThree << *t3;
            }
        }
    }
    qWarning("%s", qPrintable(out));
}
#endif


#endif // QT_NO_DIRECTFB
