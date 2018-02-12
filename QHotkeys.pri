DEFINES += QHOTKEYS

HEADERS += \
    QHotkeys/src/qhotkey.h \
    QHotkeys/src/helper.h

msvc {
    SOURCES += QHotkeys/src/qhotkey_win.cpp
    LIBS += -luser32
} else:linux {
    SOURCES += QHotkeys/src/qhotkey_linux.cpp
} else:macx {
    SOURCES += QHotkeys/src/qhotkey_osx.cpp
} else {
    SOURCES += QHotkeys/src/qhotkey.cpp
}
