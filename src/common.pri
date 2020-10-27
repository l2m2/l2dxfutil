# set QTBIN
TEMPNAME = $${QMAKE_QMAKE}
QTBIN = $$dirname(TEMPNAME)

# Copy command
win32 {
    COPY = copy /y
} else {
    COPY = cp
}

# never use foreach or Q_FOREACH
DEFINES += QT_NO_FOREACH

win32-msvc* {
    # support windows xp
    QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
    # generating pdb in release mode
    # QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINGO
    # QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_CXXFLAGS_RELEASE += /Zi
    QMAKE_LFLAGS_RELEASE += /DEBUG
}

# get platform
win32:DISTRIBUTION=windows
linux:DISTRIBUTION=linux
macx:DISTRIBUTION=macx

# dist
DIST_PATH=$$DIST_DIR/$${DISTRIBUTION}-qt$$[QT_VERSION]

# support c++11
CONFIG += c++11

# debug suffix
CONFIG += debug_and_release
CONFIG(debug, debug | release) {
    DESTDIR = $${DIST_PATH}/debug
    win32 {
        DEBUG_SUFFIX = d
    }
    macx {
        DEBUG_SUFFIX = _debug
    }
} else {
    DESTDIR = $${DIST_PATH}/release
    DEBUG_SUFFIX =
}

# libs
LIBS += -L$$DESTDIR
for (lib, LIB_LIST) {
    LIBS += -l$${lib}$${DEBUG_SUFFIX}
}
