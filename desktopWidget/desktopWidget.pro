#===============================================================================
#
# Qt Project: Resources Monitor for Desktop
#
#===============================================================================

include( common.pri )

# Sources and Headers ==========================================================

SOURCES += \
    main.cpp

HEADERS += \
    common.h

# Output dir ===================================================================

CONFIG(release, debug|release) {
    win32: DESTDIR = $${PWD}/../_distrib/win_$${QMAKE_HOST.arch}/bin
    else: unix:!android: DESTDIR  = $${PWD}/../_distrib/linux_$${QMAKE_HOST.arch}/bin
}

