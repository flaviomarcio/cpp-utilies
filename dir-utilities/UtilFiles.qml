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
                    id: textExtention
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
                    id: textExpression
                    placeholderText: "Search expression"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
                TextField{
                    id: textReplaceText
                    placeholderText: "Search text"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
                TextField{
                    id: textNewText
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
                            onClicked: searchModel.rename(textReplaceText.text, textNewText.text)
                        }
                    }
                }
            }
        }

//        FolderListModel {
//            id: folderModel
//            nameFilters:{
//                if(!String(textExtention.text).trim())
//                    return ["*.*"];
//                try {
//                    return JSON.parse(textExtention.text)
//                }
//                catch(err) {
//                    return [textExtention.text]
//                }
//            }
//        }

        SearchModel{
            id: searchModel
            Component.onCompleted: {
                textWorkDir.text=searchModel.rootDir
                searchModel.rootDir=Qt.binding(function(){ return textWorkDir.text })

                textExtention.text=searchModel.ext
                searchModel.ext=Qt.binding(function(){ return textExtention.text })

                textExpression.text=searchModel.expression
                searchModel.expression=Qt.binding(function(){ return textExpression.text })

                checkChangeIntoFiles.checked=searchModel.changeIntoFiles
                searchModel.changeIntoFiles=Qt.binding(function(){ return checkChangeIntoFiles.checked })

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
                                    text: String(fileName).replace(textReplaceText.text, textNewText.text)
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
