cmake_minimum_required(VERSION 3.5)
project(pixie)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

qt5_add_resources(RESOURCES_RCC resources.qrc)

add_executable(
    pixie
    main.cpp
    windows/MainWindow.cpp
    windows/CanvasWidget.cpp
    windows/ColorPaletteWidget.cpp
    windows/ToolPanelWidget.cpp
    windows/PreviewWindow.cpp
    windows/customButtons/CustomButton.cpp
    windows/customButtons/ColorButton.cpp
    utils/BrailleConverter.cpp
    managers/PaletteManager.cpp
    ${RESOURCES_RCC} 
)

target_link_libraries(pixie Qt5::Widgets)
