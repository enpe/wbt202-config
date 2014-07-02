#ifndef COMMAND_H
#define COMMAND_H

#include <string>

enum Action
{
	NO_ACTION = 0,
	DISPLAY_USAGE,
	DISPLAY_VERSION,
	ENCODE,
	DECODE
};

struct Command
{
	int status;

	Action action;

	std::string iniFile;
	std::string gpsFile;
	std::string logFile;
	std::string sysFile;

	Command() :
		status( 0 ),
		action( NO_ACTION ),
		iniFile( "" ),
		gpsFile( "" ),
		logFile( "" ),
		sysFile( "" ) {}
};

#endif // COMMAND_H
