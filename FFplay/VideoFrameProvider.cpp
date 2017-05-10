#include "VideoFrameProvider.h"
#include <QPainter>

VideoFrameProvider::VideoFrameProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

QPixmap VideoFrameProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    return p;
}

void VideoFrameProvider::updateImgHandler(QImage img)
{
    p = QPixmap::fromImage(img);
    emit imgUpdated();
}
