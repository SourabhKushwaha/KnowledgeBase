#include "DataManager.h"

struct DataManagerData
{
    DataManagerData():
        lattitute(0.0),
        longitute(0.0)
    {}

    double lattitute;
    double longitute;
    QString apiKey;
};

DataManager::DataManager(QObject *parent):
    QObject(parent)
{
    d = new DataManagerData;
    d->lattitute = 26.4499;
    d->longitute = 80.3319;
}

double DataManager::lattitute()
{
    return d->lattitute;
}

void DataManager::setLattitute(double val)
{
    if(d->lattitute != val)
    {
        d->lattitute = val;
        emit lattituteChanged(val);
    }
}

double DataManager::longitute()
{
    return d->longitute;
}

void DataManager::setLongitute(double val)
{
    if(d->longitute != val)
    {
        d->longitute = val;
        emit longituteChanged(val);
    }
}

QString DataManager::getAPIKey()
{
    return QString("AIzaSyBCdNVOM-Zie0oZjy4Dg-4ImIXFAHvfNx0");
}

QString DataManager::htmlURL()
{
    return "qrc:/Map/Map.html";
}
