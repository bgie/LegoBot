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
#include "RemoteController.h"
#include <QTiltReading>
#include <QGuiApplication>

namespace
{
const qreal TILT_RANGE = 45;
const qreal TILT_Y_OFFSET = 45;
const qreal TILT_DEAD_ZONE = 12;

qreal tiltToPercentage(qreal tilt)
{
    if(tilt >= - TILT_DEAD_ZONE && tilt <= TILT_DEAD_ZONE)
    {
        return 0;
    }
    else {
        return (tilt * 100) / TILT_RANGE;
    }
}
qreal clampPercentage(qreal p)
{
    if(p <= -100) {
        return -100;
    }
    else if( p >= 100) {
        return 100;
    }
    else {
        return p;
    }
}
}

RemoteController::RemoteController(QObject *parent)
    : QObject(parent)
    , _connection(nullptr)
    , _leftSpeed(0)
    , _rightSpeed(0)
{
    connect(qGuiApp, &QGuiApplication::applicationStateChanged
            , this, &RemoteController::onApplicationStateChanged);

    connect(&_tiltSensor, &QSensor::readingChanged, this, &RemoteController::onTiltReadingChanged);
    if(_tiltSensor.start())
    {
        onTiltReadingChanged();
    }
    else
    {
        _sensorDebug = tr("Failed to start tilt sensor");
    }
}

RemoteController::~RemoteController()
{}

void RemoteController::setSlaveConnection(SlaveConnection *connection)
{
    if(_connection != connection)
    {
        if(_connection)
        {
            QObject::disconnect(_connection, 0, this, 0);
        }

        _connection = connection;

        if(_connection)
        {
            QObject::connect(_connection, &SlaveConnection::nameChanged, this, &RemoteController::titleChanged);
        }

        emit titleChanged(title());
    }
}

QString RemoteController::title() const
{
    return _connection ? _connection->name() : QString("");
}

QString RemoteController::sensorDebug() const
{
    return _sensorDebug;
}

void RemoteController::disconnect()
{
    if(_connection) _connection->disconnect();
}

void RemoteController::setLeftSpeed(qreal leftSpeed)
{
    if (qFuzzyCompare(_leftSpeed, leftSpeed))
        return;

    _leftSpeed = leftSpeed;
    emit leftSpeedChanged(_leftSpeed);
}

void RemoteController::setRightSpeed(qreal rightSpeed)
{
    if (qFuzzyCompare(_rightSpeed, rightSpeed))
        return;

    _rightSpeed = rightSpeed;
    emit rightSpeedChanged(_rightSpeed);
}

qreal RemoteController::leftSpeed() const
{
    return _leftSpeed;
}

qreal RemoteController::rightSpeed() const
{
    return _rightSpeed;
}

void RemoteController::setSensorDebug(QString sensorDebug)
{
    if (_sensorDebug == sensorDebug)
        return;

    _sensorDebug = sensorDebug;
    emit sensorDebugChanged(_sensorDebug);
}

void RemoteController::onTiltReadingChanged()
{
    auto reading = _tiltSensor.reading();

    qreal x = reading->xRotation();
    qreal y = reading->yRotation();
    setSensorDebug(QString("x: %1, y: %2")
                   .arg(x, 2, 'f', 1)
                   .arg(y, 2, 'f', 1)
                   );

//    qreal forward = tiltToPercentage(y + TILT_Y_OFFSET);
//    qreal turn = tiltToPercentage(x);
//    setLeftSpeed(clampPercentage(forward + turn));
//    setRightSpeed(clampPercentage(forward - turn));

    qreal left = tiltToPercentage(y + TILT_Y_OFFSET + x);
    qreal right = tiltToPercentage(y + TILT_Y_OFFSET - x);
    setLeftSpeed(clampPercentage(left));
    setRightSpeed(clampPercentage(right));
}

void RemoteController::onApplicationStateChanged(Qt::ApplicationState state)
{
    if(state == Qt::ApplicationSuspended)
    {
        emit applicationSuspended();
    }
}
