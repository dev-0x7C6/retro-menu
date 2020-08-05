import QtQuick 2.15

Item {
	id: gameButton
	property color borderAnimation : "#2498c7"
	property string coverImage : ""

    Rectangle {
        anchors.centerIn: parent;
        width: parent.width - 6
        height: parent.height - 6
        gradient: Gradient {
                GradientStop { position: 0.0; color: "#A0202020" }
                GradientStop { position: 1.0; color: "#A04F4F4F" }
            }
        //opacity: 0.5
        border.color: "#A02498c7"
        border.width: 2
        radius: 5
    }

	Image {
		id: cover
		anchors.centerIn: parent
        width: parent.width - 32
        height: parent.height - 32
		source: coverImage
        sourceSize.width: width
        sourceSize.height: height
	}

	Component {
		id: fadeOutComponent

		Image {
			id: fadeOut
			layer.enabled: true

			x: cover.x
			y: cover.y
			width: cover.width
			height: cover.height

			fillMode: Image.Stretch
			source: coverImage
            sourceSize.width: width
            sourceSize.height: height
			scale: 1.0
			opacity: 0.5

			ParallelAnimation {
				id: runOut
				running: true
				NumberAnimation { target: fadeOut; property: "scale"; from: 1.0; to: 1.3; duration: 300 }
				NumberAnimation { target: fadeOut; property: "opacity"; from: 0.5;  to: 0.0; duration: 300 }

				onStopped: {
					fadeOutLoader.active = false;
				}
			}
		}
	}

	Loader {
		id: fadeOutLoader
		active: false;
		sourceComponent : fadeOutComponent
	}


	SequentialAnimation {
		id: clickAnimation
		NumberAnimation { target: gameButton; property: "scale"; to: 0.9; duration: 75 }
		NumberAnimation { target: gameButton; property: "scale"; to: 1.0; duration: 75 }
		loops: 1
	}


	Keys.onReturnPressed: {
		fadeOutLoader.active = true;
        onClicked()
	}

	MouseArea {
		anchors.fill: parent
		onClicked: {
			if (parent.focus === true) {
				clickAnimation.start()
				fadeOutLoader.active = true;
			}

			parent.forceActiveFocus()
			parent.focus = true;
			parent.onClicked()
		}
	}

	function onClicked() {}
}
