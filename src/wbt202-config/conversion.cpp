#include "conversion.h"

#include <wbt202/wbt202.h>
#include <wbt202/wbt202_utils.h>

#include <cassert>

Status encode(
	std::string gpsFile,
	std::string logFile,
	std::string sysFile,
	std::string iniFile )
{
	// Initialize the standard values for the device configuration
	Wbt202 wbt202;
	loadIni( wbt202, iniFile );

	unsigned char* gps = toBinary( &(wbt202.gps) );
	unsigned char* log = toBinary( &(wbt202.log) );
	unsigned char* sys = toBinary( &(wbt202.sys) );
	assert( gps && log && sys );

	struct FilenameData
	{
		const char * filename;
		const unsigned char * data;
		size_t size;
	};

	FilenameData d[] =
	{
		{ gpsFile.c_str(), gps, SIZE_GPS_BIN },
		{ logFile.c_str(), log, SIZE_LOG_BIN },
		{ sysFile.c_str(), sys, SIZE_SYS_BIN }
	};
	int count = static_cast<int>( sizeof( d ) / sizeof( FilenameData ) );

	for ( int i = 0; i < count; ++i )
	{
		std::vector<unsigned char> data( d[ i ].data, d[ i ].data + d[ i ].size );

		writeFile( d[ i ].filename, data );
	}

	return STATUS_NO_ERROR;
}

Status decode(
	std::string iniFile,
	std::string gpsFile,
	std::string logFile,
	std::string sysFile )
{
	// Load the binary files into memory.
	GpsBin * gps = toGpsBin( readFile( gpsFile.c_str() ) );
	LogBin * log = toLogBin( readFile( logFile.c_str() ) );
	SysBin * sys = toSysBin( readFile( sysFile.c_str() ) );

	if ( ! ( gps && log && sys ) )
		return STATUS_BINARIES_MISSING;

	// Store configuration as a text file.
	Wbt202 wbt202;

	wbt202.gps = *gps;
	wbt202.log = *log;
	wbt202.sys = *sys;

	saveIni( iniFile, wbt202 );

	return STATUS_NO_ERROR;
}

