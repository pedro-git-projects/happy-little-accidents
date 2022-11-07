import QtQuick 2.15

Item {
    id: drawingScreen

    Rectangle {
        id: background
        anchors.fill: parent
        color: "#282828"
    }

    Text {
        id: titleText
        font.pixelSize: 72
        font.bold: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors {
            top: parent.top
            topMargin: 40
            horizontalCenter: parent.horizontalCenter
        }
        color: "#fbf1c7"
        text: "Scribble Something!"
    }


}
