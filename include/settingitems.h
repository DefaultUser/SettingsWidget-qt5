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

#ifndef SETTINGITEMS_H
#define SETTINGITEMS_H

#include <QtWidgets>
#include <QJsonObject>


/**
 * @brief Abstract Item for SettingsPanel
 *
 */
class SettingItem : public QWidget
{
    Q_OBJECT

public:

    SettingItem(QSettings* settings, QString section, QString key, QString desc = "", QWidget* parent = 0);
    /**
     * @brief Parse the given Json object and populate the SettingItem with its information
     *
     * @param obj the json object
     * @param parent the SettingItem's parent
     * @return SettingItem*
     */
    static SettingItem* fromJsonObject(QJsonObject obj, QSettings* settings, QWidget* parent = 0);

    /**
     * @brief Restore the default value
     * 
     * @return void
     */
    virtual void restoreDefault() = 0;

protected:

    /**
     * @brief Load the setting
     *
     * @return void
     */
    virtual void loadSetting() = 0;

    /**
     * @brief Save the setting
     *
     * @return void
     */
    virtual void saveSetting() = 0;

    /**
     * @brief Pointer to the settings instance
     */
    QSettings* _settings;

    /**
     * @brief The section where the setting should be saved
     */
    QString _section;
    /**
     * @brief The key which is used to save the setting
     */
    QString _key;
};


/**
 * @brief A labeled checkbox
 *
 */
class SettingBool : public SettingItem
{
    Q_OBJECT

public:

    SettingBool(QSettings* settings, QString title, QString section, QString key, bool default_value, QString desc = "", QWidget* parent = 0);

    static SettingItem* fromJsonObject(QJsonObject obj, QSettings* settings, QWidget* parent = 0);

    /**
     * @brief Restore the default value
     *
     * @return void
     */
    void restoreDefault();

protected:

    /**
     * @brief Load the setting
     *
     * @return void
     */
    void loadSetting();

    /**
     * @brief Save the setting
     *
     * @return void
     */
    void saveSetting();

private:
    QCheckBox* _checkbox;

    bool _default_value;
};


typedef SettingItem* (*SettingItemFactory)(QJsonObject, QSettings*, QWidget*);
typedef QMap<QString, SettingItemFactory> SettingsTypeMap;


// SettingItem creation from json
namespace SettingItemCreation
{
    /**
     * @brief Register a new SettingItem for building Settings from Json. You don't need to register types
     * when you are building the SettingsPanel via code.
     *
     * @param identifier Corresponds to the "type" field in the json object
     * @param factory The function that creates the new SettingItem
     * @return void
     */
    void registerType(QString identifier, SettingItemFactory factory);
    /**
     * @brief Create a SettingItem from the supplied json object. Returns nullptr when the type was not registered
     *
     * @param json Json object with all information about the SettingItem
     * @param parent The SettingItem's parent
     * @return SettingItem*
     */
    SettingItem* createItemfromJson(QJsonObject json, QSettings* settings, QWidget* parent = 0);
}

#endif // SETTINGITEMS_H
