QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += "$$PWD/Headers"

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Source/edge.cpp \
    Source/graph.cpp \
    Source/main.cpp \
    Source/graphwindow.cpp \
    Source/mytextedit.cpp \
    Source/node.cpp \
    Source/algorithm.cpp \
    Source/graphicnode.cpp \
    Source/graphtable.cpp \
    Source/graphicedge.cpp \
    Source/popup.cpp

HEADERS += \
    Headers/edge.h \
    Headers/graph.h \
    Headers/graphwindow.h \
    Headers/mytextedit.h \
    Headers/node.h \
    Headers/algorithm.h \
    Headers/graphicnode.h \
    Headers/graphtable.h \
    Headers/graphicedge.h \
    Headers/popup.h

FORMS += \
    Forms/graphwindow.ui \
    Forms/popup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES += \
    Resources/close.png \
    Resources/open.png \
    Resources/save.png \
    Resources/saveasjpg.png \
    Resources/saveaspng.png \
    Resources/toJson.png \
    Resources/fromJson.png
