import QtQuick 2.15

Item {
    id: background
    anchors.fill: parent

    default property alias contents: placeholder.data

    ShaderEffect  {
        id: shader
        anchors.fill: background

        property real iTime : 0
        property real opacity_value: background.opacity
        property variant src: background

        Timer {
            repeat: true
            running: true
            interval: 10
            onTriggered: parent.iTime += (interval / 100.0);
        }

        vertexShader: "qrc:/background.vsh"
        fragmentShader: "qrc:/background.fsh"
    }

    onOpacityChanged: {
        shader.opacity = opacity
    }

    Item {
        id: placeholder
        anchors.fill: parent
        property real marginRatio: 0.02

        anchors.topMargin: parent.height * marginRatio
        anchors.bottomMargin: parent.height * marginRatio
        anchors.leftMargin: parent.width * marginRatio
        anchors.rightMargin: parent.width * marginRatio
    }
}
