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
#ifndef CONNECTCONTROLLER_H
#define CONNECTCONTROLLER_H

#include <QObject>
#include <QUdpSocket>
#include "SlavesListModel.h"
#include "../Remote/SlaveConnection.h"

class ConnectController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool slavesFound READ slavesFound NOTIFY slavesFoundChanged)
    Q_PROPERTY(SlavesListModel* slaves READ slaves CONSTANT)

public:
    explicit ConnectController(QObject *parent = nullptr);
    Q_INVOKABLE void setSlaveConnection(SlaveConnection * connection);

    bool slavesFound() const;
    SlavesListModel* slaves() const;

    Q_INVOKABLE void refreshSlaveIps();
    Q_INVOKABLE void connectSlave(QString name, QString slaveIp);

signals:
    void slavesFoundChanged(bool found);

private:
    void onSocketReadyRead();    

private:
    SlavesListModel * _slaves;
    QUdpSocket _sendSocket;
    QUdpSocket _listenSocket;
    SlaveConnection * _connection;
};

#endif // CONNECTCONTROLLER_H
