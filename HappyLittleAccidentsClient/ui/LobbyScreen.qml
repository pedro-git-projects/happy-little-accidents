import QtQuick 2.15

Item {
    id: lobbyScreen

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
        text: "Lobby Code:" + gameManager.getLobbyRoomCode()
    }

    Rectangle {
        id: lobbyRoomListBackGround
        radius: 5
        color: "#a89984"
        width: 358
        height: 418
        anchors {
            top: titleText.bottom
            left: parent.left
            topMargin: 20
            leftMargin: 40
        }
    }

    Rectangle {
        id: messageWindowBackground
        radius: 5
        color: "#a89984"
        anchors {
            left: lobbyRoomListBackGround.right
            leftMargin: 20
            right: parent.right
            rightMargin: 40
            top: lobbyRoomListBackGround.top
            bottom: lobbyRoomListBackGround.bottom
        }
    }

    GameButton {
        id: buttonReady
        buttonText: "Ready"
        buttonTextPixelSize: 36
        width: 314
        height: 80

        anchors {
            top: lobbyRoomListBackGround.bottom
            topMargin: 20
            horizontalCenter: lobbyRoomListBackGround.horizontalCenter
        }
    }

    GameButton {
        id: buttonSendText
        buttonText: "Send"
        buttonTextPixelSize: 36
        width: 174

        anchors {
            top: buttonReady.top
            bottom: buttonReady.bottom
            right: messageWindowBackground.right
        }
    }

    Rectangle {
        id: sendTextFieldBackground
        color: "#a89984"
        radius: 5
        anchors {
            top: buttonReady.top
            bottom: buttonReady.bottom
            left: messageWindowBackground.left
            right: buttonSendText.left
            rightMargin: 20
        }
    }


    TextEdit {
        id: editSendText
        anchors.fill: sendTextFieldBackground
        font.pixelSize: 36
        color: "#fbf1c7"
        clip: true
    }

}
