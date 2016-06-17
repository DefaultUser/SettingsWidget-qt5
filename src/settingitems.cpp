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

SettingItem::SettingItem(QSettings* settings, QString section, QString key, QString desc, QWidget* parent)
    : QWidget(parent), _settings(settings), _section(section), _key(key)
{
    setToolTip(desc);
}


SettingBool::SettingBool(QSettings* settings, QString title, QString section, QString key, bool default_value,
                         QString desc, QWidget* parent)
    : SettingItem(settings, section, key, desc, parent), _default_value(default_value)
{
    auto layout = new QHBoxLayout(this);
    QLabel* label = new QLabel(title, this);
    _checkbox = new QCheckBox(this);
    layout->addWidget(label);
    layout->addWidget(_checkbox);
    setLayout(layout);

    // load the settings
    loadSetting();
}


SettingItem* SettingBool::fromJsonObject(QJsonObject obj, QSettings* settings, QWidget* parent)
{
    if (!obj.contains("title") or !obj.contains("section") or !obj.contains("key"))
    {
        qWarning() << "SettingBool item created from json is missing (a) mandatory field(s)";
        return nullptr;
    }
    // parse the json object
    QString title = obj["title"].toString();
    QString section = obj["section"].toString();
    QString key = obj["key"].toString();
    bool default_value = obj["default"].toBool();
    QString desc = obj["desc"].toString();

    return new SettingBool(settings, title, section, key, default_value, desc, parent);
}


void SettingBool::restoreDefault()
{
    _checkbox->setChecked(_default_value);
}


void SettingBool::loadSetting()
{
    _settings->beginGroup(_section);
    bool value = _settings->value(_key, _default_value).toBool();
    _checkbox->setChecked(value);
    _settings->endGroup();
}


void SettingBool::saveSetting()
{
    _settings->beginGroup(_section);
    _settings->setValue(_key, _checkbox->isChecked());
    _settings->endGroup();
}


namespace SettingItemCreation
{
    namespace
    {
        SettingsTypeMap _typemap = {{"bool", SettingBool::fromJsonObject}};
    }

    void registerType(QString identifier, SettingItemFactory factory)
    {
        if (_typemap.contains(identifier))
        {
            qWarning() << identifier << " allready exists - not adding the new SettingItem";
            return;
        }
        _typemap[identifier] = factory;
    }

    SettingItem* createItemfromJson(QJsonObject json, QSettings* settings, QWidget* parent)
    {
        QString type = json["type"].toString();
        if (!_typemap.contains(type))
        {
            qWarning() << type << " is no registered type - Skipping item";
            return nullptr;
        }
        return _typemap[type](json, settings, parent);
    }
}
