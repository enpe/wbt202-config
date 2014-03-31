TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# Change this to one if your hardware uses big endian byte order.
DEFINES += IS_BIG_ENDIAN=0

#QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    main.cpp \
    wbt202_utils.cpp

HEADERS += \
    wbt202.h \
    wbt202_gps.h \
    wbt202_gps_details.h \
    wbt202_log.h \
    wbt202_sys.h \
    wbt202_utils.h

OTHER_FILES += \
    CMakeLists.txt
