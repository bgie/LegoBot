/*  LegoBot Android Remote
 *  Copyright (C) 2018 Brecht Kuppens
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
import QtQuick 2.9
import QtQuick.Controls 2.2

import "RawUdp"

ApplicationWindow {
    id: window
    visible: true
    width: 600
    height: 800
    title: qsTr("ESP Remote")

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Connect")
                width: parent.width
                onClicked: {
                    stackView.replace("Connect/ConnectPage.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Raw UDP socket")
                width: parent.width
                onClicked: {
                    stackView.replace("RawUdp/RawUdpPage.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("About")
                width: parent.width
                onClicked: {
                    stackView.replace("Info/InfoPage.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "Connect/ConnectPage.qml"
        anchors.fill: parent
        anchors.margins: 10
    }
}
