#  LegoBot Android Remote
#  Copyright (C) 2018 Brecht Kuppens
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <https://www.gnu.org/licenses/>.

QT += quick network sensors
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    RawUdp/RawUdpController.h \
    Connect/ConnectController.h \
    Connect/SlaveIp.h \
    Connect/SlavesListModel.h \
    Remote/SlaveConnection.h \
    Remote/RemoteController.h

SOURCES += main.cpp \
    RawUdp/RawUdpController.cpp \
    Connect/ConnectController.cpp \
    Connect/SlaveIp.cpp \
    Connect/SlavesListModel.cpp \
    Remote/SlaveConnection.cpp \
    Remote/RemoteController.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
