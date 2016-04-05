import QtQuick 2.5
import GameComponents 1.0

Rectangle {
    id: window
    width: 800
    height: 600

    Rectangle {
        id: board
        border.width: 4
        border.color: "black"
        radius: 10
        anchors.fill: parent

        Item {
            id: cellContainer
            anchors.fill: parent
            anchors.margins: 10
            property real windowProportion: width / height
            property real fieldProportion: field.width * 1.0 / field.height
            property real fixupFactor: windowProportion > fieldProportion ? 1 : windowProportion / fieldProportion
            property int preferredSize: height / field.height * fixupFactor

            Grid {
                id: fieldItem
                anchors.centerIn: parent

                columns: field.width
                Repeater {
                    id: cellRepeater
                    model: field.resetInProgress ? 0 : field.width * field.height

                    CellItem {
                        cell: field.cellAt(index % field.width, index / field.width)
                        size: cellContainer.preferredSize
                    }
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

    focus: true
    Keys.onPressed: {
        if (event.matches(StandardKey.New)) {
            field.startNewGame();
        }
    }
}
