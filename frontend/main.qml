import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtCharts 2.0
import "."


ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 800
    height: 600
    title: qsTr("Final One")

    ChartView {
        id: outlineChart
        width: 600
        height: 400

        LineSeries {
            id: outlineSeries

        }
    }
    TextInput {
        id:initNum
        text: "101"
    }

    Button {
        id: btn1
//        anchors.top: outlineChart.bottom
        anchors.left: initNum.right
        text: qsTr("init")
        onClicked: {
            envControl.init(parseInt(initNum.text))
            applicationWindow.iteration = 0
            console.log("env init "+initNum.text)
        }
    }
    Button {
        id:btn2
        anchors.left: btn1.right
        text: qsTr("startLoop")
        onClicked: {
            envControl.startLoop();
            console.log("env started loop")
        }
    }
    Button {
        id: btn3
        anchors.left: btn2.right
        text:qsTr("stopLoop")
        onClicked: {
            envControl.stopLoop();
            console.log("env stopped loop")
        }
    }

    property int iteration: 0
    Connections {
        target: envControl
        onSteped: {
            applicationWindow.iteration += 1
            console.log(applicationWindow.iteration)
        }
    }
    Connections {
        target: envControl
        onInited: {
            if(result){
                console.log("ok")
            }
            else{
                console.log("failed")
            }
        }
    }
}
