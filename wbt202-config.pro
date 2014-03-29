TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    wbt202_utils.cpp

HEADERS += \
    wbt202.h \
    wbt202_gps.h \
    wbt202_log.h \
    wbt202_sys.h \
    wbt202_utils.h

OTHER_FILES += \
    CMakeLists.txt
