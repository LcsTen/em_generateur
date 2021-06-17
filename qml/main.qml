import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
	id: window
	visible: true
	width: 800
	height: 800
	property var categories: ["History", "Politics", "Ecology", "Calendar", "Space"]

	function updateWorld(){
		for(let i = 0;i < categories.length;i++){
			catRepeater.itemAt(i).update();
		}
	}

	function printLog(log){
		catRepeater.itemAt(0).append(log);
	}

	Column {
		Row {
			id: tabRow

			Repeater {
				id: tabRepeater
				model: categories
				delegate: Tab {
					text: modelData
					activated: catRepeater.itemAt(index).visible

					onClicked: {
						for(let i = 0;i < categories.length;i++){
							let display = catRepeater.itemAt(i);
							display.visible = false;
						}
						catRepeater.itemAt(index).visible = true
					}
				}
			}

			Tab {
				text: "Skip 10 years"

				onClicked: console.log("TODO: Skip 10 years")
			}

			Tab {
				text: "Generate a new world"

				onClicked: Backend.generateWorld()
			}
		}

		Repeater {
			id: catRepeater
			model: categories
			delegate: ScrollView {
				width: window.width
				height: window.height - tabRow.height
				clip: true
				contentHeight: label.height
				visible: index === 0

				function update(){
					if(index === 0){
						label.text = ""
					}else if(index === 1){
						// Politics
						label.text = Backend.politicsToHtml();
					}else if(index === 2){
						label.text = "Ecology"
					}else if(index === 3){
						label.text = "Calendar"
					}else if(index === 4){
						// Space
						label.text = Backend.spaceToHtml();
					}
				}

				function append(log){
					label.text += log;
				}

				Text {
					id: label
					clip: true
					text: {
						if(index === 0){
							// History
							""
						}else if(index === 1){
							// Politics
							Backend.politicsToHtml();
						}else if(index === 2){
							"Ecology"
						}else if(index === 3){
							"Calendar"
						}else if(index === 4){
							// Space
							Backend.spaceToHtml();
						}
					}
				}
			}
		}
	}

	Component.onCompleted: {
		Backend.worldChanged.connect(updateWorld);
		Backend.logPrinted.connect(printLog);
		Backend.generateWorld();
	}
}
