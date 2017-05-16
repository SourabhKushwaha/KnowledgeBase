import QtQuick 2.6

Rectangle{
    id: workSpaceTile

    state: "Maximize"
    property int index
    property QtObject item: null
    signal tileStateChanged(variant tile)
    property bool isActive: false

    states: [
        State {
            name: "Maximize"

            AnchorChanges {
                target: workSpaceTile;
                anchors.left: workSpaceTile.parent.left;
                anchors.right: workSpaceTile.parent.right;
                anchors.top: workSpaceTile.parent.top;
                anchors.bottom: workSpaceTile.parent.bottom;
            }

            PropertyChanges {
                target: workSpaceTile;
                isActive: true
            }

            PropertyChanges {
                target: mouseArea;
                z: -10
            }
        },

        State {
            name: "SmallSize"

            PropertyChanges {
                target: workSpaceTile;
                width: workSpaceTile.parent.width * 0.2;
                height: width / mainWindow.screenAspectRatio;
                anchors.bottomMargin: 20;
                anchors.rightMargin: {
                    return 20;
                }

                isActive: false
            }

            PropertyChanges {
                target: mouseArea;
                z: 10
            }

            AnchorChanges {
                target: workSpaceTile;
                anchors.bottom: workSpaceTile.parent.bottom;
                anchors.right: workSpaceTile.parent.right;
            }
        }
    ]

    onStateChanged: {
        tileStateChanged(this);
    }

    MouseArea{
        id:mouseArea
        anchors.fill: parent
        z: 10

        onDoubleClicked: {
            if(!isActive){
                if(workSpaceTile.state === "Maximize")
                    workSpaceTile.state = "SmallSize";
                else
                    workSpaceTile.state = "Maximize";
            }

            mouse.accepted = false;
        }
    }
}
