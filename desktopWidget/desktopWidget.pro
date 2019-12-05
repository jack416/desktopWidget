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
    customscene.cpp \
    main.cpp \
    monitorobject.cpp \
    settings.cpp

HEADERS += \
    canvas.h \
    common.h \
    customscene.h \
    monitorobject.h \
    settings.h

# Output dir ===================================================================

CONFIG(release, debug|release) {
    win32: DESTDIR = $${PWD}/../_distrib/win_$${QMAKE_HOST.arch}/bin
    else: unix:!android: DESTDIR  = $${PWD}/../_distrib/linux_$${QMAKE_HOST.arch}/bin
}

