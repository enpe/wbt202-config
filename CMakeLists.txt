project(wbt202-config)
cmake_minimum_required(VERSION 2.8)

# Check support for C++11, and, if available, enable it.
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)

IF (${COMPILER_SUPPORTS_CXX11})
ADD_DEFINITIONS(-DCOMPILER_SUPPORTS_CXX11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ENDIF(${COMPILER_SUPPORTS_CXX11})

# Check the endianness of the system and set define accordingly.
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

