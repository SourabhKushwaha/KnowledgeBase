#ifndef IMAGETHREAD_H
#define IMAGETHREAD_H

#include <QThread>
#include <QImage>

class AV_DATA;

class ImageThread : public QThread
{
    Q_OBJECT
public:
    ImageThread(QObject *parent = NULL);
    ~ImageThread();
    void setPath(QString path);
    void run();

signals:
    Q_SIGNAL void updateImg(QImage img);

public:
    AV_DATA *d;
};

#endif // IMAGETHREAD_H
