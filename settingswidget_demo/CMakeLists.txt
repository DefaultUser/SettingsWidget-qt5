#
# Copyright (C) 2016 Sebastian Schmidt
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
cmake_minimum_required(VERSION 2.6)
project(settingswidget_demo CXX)

# Qt
find_package(Qt5Widgets REQUIRED)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTORCC OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${Qt5Designer_INCLUDE_DIRS} ../include)

find_package(Qt5Core)
get_target_property(QtCore_location Qt5::Core LOCATION)

set(SOURCES main.cpp)

add_executable(settingswidget_demo ${SOURCES})
target_link_libraries(settingswidget_demo Qt5::Widgets)
target_link_libraries(settingswidget_demo ${SETTINGSWIDGET_LIBRARY})
