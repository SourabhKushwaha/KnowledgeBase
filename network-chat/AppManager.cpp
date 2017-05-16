#include "AppManager.h"
#include "QmlBridge.h"

struct AppManagerData
{
    AppManagerData():
        qmlBridge(0)
    {
        qmlBridge = QmlBridge::instance();
    }

    QmlBridge *qmlBridge;
    QString myNickName;
};

AppManager::AppManager()
{
    d =  new AppManagerData;

    connect(&client, SIGNAL(newMessage(QString,QString)),
            this, SLOT(appendMessage(QString,QString)));
    connect(&client, SIGNAL(newParticipant(QString)),
            this, SLOT(newParticipant(QString)));
    connect(&client, SIGNAL(participantLeft(QString)),
            this, SLOT(participantLeft(QString)));

    myNickName = client.nickName();
    newParticipant(myNickName);
}

void AppManager::appendMessage(const QString &from, const QString &message)
{
    d->qmlBridge->recievedMsg(QString("%1:%2").arg(from).arg(message));
}

void AppManager::sendDataOverNetwork(const QString &msg)
{
    client.sendMessage(msg);
}

void AppManager::newParticipant(const QString &nick)
{
    d->qmlBridge->recievedMsg(nick);
}

void AppManager::participantLeft(const QString &nick)
{
    d->qmlBridge->recievedMsg(nick);
}
