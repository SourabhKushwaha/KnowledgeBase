#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SerialCommunicator.h"
#include <QStandardItemModel>

struct MainWindowData
{
    MainWindowData() :
        serialCommunicator(0)
    {}

    ~MainWindowData()
    {
        if(serialCommunicator)
        {
            delete serialCommunicator;
            serialCommunicator = 0;
        }
    }

    SerialCommunicator* serialCommunicator;
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    d = new MainWindowData;

    d->serialCommunicator = new SerialCommunicator(this);
    connect(d->serialCommunicator,
            SIGNAL(dataReceived(QByteArray)),
            this,
            SLOT(onDataReceived(QByteArray)));
    ui->comPortComboBox->setModel(d->serialCommunicator->comPortModel());
    ui->baudRateComboBox->setModel(d->serialCommunicator->baudRateModel());
    ui->baudRateComboBox->setCurrentIndex(
                d->serialCommunicator->baudRateModel()->rowCount() - 1);

    ui->showReceivedCheckBox->setChecked(true);
    ui->showSendCheckBox->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startPushButton_clicked()
{
    if(!d->serialCommunicator)
        return;

    d->serialCommunicator->setPortName(ui->comPortComboBox->currentText());
    d->serialCommunicator->setBaudRate(ui->baudRateComboBox->currentText().toInt());
    d->serialCommunicator->startCommunication();
}

void MainWindow::on_stopPushButton_clicked()
{
    if(!d->serialCommunicator)
        return;

    d->serialCommunicator->stopCommunication();
}

void MainWindow::on_clearPushButton_clicked()
{
    ui->dataTextBrowser->clear();
}

void MainWindow::on_updatePortsPushButton_clicked()
{
    if(!d->serialCommunicator)
        return;

    d->serialCommunicator->updateAvailablePorts();
}

void MainWindow::onDataReceived(const QByteArray &data)
{
    int recsize = data.size();

    if (recsize > 0)
    {
        ui->dataTextBrowser->append(data);
    }
}

void MainWindow::on_sendMsgBtn_clicked()
{

    if(!d->serialCommunicator)
        return;

    d->serialCommunicator->sendData(ui->sendMsgLEdit->text().toUtf8());
}
