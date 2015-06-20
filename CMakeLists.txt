cmake_minimum_required( VERSION 3.0 )
project( wbt202-config VERSION 0.1 )

list( APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )
include ( config )

add_subdirectory( src/libwbt202 )
add_subdirectory( src/tests     )

# Build targets
add_executable( ${PROJECT_NAME} src/main.cpp )
target_link_libraries( ${PROJECT_NAME} wbt202 )

# Print build configuration and info
message( "" )
message( "  Build configuration" )
message( "    Debug build:      " ${INFO_IS_DEBUG} )
message( "    C++11 support:    " ${INFO_SUPPORTS_CXX11} )
message( "" )
message( "  Platform information" )
message( "    Endianness:       " ${INFO_ENDIANNESS} )
message( "" )
