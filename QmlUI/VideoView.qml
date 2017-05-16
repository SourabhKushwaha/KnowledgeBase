import QtQuick 2.6

WorkSpaceTile
{
    id: workSpaceTile
    Rectangle{
        id:videoView
        anchors.fill: parent
        color: "red"

        MouseArea{
            anchors.fill: parent
            onDoubleClicked: console.log("Video");
        }
    }
}
