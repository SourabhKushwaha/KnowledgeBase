import QtQuick 2.6
import QtQuick.Window 2.2
//import com.example.ICustom 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Text {
        id: name
        anchors.centerIn: parent
        text: {
            if(helper.custom)
                return helper.custom.name;

            return helper.name;
        }
    }
}
