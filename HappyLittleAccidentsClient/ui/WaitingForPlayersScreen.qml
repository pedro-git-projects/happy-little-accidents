import QtQuick 2.15

Item {
    Rectangle {
        id: background
        anchors.fill: parent
        color: "#282828"
    }

    Component.onCompleted: {
       gameManager.drawingFinished()
    }

    Text {
        id: titleText
        font.pixelSize: 72
        font.bold: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors {
            centerIn: parent
        }
        color: "#fbf1c7"
        text: "Waiting for everyone<br> to finish..."
        horizontalAlignment: Text.AlignHCenter
    }

}
