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
import QtQuick.Layouts 1.3

import androidremote 1.0

Page {
    title: qsTr("Raw UDP socket")

    property int smallMargin: 40
    property int largeMargin: 80

    RawUdpController {
        id: controller
    }

    ScrollView {
        id: scrollView
        anchors.fill: parent

        ColumnLayout {
            spacing: 10
            width: Math.max(scrollView.width, implicitWidth)

            Label {
                text: qsTr("Send UDP packet")
                font.pointSize: 12
            }

            Label {
                text: qsTr("Target Address:Port")
                Layout.leftMargin: smallMargin
            }
            TextField {
                id: targetLocation
                Layout.leftMargin: largeMargin
                Layout.fillWidth: true
                Layout.rightMargin: smallMargin
                selectByMouse: true
                text: "127.0.0.1:8000"
            }

            Label {
                text: qsTr("Message")
                Layout.leftMargin: smallMargin
            }

            TextField {
                id: message
                Layout.leftMargin: largeMargin
                Layout.fillWidth: true
                Layout.rightMargin: smallMargin
            }

            Button {
                text: qsTr("Send")
                Layout.alignment: Qt.AlignHCenter
                width: largeMargin
                onClicked: controller.send(targetLocation.text, message.text)
            }

            Item {
                height: 20
            }

            CheckBox {
                id: listenCheckbox
                text: qsTr("Listen for UDP packets")
                font.pointSize: 12

                onClicked: controller.enableListen(listenCheckbox.checked)
            }

            Label {
                text: qsTr("Host Address:Port")
                Layout.leftMargin: smallMargin
            }
            TextField {
                id: hostLocation
                Layout.leftMargin: largeMargin
                Layout.fillWidth: true
                Layout.rightMargin: smallMargin
                selectByMouse: true

                text: controller.hostLocation
                Binding {
                    target: controller
                    property: "hostLocation"
                    value: hostLocation.text
                }
            }

            Label {
                text: qsTr("Packets received")
                Layout.leftMargin: smallMargin
            }

            Label {
                text: controller.receivedLog.length == 0 ? "-" : controller.receivedLog
                Layout.leftMargin: largeMargin
                Layout.fillWidth: true
                Layout.rightMargin: smallMargin
                Layout.fillHeight: true
            }
        }
    }
}
