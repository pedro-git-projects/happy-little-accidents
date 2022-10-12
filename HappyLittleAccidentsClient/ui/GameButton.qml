import QtQuick 2.15

Rectangle {
   id: gameButton
   property string buttonColor:  "#FE8019"
   property string buttonClickedColor: "#BB7548"
   property string buttonText: ""
   property  string buttonTextColor: "#fbf1c7"
   property int buttonTextPixelSize: 72

   signal buttonClicked()

   radius: 5
   color: buttonColor
   Text {
       anchors.centerIn:  parent
       color: buttonTextColor
       text: buttonText
       font.pixelSize: buttonTextPixelSize
   }

   MouseArea {
       anchors.fill: parent
       onPressed: gameButton.color = buttonClickedColor
       onReleased: gameButton.color = buttonColor
       onClicked: gameButton.buttonClicked()
   }
}
