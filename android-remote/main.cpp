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
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "RawUdp/RawUdpController.h"
#include "Connect/ConnectController.h"
#include "Remote/RemoteController.h"

#include "Remote/SlaveConnection.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<RawUdpController>("androidremote", 1, 0, "RawUdpController");
    qmlRegisterType<ConnectController>("androidremote", 1, 0, "ConnectController");
    qmlRegisterType<RemoteController>("androidremote", 1, 0, "RemoteController");

    QQmlApplicationEngine engine;

    SlaveConnection * connection = new SlaveConnection(&engine);
    engine.rootContext()->setContextProperty("connection", connection);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
