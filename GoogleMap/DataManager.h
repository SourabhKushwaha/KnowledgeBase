#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>

struct DataManagerData;

class DataManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double lattitute READ lattitute WRITE setLattitute NOTIFY lattituteChanged)
    Q_PROPERTY(double longitute READ longitute WRITE setLongitute NOTIFY longituteChanged)

public:
    DataManager(QObject* parent = NULL);

    double lattitute();
    void setLattitute(double);
    Q_SIGNAL void lattituteChanged(double);

    double longitute();
    void setLongitute(double);
    Q_SIGNAL void longituteChanged(double);

    Q_INVOKABLE QString getAPIKey();
    Q_INVOKABLE QString htmlURL();

private:
    DataManagerData *d;
};

#endif // DATAMANAGER_H
