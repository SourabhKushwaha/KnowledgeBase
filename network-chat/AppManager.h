#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>
#include "client.h"

struct AppManagerData;

class AppManager : public QObject
{
    Q_OBJECT
public:
    AppManager();

public slots:
    void appendMessage(const QString &from, const QString &message);

private slots:
    void sendDataOverNetwork(const QString&);
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);

private:
    Client client;
    QString myNickName;
    AppManagerData *d;
};

#endif // APPMANAGER_H
