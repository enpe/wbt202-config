
file( GLOB LIBWBT202_SRC_LIST
	"include/wbt202/*.h"
	"src/*.h"
	"src/*.cpp"
)

add_library( wbt202 SHARED ${LIBWBT202_SRC_LIST} )

###
# Target properties

# Export header file:
#  * ${CMAKE_CURRENT_BINARY_DIR}/wbt202_export.h
include( GenerateExportHeader )
set( BINARY_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/include" )
set( EXPORT_HEADER_FILE "${BINARY_INCLUDE_DIR}/wbt202/wbt202_export.h" )
generate_export_header( wbt202
	EXPORT_FILE_NAME "${EXPORT_HEADER_FILE}"
)

# Include directories
target_include_directories( wbt202
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
	$<INSTALL_INTERFACE:include>

	PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/src
	${BINARY_INCLUDE_DIR}
)

###
# Installation

# Using this layout for the installation:
#   * <prefix>/lib/cmake/<PROJECT-NAME>
#   * <prefix>/lib/
#   * <prefix>/lib-static/
#   * <prefix>/include/
set( config_install_dir "lib/cmake/${PROJECT_NAME}" )
set( include_install_dir "include" )

# Location of temporary CMake files.
set( generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated" )

# Package configuration
set( version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake" )
set( project_config "${generated_dir}/${PROJECT_NAME}Config.cmake" )
set( targets_export_name "${PROJECT_NAME}Targets" )
#set( namespace "${PROJECT_NAME}::" )

# Load module which provides a macro the generation of simple
# 'ConfigVersion.cmake'
#
# Note: PROJECT_VERSION is used as a VERSION
#
# http://www.cmake.org/cmake/help/git-master/module/CMakePackageConfigHelpers.html#module:CMakePackageConfigHelpers
include( CMakePackageConfigHelpers )
write_basic_package_version_file(
	"${version_config}" COMPATIBILITY SameMajorVersion
)

# Configure the package config file '<PROJECT-NAME>Config.cmake'
# Note: variable 'targets_export_name' used
configure_file( "${CMAKE_SOURCE_DIR}/cmake/Config.cmake.in" "${project_config}" @ONLY )

# Targets:
#  * Move libraries to <prefix>/lib
#  * Move executables to <prefix>/bin
#  * Move include files to <prefix>/include
#  * Header files can included as: #include <foo/Bar.h>
install(
	TARGETS wbt202
	EXPORT "${targets_export_name}"
	LIBRARY  DESTINATION "lib" # dynamic libraries
	ARCHIVE  DESTINATION "lib-static" # static libraries
	RUNTIME  DESTINATION "bin"
	INCLUDES DESTINATION "${include_install_dir}"
)

# Header files:
#  * Copy <source>/include/* -> <prefix>/include/
install(
	DIRECTORY "include/"
	DESTINATION "${include_install_dir}"
	FILES_MATCHING PATTERN "*.h"
)

# Export headers:
#  * Copy ${CMAKE_CURRENT_BINARY_DIR}/{bar,baz}_export.h -> <prefix>/include
install(
	FILES "${EXPORT_HEADER_FILE}"
	DESTINATION "${include_install_dir}/wbt202"
)

# Package config-files:
#  * FooConfig.cmake
#  * FooConfigVersion.cmake
#  * FooTargets.cmake
install(
	FILES
		"${project_config}"
		"${version_config}"
	DESTINATION "${config_install_dir}"
)

install(
	EXPORT "${targets_export_name}"
#	NAMESPACE "${namespace}"
	DESTINATION "${config_install_dir}"
)
