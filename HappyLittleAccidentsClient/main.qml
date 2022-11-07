import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("Happy Little Accidents")

    Connections {
       target: gameManager
       onInGameLobby: mainLoader.source = "qrc:/ui/LobbyScreen.qml"
       onGameStarting: mainLoader.source = "qrc:/ui/DrawingScreen.qml"
    }

    Loader {
       id: mainLoader
       anchors.fill: parent
       //source: "qrc:ui/MainMenuScreen.qml"
       source: "qrc:ui/DrawingScreen.qml"
       Component.onCompleted:  console.log("Loader", mainLoader.status)
    }

}
