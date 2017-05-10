#include "VideoItem.h"
#include <QSGSimpleRectNode>

VideoItem::VideoItem(QQuickItem *parent)
    : QQuickItem(parent)
{

}

VideoItem::~VideoItem()
{

}

QSGNode *VideoItem::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    QSGGeometryNode *node = 0;
    QSGGeometry *geometry = 0;

    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 32);
        geometry->setLineWidth(2);
        geometry->setDrawingMode(QSGGeometry::DrawLineStrip);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);



    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(32);
    }

    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
    material->setColor(QColor(255, 0, 0));
    node->setMaterial(material);
    node->setFlag(QSGNode::OwnsMaterial);
/*
    QRectF bounds = boundingRect();
       QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();
       for (int i = 0; i < 32; ++i) {
           qreal t = i / qreal(32 - 1);
           qreal invt = 1 - t;

           QPointF pos = invt * invt * invt * m_p1
                       + 3 * invt * invt * t * m_p2
                       + 3 * invt * t * t * m_p3
                       + t * t * t * m_p4;

           float x = bounds.x() + pos.x() * bounds.width();
           float y = bounds.y() + pos.y() * bounds.height();

           vertices[i].set(x, y);
       }
       */
       node->markDirty(QSGNode::DirtyGeometry);

       return node;
}
