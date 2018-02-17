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
#include "SlavesListModel.h"

SlavesListModel::SlavesListModel(QObject *parent)
    : QAbstractListModel(parent)
{}

void SlavesListModel::addSlave(SlaveIp slave)
{
    beginInsertRows(QModelIndex(), _slaves.count(), _slaves.count());
    _slaves.append(slave);
    endInsertRows();
}

void SlavesListModel::clear()
{
    beginResetModel();
    _slaves.clear();
    endResetModel();
}

int SlavesListModel::rowCount(const QModelIndex &) const
{
    return _slaves.count();
}

QVariant SlavesListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= 0 && index.row() < _slaves.count())
    {
        auto item = _slaves.at(index.row());

        switch (role)
        {
            case NameRole:
                return item.name();

            case IpRole:
                return item.ip().toString();
        }
    }
    return QVariant();
}

QHash<int, QByteArray> SlavesListModel::roleNames() const
{
    static QHash<int, QByteArray> roles;
    if(roles.empty())
    {
        roles.insert(NameRole, "name");
        roles.insert(IpRole, "ip");
    }
    return roles;
}
