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
        text: "Let's have some fun."
    }

    Rectangle {
        id: canvasBackground
        anchors.fill: drawingCanvas
        color: "#fbf1c7"
    }

    Canvas {
        id: drawingCanvas

        property int startX: -1
        property int startY: -1
        property int finishX: -1
        property int finishY: -1

        function clearCanvas() {
            const ctx = drawingCanvas.getContext("2d")
            ctx.clearRect(0, 0, drawingCanvas.width, drawingCanvas.height)
            requestPaint()
        }

        onPaint: {
            const ctx = drawingCanvas.getContext("2d")
            ctx.beginPath()
            ctx.stokeStyle = "#1d2021"
            ctx.lineWidth = 5
            ctx.lineJoin = "round"
            ctx.moveTo(startX, startY)
            ctx.lineTo(finishX, finishY)
            ctx.closePath()
            ctx.stroke()
            startX = finishX
            startY = finishY
        }

        anchors {
            top: titleText.bottom
            bottom: clearButton.top
            topMargin: 20
            bottomMargin: 20
            left: parent.left
            right: parent.right
            leftMargin: 80
            rightMargin: 80
        }

        MouseArea {
            anchors.fill: parent

            onPressed: {
                drawingCanvas.startX = mouseX
                drawingCanvas.startY = mouseY
            }

            onPositionChanged: {
                drawingCanvas.finishX = mouseX
                drawingCanvas.finishY = mouseY
                drawingCanvas.requestPaint()
            }

        }
    }

    GameButton {
        id: clearButton
        width: 174
        height: 80
        buttonColor: "#fb4934"
        buttonClickedColor: "#cc241d"
        buttonText: "Clear"
        buttonTextPixelSize: 36
        anchors {
            left: parent.left
            bottom: parent.bottom
            leftMargin: 80
            bottomMargin: 40
        }
        onButtonClicked: drawingCanvas.clearCanvas()
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
        onButtonClicked: {
            drawingCanvas.save("temp.png")
        mainLoader.source = "qrc:/ui/WaitingForPlayersScreen.qml"
        }
    }
}
