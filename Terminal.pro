######################################################################
# Automatically generated by qmake (2.01a) Sun Jan 5 13:38:58 2014
######################################################################

TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .
QT += core gui
QT += widgets
RESOURCES = resources.qrc
QT += serialport
RC_FILE = icon.rc

# Input
HEADERS += terminal.h macro_editor.h status_bar.h
FORMS += ui/terminal.ui ui/macro.ui
SOURCES += main.cpp terminal.cpp macro_editor.cpp status_bar.cpp
