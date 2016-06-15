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

#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

#include <QWidget>
#include <QJsonArray>

#include "settingitems.h"


/**
 * @brief A panel displaying several settings
 *
 */
class SettingsPanel : public QScrollArea
{
    Q_OBJECT

public:

    SettingsPanel(QSettings* settings, QWidget* parent = 0);

    /**
     * @brief Generate a SettingsPanel from a json array
     *
     * @param json A json array with information on how to fill the panel
     * @param parent The panel's parent
     * @return SettingsPanel*
     */
    static SettingsPanel* fromJson(QJsonArray json, QSettings* settings, QWidget* parent = 0);

    /**
     * @brief Add a new SettingItem to the panel
     *
     * @param item the SettingItem to add
     * @return void
     */

    void addSettingItem(SettingItem* item);
    /**
     * @brief Add a title seperator to the panel
     *
     * @param title the text that should be displayed
     * @return void
     */

    void addTitle(QString title);

    /**
     * @brief Restore the default value for all SettingItems
     *
     * @return void
     */
    void restoreDefaults();

    /**
     * @brief Save the settings to disk
     *
     * @return void
     */
    void saveSettings();

private:

    /**
     * @brief List of all the SettingItems in this panel
     */
    std::list<SettingItem*> _items = {};

    /**
     * @brief The settings to use
     */
    QSettings* _settings;
};

#endif // SETTINGSPANEL_H
