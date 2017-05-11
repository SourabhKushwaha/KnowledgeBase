#include "SerialCommunicator.h"
#include "DataConverter.h"

#include <QStandardItemModel>
#include <QSerialPort>
#include <QHash>

#include <QDebug>

struct SerialCommunicatorData
{
    SerialCommunicatorData() : serialPort(0),
                               comPortModel(0)
                               {}

    ~SerialCommunicatorData()
    {
        if(serialPort)
        {
            delete serialPort;
            serialPort = 0;
        }

        if(comPortModel)
        {
            delete comPortModel;
            comPortModel = 0;
        }
    }

    QSerialPort* serialPort;
    QString portName;
    int baudRate;
    QStandardItemModel* comPortModel;
    QStandardItemModel* baudRateModel;
    QHash<QString, QSerialPortInfo> portNameSerialPortInfoHash;
};

SerialCommunicator::SerialCommunicator(QObject *parent)
    : QObject(parent)
{
    d = new SerialCommunicatorData;

    d->serialPort = new QSerialPort(this);
    connect(d->serialPort,
            SIGNAL(readyRead()),
            this,
            SLOT(onReadyRead()));

    d->comPortModel = new QStandardItemModel(this);
    this->updateAvailablePorts();

    d->baudRateModel = new QStandardItemModel(this);
    for(int i=1200; i<=115200; i*=2)
    {
        if(i == 76800)
            i = 57600;

        QStandardItem* item = new QStandardItem(QString::number(i));
        d->baudRateModel->appendRow(item);
    }
}

SerialCommunicator::~SerialCommunicator()
{
    delete d;
    d = 0;
}

void SerialCommunicator::startCommunication()
{
    if(!d->serialPort || d->serialPort->isOpen())
        return;

    d->serialPort->setPort(d->portNameSerialPortInfoHash.value(d->portName));
    if(d->serialPort->open(QIODevice::ReadWrite))
    {
        d->serialPort->setBaudRate(QSerialPort::BaudRate(d->baudRate));
        d->serialPort->setFlowControl(QSerialPort::NoFlowControl);
        d->serialPort->setDataBits(QSerialPort::Data8);
        d->serialPort->setParity(QSerialPort::NoParity);
        d->serialPort->setStopBits(QSerialPort::OneStop);
    }
}

void SerialCommunicator::stopCommunication()
{
    if(!d->serialPort || !d->serialPort->isOpen())
        return;

    d->serialPort->close();
}

void SerialCommunicator::sendData(const QByteArray &data)
{
    if(!d->serialPort || !d->serialPort->isOpen())
        return;

    d->serialPort->write(data);
}

void SerialCommunicator::setPortName(const QString &portName)
{
    if(d->portName == portName)
        return;

    d->portName = portName;
    emit portNameChanged(portName);
}

QString SerialCommunicator::portName() const
{
    return d->portName;
}

void SerialCommunicator::setBaudRate(int baudRate)
{
    if(d->baudRate == baudRate)
        return;

    d->baudRate = baudRate;
    emit baudRateChanged(baudRate);
}

int SerialCommunicator::baudRate() const
{
    return d->baudRate;
}

void SerialCommunicator::updateAvailablePorts()
{
    if(!d->comPortModel)
        return;

    d->comPortModel->clear();
    Q_FOREACH(QSerialPortInfo serialPortInfo, QSerialPortInfo::availablePorts())
    {
        QStandardItem* item = new QStandardItem(serialPortInfo.portName());
        d->portNameSerialPortInfoHash.insert(
                    serialPortInfo.portName(), serialPortInfo);
        d->comPortModel->appendRow(item);
    }
}

QStandardItemModel* SerialCommunicator::comPortModel()
{
    return d->comPortModel;
}

QStandardItemModel* SerialCommunicator::baudRateModel()
{
    return d->baudRateModel;
}

void SerialCommunicator::onReadyRead()
{
    if(!d->serialPort)
        return;

    QByteArray data = d->serialPort->readAll();
    emit dataReceived(data);
}
