cmake_minimum_required(VERSION 3.5)

project(generator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/usr/local/opt/qt")

if (WIN32)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network Multimedia REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network Multimedia REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/MainWindow/mainwindow.cpp
        src/MainWindow/mainwindow.h
        src/MainWindow/mainwindow.ui
        src/ApiClient/apiclient.cpp
        src/ApiClient/apiclient.h
        src/Media/media.cpp
        src/Media/media.h
        src/Data/data.h
        src/Data/data.cpp
        src/Calendar/calendar.h
        src/Calendar/calendar.cpp
        src/Logger/logger.h
        src/Logger/logger.cpp
        img.qrc
        )


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(generator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET generator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

else()
    add_executable(generator
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(generator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Multimedia)

set_target_properties(generator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER gena
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(generator)
endif()

install(TARGETS generator DESTINATION ${INSTALL_PREFIX})
