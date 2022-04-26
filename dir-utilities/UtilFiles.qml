import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import Qt.labs.folderlistmodel
import Qt.labs.platform
import Utils 0.0

Rectangle {
    Item {
        id: name
        anchors{
            fill: parent
            margins: 10
        }
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
                    placeholderText: "Set work dir"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: StandardPaths.writableLocation(StandardPaths.AppDataLocation);
                    onTextChanged: {
                        let dir=String(text).replace("file://","")
                    }
                }
                TextField{
                    id: textSearchExtension
                    text: "*.*"
                    placeholderText: "Set extensions, ex: *.*"
                    Layout.fillHeight: true
                }
                CheckBox{
                    id: checkChangeIntoFiles
                    Layout.fillHeight: true
                    text: "Change into files"
                }
            }
            RowLayout{
                Layout.fillHeight: true
                Layout.fillWidth: true
                TextField{
                    id: textSearchExpression
                    placeholderText: "Search expression"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
                TextField{
                    id: textSearchText
                    placeholderText: "Search text"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
                TextField{
                    id: textSearchTextReplace
                    placeholderText: "Text to replace"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }
            RowLayout{
                Layout.fillHeight: true
                Layout.fillWidth: true

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
                            text: "Rename"
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            onClicked: searchModel.rename(textSearchText.text, textSearchTextReplace.text)
                        }
                    }
                }
            }
        }




        SearchModel{
            id: searchModel


            function setData(){
                textWorkDir.text=settings.workDir
                textSearchExtension.text=settings.searchExtension
                checkChangeIntoFiles.checked=settings.changeIntoFiles
                textSearchExpression.text=settings.searchExpression
                textSearchText.text=settings.searchText
                textSearchTextReplace.text=settings.searchTextReplace

                settings.workDir=Qt.binding(function(){ return textWorkDir.text })
                settings.searchExtension=Qt.binding(function(){ return textSearchExtension.text })
                settings.changeIntoFiles=Qt.binding(function(){ return checkChangeIntoFiles.checked })
                settings.searchExpression=Qt.binding(function(){ return textSearchExpression.text })
                settings.searchText=Qt.binding(function(){ return textSearchText.text })
                settings.searchTextReplace=Qt.binding(function(){ return textSearchTextReplace.text })

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
    Component.onCompleted: searchModel.setData()
}
