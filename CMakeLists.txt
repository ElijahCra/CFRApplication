cmake_minimum_required(VERSION 3.27)
project(CFRApp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(CFRApp main.cpp
        mainwindow.cpp
        customsquare.cpp)
target_link_libraries(CFRApp
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

