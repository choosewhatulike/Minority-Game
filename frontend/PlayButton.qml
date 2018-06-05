import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    property real backSize: 100
    property color backColor: "#ff0a0a"
    property color hoverColor: "#aa0000"

    width: backSize
    height: backSize

    Canvas {
        anchors.fill: parent
        id: backCanvas
        visible: true
        onPaint: {
            var ctx = backCanvas.getContext("2d");
            var px = parent.width/2;
            var py = parent.height/2;
            var r = backSize/2;
            ctx.beginPath();
            ctx.moveTo(px, py)
            ctx.arc(px, py, r, 0, Math.PI*2, false);
            ctx.closePath();

            ctx.fillStyle = backColor;
            ctx.fill();
            console.log("paint")
        }
    }

    Glow {
        id: edgeGlow
        visible: false
        anchors.fill: backCanvas
        samples: 20
        color: "#ffaaaa"
        source: backCanvas
    }


    MouseArea {
        anchors.fill: edgeGlow
        hoverEnabled: true
        onEntered: {
            edgeGlow.visible = true;
            console.log("enter");
        }
        onExited: {
           edgeGlow.visible = false;
            console.log("exit");
        }
    }
}
