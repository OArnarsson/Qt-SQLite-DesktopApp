TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QT += sql

SOURCES += main.cpp \
    src/ComputerScientist.cpp \
    src/FileDataBase.cpp \
    src/magicaldataclass.cpp \
    src/dbtest.cpp

HEADERS += \
    include/ComputerScientist.h \
    include/FileData.h \
    include/magicaldataclass.h \
    include/ui.h \
    include/dbtest.h \

DISTFILES += \
    LOL.txt \
    sqlite3.dll \
    Lib/sqlite3.dll \
    Lib/sqlite3.def

