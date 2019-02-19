TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    agent.cpp \
    exceptionhandler.cpp \
    options.cpp \
    socialprefnode.cpp \
    pairsofopts.cpp \
    pairwiserank.cpp \
    preferencematrix.cpp \
    sctheory.cpp \
    sctgraph.cpp \
    sctrank.cpp \
    population.cpp \
    profile.cpp \
    procedure.cpp \
    plurality_rules.cpp \
    majoritarian_rules.cpp \
    proportional_rules.cpp

HEADERS += \
    exceptionhandler.hpp \
    socialprefnode.hpp \
    options.hpp \
    pairsofopts.hpp \
    pairwiserank.hpp \
    preferencematrix.hpp \
    agent.hpp \
    options.hpp \
    pairsofopts.hpp \
    pairwiserank.hpp \
    preferencematrix.hpp \
    sctgraph.hpp \
    socialprefnode.hpp \
    sctrank.hpp \
    sctheory.hpp \
    population.hpp \
    profile.hpp \
    procedure.hpp \
    plurality_rules.hpp \
    majoritarian_rules.hpp \
    proportional_rules.hpp
