// Memory alignment
//http://stackoverflow.com/a/9852749
//http://solidsmoke.blogspot.com.br/2010/07/woes-of-structure-packing-pragma-pack.html
//#pragma pack(1)

#include "wbt202.h"
#include "wbt202_utils.h"

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define OFFSET( p1, p2 ) reinterpret_cast<size_t>( p1 ) - reinterpret_cast<size_t>( p2 )

std::string data_path = "./";

int main( int argc, char ** argv )
{
	if ( argc == 2 )
		data_path = argv[1];

	// LOG.BIN
	std::string log_file = data_path + "LOG.BIN";
	std::fstream file( log_file.c_str(), std::ios::in | std::ios::binary );

	if ( ! file.is_open() )
	{
		std::cerr << "Cannot open <" << log_file << ">!" << std::endl;
		return -1;
	}

	std::vector<char> buffer( BYTE_COUNT_LOG, 0 );
	file.read( buffer.data(), buffer.size() );
	file.close();

	Log * log = deserializeLog(
		reinterpret_cast<unsigned char*>( buffer.data() ) );

	std::cout << "file: " << log_file << std::endl;
	std::cout << *log << std::endl;

	delete log;

	// SYS.BIN
	std::string sys_file = data_path + "SYS.BIN";

	file.open( sys_file.c_str(), std::ios::in | std::ios::binary );
	assert( file.is_open() );

	buffer.resize( 150, 255 );
	file.read( buffer.data(), buffer.size() );
	file.close();

	Sys * sys = deserializeSys(
		reinterpret_cast<unsigned char*>( buffer.data() ) );

	std::cout << "file: " << sys_file << std::endl;
	std::cout << *sys << std::endl;

	delete sys;

	std::cout << "sizeof(Sys) = " << sizeof(Sys) << std::endl;


	return 0;
}
