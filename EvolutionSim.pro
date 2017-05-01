QT       += core gui widgets

TARGET = EvolutionSim
TEMPLATE = app

SOURCES += src/main.cpp \
    src/bug.cpp \
    src/Random.cpp \
    src/pool.cpp \
    src/ecosystem.cpp \
    src/EcosystemWidget.cpp \
    src/mainwindow.cpp
HEADERS += \
    src/bug.h \
    src/Random.h \
    src/pool.h \
    src/ecosystem.h \
    src/bacterium.h \
    src/EcosystemWidget.h \
    src/mainwindow.h
FORMS   += \
    src/mainwindow.ui

RESOURCES +=
