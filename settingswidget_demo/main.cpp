/**
 * SettingsWidget-qt5 demo
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

#include <QApplication>
#include <QSettings>
#include "settingswidget.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto settings = new QSettings(QSettings::IniFormat, QSettings::UserScope,
                                  "settingswidget_demo", "settingswidget_demo");

    SettingsWidget wid(settings, 0, QTabWidget::West);
    SettingsPanel* panel = new SettingsPanel(settings, &wid);
    panel->addTitle("Title");
    // from json
    QJsonObject json;
    json["type"] = "bool";
    json["title"] = "jsontest";
    json["section"] = "sec1";
    json["key"] = "key_json";
    json["default"] = true;
    auto myBool = SettingItemCreation::createItemfromJson(json, settings, panel);
    if (myBool)
    {
        panel->addSettingItem(myBool);
    }
    // from code
    SettingBool* set_bool = new SettingBool(settings, "testbool", "sec1", "key1", false, "TEST", panel);
    panel->addSettingItem(set_bool);
    panel->addTitle("Title2");
    SettingBool* set_bool2 = new SettingBool(settings, "testbool2", "sec1", "key2", false, "", panel);
    panel->addSettingItem(set_bool2);
    SettingBool* set_bool3 = new SettingBool(settings, "testbool3", "sec1", "key3", false, "", panel);
    panel->addSettingItem(set_bool3);
    wid.addPanel("Testpanel", panel, QIcon::fromTheme("document-new"));
    wid.show();

    return a.exec();
}
