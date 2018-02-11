#-------------------------------------------------
#
# Project created by QtCreator 2018-01-17T14:09:43
#
#-------------------------------------------------

QT       += core gui
unix {
    QT += gui-private
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PostShot
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += UGLOBALHOTKEY_LIBRARY

include(UGlobalHotkeys/uglobalhotkey-headers.pri)
include(UGlobalHotkeys/uglobalhotkey-sources.pri)
include(UGlobalHotkeys/uglobalhotkey-libs.pri)


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    Modules/Screenshot.cpp \
    Modules/ImageManipulation.cpp \
    GUI/TrayIcon.cpp \
    GUI/SettingsWindow.cpp \
    GUI/HelpWindow.cpp \
    GUI/CaptureImage.cpp

HEADERS += \
    globals.h \
    Modules/WindowHelper.h \
    Modules/Screenshot.h \
    Modules/Screenmanager.h \
    Modules/ImageManipulation.h \
    GUI/TrayIcon.h \
    GUI/SettingsWindow.h \
    GUI/HelpWindow.h \
    GUI/CaptureImage.h \
    GUI/Animation.h

RESOURCES += \
    resources.qrc

FORMS += \
    GUI/HelpWindow.ui \
    GUI/SettingsWindow.ui

DISTFILES += \
    UGlobalHotkeys/uglobalhotkey.pri \
    UGlobalHotkeys/uglobalhotkey-headers.pri \
    UGlobalHotkeys/uglobalhotkey-libs.pri \
    UGlobalHotkeys/uglobalhotkey-sources.pri \
    Modules/screenshot.cpp.old.go \
    Modules/screenshot.h.old.go
