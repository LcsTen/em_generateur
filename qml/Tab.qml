import QtQuick 2.15

Rectangle {
	id: root
	width: text.width + 2
	height: text.height
	border.color: "black"
	color: activated ? "yellow" : "white"

	property bool activated: false
	property string text: ""

	signal clicked

	Text {
		id: text
		text: root.text
		anchors.horizontalCenter: root.horizontalCenter
	}

	MouseArea {
		anchors.fill: parent
		cursorShape: Qt.PointingHandCursor

		onClicked: root.clicked()
	}
}
