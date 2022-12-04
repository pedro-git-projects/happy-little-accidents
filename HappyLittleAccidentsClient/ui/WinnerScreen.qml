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
        text: gameManager.winner + "was the best!";
    }

    GameButton {
        id: doneButton
        width: 174
        height: 80
        buttonColor: "#8ec07c"
        buttonClickedColor: "#689d6a"
        buttonText: "Done"
        buttonTextPixelSize: 36
        anchors {
            right: parent.right
            bottom: parent.bottom
            rightMargin: 80
            bottomMargin: 40
        }
        onButtonClicked: Qt.quit()
    }

    Rectangle {
       anchors.fill: winnerImage
       color: "#fbf1c7"
    }

    Image {
        id: winnerImage
        anchors {
            top: titleText.bottom
            bottom: doneButton.top
            left: parent.left
            right: parent.right
            margins: 20
        }
        source: gameManager.winnerImage()
    }
}
