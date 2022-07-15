include(../common_app.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    customlabel.cpp \
    draglabel.cpp \
    droplabel.cpp \
    main.cpp \
    resultdialog.cpp \
    widget.cpp \
    wordwidget.cpp

HEADERS += \
    customlabel.h \
    draglabel.h \
    droplabel.h \
    resultdialog.h \
    resultinfo.h \
    widget.h \
    wordinfo.h \
    wordwidget.h

RESOURCES += \
    res.qrc
