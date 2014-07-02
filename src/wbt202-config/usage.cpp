#include "usage.h"

#include <iostream>

void displayUsage( std::string argv0 )
{
	std::cout << "Usage: ";
	std::cout << argv0 << " [-h|-v] [[-e|-d] -c file -b directory]\n";
	std::cout << std::endl;
	std::cout << "  -e\tEncode configuration file as .BIN-files.\n";
	std::cout << "  -d\tDecode .BIN-files. Stores them as human-readable file.\n";
	std::cout << "  -h\tThis help/usage message.\n";
	std::cout << "  -v\tDisplays the version and build revision.\n";
	std::cout << std::endl;
	std::cout << "Examples:\n";
	std::cout << "  " << argv0 << " -e -c ./config.ini -b /mnt/wbt202/\n";
	std::cout << "  " << argv0 << " -d -c ./config.ini -b /mnt/wbt202/\n";
	std::cout << std::endl;
}

void displayVersion()
{
	std::cout << "TODO: VERSION-TAG, GIT-REVISION, BUILD-DATE" << std::endl;
}
