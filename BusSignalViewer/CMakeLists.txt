cmake_minimum_required(VERSION 3.20)

project(BusSignalViewer LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.h mainwindow.cpp
    buscanvas.h buscanvas.cpp
)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)