import QtQuick 2.5
import GameComponents 1.0

Rectangle {
    id: window
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

    Item {
        id: panel
        width: parent.width
        height: parent.height * 0.1
        Text {
            property string time: "00:00"
            font.pixelSize: parent.height * 0.6
            anchors.centerIn: parent
            text: "Time: " + time
        }
    }

    Item {
        id: cellContainer
        anchors.top: panel.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
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
                model: {
                    if (field.resetInProgress) {
                        return 0
                    } else {
                        return field.width * field.height
                    }
                }

                CellItem {
                    cell: field.cellAt(index % field.width, index / field.width)
                    size: cellContainer.preferredSize
                }
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
