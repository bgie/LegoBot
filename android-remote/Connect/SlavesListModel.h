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
#ifndef SLAVESLISTMODEL_H
#define SLAVESLISTMODEL_H

#include <QAbstractListModel>
#include "SlaveIp.h"

class SlavesListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(Roles)

public:
    enum Roles
    {
        NameRole = 0
        , IpRole
    };

public:
    explicit SlavesListModel(QObject *parent = nullptr);

    void addSlave(SlaveIp slave);
    void clear();

    virtual int rowCount(const QModelIndex & index= QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    QVector<SlaveIp> _slaves;
};

#endif // SLAVESLISTMODEL_H
