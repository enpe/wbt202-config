PROJECT( wbt202-config )
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

# Check support for C++11, and, if available, enable it.
INCLUDE( CheckCXXCompilerFlag )
CHECK_CXX_COMPILER_FLAG( "-std=c++11" COMPILER_SUPPORTS_CXX11 )
CHECK_CXX_COMPILER_FLAG( "-std=c++0x" COMPILER_SUPPORTS_CXX0X )

IF ( ${COMPILER_SUPPORTS_CXX11} )
	ADD_DEFINITIONS( -DCOMPILER_SUPPORTS_CXX11 )
	SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
ELSEIF ( ${COMPILER_SUPPORTS_CXX0X} )
	# Treat support of C++0x as C++11 support because that also suffices for
	# what we are currently using.
	ADD_DEFINITIONS( -DCOMPILER_SUPPORTS_CXX11 )
	SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )
ENDIF( ${COMPILER_SUPPORTS_CXX11} )

# Check the endianness of the system and set define accordingly.
# Taken from:
# http://barney.cs.uni-potsdam.de/pipermail/kdevelop/2011-February/016896.html
INCLUDE( TestBigEndian )
TEST_BIG_ENDIAN( IS_BIG_ENDIAN )

ADD_DEFINITIONS( -DIS_BIG_ENDIAN=${IS_BIG_ENDIAN} )

# Debug build
IF ( DEBUG )
	ADD_DEFINITIONS( -DDEBUG )
	ADD_DEFINITIONS( -g -O0 -Wall )
ENDIF ()

# Include directories and sources.
SET( PROJECT_INCLUDE_DIRS ${CMAKE_SOURCE_DIR} )
INCLUDE_DIRECTORIES( BEFORE SYSTEM ${CMAKE_SOURCE_DIR}/src )
INCLUDE_DIRECTORIES(               ${CMAKE_SOURCE_DIR}/src )

# Build targets
FILE( GLOB WBT202_SRC_LIST "src/wbt202/*.h" "src/wbt202/*.cpp" )
ADD_EXECUTABLE( ${PROJECT_NAME} src/main.cpp ${WBT202_SRC_LIST} )

# Tests
ADD_EXECUTABLE( test_memory_alignment src/tests/test_memory_alignment.cpp ${WBT202_SRC_LIST} )
ADD_EXECUTABLE( test_endianness       src/tests/test_endianness.cpp       ${WBT202_SRC_LIST} )
ADD_EXECUTABLE( test_gps_checksums    src/tests/test_gps_checksums.cpp    ${WBT202_SRC_LIST} )

ENABLE_TESTING()
ADD_TEST( NAME MEMORY_ALIGNMENT COMMAND test_memory_alignment                                            )
ADD_TEST( NAME ENDIANNESS       COMMAND test_endianness                                                  )
ADD_TEST( NAME GPS_CHECKSUMS    COMMAND test_gps_checksums "${CMAKE_SOURCE_DIR}/data/WBT202/SYS/GPS.BIN" )


