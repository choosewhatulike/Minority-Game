import QtQuick 2.0

Item {
    property real frontSize: 50
    property color frontColor: "#ffffff"

    Item {
        anchors.centerIn: parent
        width: frontSize/2
        height: frontSize

        Rectangle {
            id: rect1
            width: frontSize/10
            height: frontSize
            color: frontColor

            anchors.left: parent.left
        }

        Rectangle {
            id: rect2
            width: rect1.width
            height: rect1.height
            color: rect1.color

            anchors.right: parent.right
        }
    }

}
