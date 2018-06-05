import QtQuick 2.0
import QtQml.Models 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "."

Rectangle {
    id: vtabbar

    Column {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        spacing: 15
        TabButton {
            id: tabbtn1

        }
        TabButton {
            id: tabbtn2

        }
        TabButton {
            id: tabbtn3

        }
    }
}
