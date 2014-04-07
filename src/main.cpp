#include <wbt202/wbt202.h>
#include <wbt202/wbt202_utils.h>

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

std::string dataPath = "./WBT202/SYS/";

namespace {

bool loadWbt202( Wbt202 & wbt202, std::string path )
{
	std::string gpsFilename = path + "/GPS.BIN";
	std::string logFilename = path + "/LOG.BIN";
	std::string sysFilename = path + "/SYS.BIN";

	GpsBin * gps = toGpsBin( readFile( gpsFilename.c_str() ) );
	LogBin * log = toLogBin( readFile( logFilename.c_str() ) );
	SysBin * sys = toSysBin( readFile( sysFilename.c_str() ) );

	if ( gps && log && sys )
	{
		wbt202.gps = *gps;
		wbt202.log = *log;
		wbt202.sys = *sys;

		return true;
	}

	return false;
}

void testIniWrite( const Wbt202 & wbt202 )
{
	Wbt202 other = wbt202;

	Wbt202Status status;

	status = setDeviceName( other, "NSA-bug" );
	assert( status == WBT202_SUCCESS );

	status = setDeviceInfo( other, "Ach, wie gut ..." );
	assert( status == WBT202_SUCCESS );

	status = setRestartMode( other, COLD_START );
	assert( status == WBT202_SUCCESS );

	status = setShakeMode( other, ON );
	assert( status == WBT202_SUCCESS );

	status = setShakeModeTimeout( other, 151 );
	assert( status == WBT202_SUCCESS );

	status = setPowerOffTimout( other, 123 );
	assert( status == WBT202_SUCCESS );

	status = setSystemOfUnits( other, IMPERIAL );
	assert( status == WBT202_SUCCESS );

	status = setTimeZone( other, -150 );
	assert( status == WBT202_SUCCESS );

	saveIni( "other.ini", other );
	saveIni( "wbt202.ini", wbt202 );
}

void testIniRead( std::string filename )
{

}

} // namespace

int main( int argc, char ** argv )
{
	if ( argc == 2 )
		dataPath = argv[1];

	Wbt202 wbt202;
	bool success = loadWbt202( wbt202, dataPath );
	assert( success );

	if ( success )
	{
		std::cout << wbt202.gps << std::endl;
		std::cout << wbt202.log << std::endl;
		std::cout << wbt202.sys << std::endl;

		saveIni( "wbt202.ini", wbt202 );

		testIniWrite( wbt202 );
	}
	else
	{
		std::cout << "Could not load files from " << dataPath << std::endl;
	}

	return 0;
}
