project(wbt202-config)

cmake_minimum_required(VERSION 2.8)

# Check the endianness of the system; add compiler define if it is big endian.
# Taken from:
# http://barney.cs.uni-potsdam.de/pipermail/kdevelop/2011-February/016896.html
INCLUDE(TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)

ADD_DEFINITIONS(-DIS_BIG_ENDIAN=${IS_BIG_ENDIAN})

# Include directories and sources.
set(wbt202-config_INCLUDE_DIRS ${CMAKE_SOURCE_DIR} )
include_directories(${wbt202-config_INCLUDE_DIRS})

file(GLOB SRC_LIST "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${SRC_LIST})

