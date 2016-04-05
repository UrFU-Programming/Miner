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

    Text {
        anchors.centerIn: parent
        text: symbol()
        font.pixelSize: 32

        function symbol() {
            if (cell.isOpen) {
                if (cell.haveMine) {
                    return "+"
                }
                if (cell.minesAround > 0) {
                    return cell.minesAround
                }
            } else {
                switch (cell.mark) {
                case Cell.MarkNothing:
                    break;
                case Cell.MarkFlagged:
                    return "!"
                case Cell.MarkQuestioned:
                    return "?"
                }
            }

            return ""
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: cell.open()
    }
}
