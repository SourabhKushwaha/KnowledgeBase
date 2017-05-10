import QtQuick 2.1

Rectangle {
    id: root
    color: "black"
    width: 600
    height: 450

    property int count: 0

    Image {
        id: imgFrame
        anchors.fill: parent
    }

    Component.onCompleted: {
        vFrameProvider.imgUpdated.connect(function() {
            imgFrame.source = "image://vFrameProvider/"+count;
            count++;
            if(count == 100)
                count = 0;
        });
    }
}
