#include <QApplication>
#include <MainWindow.h>
#include <ImageThread.h>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QQmlContext>
#include <VideoFrameProvider.h>

#include <VideoItem.h>

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    ImageThread *imgT = new ImageThread;
    int val = 2;
    if(val == 1){
        MainWindow *mainWin = new MainWindow;
        QObject::connect(imgT, SIGNAL(updateImg(QImage)), mainWin, SLOT(updateImgHandler(QImage)));
        imgT->setPath("udp://@224.10.10.10:15004/");
        imgT->start();
        mainWin->show();
    }
    else if(val == 2)
    {
        QQuickView *viewer = new QQuickView;
        QQmlEngine *engine = viewer->engine();
        imgT->setPath("udp://@224.10.10.10:15004/");
        //imgT->setPath("rtp://224.10.10.10:15004");

        //qmlRegisterType<VideoItem>("VideoLib", 1, 0, "VideoItem");

        VideoFrameProvider *vFrameProvider = new VideoFrameProvider;
        engine->addImageProvider(QLatin1String("vFrameProvider"), vFrameProvider);
        QObject::connect(imgT, SIGNAL(updateImg(QImage)), vFrameProvider, SLOT(updateImgHandler(QImage)));
        viewer->rootContext()->setContextProperty("vFrameProvider", vFrameProvider);
        imgT->start();
        viewer->setSource(QUrl(QLatin1String("qrc:///qml/Main.qml")));
        viewer->show();
    }

    return app.exec();
}
