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
        text: "Lobby Code:" + gameManager.lobbyRoomCode
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

    ListView {
       id: lobbyRoomList
       model: gameManager.clientsInLobby
       delegate: Text {
           anchors.horizontalCenter: parent.horizontalCenter
           text: modelData
           font.pixelSize: 36
           font.bold: true
           color: "#fbf1c7"
       }
       anchors.fill: lobbyRoomListBackGround
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

    TextEdit {
       id: messageWindow
       anchors.fill: messageWindowBackground
       color: "#fbf1c7"
       font.pixelSize: 24
       readOnly: true
    }

    Connections {
       target: gameManager
       onNewLobbyMessage: messageWindow.append(message)
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
        onButtonClicked: {
           gameManager.sendMessageToLobby(sendTextInput.text)
            sendTextInput.text = ""
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


    TextInput {
        id: sendTextInput
        anchors.fill: sendTextFieldBackground
        font.pixelSize: 36
        color: "#fbf1c7"
        clip: true
        onAccepted: {
            gameManager.sendMessageToLobby(sendTextInput.text)
            sendTextInput.text = ""
        }
    }

}
