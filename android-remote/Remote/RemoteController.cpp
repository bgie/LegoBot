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

RemoteController::RemoteController(QObject *parent)
    : QObject(parent)
    , _connection(nullptr)
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

    setSensorDebug(QString("x: %1, y: %2").arg(reading->xRotation()).arg(reading->yRotation()));
}

void RemoteController::onApplicationStateChanged(Qt::ApplicationState state)
{
    if(state == Qt::ApplicationSuspended)
    {
        emit applicationSuspended();
    }
}
