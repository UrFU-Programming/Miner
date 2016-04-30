import QtQuick 2.0
import GameComponents 1.0

Rectangle {
    width: 800
    height: 600

    Grid {
        columns: field.width
        Repeater {
            model: field.width * field.height

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
