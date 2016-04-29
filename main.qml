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
}
