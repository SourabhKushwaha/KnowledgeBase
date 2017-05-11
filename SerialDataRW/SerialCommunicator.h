#ifndef SERIALCOMMUNICATOR_H
#define SERIALCOMMUNICATOR_H

#include <QObject>
#include <QSerialPortInfo>

class QStandardItemModel;
struct SerialCommunicatorData;
class SerialCommunicator : public QObject
{
    Q_OBJECT

public:
    SerialCommunicator(QObject* parent = 0);
    ~SerialCommunicator();

    void startCommunication();
    void stopCommunication();

    void sendData(const QByteArray& data);
    Q_SIGNAL void dataReceived(const QByteArray& data);

    void setPortName(const QString& portName);
    QString portName() const;
    Q_SIGNAL void portNameChanged(const QString& portName);

    void setBaudRate(int baudRate);
    int baudRate() const;
    Q_SIGNAL void baudRateChanged(int baudRate);

    void updateAvailablePorts();
    QStandardItemModel* comPortModel();
    QStandardItemModel* baudRateModel();

    void startSendingHeartbeat();
    void stopSendingHeartbeat();

private slots:
    void onReadyRead();

private:
    SerialCommunicatorData* d;
};

#endif // SERIALCOMMUNICATOR_H
