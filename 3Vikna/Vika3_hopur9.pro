#-------------------------------------------------
#
# Project created by QtCreator 2015-12-10T10:26:41
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Vika3_hopur9
TEMPLATE = app


SOURCES += main.cpp\
        gui.cpp \
    src/computer.cpp \
    src/ComputerScientist.cpp \
    src/FileDataBase.cpp \
    src/magicaldataclass.cpp \

HEADERS  += gui.h \
    include/computer.h \
    include/ComputerScientist.h \
    include/FileData.h \
    include/magic.h \
    include/magicaldataclass.h \
    include/ui.h \

FORMS    += gui.ui \
    addpopup.ui

DISTFILES += \
    include/ComputerScientist.h.gch \
    include/FileData.h.gch

RESOURCES = icons.qrc
