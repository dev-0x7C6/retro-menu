import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: clock
    property string time_string;

    Label {
        id: clockLabel
        anchors.right: parent.right
        text: time_string
        font.bold: true
        font.pointSize: 18
        color: "white"
    }

    function timeChanged() {
        var time = new Date;
        time_string = ("0" + time.getHours()).slice(-2) + ":" + ("0" + time.getMinutes()).slice(-2);
    }

    Timer {
        interval: 100;
        repeat: true;
        running: true;
        onTriggered: clock.timeChanged()
    }
}
