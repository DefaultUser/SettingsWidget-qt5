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

#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QtWidgets>
#include <QSettings>
#include "settingspanel.h"

/**
 * @brief A widget to display and edit settings using several SettingsPanels.
 *
 */
class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    SettingsWidget(QSettings* settings, QWidget* parent = 0, QTabWidget::TabPosition position = QTabWidget::North);
    void setTabbarPosition(QTabWidget::TabPosition position);
    /**
     * @brief Add a SettingsPanel to the QTabWidget
     *
     * @param panelname The name for the panel
     * @param panel The actual SettingsPanel
     * @param icon optional icon that is displayed in the QTabBar
     * @return void
     */
    void addPanel(QString panelname, SettingsPanel* panel, QIcon icon = QIcon());
    /**
     * @brief Generate a SettingsPanel from a .json file and add it to this SettingsWidget
     *
     * @param panelname The name for the panel
     * @param filename The filename of the .json file
     * @param icon optional icon that is displayed in the QTabBar
     * @return void
     */
    void addJsonPanel(QString panelname, QString filename, QIcon icon = QIcon());

private:
    QSettings* _settings;

    QTabWidget* _panel_container;
};

#endif // SETTINGSWIDGET_H
