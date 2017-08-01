#include <QGUIApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QtCore/QSettings>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkSession>

#include "AppManager.h"
#include "QmlBridge.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QString userScope("QtProject");
    QString networkName("QtNetwork");
    QString networkConfg("DefaultNetworkConfiguration");

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)
    {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, userScope);
        settings.beginGroup(networkName);
        const QString id = settings.value(networkConfg).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        QNetworkSession *networkSession = new QNetworkSession(config, &app);
        networkSession->open();
        networkSession->waitForOpened();

        if (networkSession->isOpen()) {
            // Save the used configuration
            QNetworkConfiguration config = networkSession->configuration();
            QString id;
            if (config.type() == QNetworkConfiguration::UserChoice) {
                id = networkSession->sessionProperty(
                        QLatin1String("UserChoiceConfiguration")).toString();
            } else {
                id = config.identifier();
            }

            QSettings settings(QSettings::UserScope, userScope);
            settings.beginGroup(networkName);
            settings.setValue(networkConfg, id);
            settings.endGroup();
        }
    }


    AppManager *appM = new AppManager;
    QmlBridge *qmlBridge = QmlBridge::instance();

    QObject::connect(qmlBridge, SIGNAL(sendDataOverNetwork(QString)),
                     appM, SLOT(sendDataOverNetwork(QString)));

    QQuickView *view = new QQuickView;
    view->setSource(QUrl("qrc:/Qml/Main.qml"));
    view->rootContext()->setContextProperty("qmlBridge", qmlBridge);
    qmlBridge->setQmlContext(view->rootContext());
    qmlBridge->setQmlRootItem(view->rootObject());
    view->resize(200, 300);
    view->show();

    return app.exec();
}
