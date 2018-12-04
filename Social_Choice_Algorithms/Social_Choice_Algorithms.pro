TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    options.cpp \
    preferencematrix.cpp \
    agent.cpp \
    pairsofopts.cpp \
    pairwiserank.cpp \
    socialprefnode.cpp \
    aggregation_rules.cpp \
    helper_functions.cpp \
    sctheory.cpp \
    cycle.cpp \
    exceptionhandler.cpp

HEADERS += \
    options.h \
    preferencematrix.h \
    agent.h \
    pairsofopts.h \
    pairwiserank.h \
    socialprefnode.h \
    cycle.h \
    exceptionhandler.h
