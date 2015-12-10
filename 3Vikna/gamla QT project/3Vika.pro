QT += core
QT += sql
QT -= gui
TARGET = untitled
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    src/ComputerScientist.cpp \
    src/FileDataBase.cpp \
    src/magicaldataclass.cpp \
    src/computer.cpp

HEADERS += \
    include/ComputerScientist.h \
    include/FileData.h \
    include/magicaldataclass.h \
    include/ui.h \
    include/computer.h \
    include/magic.h

DISTFILES += \
    LOL.txt \
    Lib/sqlite3.dll \
    Lib/sqlite3.def \

