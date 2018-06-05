import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    width: 200
    height: 120
    property string mytext: qsTr("Button")

    signal buttonClick()
    Rectangle {
        id: mybtn
        color: "#1961c7"
        anchors.fill: parent
        Text {
            text: mytext
            anchors.centerIn: parent
            font.pointSize: 20
        }
        radius: 10
    }
    Glow {
        id: btnglow
        visible: false
        anchors.fill: mybtn
        source: mybtn
        samples: 17
        spread: 0.5
        color: "#aaaaaa"
    }
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {btnglow.visible = true}
        onExited: {btnglow.visible = false}
        onClicked: {buttonClick()}
    }

}
