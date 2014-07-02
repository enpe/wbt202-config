#include "parse_arguments.h"
#include "status.h"

#include <getopt.h>

#include <cassert>
#include <iostream>

namespace {

const char shortOpts[] = "edc:b:vh";

bool fileExists( std::string filename )
{
	// TODO Check if the file really exists.
	return true;
}

} // namespace

Command parseArguments( int argc, char ** argv )
{
	Command command;

	if ( argc < 2 )
	{
		command.status = STATUS_INCORRECT_PARAMETERS;
		return command;
	}

	//
	char ch = 0;
	bool encode = false, decode = false;
	std::string config, binary;

	while ( ( ch = getopt( argc, argv, shortOpts ) ) != -1 )
	{
		switch ( ch )
		{
			case 'e':
				encode = true;
				break;

			case 'd':
				decode = true;
				break;

			case 'c':
				config = optarg;
				break;

			case 'b':
				binary = optarg;
				break;

			case 'h':
				command.action = DISPLAY_USAGE;
				break;

			case 'v':
				command.action = DISPLAY_VERSION;
				break;

			case '?':
			default:
				break;
		}
	}

	assert( ! ( encode && decode ) );
	if ( encode && decode )
	{
		command.status += STATUS_ACTION_MISMATCH;
	}
	else if ( encode || decode )
	{
		if ( binary.empty() )
			command.status += STATUS_BINARIES_MISSING;

		if ( config.empty() )
			command.status += STATUS_CONFIG_FILE_MISSING;

		if ( ! ( binary.empty() && config.empty() ) )
		{
			if ( encode ) command.action = ENCODE;
			else          command.action = DECODE;

			command.iniFile = config;
			command.gpsFile = std::string( binary ) + std::string( "/GPS.BIN" );
			command.logFile = std::string( binary ) + std::string( "/LOG.BIN" );
			command.sysFile = std::string( binary ) + std::string( "/SYS.BIN" );

			std::string filenames[] =
			{
				command.iniFile,
				command.gpsFile,
				command.logFile,
				command.sysFile
			};
			int count = static_cast<int>( sizeof( filenames ) / sizeof( std::string ) );

			for ( int i = 0; i < count; ++i )
				if ( ! fileExists( filenames[ i ] ) )
					return Command();
		}
	}

	return command;
}
