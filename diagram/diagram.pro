QT += widgets
QT += network

PRECOMPILED_HEADER = stable.h

TEMPLATE      = app
HEADERS       = diagramwindow.h \
                link.h \
                node.h \
                propertiesdialog.h \
    stable.h
SOURCES       = diagramwindow.cpp \
                link.cpp \
                main.cpp \
                node.cpp \
                propertiesdialog.cpp
FORMS         = propertiesdialog.ui
RESOURCES     = resources.qrc
