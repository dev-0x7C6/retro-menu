import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtGamepad 1.15

Window {
	id: mainWindow
	visible: true
    width: 1280
    height: 720
    title: qsTr("RetroMenu")
    color: "black"

    property string programToRun: ""


	Gamepad {
		id: gamepad1
		deviceId: GamepadManager.connectedGamepads.length > 0 ? GamepadManager.connectedGamepads[0] : -1
	}

	Connections {
		target: GamepadManager

        function onGamepadConnected() {
            gamepad1.deviceId = deviceId;
        }
	}

	GamepadKeyNavigation {
		id: gamepadKeyNavigation
		gamepad: gamepad1
		active: true
		buttonXKey: Qt.Key_Return
	}

    Background {
        id: background
        opacity: 0.0

		SequentialAnimation {
			id: startGameAnimation

            PauseAnimation { duration: 500 }
			ParallelAnimation {
                NumberAnimation { target: background; property: "scale"; to: 0.9; duration: 250 }
                NumberAnimation { target: background; property: "opacity"; to: 0; duration: 250 }
                ColorAnimation { target: mainWindow; property: "color"; to: "black"; duration: 1000 }
				loops: 1
			}

            onFinished: {
                process.start(programToRun);
                Qt.quit();
            }
		}


        ParallelAnimation {
            NumberAnimation { target: background; property: "scale"; to: 1; duration: 500 }
            NumberAnimation { target: background; property: "opacity"; to: 1; duration: 500 }
            ColorAnimation { target: mainWindow; property: "color"; to: "#2d2d2d"; duration: 1000 }
            loops: 1
            running: true
        }

        Clock {
            id: topMenu
            anchors.top: parent.top
            width: parent.width
            height: parent.height * 0.1
        }

		Item {
			id: gameManagerArea
			anchors.top: topMenu.bottom
			width: parent.width
			height: parent.height * 0.8

			Label {
				id: currentGameLabel
				font.pointSize: 24
				font.bold: false
				color: "#24d9c7"
				anchors.bottom: gameGridView.top
				anchors.bottomMargin: 20
			}

			GridView {
				id: gameGridView
				anchors.centerIn: parent
				width: parent.width
				height: parent.height * 0.5
				cellHeight: height
				cellWidth: height
				anchors.leftMargin: 20
				anchors.rightMargin: 20
				focus: true
				model: GameLibrarySortedModel
				flow: GridView.FlowTopToBottom
				snapMode: GridView.SnapOneRow

				delegate: GameButton {
					width: GridView.view.cellWidth
					height: GridView.view.cellHeight
                    coverImage: cover

					function onClicked() {
						GridView.view.currentIndex = index

						startGameAnimation.start()
                        programToRun = exec
						updateLabel()
					}

					function updateLabel() {
						currentGameLabel.text = name
					}
				}

                onCurrentIndexChanged: {
                    currentItem.updateLabel();
                }

				highlight: Rectangle {
					radius: 5
					border.width: 4

					color : "#00000000"

					SequentialAnimation on border.color {
						running: true
						ColorAnimation { to: "#24d9c7"; duration: 500; }
						ColorAnimation { to: "#2488c7"; duration: 500; }
						loops: Animation.Infinite
					}

					z: 10000
					visible: gameGridView.focus
				}
			}
		}

		Item {
			id: statusBar
			anchors.top: gameManagerArea.bottom
			width: parent.width
			height: parent.height * 0.1

			Rectangle {
				anchors.top: statusBar.top
				width: parent.width
				height: 1
				color: "white"
			}
		}
	}
}
