#include "MainWindow.h"
#include <QApplication>
#include <QQuickView>
#include <QQmlContext>
#include <DataManager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataManager *d = new DataManager;
    //qmlRegisterType<DataManager>("com.example.DataManager", 1, 0, "DataManager");

    QQuickView *viewver = new QQuickView;
    viewver->rootContext()->setContextProperty("dataManager", d);
    viewver->setSource(QUrl("qrc:/Qml/Main.qml"));
    viewver->show();

    //MainWindow w;
    //w.show();

    return a.exec();
}
