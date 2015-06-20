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

# Check the endianness of the system and set define accordingly.
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

# Debug builds: append -d to all targets.
set( CMAKE_DEBUG_POSTFIX "d" )

enable_testing()
