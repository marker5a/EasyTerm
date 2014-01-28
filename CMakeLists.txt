cmake_minimum_required(VERSION 2.8.11)

project(EasyTerm)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5SerialPort)

qt5_wrap_ui(UI_HEADERS ui/terminal.ui ui/macro.ui ui/about.ui)
qt5_add_resources(UI_RESOURCES resources.qrc)

# Tell CMake to create the helloworld executable
add_executable(EasyTerm main.cpp terminal.cpp macro_editor.cpp status_bar.cpp about_dialog.cpp icon.rc ${UI_HEADERS} ${UI_RESOURCES})

# Use the Widgets module from Qt 5.
target_link_libraries(EasyTerm Qt5::Widgets Qt5::SerialPort)

