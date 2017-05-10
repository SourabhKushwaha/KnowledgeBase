#include "MainWindow.h"

#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent)
{
    qWid = new QLabel;
    this->setCentralWidget(qWid);
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //event->ignore();
}

void MainWindow::updateImgHandler(QImage img)
{
    //img.setDevicePixelRatio(0.25);
    qWid->setPixmap(QPixmap::fromImage(img));
}
