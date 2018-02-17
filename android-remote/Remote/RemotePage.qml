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
    id: remotePage
    RemoteController {
        id: controller

        onApplicationSuspended: {
            stackView.pop(remotePage);
            stackView.pop();
            controller.disconnect();
        }
    }

    Component.onCompleted:  {
        controller.setSlaveConnection(connection);
    }

    title: controller.title

    Label {
        id: sensorLabel
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        text: controller.sensorDebug
        horizontalAlignment: Text.AlignHCenter
    }
    RowLayout {
        anchors.top: sensorLabel.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        WheelSpeedIndicator {
            id: leftSpeed
            mirror: true
            size: 128
            Layout.alignment: Qt.AlignCenter
            speed: controller.leftSpeed
        }
        Item {
            Layout.fillWidth: true
        }
        WheelSpeedIndicator {
            id: righSpeed
            mirror: false
            size: 128
            Layout.alignment: Qt.AlignCenter
            speed: controller.rightSpeed
        }
    }
}
