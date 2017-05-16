#ifndef QMLBRIDGE_H
#define QMLBRIDGE_H

#include <QObject>
#include <QQmlContext>
#include <QQuickItem>

struct QmlBridgeData;

class QmlBridge : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
public:
    static QmlBridge* instance();
    ~QmlBridge();

    QString userName();
    Q_INVOKABLE void setUserName(QString);
    Q_SIGNAL void userNameChanged();
    Q_INVOKABLE void sendMsg(QString);

    void recievedMsg(QString);

    void setQmlContext(QQmlContext*);
    void setQmlRootItem(QQuickItem*);

signals:
    void sendDataOverNetwork(QString);

protected:
    QmlBridge();

private:
    QmlBridgeData *d;

};

#endif // QMLBRIDGE_H
