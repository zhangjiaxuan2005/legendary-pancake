import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Text{
        text: qsTr("Hello World")
        font.pixelSize: 24
    }
}