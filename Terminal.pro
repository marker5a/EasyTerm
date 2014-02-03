TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .
QT += core gui
QT += widgets
RESOURCES = resources.qrc
QT += serialport
RC_FILE = icon.rc
TARGET = EasyTerm
CONFIG += Release

# Input
HEADERS += src/terminal.h src/macro_editor.h src/status_bar.h src/about_dialog.h# tx_rx_thread.h
FORMS += ui/terminal.ui ui/macro.ui ui/about.ui
SOURCES += src/main.cpp src/terminal.cpp src/macro_editor.cpp src/status_bar.cpp src/about_dialog.cpp# tx_rx_thread.cpp

# Keep main directory clean
Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui
Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui
