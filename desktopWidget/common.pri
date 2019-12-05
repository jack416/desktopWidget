#===============================================================================
#
# Common Projects Settings
#
#===============================================================================

QT      += widgets network
CONFIG  += c++14
DEFINES += QT_DEPRECATED_WARNINGS

# Includes =====================================================================

INCLUDEPATH += \
    include \

# Version and Build date =======================================================

win32: BUILD_DATE = '$(shell echo %DATE:~6,4%-%DATE:~3,2%-%DATE:~0,2%)'
else:  BUILD_DATE = '$(shell date +%Y-%m-%d)'
VERSION  = 1.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += APP_BUILD_DATE=\\\"$$BUILD_DATE\\\"

# Sources and Headers ==========================================================


SOURCES += \
    src/app_core.cpp \
    src/gui_utils.cpp \
    src/convert.cpp \
    src/file_sys.cpp \
    src/system_utils.cpp \
    src/hardware_utils.cpp \
    src/log.cpp \
    src/graph.cpp \
    src/network_client.cpp \
    src/geo.cpp

HEADERS += \
    include/app_core.h \
    include/gui_utils.h \
    include/convert.h \
    include/file_sys.h \
    include/system_utils.h \
    include/hardware_utils.h \
    include/log.h \
    include/graph.h \
    include/network_client.h \
    include/geo.h

# Resources ====================================================================

RESOURCES += \
    main.qrc

win32:RC_FILE = main.rc

win32:LIBS += -lKernel32 -lPsapi
