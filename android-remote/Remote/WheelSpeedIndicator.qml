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

Column {
    property alias mirror: wheelImage.mirror
    property real size: 32
    property real speed: 0

    property real activeOpacity: 1.0
    property real inactiveOpacity: 0.05

    spacing: 32

    Image {        
        source: "qrc:/img/arrows.png"
        rotation: -90
        height: size
        width: size        
        opacity: (speed > 0) ? activeOpacity : inactiveOpacity
    }
    Image {
        id: wheelImage
        source: "qrc:/img/wheel.png"
        height: size
        width: size
        opacity: (speed == 0) ? activeOpacity : inactiveOpacity
    }
    Image {
        source: "qrc:/img/arrows.png"
        rotation: 90
        height: size
        width: size
        opacity: (speed < 0) ? activeOpacity : inactiveOpacity
    }
}
