#include "Helper.h"
#include "Custom.h"

Helper::Helper()
{

}

QString Helper::name()
{
    return "Hello";
}

void Helper::setName(QString)
{

}

Custom *Helper::custom()
{
    return new Custom;
}

void Helper::setCustom(Custom *)
{

}
