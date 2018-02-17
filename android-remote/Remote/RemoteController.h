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
#ifndef REMOTECONTROLLER_H
#define REMOTECONTROLLER_H

#include <QObject>
#include <QTiltSensor>
#include "SlaveConnection.h"

class RemoteController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString sensorDebug READ sensorDebug NOTIFY sensorDebugChanged)
    Q_PROPERTY(qreal leftSpeed READ leftSpeed WRITE setLeftSpeed NOTIFY leftSpeedChanged)
    Q_PROPERTY(qreal rightSpeed READ rightSpeed WRITE setRightSpeed NOTIFY rightSpeedChanged)

public:
    explicit RemoteController(QObject *parent = nullptr);
    virtual ~RemoteController();
    Q_INVOKABLE void setSlaveConnection(SlaveConnection * connection);

    QString title() const;
    QString sensorDebug() const;
    qreal leftSpeed() const;
    qreal rightSpeed() const;

    Q_INVOKABLE void disconnect();

public slots:
    void setLeftSpeed(qreal leftSpeed);
    void setRightSpeed(qreal rightSpeed);

signals:
    void titleChanged(QString title);
    void applicationSuspended();

    void sensorDebugChanged(QString sensorDebug);
    void leftSpeedChanged(qreal leftSpeed);
    void rightSpeedChanged(qreal rightSpeed);

private slots:
    void onTiltReadingChanged();
    void onApplicationStateChanged(Qt::ApplicationState state);

private:
    void setSensorDebug(QString sensorDebug);

private:
    SlaveConnection * _connection;
    QTiltSensor _tiltSensor;
    QString _sensorDebug;
    qreal _leftSpeed;
    qreal _rightSpeed;
};

#endif // REMOTECONTROLLER_H
