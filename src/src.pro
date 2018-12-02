QT += core gui

greaterThan( QT_MAJOR_VERSION, 4 ): QT += widgets

TARGET = src
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
    SCT_Algorithms/agent.cpp \
    SCT_Algorithms/aggregation_rules.cpp \
    SCT_Algorithms/cycle.cpp \
    SCT_Algorithms/exceptionhandler.cpp \
    SCT_Algorithms/helper_functions.cpp \
    SCT_Algorithms/main.cpp \
    SCT_Algorithms/nodeopt.cpp \
    SCT_Algorithms/options.cpp \
    SCT_Algorithms/pairsofopts.cpp \
    SCT_Algorithms/pairwiserank.cpp \
    SCT_Algorithms/preferencematrix.cpp \
    SCT_Algorithms/SCTheory.cpp \
    SCT_Algorithms/sctheory.cpp \
    SCT_Algorithms/socialprefnode.cpp \
    mainwindow.cpp \
    treewidget.cpp

FORMS += \
    mainwindow.ui

HEADERS += \
    Classes/agent.h \
    Classes/cycle.h \
    Classes/exceptionhandler.h \
    Classes/nodeopt.h \
    Classes/options.h \
    Classes/pairsofopts.h \
    Classes/pairwiserank.h \
    Classes/preferencematrix.h \
    Classes/program_logic.h \
    Classes/q_graphic_node.h \
    Classes/socialprefnode.h \
    mainwindow.h \
    treewidget.h \
    Classes/aggregation_rules.h \
    Classes/helper_functions.h \
    Classes/sctheory.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
