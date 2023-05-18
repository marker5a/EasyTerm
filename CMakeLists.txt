cmake_minimum_required(VERSION 2.8.11)

project(EasyTerm)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.2.0/5.2.0/mingw48_32")

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5SerialPort)
find_package(Qt5OpenGL)
find_package(Qt5OpenGLExtensions)

qt5_wrap_ui(UI_HEADERS ui/terminal.ui ui/macro.ui ui/about.ui)
qt5_add_resources(UI_RESOURCES resources.qrc)

# Tell CMake to create the helloworld executable
add_executable(EasyTerm WIN32 src/main.cpp src/terminal.cpp src/macro_editor.cpp src/status_bar.cpp src/about_dialog.cpp icon.rc ${UI_HEADERS} ${UI_RESOURCES})
set(CMAKE_BUILD_TYPE "RELEASE")

# Use the Widgets module from Qt 5.
target_link_libraries(EasyTerm Qt5::Widgets Qt5::SerialPort ${QT_QTMAIN_LIBRARY} ${QT_LIBRARIES})

