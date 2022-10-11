import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Button {
        anchors.centerIn: parent
        text: "Click Me!"
        onClicked: webSocketHandler.connectToServer("ws://127.0.0.1:8585")
    }
}
