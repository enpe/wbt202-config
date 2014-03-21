// Memory alignment
//http://stackoverflow.com/a/9852749
//http://solidsmoke.blogspot.com.br/2010/07/woes-of-structure-packing-pragma-pack.html
//#pragma pack(1)

#include "wbt202.h"
#include "wbt202_utils.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define OFFSET( p1, p2 ) reinterpret_cast<size_t>( p1 ) - reinterpret_cast<size_t>( p2 )

std::string filename = "WBT202/SYS/LOG.BIN";

int main( int argc, char ** argv )
{
	if ( argc == 2 )
		filename = argv[1];

	// Read the specified file.
	std::fstream file( filename.c_str(), std::ios::in | std::ios::binary );

	if ( ! file.is_open() )
	{
		std::cerr << "Cannot open <" << filename << ">!" << std::endl;
		return -1;
	}

	std::vector<char> buffer( BYTE_COUNT_LOG, 0 );
	file.read( buffer.data(), buffer.size() );

	// Deserialize the data and print it.
	Log * log = deserializeLog(
		reinterpret_cast<unsigned char*>( buffer.data() ) );

	std::cout << *log << std::endl;

	return 0;
}
