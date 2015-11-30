TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/ComputerScientist.cpp \
    src/FileDataBase.cpp

HEADERS += \
    include/ComputerScientist.h \
    include/FileData.h

DISTFILES += \
    LOL.txt

