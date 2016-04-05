import QtQuick 2.0
import GameComponents 1.0

Rectangle {
    width: 800
    height: 600

    Rectangle {
        id: board
        border.width: 4
        border.color: "black"
        radius: 10
        anchors.fill: parent

        Grid {
            id: fieldItem
            anchors.centerIn: parent
            columns: field.width
            Repeater {
                model: field.width * field.height

                CellItem {
                    cell: field.cellAt(index % field.width, index / field.width)
                }
            }
        }
    }

    Item {
        id: gameStateItem
        visible: field.state === Field.StateEnded
        x: 0
        y: (fieldItem.height - height) / 2 + fieldItem.y
        width: parent.width
        height: fieldItem.height * 0.3

        Rectangle {
            anchors.fill: parent
            opacity: 0.7
            color: "#c0c0c0"
            border.width: 2
        }

        Text {
            anchors.centerIn: parent
            text: "Game over"
            font.pixelSize:  parent.height * 0.6
        }
    }
}
