import QtQuick 2.15

Item {
    id: gameSelectScreen

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
            top: parent.topo
            topMargin: 40
            horizontalCenter: parent.horizontalCenter
        }
        color: "#fbf1c7"
        text: "Happy Little Accidents"
    }

    GameButton {
        id: createGameButton
        anchors {
            top: titleText.bottom
            topMargin: 160
            horizontalCenter: parent.horizontalCenter
        }

        buttonText: "Create Game"
        buttonTextPixelSize: 48
        width: 336
        height: 105
        // onButtonClicked: mainLoader.source = "qrc:/ui/GameSelectScreen.qml"
    }

    GameButton {
        id: joinGameButton
        anchors {
            top: createGameButton.bottom
            topMargin: 40
            horizontalCenter: parent.horizontalCenter
        }

        buttonText: "Join Game"
        buttonTextPixelSize: 48
        width: 336
        height: 105
        // onButtonClicked: mainLoader.source = "qrc:/ui/GameSelectScreen.qml"
    }

    GameButton {
        id: backButton
        anchors {
            top: joinGameButton.bottom
            topMargin: 40
            horizontalCenter: parent.horizontalCenter
        }

        buttonText: "Go Back"
        buttonTextPixelSize: 48
        width: 336
        height: 105
        onButtonClicked: mainLoader.source = "qrc:/ui/MainMenuScreen.qml"
    }


}