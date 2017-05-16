import QtQuick 2.6
import QtQuick.Window 2.2

Item{
    id: mainWindow
    height: 600
    width: 800
    property real screenAspectRatio: width/height

    WorkSpace{
        id:workspace
        anchors.fill: parent
    }

    Component.onCompleted: {
        var googleMapsComponent = Qt.createComponent("qrc:/MapView.qml")
        if (googleMapsComponent.status === Component.Ready){
            var googleMapObject  = googleMapsComponent.createObject(workspace);
            workspace.addTile(googleMapObject);
        }

        var videoPlayerComponent = Qt.createComponent("qrc:/VideoView.qml")
        if (videoPlayerComponent.status === Component.Ready){
            var videoPlayerObject  = videoPlayerComponent.createObject(workspace);
            workspace.addTile(videoPlayerObject);
        }
    }
}
