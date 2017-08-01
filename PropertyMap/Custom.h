#ifndef CUSTOM_H
#define CUSTOM_H

#include <QObject>
#include "ICustom.h"

class Custom : public QObject, public Example::ICustom
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    Custom(QObject *parent = 0);

    QString name() const;
    void setName(const QString &);
    Q_SIGNAL void nameChanged(QString);
};

#endif // CUSTOM_H
