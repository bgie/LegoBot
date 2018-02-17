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
#ifndef SLAVEIP_H
#define SLAVEIP_H

#include <QString>
#include <QHostAddress>

class SlaveIp
{
public:
    SlaveIp();
    SlaveIp(QString name, QHostAddress ip);

    QString name() const;
    QHostAddress ip() const;

    bool operator ==(const SlaveIp & other) const;
    bool operator !=(const SlaveIp & other) const;

private:
    QString _name;
    QHostAddress _ip;
};

#endif // SLAVEIP_H
