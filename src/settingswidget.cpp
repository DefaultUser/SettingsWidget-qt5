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

#include <iostream>
#include "settingswidget.h"


SettingsWidget::SettingsWidget(QSettings* settings, QWidget* parent, QTabWidget::TabPosition position)
    : QWidget(parent), _settings(settings)
{
    // Layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    _buttons = new QDialogButtonBox(QDialogButtonBox::Ok |
                                    QDialogButtonBox::Cancel |
                                    QDialogButtonBox::RestoreDefaults, this);
    _panel_container = new QTabWidget();
    setTabbarPosition(position);
    layout->addWidget(_panel_container);
    layout->addWidget(_buttons);
    setLayout(layout);

    connect(_buttons, &QDialogButtonBox::clicked, this, &SettingsWidget::on_buttonClicked);
}


void SettingsWidget::setTabbarPosition(QTabWidget::TabPosition position)
{
    // TODO: maybe subclass QTabBar and reimplement paintEvent for horizontal text
    _panel_container->setTabPosition(position);
}


void SettingsWidget::addPanel(QString panelname, SettingsPanel* panel, QIcon icon)
{
    _panel_container->addTab(panel, icon, panelname);
}


void SettingsWidget::addJsonPanel(QString panelname, QString filename, QIcon icon)
{
    QFile json_file(filename);
    if(!json_file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Couldn't open json file " << filename << " - skipping panel creation";
        return;
    }

    QByteArray data = json_file.readAll();
    json_file.close();
    QJsonDocument json_doc = QJsonDocument::fromJson(data);

    if(!json_doc.isArray())
    {
        qWarning() << "Json file " << filename << " does not contain a json array - skipping panel creation.";
        return;
    }

    addJsonPanel(panelname, json_doc.array(), icon);
}


void SettingsWidget::addJsonPanel(QString panelname, QJsonArray json, QIcon icon)
{
    addPanel(panelname, SettingsPanel::fromJson(json, _settings), icon);
}


void SettingsWidget::restoreDefaults()
{
    SettingsPanel* panel = (SettingsPanel*)_panel_container->currentWidget();
    panel->restoreDefaults();
}


void SettingsWidget::on_buttonClicked(QAbstractButton* button)
{
    QDialogButtonBox::StandardButton standard_button = _buttons->standardButton(button);
    switch(standard_button)
    {
        case QDialogButtonBox::RestoreDefaults:
            restoreDefaults();
            break;
        default:
            break;
    }
}
