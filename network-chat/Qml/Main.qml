import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Window 2.0

Item{
    id:root
    objectName: "root"
    anchors.fill: parent

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

            GridView{
                id:onlineUsers
                anchors.fill: parent
                flickableDirection: Flickable.HorizontalAndVerticalFlick
                model:userList
                delegate: Column {
                    //Image { source: portrait; anchors.horizontalCenter: parent.horizontalCenter }
                    Text { text: name }//; anchors.horizontalCenter: parent.horizontalCenter
                }

                ListModel {
                    id:userList
                    ListElement {
                        name: "Jim Williams"
                        portrait: "pics/portrait.png"
                    }
                    ListElement {
                        name: "John Brown"
                        portrait: "pics/portrait.png"
                    }
                    ListElement {
                        name: "Bill Smyth"
                        portrait: "pics/portrait.png"
                    }
                    ListElement {
                        name: "Sam Wise"
                        portrait: "pics/portrait.png"
                    }
                }
            }
        }

        Rectangle{
            id: messageAreaRect
            anchors.top: userNameRect.bottom
            height: 3*parent.height/5
            width: parent.width
            color: "pink"
            ListView {
                id: listView
                anchors.fill: parent
                model: listModel

                delegate: Rectangle {
                    color: "transparent"
                    width: listView.width
                    height: vHeight
                    Text {
                        text: textVal
                        font.pixelSize: 14
                        anchors.centerIn: parent
                    }
                }
            }

            ListModel {
                id: listModel
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
                font.pixelSize: 14
                anchors.fill: parent
            }
        }

        Button{
            id: sendMsgBtn
            anchors.top: messageAreaRect.bottom
            anchors.left: sendMsgBoxRect.right
            height: sendMsgBoxRect.height
            width: root.width/5

            Text{
                anchors.centerIn: sendMsgBtn
                text: "Send"
            }

            onClicked: {
                if(sendMsgBox.text !== ""){
                    qmlBridge.sendMsg(sendMsgBox.text);
                    sendMsgBox.text = "";
                }
            }
        }
    }

    function appendMsgInMsgArea(val){
        listModel.append(createListElement(val));
    }

    function createListElement(val) {
        return {
            vHeight:(count(val)*15),
            textVal:val
        }
    }

    function count(string) {
        var count = 1;
        for (var i=0; i<string.length; i += 1)
                if (string[i] === "\n")
                    count += 1;

         return count;
    }
}
