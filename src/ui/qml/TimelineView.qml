import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: timelineView
    
    property real duration: 60.0
    property real currentTime: 0.0
    property real zoom: 1.0
    
    Rectangle {
        anchors.fill: parent
        color: "#2D2D30"
        
        // Time ruler
        Rectangle {
            id: timeRuler
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 30
            color: "#1E1E1E"
            
            Text {
                anchors.centerIn: parent
                text: formatTime(currentTime)
                color: "#B4B4B4"
                font.pixelSize: 12
            }
        }
        
        // Timeline area
        Flickable {
            id: timelineFlickable
            anchors.top: timeRuler.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            
            contentWidth: duration * zoom * 50
            contentHeight: tracksColumn.height
            clip: true
            
            Column {
                id: tracksColumn
                width: timelineFlickable.contentWidth
                spacing: 2
                
                Repeater {
                    model: 3
                    
                    Rectangle {
                        width: tracksColumn.width
                        height: 60
                        color: "#3C3C3C"
                        border.color: "#646464"
                        border.width: 1
                        
                        Text {
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                            text: "Track " + (index + 1)
                            color: "#C8C8C8"
                        }
                    }
                }
            }
            
            // Playhead
            Rectangle {
                id: playhead
                x: (currentTime / duration) * timelineFlickable.contentWidth
                width: 2
                height: timelineFlickable.contentHeight
                color: "#FF0000"
                z: 100
                
                Rectangle {
                    width: 16
                    height: 16
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    color: "#FF0000"
                    rotation: 45
                }
            }
        }
        
        MouseArea {
            anchors.fill: timelineFlickable
            onClicked: {
                var clickX = mouse.x + timelineFlickable.contentX
                currentTime = (clickX / timelineFlickable.contentWidth) * duration
            }
        }
    }
    
    function formatTime(seconds) {
        var mins = Math.floor(seconds / 60)
        var secs = Math.floor(seconds % 60)
        return mins + ":" + (secs < 10 ? "0" : "") + secs
    }
}
