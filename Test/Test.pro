QT = gui

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
    $$PROJECT_DIR/graphwindow.ui \
    $$PROJECT_DIR/popup.ui


SOURCES +=     main.cpp     \
    tests/testGraph.cpp \
    ../GraphVisual/Source/graph.cpp \
    ../GraphVisual/Source/edge.cpp \
    ../GraphVisual/Source/node.cpp \
    ../GraphVisual/Source/algorithm.cpp \
    tests/testAlgorithm.cpp
#    ../GraphVisual/Source/graphicedge.cpp \
#    ../GraphVisual/Source/graphicnode.cpp \
#    ../GraphVisual/Source/graphtable.cpp \
#    ../GraphVisual/Source/graphwindow.cpp

HEADERS += \
    catch.hpp \
    ../GraphVisual/Headers/graph.h \
    ../GraphVisual/Headers/edge.h \
    ../GraphVisual/Headers/node.h \
    ../GraphVisual/Headers/algorithm.h \
#    ../GraphVisual/Headers/graphicedge.h \
#    ../GraphVisual/Headers/graphicnode.h \
#    ../GraphVisual/Headers/graphtable.h \
#    ../GraphVisual/Headers/graphwindow.h


TARGET = Test


