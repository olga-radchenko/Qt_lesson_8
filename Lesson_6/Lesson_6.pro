QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    file_viewer.cpp \
    find_file_thread.cpp \
    main.cpp \
    mainwindow.cpp \
    mymainwindow.cpp \
    myqplaintextedit.cpp

HEADERS += \
    file_viewer.h \
    find_file_thread.h \
    mainwindow.h \
    mymainwindow.h \
    myqplaintextedit.h

FORMS += \
    file_viewer.ui \
    mainwindow.ui \
    mymainwindow.ui

TRANSLATIONS += \
    Lesson_6_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    dark_theme.qss \
    light_theme.qss
