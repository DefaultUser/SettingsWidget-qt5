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


SettingsPanel::SettingsPanel(QSettings* settings, QWidget* parent) : QWidget(parent), _settings(settings)
{
    auto layout = new QVBoxLayout(this);
    setLayout(layout);
}


SettingsPanel* SettingsPanel::fromJson(QJsonArray json, QSettings* settings, QWidget* parent)
{
    auto panel = new SettingsPanel(settings, parent);
    // extract info from the json array
    for(auto obj_ref : json)
    {
        if(!obj_ref.isObject())
        {
            qWarning() << "Json array does not contain json objects - skipping ...";
            continue;
        }
        QJsonObject obj = obj_ref.toObject();

        // sort out titles
        if(obj["type"].toString() == "title")
        {
            panel->addTitle(obj["title"].toString());
        }
        else
        {
            auto new_item = SettingItemCreation::createItemfromJson(obj, settings, panel);
            if(!new_item)
            {
                qWarning() << "SettingItemCreation for type " << obj["type"].toString() << " failed.";
                continue;
            }
            panel->addSettingItem(new_item);
        }
    }
    return panel;
}


void SettingsPanel::addSettingItem(SettingItem* item)
{
    _items.push_back(item);
    layout()->addWidget(item);
}

void SettingsPanel::addTitle(QString title)
{
    QLabel* label = new QLabel("<b>" + title + "<b/>", this);
    label->setAlignment(Qt::AlignCenter);
    layout()->addWidget(label);
}
