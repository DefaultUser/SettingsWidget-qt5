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
set(SETTINGSWIDGET_LIBRARY SettingsWidget-qt5)
set(PROJECT_VERSION "")
project(${SETTINGSWIDGET_LIBRARY} CXX)

# Qt
find_package(Qt5Widgets REQUIRED)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTORCC OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pedantic -Werror")

# C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# For some reason the above flags don't really work...
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR CMAKE_COMPILER_IS_GNUCXX)
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag(--std=c++${CMAKE_CXX_STANDARD} STD_CXX)
    if(STD_CXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++${CMAKE_CXX_STANDARD}")
    else()
        message(SEND_ERROR "Requires C++${CMAKE_CXX_STANDARD} or better")
    endif()
else()
    message(WARNING "Unrecognized compiler: ${CMAKE_CXX_COMPILER_ID}, make sure it supports C++${CMAKE_CXX_STANDARD}")
endif()

# Sources
include_directories("${PROJECT_SOURCE_DIR}/include")

set(SOURCES
    src/settingswidget.cpp
    src/settingspanel.cpp
    src/settingitems.cpp
)

set(HEADERS
    include/settingswidget.h
    include/settingspanel.h
    include/settingitems.h
)

qt5_wrap_cpp(SOURCES ${HEADERS})
qt5_wrap_ui(SOURCES)

# Library
add_library(${SETTINGSWIDGET_LIBRARY} ${SOURCES})
target_link_libraries(${SETTINGSWIDGET_LIBRARY} Qt5::Widgets)

find_package(Qt5Designer)
if(Qt5Designer_FOUND)
    add_subdirectory(settingswidget_designer_plugin)
endif()

add_subdirectory(settingswidget_demo)
