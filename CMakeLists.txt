project( wbt202-config )
cmake_minimum_required( VERSION 2.8 )

option( DEBUG "Build with debug information" OFF )

# Check support for C++11, and, if available, enable it.
include( CheckCXXCompilerFlag )
check_cxx_compiler_flag( "-std=c++11" COMPILER_SUPPORTS_CXX11 )
check_cxx_compiler_flag( "-std=c++0x" COMPILER_SUPPORTS_CXX0X )

set( INFO_SUPPORTS_CXX11 "No" )
if ( ${COMPILER_SUPPORTS_CXX11} )
	add_definitions( -DCOMPILER_SUPPORTS_CXX11 )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
	set( INFO_SUPPORTS_CXX11 "Yes" )
elseif ( ${COMPILER_SUPPORTS_CXX0X} )
	# Treat support of C++0x as C++11 support because that also suffices for
	# what we are currently using.
	add_definitions( -DCOMPILER_SUPPORTS_CXX11 )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )
	set( INFO_SUPPORTS_CXX11 "Yes (C++0x only)" )
endif( ${COMPILER_SUPPORTS_CXX11} )

# Check the endianness of the system and set defines accordingly.
# Taken from:
# http://barney.cs.uni-potsdam.de/pipermail/kdevelop/2011-February/016896.html
include( TestBigEndian )
test_big_endian( IS_BIG_ENDIAN )

add_definitions( -DIS_BIG_ENDIAN=${IS_BIG_ENDIAN} )
if ( IS_BIG_ENDIAN )
	set( INFO_ENDIANNESS "big-endian" )
else ()
	set( INFO_ENDIANNESS "little-endian" )
endif ()

# Debug build
if ( DEBUG )
	add_definitions( -DDEBUG )
	add_definitions( -g -O0 -Wall )
	set( INFO_IS_DEBUG "Yes" )
else ()
	set( INFO_IS_DEBUG "No" )
endif ()

# Include directories and sources.
set( PROJECT_INCLUDE_DIRS ${CMAKE_SOURCE_DIR} )
#include_directories( BEFORE SYSTEM ${CMAKE_SOURCE_DIR}/src )
include_directories( BEFORE SYSTEM ${CMAKE_SOURCE_DIR}/submodules/simpleini )
include_directories(               ${CMAKE_SOURCE_DIR}/src )

# Static library containing the main functionality.
file( GLOB WBT202_SRC_LIST "src/wbt202/*.h" "src/wbt202/*.cpp" )
add_library( wbt202 STATIC ${WBT202_SRC_LIST} )

# CLI-tool to convert the configuration from binary to text (and vice versa).
file( GLOB WBT202_CONFIG_SRCS
	"src/wbt202-config/*.h"
	"src/wbt202-config/*.cpp" )

add_executable( ${PROJECT_NAME} ${WBT202_CONFIG_SRCS} )
target_link_libraries( ${PROJECT_NAME} wbt202 )

# Tests
add_executable( test_memory_alignment src/tests/test_memory_alignment.cpp )
add_executable( test_endianness       src/tests/test_endianness.cpp )
add_executable( test_gps_checksums    src/tests/test_gps_checksums.cpp )

target_link_libraries( test_memory_alignment wbt202 )
target_link_libraries( test_endianness       wbt202 )
target_link_libraries( test_gps_checksums    wbt202 )

enable_testing()
add_test( NAME MEMORY_ALIGNMENT COMMAND test_memory_alignment                                            )
add_test( NAME ENDIANNESS       COMMAND test_endianness                                                  )
add_test( NAME GPS_CHECKSUMS    COMMAND test_gps_checksums "${CMAKE_SOURCE_DIR}/data/WBT202/SYS/GPS.BIN" )

# Print build configuration and info
message( "" )
message( "  Build configuration" )
message( "    Debug build:      " ${INFO_IS_DEBUG} )
message( "    C++11 support:    " ${INFO_SUPPORTS_CXX11} )
message( "" )
message( "  Platform information" )
message( "    Endianness:       " ${INFO_ENDIANNESS} )
message( "" )

