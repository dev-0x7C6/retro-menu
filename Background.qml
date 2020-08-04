import QtQuick 2.15

Item {
    id: background
    anchors.fill: parent

    default property alias contents: placeholder.data
    property alias content: placeholder
    property alias fadeOut: fadeOut

    property real fade_out_opacity: 0.0
    property real fade_out_scale: 0.9
    property int fade_out_ms: 250

    property real fade_in_opacity: 1.0
    property real fade_in_scale: 1.0
    property int fade_in_ms: 500

    ShaderEffect  {
        id: shader
        anchors.fill: background

        property real iTime : 0
        property real opacity_value: placeholder.opacity
        property variant src: background
        property variant bg_color : Qt.vector3d(0.0, 0.0, 0.0)
        property variant line_color : Qt.vector3d(0.1, 0.13, 0.23)

        Timer {
            repeat: true
            running: true
            interval: 10
            onTriggered: parent.iTime += (interval / 100.0);
        }

        vertexShader: "qrc:/shaders/background.vsh"
        fragmentShader: "qrc:/shaders/background.fsh"
    }

    Item {
        id: placeholder
        anchors.fill: parent
        scale: 0.9
        opacity: 0.0
        property real marginRatio: 0.02

        anchors.topMargin: parent.height * marginRatio
        anchors.bottomMargin: parent.height * marginRatio
        anchors.leftMargin: parent.width * marginRatio
        anchors.rightMargin: parent.width * marginRatio
    }

    SequentialAnimation {
        id: fadeOut

        PauseAnimation { duration: 500 }
        ParallelAnimation {
            NumberAnimation { target: placeholder; property: "scale"; to: fade_out_scale; duration: fade_out_ms }
            NumberAnimation { target: placeholder; property: "opacity"; to: fade_out_opacity; duration: fade_out_ms }
            loops: 1
        }
        PauseAnimation { duration: 250 }

        onFinished: {
            background.onFinished();
        }
    }

    ParallelAnimation {
        NumberAnimation { target: placeholder; property: "scale"; to: fade_in_scale; duration: fade_in_ms }
        NumberAnimation { target: placeholder; property: "opacity"; to: fade_in_opacity; duration: fade_in_ms }
        loops: 1
        running: true
    }

    function onFinished() {}
}
