import QtQuick 2.6

WorkSpaceTile
{
    id: workSpaceTile
    Rectangle{
        id:mapView
        anchors.fill: parent
        color: "green"

        MouseArea{
            anchors.fill: parent
            onDoubleClicked: console.log("map");
        }
    }
}
