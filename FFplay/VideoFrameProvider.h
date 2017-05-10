#ifndef VIDEOFRAMEPROVIDER_H
#define VIDEOFRAMEPROVIDER_H

#include <QObject>
#include <QQuickImageProvider>

class VideoFrameProvider : public QObject, public QQuickImageProvider
{
    Q_OBJECT

public:
    VideoFrameProvider();

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

public slots:
    void updateImgHandler(QImage img);

signals:
    void imgUpdated();

private:
    QPixmap p;
};

#endif // VIDEOFRAMEPROVIDER_H
