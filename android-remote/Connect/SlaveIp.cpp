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
#include "SlaveIp.h"

SlaveIp::SlaveIp()
{}

SlaveIp::SlaveIp(QString name, QHostAddress ip)
    : _name(name)
    , _ip(ip)
{}

QString SlaveIp::name() const
{
    return _name;
}

QHostAddress SlaveIp::ip() const
{
    return _ip;
}

bool SlaveIp::operator ==(const SlaveIp &other) const
{
    return _ip == other._ip && _name == other._name;
}

bool SlaveIp::operator !=(const SlaveIp &other) const
{
    return !(*this == other);
}
