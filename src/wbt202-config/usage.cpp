#include "usage.h"

#include <iostream>

void usage( std::string argv0 )
{
	std::cout << "Usage: ";
	std::cout << argv0 << " [-h|-v] [[-e|-d] -c file -b directory]" << std::endl;
	std::cout << std::endl;
	std::cout << "  -e\tEncode ..." << std::endl;
	std::cout << "  -d\tDecode ..." << std::endl;
	std::cout << "  -h\tThis help/usage message." << std::endl;
	std::cout << "  -v\tDisplays the version and build revision." << std::endl;
	std::cout << std::endl;
	std::cout << "Examples: " << std::endl;
	std::cout << "  " << argv0 << " -e -c ./config.ini -b /mnt/wbt202/" << std::endl;
	std::cout << "  " << argv0 << " -d -c ./config.ini -b /mnt/wbt202/" << std::endl;
}
