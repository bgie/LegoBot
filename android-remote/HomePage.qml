import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    title: qsTr("Esp8266 remote")

    Column {
        anchors.fill: parent

        Button {
            text: qsTr("Raw UDP socket") + " \u25BA"
            width: parent.width
            onClicked: {
                stackView.push("RawUdp/RawUdpPage.qml")
            }
        }

        Button {
            text: qsTr("Connect") + "\u25BA"
            width: parent.width
            onClicked: {
                stackView.push("Connect/ConnectPage.qml")
            }
        }      
    }
}
