import QtQuick 2.1
import QtQuick.Window 2.0

Item{
    id:root
    objectName: "root"
    height: 300//Screen.desktopAvailableHeight
    width: 200//Screen.desktopAvailableWidth

    Rectangle{
        id: mainRect
        objectName: "mainRect"
        anchors.fill: parent
        color: "black"

        Rectangle{
            id: userNameRect
            anchors.top: parent.top
            height: parent.height/5
            width: parent.width
            color: "white"

            Text{
                id: userNameL
                anchors.fill: parent
                color: "blue"
                text:"hello "
            }
        }

        Rectangle{
            id: messageAreaRect
            anchors.top: userNameRect.bottom
            height: 3*parent.height/5
            width: parent.width
            color: "pink"
            Text{
                id: messageArea
                anchors.fill: parent
            }
        }

        Rectangle{
            id: sendMsgBoxRect
            color: "white"
            anchors.top: messageAreaRect.bottom
            height: parent.height/5
            width: parent.width - sendMsgBtn.width
            TextEdit{
                id: sendMsgBox
                anchors.fill: parent
            }
        }

        Rectangle{
            id: sendMsgBtn
            anchors.top: messageAreaRect.bottom
            anchors.left: sendMsgBoxRect.right
            color: "red"
            height: sendMsgBoxRect.height
            width: root.width/5

            Text{
                height: parent.height/2
                width: parent.width/2
                //anchors.fill: parent
                anchors.centerIn: sendMsgBtn.Center
                text: "Send"
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if(sendMsgBox.text !== ""){
                        qmlBridge.sendMsg(sendMsgBox.text);
                        appendMsgInMsgArea(sendMsgBox.text);
                        sendMsgBox.text = "";
                    }
                }
            }
        }
    }

    function appendUserInfo(val){
        messageArea.text += val;
    }

    function appendMsgInMsgArea(val){
        messageArea.text += val +"\n";
    }
}
