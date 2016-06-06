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

#include "settingspanel.h"


SettingsPanel::SettingsPanel(QWidget* parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    setLayout(layout);
}


SettingsPanel* SettingsPanel::fromJson(QJsonArray json, QWidget* parent)
{
    auto panel = new SettingsPanel(parent);
    return panel;
}


void SettingsPanel::addSettingItem(SettingItem* item)
{
    items.push_back(item);
    layout()->addWidget(item);
}

void SettingsPanel::addTitle(QString title)
{
    QLabel* label = new QLabel("<b>" + title + "<b/>", this);
    label->setAlignment(Qt::AlignCenter);
    layout()->addWidget(label);
}
