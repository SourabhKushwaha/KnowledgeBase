#ifndef VIDEOITEM_H
#define VIDEOITEM_H

#include <QQuickItem>

class VideoItem : public QQuickItem
{
    Q_OBJECT

public:
    VideoItem(QQuickItem *parent = 0);
    ~VideoItem();

    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
};

#endif // VIDEOITEM_H
