QT += core gui
QT += widgets

TEMPLATE = app

INCLUDEPATH += "$$PWD/../GraphVisual/Headers"

CONFIG += c++17

PROJECT_DIR = $$PWD/../GraphVisual
INCLUDEPATH += $$PROJECT_DIR

SRC_DIR = $$PWD/../GraphVisual/Source
HDR_DIR = $$PWD/../GraphVisual/Headers

FORMS += \
    ../GraphVisual/Forms/graphwindow.ui \
    ../GraphVisual/Forms/popup.ui


SOURCES +=     main.cpp     \
    tests/testClassEdge.cpp \
    tests/testClassNode.cpp \
    tests/testGraph.cpp \
    tests/testGraphicEdge.cpp \
    tests/testGraphicNode.cpp \
    tests/testAlgorithm.cpp \
    $${SRC_DIR}/graph.cpp \
    $${SRC_DIR}/edge.cpp \
    $${SRC_DIR}/node.cpp \
    $${SRC_DIR}/algorithm.cpp \
    $${SRC_DIR}/graphicnode.cpp \
    $${SRC_DIR}/graphicedge.cpp \
    $${SRC_DIR}/graphtable.cpp \
    $${SRC_DIR}/graphwindow.cpp \
    $${SRC_DIR}/popup.cpp \
    $${SRC_DIR}/mytextedit.cpp


HEADERS += \
    catch.hpp \
    $${HDR_DIR}/graph.h \
    $${HDR_DIR}/edge.h \
    $${HDR_DIR}/node.h \
    $${HDR_DIR}/algorithm.h \
    $${HDR_DIR}/graphicnode.h \
    $${HDR_DIR}/graphicedge.h \
    $${HDR_DIR}/graphtable.h \
    $${HDR_DIR}/graphwindow.h \
    $${HDR_DIR}/popup.h \
    $${HDR_DIR}/mytextedit.h

TARGET = Test
