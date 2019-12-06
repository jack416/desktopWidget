#===============================================================================
#
# Qt Project: Resources Monitor for Desktop
#
#===============================================================================

include( common.pri )

# Sources and Headers ==========================================================

SOURCES += \
    canvas.cpp \
    common.cpp \
    currentlocationobject.cpp \
    customscene.cpp \
    main.cpp \
    monitorobject.cpp \
    settings.cpp \
    utclineobject.cpp \
    worldmapobject.cpp

HEADERS += \
    canvas.h \
    common.h \
    currentlocationobject.h \
    customscene.h \
    monitorobject.h \
    settings.h \
    utclineobject.h \
    worldmapobject.h

# Output dir ===================================================================

CONFIG(release, debug|release) {
    win32: DESTDIR = $${PWD}/../_distrib/win_$${QMAKE_HOST.arch}/bin
    else: unix:!android: DESTDIR  = $${PWD}/../_distrib/linux_$${QMAKE_HOST.arch}/bin
}

