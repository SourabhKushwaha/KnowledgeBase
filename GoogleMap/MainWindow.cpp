#include "MainWindow.h"

#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineSettings>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWebEngineView* webview = new QWebEngineView;

    QUrl url = QUrl("qrc:/Map/Map.html");

    this->setCentralWidget(webview);
    webview->page()->load(url);
}

MainWindow::~MainWindow()
{
}
