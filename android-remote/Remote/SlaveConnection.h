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
#ifndef SLAVECONNECTION_H
#define SLAVECONNECTION_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include "../Connect/SlaveIp.h"

class SlaveConnection : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)

public:
    explicit SlaveConnection(QObject *parent = nullptr);
    virtual ~SlaveConnection();

    QString name() const;

    void connect(QString name, QHostAddress ip, int port);
    void sendMotorSpeeds(qreal leftPercentage, qreal rightPercentage);
    void disconnect();

signals:
    void nameChanged(QString name);

private slots:
    void onKeepAliveTimerTimeout();

private:
    QUdpSocket _socket;
    QTimer _stayingAliveTimer;

    bool _connected;
    QString _name;
    QHostAddress _ip;
    int _port;
    QString m_name;
    QByteArray _lastMotorSpeedCommand;
};



#endif // SLAVECONNECTION_H
