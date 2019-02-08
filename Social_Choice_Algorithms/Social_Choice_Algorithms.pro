TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    agent.cpp \
    aggregation_rules.cpp \
    exceptionhandler.cpp \
    helper_functions.cpp \
    options.cpp \
    socialprefnode.cpp \
    pairsofopts.cpp \
    pairwiserank.cpp \
    preferencematrix.cpp \
    sctheory.cpp \
    sct_algos.cpp \
    sctgraph.cpp \
    sctrank.cpp \
    population.cpp \
    profile.cpp

HEADERS += \
    exceptionhandler.hpp \
    socialprefnode.hpp \
    options.hpp \
    pairsofopts.hpp \
    pairwiserank.hpp \
    preferencematrix.hpp \
    sct_algos.hpp \
    agent.hpp \
    options.hpp \
    pairsofopts.hpp \
    pairwiserank.hpp \
    preferencematrix.hpp \
    sctgraph.hpp \
    socialprefnode.hpp \
    sctrank.hpp \
    helper_functions.hpp \
    aggregation_rules.hpp \
    sctheory.hpp \
    population.hpp \
    profile.hpp
