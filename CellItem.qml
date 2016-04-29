import QtQuick 2.0
import GameComponents 1.0

Rectangle {
    width: 64
    height: 64
    border.color: "black"
    border.width: 2

    property Cell cell: null

    Rectangle {
        color: "#c0c0c0"
        visible: !cell.isOpen
        anchors.fill: parent
        anchors.margins: 2
    }

    MouseArea {
        anchors.fill: parent
        onClicked: cell.open()
    }
}
