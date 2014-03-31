#include "wbt202.h"
#include "wbt202_utils.h"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

std::string dataPath = "./WBT202/SYS/";

namespace {

void testGps( std::string path )
{
	std::string filename = path + "/GPS.BIN";
	std::cout << std::endl << "file: " << filename << std::endl;

	std::vector<char> buffer = readFile( filename.c_str() );
	if ( buffer.empty() )
		return;

	Wbt202Gps * gps = toWbt202Gps( buffer );
	assert( gps );

	if ( gps )
		std::cout << *gps << std::endl;
	else
		std::cout << "Cannot display the contents of " << filename << std::endl;

	delete gps;
}

void testLog( std::string path )
{
	std::string filename = path + "/LOG.BIN";
	std::cout << std::endl << "file: " << filename << std::endl;

	std::vector<char> buffer = readFile( filename.c_str() );
	if ( buffer.empty() )
		return;

	Wbt202Log * log = toWbt202Log( buffer );

	if ( log )
		std::cout << *log << std::endl;
	else
		std::cout << "Cannot display the contents of " << filename << std::endl;

	delete log;
}

void testSys( std::string path )
{
	std::string filename = path + "/SYS.BIN";
	std::cout << std::endl << "file: " << filename << std::endl;

	std::vector<char> buffer = readFile( filename.c_str() );
	if ( buffer.empty() )
		return;

	Wbt202Sys * sys = toWbt202Sys( buffer );

	if ( sys )
		std::cout << *sys << std::endl;
	else
		std::cout << "Cannot display the contents of " << filename << std::endl;

	delete sys;
}

} // namespace

int main( int argc, char ** argv )
{
	if ( argc == 2 )
		dataPath = argv[1];

	std::cout << "System uses " << ( IS_BIG_ENDIAN ? " B I G " : "little" );
	std::cout << " endian byte order." << std::endl;

	// Test-load each binary config file.
	testGps( dataPath );
	testLog( dataPath );
	testSys( dataPath );

	return 0;
}
