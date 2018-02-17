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
#include "RawUdpController.h"
#include <QNetworkDatagram>

RawUdpController::RawUdpController(QObject *parent)
    : QObject(parent)
    , _hostLocation("127.0.0.1:8000")
{}

QString RawUdpController::hostLocation() const
{
    return _hostLocation;
}

QString RawUdpController::receivedLog() const
{
    return _receivedLog;
}

bool RawUdpController::listenerActive() const
{
    return _listener;
}

void RawUdpController::enableListen(bool enabled)
{
    if(listenerActive() != enabled)
    {
        if(enabled)
        {
            QStringList parts = _hostLocation.split(":");
            if(parts.count() == 2)
            {
                _listener.reset(new QUdpSocket());
                _listener->bind(QHostAddress(parts.at(0)), parts.at(1).toInt(), QAbstractSocket::ShareAddress);
                connect(_listener.data(), &QUdpSocket::readyRead,this, &RawUdpController::onUpdSocketReadyRead);
                logMessage(QString("Enabled UDP listening at %1\n").arg(_hostLocation));
            }
        }
        else
        {
            _listener.reset();
            logMessage(QString("Disabled UDP listener\n"));
        }
        emit listenerActiveChanged(listenerActive());
    }
}

void RawUdpController::send(QString targetLocation, QString message)
{
    QUdpSocket socket;
    QStringList parts = targetLocation.split(":");
    if(parts.count() == 2)
    {
        socket.writeDatagram(message.toLatin1(), QHostAddress(parts.at(0)), parts.at(1).toInt());
    }
}

void RawUdpController::setHostLocation(QString a)
{
    if(_hostLocation != a)
    {
        _hostLocation = a;
        emit hostLocationChanged(_hostLocation);
    }
}

void RawUdpController::setReceivedLog(QString p)
{
    if(_receivedLog != p)
    {
        _receivedLog = p;
        emit receivedLogChanged(_receivedLog);
    }
}

void RawUdpController::onUpdSocketReadyRead()
{
    while(_listener->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = _listener->receiveDatagram();
        logMessage(QString("Message '%3' received from %1:%2\n")
                   .arg(datagram.senderAddress().toString())
                   .arg(datagram.senderPort())
                   .arg(QString::fromLatin1(datagram.data())));
    }
}

void RawUdpController::logMessage(QString msg)
{
    setReceivedLog(receivedLog() + msg);
}
