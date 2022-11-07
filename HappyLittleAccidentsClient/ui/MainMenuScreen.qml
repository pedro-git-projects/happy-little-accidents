import QtQuick 2.15

Item {
    id: mainMenuScreen

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
        text: "Happy Little Accidents"
    }

    GameButton {
        id: playButton
        anchors.centerIn: parent
        buttonText: "Play"
        width: 336
        height: 105
        onButtonClicked: mainLoader.source = "qrc:/ui/GameSelectScreen.qml"
    }

    GameButton {
        id: quitButton
        anchors {
            top: playButton.bottom
            topMargin: 40
            horizontalCenter: parent.horizontalCenter
        }

        buttonText: "Quit"
        width: 336
        height: 105
        onButtonClicked: Qt.quit()
    }

}
