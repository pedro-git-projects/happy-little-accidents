import QtQuick 2.15

Item {
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
        text: "Enter Game Code"
    }

    Rectangle {
        id: joinLobbyTextBg
        color: "#a89984"
        radius: 5
        width: 618
        height: 79
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: titleText.bottom
            topMargin: 100
        }
    }

    TextInput {
        id: joinLobbyTextInput
        anchors.fill: joinLobbyTextBg
        color: "#fbf1c7"
        font.pixelSize: 48
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        maximumLength: 4
    }

    GameButton {
        id: joinButton
        width: 336
        height: 105
        buttonText: "Join Game"
        buttonTextPixelSize: 48
        anchors {
           horizontalCenter: parent.horizontalCenter
           top: joinLobbyTextBg.bottom
           topMargin: 100
        }
    }

    GameButton {
        id: backButton
        width: 336
        height: 105
        buttonText: "Go Back"
        buttonTextPixelSize: 48
        anchors {
           horizontalCenter: parent.horizontalCenter
           top: joinButton.bottom
           topMargin: 20
        }
        onButtonClicked: mainLoader.source = "qrc:/ui/GameSelectScreen.qml"
    }
}
