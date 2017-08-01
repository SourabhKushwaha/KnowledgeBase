#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "ICustom.h"
#include "Helper.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //qmlRegisterType<Example::ICustom>("com.example.ICustom", 1,0, "ICustom");
    QQmlApplicationEngine engine;
    Helper* helper = new Helper;
    engine.rootContext()->setContextProperty("helper", helper);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
