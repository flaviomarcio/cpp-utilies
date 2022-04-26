import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import dirUtilities 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("FileUtilites")

    Material.theme: Material.System
    Material.accent: Material.LightBlue

    Item {
        anchors.fill: parent
        TabBar{
            id: tabBar
            height: 40
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
            }
            TabButton{
                text: "Rename"
                width: 100
                anchors{
                    top: parent.top
                    bottom: parent.bottom
                }
            }
        }
        SwipeView{
            id: swipeView
            currentIndex: tabBar.currentIndex
            anchors{
                top: tabBar.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            UtilFiles{

            }
        }
    }
}
