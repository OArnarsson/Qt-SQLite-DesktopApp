TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/ComputerScientist.cpp \
    src/FileDataBase.cpp \
    src/magicaldataclass.cpp

HEADERS += \
    include/ComputerScientist.h \
    include/FileData.h \
    include/magicaldataclass.h \
    include/ui.h

DISTFILES += \
    LOL.txt

