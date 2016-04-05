import QtQuick 2.0
import GameComponents 1.0

Rectangle {
    id: cellItem
    width: size
    height: size
    border.color: "black"
    border.width: rectMargin > 3 ? 2 : 1

    property Cell cell: null

    property int size: 64

    property int rectMargin: (size * 0.14) < 2 ? 2 : size * 0.14

    Rectangle {
        color: "#c0c0c0"
        visible: !cell.isOpen
        anchors.fill: parent
        anchors.margins: rectMargin
    }

    Rectangle {
        color: cell.exploded ? "red" : "#00ff00"
        visible: cell.isOpen && cell.haveMine
        anchors.fill: parent
        anchors.margins: rectMargin
    }

    Text {
        anchors.centerIn: parent
        text: symbol()
        font.pixelSize: cellItem.size * 0.8

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
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        anchors.fill: parent

        onClicked: {
            if (mouse.button == Qt.LeftButton) {
                if (cell.isOpen) {
                    cell.tryToOpenAround()
                } else {
                    cell.open()
                }
            } else {
                cell.toggleMark()
            }
        }
    }
}
