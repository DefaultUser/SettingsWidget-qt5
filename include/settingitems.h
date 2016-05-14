/**
 * SettingsWidget-qt5
 *
 * Copyright (C) 2016 Sebastian Schmidt
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef SETTINGITEMS_H
#define SETTINGITEMS_H

#include <QtWidgets>
#include <QJsonObject>


class SettingItem : public QWidget
{
    Q_OBJECT

public:
    SettingItem(QWidget* parent = 0);
    static SettingItem* fromJsonObject(QJsonObject obj, QWidget* parent = 0);

protected:
    virtual void parseJsonObject(QJsonObject obj) = 0;
};


class SettingTitle : public SettingItem
{
    Q_OBJECT

public:
    SettingTitle(QString title, QString desc = "", QWidget* parent = 0);

protected:
    void parseJsonObject(QJsonObject obj);
};


class SettingBool : public SettingItem
{
    Q_OBJECT

public:
    SettingBool(QString title, QString section, QString key, bool default_value, QString desc = "", QWidget* parent = 0);

protected:
    void parseJsonObject(QJsonObject obj);

private:
    QCheckBox* checkbox;
};


typedef SettingItem* (*SettingItemFactory)(QJsonObject, QWidget*);
typedef QMap<QString, SettingItemFactory> SettingsTypeMap;

#endif // SETTINGITEMS_H
