import QtQuick 2.0
import GameComponents 1.0

Rectangle {
    width: 64
    height: 64
    border.color: "black"
    border.width: 2

    property Cell cell: null

    Rectangle {
        color: {
            if (cell.isOpen) {
                if (!cell.haveMine) {
                    return "white"
                } else {
                    if (cell.isExploded) {
                        return "red"
                    } else {
                        return "green"
                    }
                }
            } else {
                return "#c0c0c0"
            }
        }
        anchors.fill: parent
        anchors.margins: 2

        Text {
            anchors.centerIn: parent
            font.pixelSize: 60
            text: {
                if (!cell.isOpen) {
                    switch (cell.mark) {
                    case 0:
                        return ""
                    case 1:
                        return "!"
                    case 2:
                        return "?"
                    }
                } else {
                    if (cell.minesAround != 0) {
                        cell.minesAround
                    }
                    if (cell.haveMine) {
                        return "+"
                    }
                    if (cell.minesAround == 0 & !cell.haveMine) {
                        return ""
                    }
                }
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            if (mouse.button & Qt.RightButton) {
                cell.toggleMark()
            }
            if (mouse.button & Qt.LeftButton) {
                if (cell.isOpen) {
                    cell.tryToOpenAround();
                } else {
                    cell.open()
                }
            }
        }
    }
}
