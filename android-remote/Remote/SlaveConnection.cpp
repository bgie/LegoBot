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
#include "SlaveConnection.h"

namespace
{
const int stayingAliveIntervalInMsecs = 2500;
const QByteArray connectSlaveCommand("CONNECT");
const QByteArray stayingAliveCommand("HAH");
const QByteArray disconnectSlaveCommand("BYE");
const QByteArray motorSpeedCommand("MOTOR");

QByteArray motorSpeedValue(qreal speedAsPercentage)
{
    int val = static_cast<int>(qRound(1024 * speedAsPercentage / 100));
    return QByteArray(" ") + QByteArray::number(val, 10);
}
}

SlaveConnection::SlaveConnection(QObject *parent)
    : QObject(parent)
    , _connected(false)
{
    _stayingAliveTimer.setInterval(stayingAliveIntervalInMsecs);
    _stayingAliveTimer.setSingleShot(false);
    QObject::connect(&_stayingAliveTimer, &QTimer::timeout, this, &SlaveConnection::onKeepAliveTimerTimeout);
}

SlaveConnection::~SlaveConnection()
{
    disconnect();
}

QString SlaveConnection::name() const
{
    return _name;
}

void SlaveConnection::connect(QString name, QHostAddress ip, int port)
{
    disconnect();

    _name = name;
    _ip = ip;
    _port = port;
    _connected = true;

    _socket.writeDatagram(connectSlaveCommand, _ip, _port);
    _lastMotorSpeedCommand.clear();
    _stayingAliveTimer.start();

    emit nameChanged(_name);
}

void SlaveConnection::sendMotorSpeeds(qreal leftPercentage, qreal rightPercentage)
{
    if(_connected)
    {
        QByteArray cmd = motorSpeedCommand
                            + motorSpeedValue(leftPercentage)
                            + motorSpeedValue(rightPercentage);

        if(_lastMotorSpeedCommand != cmd)
        {
            _lastMotorSpeedCommand = cmd;
            _socket.writeDatagram(cmd, _ip, _port);
        }
    }
}

void SlaveConnection::disconnect()
{
    if(_connected)
    {
        _stayingAliveTimer.stop();

        _socket.writeDatagram(disconnectSlaveCommand, _ip, _port);

        _name.clear();
        _ip.clear();
        _port = 0;
        _connected = false;

        emit nameChanged(_name);
    }
}

void SlaveConnection::onKeepAliveTimerTimeout()
{
    _socket.writeDatagram(stayingAliveCommand, _ip, _port);
}
