QT += core gui
unix {
    QT += gui-private
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PostShot
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS


DEPENDPATH += src/ \
         QHotkeys/src/
INCLUDEPATH += src/ \
         QHotkeys/src/

# QHotkeys stuff
!include(QHotkeys/QHotkeys.pri) {
    error("Could not find QHotkeys project!")
}

SOURCES += \
    src/main.cpp \
    src/Modules/Screenshot.cpp \
    src/Modules/ImageManipulation.cpp \
    src/GUI/TrayIcon.cpp \
    src/GUI/SettingsWindow.cpp \
    src/GUI/HelpWindow.cpp \
    src/GUI/CaptureImage.cpp

HEADERS += \
    src/globals.h \
    src/Modules/WindowHelper.h \
    src/Modules/Screenshot.h \
    src/Modules/Screenmanager.h \
    src/Modules/ImageManipulation.h \
    src/GUI/TrayIcon.h \
    src/GUI/SettingsWindow.h \
    src/GUI/HelpWindow.h \
    src/GUI/CaptureImage.h \
    src/GUI/Animation.h

RESOURCES += \
    src/resources.qrc

FORMS += \
    src/GUI/HelpWindow.ui \
    src/GUI/SettingsWindow.ui
