#include "conversion.h"

#include <wbt202/config-file.h>
#include <wbt202/utils.h>
#include <wbt202/wbt202.h>

#include <cassert>

using namespace wbt202;

int encode(
	std::string gpsFile,
	std::string logFile,
	std::string sysFile,
	std::string iniFile )
{
	// Initialize the standard values for the device configuration
	Wbt202 wbt202;

	// Load the settings from the ini-file and overwrite the standard settings.
	loadConfigFile( wbt202, iniFile );

	// Convert the settings to binary format.
	unsigned char* gps = wbt202::toBinary( &(wbt202.gps) );
	unsigned char* log = wbt202::toBinary( &(wbt202.log) );
	unsigned char* sys = wbt202::toBinary( &(wbt202.sys) );
	assert( gps && log && sys );

	// Write binary data to corresponding files.
	struct FilenameData
	{
		const char * filename;
		std::vector<unsigned char> data;
	};

	FilenameData d[] =
	{
		{ gpsFile.c_str(), std::vector<unsigned char>( gps, gps + SIZE_GPS_BIN ) },
		{ logFile.c_str(), std::vector<unsigned char>( log, log + SIZE_LOG_BIN ) },
		{ sysFile.c_str(), std::vector<unsigned char>( sys, sys + SIZE_SYS_BIN ) }
	};
	int count = static_cast<int>( sizeof( d ) / sizeof( FilenameData ) );

	for ( int i = 0; i < count; ++i )
		wbt202::writeFile( d[ i ].filename, d[ i ].data );

	return STATUS_NO_ERROR;
}

int decode(
	std::string iniFile,
	std::string gpsFile,
	std::string logFile,
	std::string sysFile )
{
	// Load the binary files into memory.
	GpsBin * gps = wbt202::toGpsBin( wbt202::readFile( gpsFile.c_str() ) );
	LogBin * log = wbt202::toLogBin( wbt202::readFile( logFile.c_str() ) );
	SysBin * sys = wbt202::toSysBin( wbt202::readFile( sysFile.c_str() ) );

	if ( ! ( gps && log && sys ) )
		return STATUS_BINARIES_MISSING;

	// Store configuration as a text file.
	Wbt202 wbt202;

	wbt202.gps = *gps;
	wbt202.log = *log;
	wbt202.sys = *sys;

	saveConfigFile( iniFile, wbt202 );

	return STATUS_NO_ERROR;
}
