import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: previewView
    
    property url videoSource: ""
    property bool isPlaying: false
    
    Rectangle {
        anchors.fill: parent
        color: "#000000"
        
        Image {
            id: previewImage
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            width: parent.width
            height: parent.height
            
            Text {
                anchors.centerIn: parent
                text: "No Preview"
                color: "#808080"
                font.pixelSize: 24
                visible: previewImage.source == ""
            }
        }
        
        // Playback controls overlay
        Rectangle {
            id: controlsOverlay
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 50
            color: "#AA000000"
            visible: mouseArea.containsMouse
            
            Row {
                anchors.centerIn: parent
                spacing: 10
                
                Button {
                    text: isPlaying ? "⏸" : "▶"
                    width: 40
                    height: 40
                    onClicked: {
                        isPlaying = !isPlaying
                    }
                }
                
                Button {
                    text: "⏹"
                    width: 40
                    height: 40
                    onClicked: {
                        isPlaying = false
                    }
                }
            }
        }
        
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
        }
    }
}
