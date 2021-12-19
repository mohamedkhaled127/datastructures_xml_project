QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Helper_Functions.cpp \
    Tree.cpp \
    XML_Data.cpp \
    compress.cpp \
    format.cpp \
    main.cpp \
    mainwindow.cpp \
    substring.cpp

HEADERS += \
    Headers.h \
    Helper_Functions.h \
    Tree.h \
    XML_Data.h \
    compress.h \
    format.h \
    mainwindow.h \
    substring.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
