cmake_minimum_required(VERSION 3.16)

project(GestorInventario VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

add_executable(GestorInventario
    main.cpp

    component.cpp
    component.h

    databasemanager.cpp
    databasemanager.h

    inventorymanager.cpp
    inventorymanager.h

    reportgenerator.cpp
    reportgenerator.h

    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(GestorInventario
    PRIVATE
        Qt6::Widgets
        Qt6::Sql
)
configure_file(${CMAKE_SOURCE_DIR}/db/inventario.sql ${CMAKE_BINARY_DIR}/db/inventario.sql COPYONLY)
