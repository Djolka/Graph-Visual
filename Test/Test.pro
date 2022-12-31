QT += core gui
QT += widgets

TEMPLATE = app

CONFIG += c++17

#isEmpty(CATCH_INCLUDE_DIR): CATCH_INCLUDE_DIR=$$(CATCH_INCLUDE_DIR)
#!isEmpty(CATCH_INCLUDE_DIR): INCLUDEPATH *= $${CATCH_INCLUDE_DIR}

#isEmpty(CATCH_INCLUDE_DIR): {
#    message("CATCH_INCLUDE_DIR is not set, assuming Catch2 can be found automatically in your system")
#}

PROJECT_DIR = $$PWD/../GraphVisual
INCLUDEPATH += $$PROJECT_DIR

SRC_DIR = $$PWD/../GraphVisual/Sources
HDR_DIR = $$PWD/../GraphVisual/Headers

FORMS += \
    ../GraphVisual/Forms/graphwindow.ui \
    ../GraphVisual/Forms/popup.ui


SOURCES +=     main.cpp     \
    tests/testClassEdge.cpp \
    tests/testClassNode.cpp \
    tests/testGraph.cpp \
    ../GraphVisual/Source/graph.cpp \
    ../GraphVisual/Source/edge.cpp \
    ../GraphVisual/Source/node.cpp \
    ../GraphVisual/Source/algorithm.cpp \
    ../GraphVisual/Source/graphicnode.cpp \
    tests/testAlgorithm.cpp \
    ../GraphVisual/Source/graphicedge.cpp \
    ../GraphVisual/Source/graphtable.cpp \
    ../GraphVisual/Source/graphwindow.cpp \
    ../GraphVisual/Source/popup.cpp \
    ../GraphVisual/Source/mytextedit.cpp \
    tests/testGraphicNode.cpp

HEADERS += \
    catch.hpp \
    ../GraphVisual/Headers/graph.h \
    ../GraphVisual/Headers/edge.h \
    ../GraphVisual/Headers/node.h \
    ../GraphVisual/Headers/algorithm.h \
    ../GraphVisual/Headers/graphicnode.h \
    ../GraphVisual/Headers/graphicedge.h \
    ../GraphVisual/Headers/graphtable.h \
    ../GraphVisual/Headers/graphwindow.h \
    ../GraphVisual/Headers/popup.h \
    ../GraphVisual/Headers/mytextedit.h



TARGET = Test


