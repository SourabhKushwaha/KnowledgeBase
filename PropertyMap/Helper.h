#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include "Custom.h"

class Helper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(Custom* custom READ custom WRITE setCustom NOTIFY customChanged)

public:
    Helper();

    QString name();
    void setName(QString);
    Q_SIGNAL void nameChanged(QString);

    Custom* custom();
    void setCustom(Custom*);
    Q_SIGNAL void customChanged(Custom*);
};

#endif // HELPER_H
