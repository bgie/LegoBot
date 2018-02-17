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

import androidremote 1.0

Page {
    id: page

    title: qsTr("Connect")   

    property int smallMargin: 40
    property int largeMargin: 80

    ConnectController {
        id: controller
    }

    Component.onCompleted:  {
        controller.setSlaveConnection(connection);
        controller.refreshSlaveIps()
    }

    Label {
        visible: !controller.slavesFound
        text: qsTr("No devices detected")
        font.pointSize: 16
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Label {
        visible: controller.slavesFound
        id: header
        text: qsTr("Detected devices:")
        font.pointSize: 16
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
    }

    ListView {
        visible: controller.slavesFound
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: header.bottom
        anchors.leftMargin: 20
        anchors.rightMargin: 20

        model: controller.slaves;
        delegate: Row {
            height: 30
            spacing: 10

            Button {
                height: parent.height
                text: qsTr("Connect")

                onClicked: {
                    controller.connectSlave(model.name, model.ip);
                    stackView.push("../Remote/RemotePage.qml");
                }
            }

            Label {
                height: parent.height
                verticalAlignment: Text.AlignVCenter
                width: 120
                text: model.name
                font.pointSize: 12
            }
        }
    }

    Image {
        source: "qrc:/img/refresh.png"
        anchors.right: parent.right
        anchors.top: parent.top

        width: 32
        height: 32

        MouseArea {
            anchors.fill: parent
            onClicked: {
               controller.refreshSlaveIps()
            }
        }
    }
}
