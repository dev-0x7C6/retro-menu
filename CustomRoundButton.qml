import QtQuick 2.15

Rectangle {
	property color borderAnimation : "#2498c7"
	radius: (width + height) / 4

	border.color: activeFocus ? borderAnimation : "#00000000"
	border.width: 4
	color: "#505050"

	SequentialAnimation on borderAnimation {
		running: activeFocus
		ColorAnimation { to: "#24d9c7"; duration: 500; }
		ColorAnimation { to: "#2488c7"; duration: 500; }
		loops: Animation.Infinite
	}
}
