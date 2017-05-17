import QtQuick 2.0
import QtQuick.Window 2.0

import QtWebEngine 1.4
import QtWebChannel  1.0

Item{
    id:root
    height: 500
    width:  500

    // Create WebChannel
    WebChannel{
        id:webChannel
    }

    //Now, let’s create an object that we want to publish to the HTML/JavaScript clients:
    QtObject {
        id: qmlObject

        property var send: function (arg) {
            sendTextMessage(arg);
        }
        // signals, methods and properties are
        // accessible to JavaScript code
        signal someSignal(string message);

        function someMethod(message) {
            console.log(message);
            someSignal(message);
            callHtmlFunction();
            return message+" QML";
        }

        function callHtmlFunction(){
            //Call javascript function
            webEnginView.runJavaScript("updateMarker("+ 20.97 +")");
        }
    }

    Rectangle{
        anchors.fill: parent
        color: "black"

        WebEngineView{
            id : webEnginView
            anchors.fill: parent
            url : dataManager.htmlURL();
            webChannel: webChannel
        }
    }

    Component.onCompleted: {
        webChannel.registerObject("qmlObject", qmlObject);
        webChannel.registerObject("dataManager", dataManager);
    }
}
