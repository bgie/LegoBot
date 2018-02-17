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

Page {
    title: qsTr("About")

    ColumnLayout {
        anchors.fill: parent

        Label {
            text: qsTr("LegoBot Android Remote")
            font.pointSize: 16
            Layout.alignment: Qt.AlignCenter
        }
        Label {
            text: qsTr("Copyright (C) 2018 Brecht Kuppens")
            Layout.alignment: Qt.AlignCenter
        }
        Item {
            height: 10
        }
        LinkLabel {
            text: qsTr("This program is free software: you can redistribute it and/or modify<br/>
                        it under the terms of the GNU General Public License as published by<br/>
                        the Free Software Foundation, either version 3 of the License, or<br/>
                        (at your option) any later version.<br/>
                        <br/>
                        This program is distributed in the hope that it will be useful,<br/>
                        but WITHOUT ANY WARRANTY; without even the implied warranty of<br/>
                        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the<br/>
                        <a href=\"http://www.gnu.org/licenses/gpl-3.0.html\">GNU General Public License</a> for more details.")
            font.pointSize: 9
            Layout.alignment: Qt.AlignCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            text: qsTr("Source code")
            font.pointSize: 14
            Layout.alignment: Qt.AlignCenter
            Layout.topMargin: 25
        }
        LinkLabel {
            text: qsTr("Source code is hosted on <a href=\"https://github.com/bgie/LegoBot\">github</a>");
            Layout.alignment: Qt.AlignCenter
        }

        Label {
            text: qsTr("Artwork")
            font.pointSize: 14
            Layout.alignment: Qt.AlignCenter
            Layout.topMargin: 25
        }
        LinkLabel {
            text: "refresh icon by <a href=\"http://naomiatkinson.com/\">Naomi Atkinson</a><br\>
                  wheel & arrows icons by <a href=\"https://www.freepik.com/\">Freepik</a> from www.flaticon.com"

            Layout.alignment: Qt.AlignCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
