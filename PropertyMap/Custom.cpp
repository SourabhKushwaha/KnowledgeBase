#include "Custom.h"

Custom::Custom(QObject *parent):
    QObject(parent)
{

}

QString Custom::name() const
{
    return "Custom";
}

void Custom::setName(const QString &)
{

}
