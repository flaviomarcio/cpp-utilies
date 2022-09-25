import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import Qt.labs.folderlistmodel
import Qt.labs.platform
import Utils 0.0
import Qt.labs.folderlistmodel 2.3

Item {
    id: name
    Component.onCompleted: searchModel.setData()
    ColumnLayout{
        id: cLayout
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
        }
        RowLayout{
            Layout.fillHeight: true
            Layout.fillWidth: true
            TextField{
                id: textWorkDir
                placeholderText: "Set QtDir"
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: StandardPaths.writableLocation(StandardPaths.HomeLocation)+"/Qt";
            }
            TextField{
                id: textDestineDir
                placeholderText: "Set QtLibs"
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: StandardPaths.writableLocation(StandardPaths.HomeLocation)+"/erp-worker/binary/qt-lib";
            }
            TextField{
                id: textSearchExtension
                text: "*.so"
                placeholderText: "Set extensions, ex: *.*"
                Layout.fillHeight: true
            }
        }
        ToolBar{
            Layout.fillHeight: true
            Layout.fillWidth: true
            RowLayout{
                spacing: 5
                anchors{
                    top: parent.top
                    left: parent.left
                    bottom: parent.bottom
                    margins: spacing
                }
                RowLayout{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    //layoutDirection: Qt.RightToLeft
                    ToolButton{
                        text: "Copy"
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        //onClicked: searchModel.rename(textSearchText.text, textSearchTextReplace.text)
                    }
                }
            }
        }
    }




    SearchQtLibModel{
        id: searchModel
        settings.name: "UtilQt"


        function setData(){
//            textWorkDir.text=settings.workDir
//            textSearchExtension.text=settings.searchExtension
//            checkChangeIntoFiles.checked=settings.changeIntoFiles
//            checkShowAllFiles.checked=settings.showAllFiles
//            textSearchExpression.text=settings.searchExpression
//            textSearchText.text=settings.searchText
//            textSearchTextReplace.text=settings.searchTextReplace

            settings.workDir=Qt.binding(function(){ return textWorkDir.text })
            settings.searchExtension=Qt.binding(function(){ return textSearchExtension.text })
//            settings.changeIntoFiles=Qt.binding(function(){ return checkChangeIntoFiles.checked })
//            settings.showAllFiles=Qt.binding(function(){ return checkShowAllFiles.checked })
//            settings.searchExpression=Qt.binding(function(){ return textSearchExpression.text })
//            settings.searchText=Qt.binding(function(){ return textSearchText.text })
//            settings.searchTextReplace=Qt.binding(function(){ return textSearchTextReplace.text })

            searchModel.search();
        }

    }

    ListView{
        id: listView
        clip: true
        anchors{
            top: cLayout.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        model: searchModel
        delegate: ItemDelegate{
            //Layout.fillWidth: true
            width: listView.width
            contentItem: ItemDelegate{
                Layout.fillWidth: true
                RowLayout{
                    clip: true
                    anchors{
                        top: parent.top
                        left: parent.left
                        right: parent.right
                        bottom: parent.bottom
                    }
                    ToolSeparator{
                        //Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                    ColumnLayout{
                        id: itemLayCol
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        RowLayout{
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Label{
                                horizontalAlignment: Qt.AlignLeft
                                Material.foreground: Material.Grey
                                Layout.fillHeight: true
                                text: "fileName: "
                            }
                            Label{
                                Layout.fillHeight: true
                                text: model.filePath
                            }
                        }
                        RowLayout{
                            id:itemLayRow
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Label{
                                Material.foreground: Material.Grey
                                Layout.fillHeight: true
                                text: "rename"
                            }
                            Label{
                                text: fileName
                                Layout.fillHeight: true
                            }
                            Label{
                                Layout.fillHeight: true
                                Material.foreground: Material.Grey
                                text: "to"
                            }
                            Label{
                                Layout.fillHeight: true
                                text: String(fileName).replace(textSearchText.text, textSearchTextReplace.text)
                            }
                        }
                    }
                }
            }
        }
    }
}
