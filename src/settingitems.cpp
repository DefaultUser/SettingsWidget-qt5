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

#include "settingitems.h"

SettingItem::SettingItem(QString section, QString key, QString desc, QWidget* parent)
    : QWidget(parent), _section(section), _key(key)
{
    setToolTip(desc);
}


SettingBool::SettingBool(QString title, QString section, QString key, bool default_value,
                         QString desc, QWidget* parent)
    : SettingItem(section, key, desc, parent)
{
    auto layout = new QHBoxLayout(this);
    QLabel* label = new QLabel(title, this);
//     checkbox = new QCheckBox(this);
    // TODO: load state from settings and use "default_value" if not found
    layout->addWidget(label);
    layout->addWidget(checkbox);
    setLayout(layout);
}


SettingItem* SettingBool::fromJsonObject(QJsonObject obj, QWidget* parent)
{
    // TODO: parse the json object
    return new SettingBool("", "", "", true, "", parent);
}
