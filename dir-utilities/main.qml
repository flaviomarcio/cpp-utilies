import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import dirUtilities 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("FileUtilites")

    Material.theme: Material.System
    Material.accent: Material.LightBlue

    header: TabBar {
        id: tabBar
        Layout.fillWidth: true
        TabButton {
            text: qsTr("QtLibs")
        }
        TabButton {
            text: qsTr("DirUtil")
        }
    }

    ColumnLayout {
        id: layout
        anchors.fill: parent
        Rectangle{
            Layout.fillWidth: true
            height: 1
            color: "lightGray"
        }
        SwipeView{
            id: swipeView
            interactive: false
            Layout.fillWidth: true
            Layout.fillHeight: true

            currentIndex: tabBar.currentIndex
            UtilQt{
                clip: true
            }
            UtilFiles{
                clip: true
            }
        }
    }
}
