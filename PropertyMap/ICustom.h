#ifndef ICUSTOM_H
#define ICUSTOM_H

#include <QtPlugin>

namespace Example
{

class ICustom
{
public:
    virtual QString name() const = 0;
    virtual void setName(const QString &) = 0;
    virtual void nameChanged(QString) = 0;
};

}

Q_DECLARE_INTERFACE(Example::ICustom, "com.example.ICustom/1.0")

#endif // ICUSTOM_H
