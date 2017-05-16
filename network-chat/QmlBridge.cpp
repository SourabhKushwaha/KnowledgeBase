#include "QmlBridge.h"
#include <QQuickItem>
#include <QDebug>

struct QmlBridgeData
{
    QmlBridgeData():
        qmlRootContext(0),
        rootItem(0)
    {

    }

    QString userName;
    QQmlContext *qmlRootContext;
    QQuickItem *rootItem;

};

QmlBridge::QmlBridge()
{
    d = new QmlBridgeData;
}


QmlBridge *QmlBridge::instance()
{
    static QmlBridge theInstance;
    return &theInstance;
}

QmlBridge::~QmlBridge()
{
    delete d;
}

QString QmlBridge::userName()
{
    return d->userName;
}

void QmlBridge::setUserName(QString val)
{
    if(d->userName != val)
    {
        d->userName = val;
        emit userNameChanged();
    }
}

void QmlBridge::sendMsg(QString msg)
{
    emit sendDataOverNetwork(msg);
}

void QmlBridge::recievedMsg(QString msg)
{
    QVariant returnedValue;
    if(d->rootItem){
        //        QQuickItem* item = d->rootItem->findChild
        //                <QQuickItem*>(QString("root"), Qt::FindChildrenRecursively);
        QMetaObject::invokeMethod(d->rootItem, "appendMsgInMsgArea",
                                  Q_RETURN_ARG(QVariant, returnedValue),
                                  Q_ARG(QVariant, msg));

        //qDebug() << "QML function returned:" << returnedValue.toString();
    }
}

void QmlBridge::setQmlContext(QQmlContext *ctx)
{
    d->qmlRootContext = ctx;
}

void QmlBridge::setQmlRootItem(QQuickItem *item)
{
    d->rootItem = item;
}
