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
            property string seconds: timer.seconds < 10 ? "0" + timer.seconds : timer.seconds
            property string minutes: timer.minutes < 10 ? "0" + timer.minutes : timer.minutes
            property string time: field.state === Field.StateIdle ? "00:00" : minutes + ":" + seconds
            font.pixelSize: parent.height * 0.6
            anchors.centerIn: parent
            text: "Time: " + time

            Timer {
                id: timer
                property int seconds: 0
                property int minutes: 0
                interval: 1000
                repeat: true
                running: field.state === Field.StateStarted
                onTriggered: {
                    if (seconds === 59) {
                        minutes += 1
                        seconds = -1
                    }
                    seconds += 1
                }
                onRunningChanged: {
                    if (running) {
                        seconds = 0
                        minutes = 0
                    }
                }
            }
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
