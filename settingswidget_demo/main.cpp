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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto settings = new QSettings(QSettings::IniFormat, QSettings::UserScope,
                                  "settingswidget_demo", "settingswidget_demo");

    SettingsWidget wid(settings, 0, QTabWidget::West);
    SettingsPanel* panel = new SettingsPanel(&wid);
    SettingTitle* title = new SettingTitle("Title", "", panel);
    panel->addSettingItem(title);
    SettingBool* set_bool = new SettingBool("testbool", "sec1", "key1", false, "", panel);
    panel->addSettingItem(set_bool);
    SettingTitle* title2 = new SettingTitle("Title2", "", panel);
    panel->addSettingItem(title2);
    SettingBool* set_bool2 = new SettingBool("testbool2", "sec1", "key2", false, "", panel);
    panel->addSettingItem(set_bool2);
    SettingTitle* title3 = new SettingTitle("Title3", "", panel);
    panel->addSettingItem(title3);
    SettingBool* set_bool3 = new SettingBool("testbool3", "sec1", "key3", false, "", panel);
    panel->addSettingItem(set_bool3);
    wid.addPanel("Testpanel", panel);
    wid.show();

    return a.exec();
}
