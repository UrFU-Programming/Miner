import QtQuick 2.5
import GameComponents 1.0

Rectangle {
    width: 800
    height: 600
    focus: true
    Keys.onPressed: {
        if (event.matches(StandardKey.New)) {
            field.startNewGame()
        }
        if ((event.key === Qt.Key_Q) && (event.modifiers & Qt.ControlModifier)) {
            Qt.quit()
        }
    }

    Grid {
        columns: field.width
        Repeater {
            model: {
                if (field.resetInProgress) {
                    return 0
                } else {
                    return field.width * field.height
                }
            }

            CellItem {
                cell: field.cellAt(index % field.width, index / field.width)
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "#c0c0c0"
        opacity: 0.7
        visible: field.state === Field.StateEnded
        Text {
            anchors.centerIn: parent
            font.pixelSize: 64
            text: "Game over"
        }
    }
}
