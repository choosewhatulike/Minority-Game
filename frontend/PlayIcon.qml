import QtQuick 2.0

Item {
    property real frontSize: 50
    property color frontColor: "#ffffff"

    Canvas {
        id: frontCanvas
        anchors.fill: parent
        onPaint: {
            var ctx = frontCanvas.getContext("2d");
            var px = parent.width/2;
            var py = parent.height/2;
            var len = frontSize;
            var SQRT3 = Math.sqrt(3);

            px = px - len/(2*SQRT3); py = py - len/2;
            ctx.beginPath();
            ctx.moveTo(px, py);
            py = py + len;
            ctx.lineTo(px, py);
            px = px + len*SQRT3/2; py = py - len/2;
            ctx.lineTo(px, py);
            ctx.closePath();

            ctx.fillStyle = frontColor;
            ctx.fill();
        }
    }
}
