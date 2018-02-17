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
#ifndef RAWUDPCONTROLLER_H
#define RAWUDPCONTROLLER_H

#include <QObject>
#include <QUdpSocket>

class RawUdpController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString hostLocation READ hostLocation WRITE setHostLocation NOTIFY hostLocationChanged)
    Q_PROPERTY(QString receivedLog READ receivedLog WRITE setReceivedLog NOTIFY receivedLogChanged)
    Q_PROPERTY(bool listenerActive READ listenerActive NOTIFY listenerActiveChanged)

public:
    explicit RawUdpController(QObject *parent = nullptr);

    QString hostLocation() const;
    QString receivedLog() const;
    bool listenerActive() const;

    Q_INVOKABLE void enableListen(bool enabled);
    Q_INVOKABLE void send(QString targetLocation, QString message);

public slots:
    void setHostLocation(QString a);
    void setReceivedLog(QString p);

signals:
    void hostLocationChanged(QString a);
    void receivedLogChanged(QString p);
    void listenerActiveChanged(bool active);

private slots:
    void onUpdSocketReadyRead();

private:
    void logMessage(QString msg);

private:
    QString _hostLocation;
    QString _receivedLog;

    QScopedPointer<QUdpSocket> _listener;
};

#endif // RAWUDPCONTROLLER_H
