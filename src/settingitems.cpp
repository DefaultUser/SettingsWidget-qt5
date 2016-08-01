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


/////////////////////////////
// SettingBool
/////////////////////////////

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


/////////////////////////////
// SettingString
/////////////////////////////

SettingString::SettingString(QSettings* settings, QString title, QString section, QString key, QString default_value,
                             QString desc, QWidget* parent)
    : SettingItem(settings, section, key, desc, parent), _default_value(default_value)
{
    auto layout = new QHBoxLayout(this);
    QLabel* label = new QLabel(title, this);
    _line_edit = new QLineEdit(this);
    layout->addWidget(label);
    layout->addWidget(_line_edit);
    setLayout(layout);

    // load the settings
    loadSetting();
}


SettingItem* SettingString::fromJsonObject(QJsonObject obj, QSettings* settings, QWidget* parent)
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
    QString default_value = obj["default"].toString();
    QString desc = obj["desc"].toString();

    return new SettingString(settings, title, section, key, default_value, desc, parent);
}


void SettingString::restoreDefault()
{
    _line_edit->setText(_default_value);
}


void SettingString::loadSetting()
{
    _settings->beginGroup(_section);
    QString value = _settings->value(_key, _default_value).toString();
    _line_edit->setText(value);
    _settings->endGroup();
}


void SettingString::saveSetting()
{
    _settings->beginGroup(_section);
    _settings->setValue(_key, _line_edit->text());
    _settings->endGroup();
}


/////////////////////////////
// SettingPath
/////////////////////////////

SettingPath::SettingPath(QSettings* settings, QString title, QString section, QString key, QString default_value,
                         QString desc, Behaviour behaviour, QString filter, QWidget* parent)
    : SettingItem(settings, section, key, desc, parent), _default_value(default_value),
      _behaviour(behaviour), _filter(filter)
{
    auto layout = new QHBoxLayout(this);
    QLabel* label = new QLabel(title, this);
    _line_edit = new QLineEdit(this);
    _btn = new QPushButton(QIcon::fromTheme("folder"), "", this);
    layout->addWidget(label);
    layout->addWidget(_line_edit);
    layout->addWidget(_btn);
    setLayout(layout);

    // QCompleter for file models
    auto completer = new QCompleter(this);
    auto model = new QFileSystemModel(completer);
    model->setRootPath(QDir::rootPath());
    if (_behaviour == Directory)
    {
        model->setFilter(QDir::Dirs);
    }
    completer->setModel(model);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    _line_edit->setCompleter(completer);

    // connect the Push button
    connect(_btn, &QPushButton::clicked, this, &SettingPath::showFileDialog);

    // load the settings
    loadSetting();
}


SettingItem* SettingPath::fromJsonObject(QJsonObject obj, QSettings* settings, QWidget* parent)
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
    QString default_value = obj["default"].toString();
    QString desc = obj["desc"].toString();

    QString behaviour_str = obj["behaviour"].toString().toLower();
    Behaviour behaviour;

    if(behaviour_str == "openfile")
    {
        behaviour = OpenFile;
    }
    else if(behaviour_str == "savefile")
    {
        behaviour = SaveFile;
    }
    else if(behaviour_str == "directory")
    {
        behaviour = Directory;
    }
    else
    {
        qWarning() << "Undefined behaviour for SettingPath " << title << " - using default: Directory";
        behaviour = Directory;
    }

    QString filter = obj["filter"].toString();

    return new SettingPath(settings, title, section, key, default_value, desc, behaviour, filter, parent);
}


void SettingPath::restoreDefault()
{
    _line_edit->setText(_default_value);
}


void SettingPath::loadSetting()
{
    _settings->beginGroup(_section);
    QString value = _settings->value(_key, _default_value).toString();
    _line_edit->setText(value);
    _settings->endGroup();
}


void SettingPath::saveSetting()
{
    _settings->beginGroup(_section);
    _settings->setValue(_key, _line_edit->text());
    _settings->endGroup();
}


void SettingPath::showFileDialog()
{
    QString filename;
    switch(_behaviour)
    {
        case OpenFile:
            filename = QFileDialog::getOpenFileName(this, "Select File", _line_edit->text(), _filter);
            break;
        case SaveFile:
            filename = QFileDialog::getSaveFileName(this, "Select File", _line_edit->text(), _filter);
            break;
        case Directory:
            filename = QFileDialog::getExistingDirectory(this, "Select File", _line_edit->text());
    }
    if (!filename.isEmpty())
    {
        _line_edit->setText(filename);
    }
}


/////////////////////////////
// SettingInt
/////////////////////////////

SettingInt::SettingInt(QSettings* settings, QString title, QString section, QString key, int default_value,
                       QString desc, int minimum, int maximum, QWidget* parent)
    : SettingItem(settings, section, key, desc, parent), _default_value(default_value)
{
    auto layout = new QHBoxLayout(this);
    QLabel* label = new QLabel(title, this);
    _spinbox = new QSpinBox(this);
    _spinbox->setRange(minimum, maximum);
    layout->addWidget(label);
    layout->addWidget(_spinbox);
    setLayout(layout);

    // load the settings
    loadSetting();
}


SettingItem* SettingInt::fromJsonObject(QJsonObject obj, QSettings* settings, QWidget* parent)
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
    int default_value = obj["default"].toInt();
    QString desc = obj["desc"].toString();
    int minimum = 0;
    int maximum = 99;
    if(obj.contains("minimum"))
    {
        minimum = obj["minimum"].toInt();
    }
    if(obj.contains("maximum"))
    {
        maximum = obj["maximum"].toInt();
    }

    return new SettingInt(settings, title, section, key, default_value, desc, minimum, maximum, parent);
}


void SettingInt::restoreDefault()
{
    _spinbox->setValue(_default_value);
}


void SettingInt::loadSetting()
{
    _settings->beginGroup(_section);
    int value = _settings->value(_key, _default_value).toInt();
    _spinbox->setValue(value);
    _settings->endGroup();
}


void SettingInt::saveSetting()
{
    _settings->beginGroup(_section);
    _settings->setValue(_key, _spinbox->value());
    _settings->endGroup();
}


/////////////////////////////
// SettingItemCreation
/////////////////////////////

namespace SettingItemCreation
{
    namespace
    {
        SettingsTypeMap _typemap = {{"bool", SettingBool::fromJsonObject},
                                    {"string", SettingString::fromJsonObject},
                                    {"path", SettingPath::fromJsonObject},
                                    {"int", SettingInt::fromJsonObject}};
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
