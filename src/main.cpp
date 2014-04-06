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
	}
	else
	{
		std::cout << "Could not load files from " << dataPath << std::endl;
	}

	return 0;
}
