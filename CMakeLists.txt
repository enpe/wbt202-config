PROJECT( wbt202-config )
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

# Check support for C++11, and, if available, enable it.
INCLUDE( CheckCXXCompilerFlag )
CHECK_CXX_COMPILER_FLAG( "-std=c++11" COMPILER_SUPPORTS_CXX11 )

IF ( ${COMPILER_SUPPORTS_CXX11} )
ADD_DEFINITIONS( -DCOMPILER_SUPPORTS_CXX11 )
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
ENDIF( ${COMPILER_SUPPORTS_CXX11} )

# Check the endianness of the system and set define accordingly.
# Taken from:
# http://barney.cs.uni-potsdam.de/pipermail/kdevelop/2011-February/016896.html
INCLUDE( TestBigEndian )
TEST_BIG_ENDIAN( IS_BIG_ENDIAN )

ADD_DEFINITIONS( -DIS_BIG_ENDIAN=${IS_BIG_ENDIAN} )

# Include directories and sources.
SET( PROJECT_INCLUDE_DIRS ${CMAKE_SOURCE_DIR} )
INCLUDE_DIRECTORIES( ${PROJECT_INCLUDE_DIRS} )

# Build targets
FILE( GLOB WBT202_SRC_LIST "wbt202*.h" "wbt202*.cpp" )
ADD_EXECUTABLE( ${PROJECT_NAME} ${WBT202_SRC_LIST} main.cpp )

ADD_EXECUTABLE( test_gps_checksums tests/test_gps_checksums.cpp ${WBT202_SRC_LIST} )

# Tests
ENABLE_TESTING()

ADD_TEST( NAME GPS_CHECKSUMS COMMAND test_gps_checksums "${CMAKE_SOURCE_DIR}/data/WBT202/SYS/" )


