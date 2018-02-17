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
#include "ConnectController.h"
#include <QHostAddress>
#include <QNetworkInterface>
#include <QNetworkDatagram>
#include "SlaveIp.h"

const QByteArray discoverSlavesCommand("HI");
const int masterPort(8000);
const int slavePort(8001);  // different port to avoid broadcasting to self issue

ConnectController::ConnectController(QObject *parent)
    : QObject(parent)
    , _slaves(new SlavesListModel(this))
    , _connection(nullptr)
{
    connect(&_listenSocket, &QUdpSocket::readyRead, this, &ConnectController::onSocketReadyRead);
    _listenSocket.bind(QHostAddress::Any, masterPort, QAbstractSocket::ShareAddress);
}

void ConnectController::setSlaveConnection(SlaveConnection *connection)
{
    _connection = connection;
}

bool ConnectController::slavesFound() const
{
    return _slaves->rowCount() > 0;
}

SlavesListModel *ConnectController::slaves() const
{
    return _slaves;
}

void ConnectController::refreshSlaveIps()
{
    _slaves->clear();
    emit slavesFoundChanged(slavesFound());

    foreach(auto interface, QNetworkInterface::allInterfaces())
    {
        foreach(auto address, interface.addressEntries())
        {
            QHostAddress dest = address.broadcast();

            _sendSocket.writeDatagram(discoverSlavesCommand, dest, slavePort);
        }
    }
}

void ConnectController::connectSlave(QString name, QString slaveIp)
{
    Q_ASSERT(_connection);

    _connection->connect(name, QHostAddress(slaveIp), slavePort);
}

void ConnectController::onSocketReadyRead()
{
    bool changes = false;
    while(_listenSocket.hasPendingDatagrams())
    {
        QNetworkDatagram datagram = _listenSocket.receiveDatagram();
        QHostAddress slaveIp = datagram.senderAddress();
        QString slaveName = datagram.data();
        _slaves->addSlave(SlaveIp(slaveName, slaveIp));
        changes = true;
    }

    if(changes)
    {
        emit slavesFoundChanged(slavesFound());
    }
}
