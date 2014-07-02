/** @file */

#ifndef COMMAND_H
#define COMMAND_H

#include <string>

/** @brief List of supported actions. */
enum Action
{
	NO_ACTION = 0,
	DISPLAY_USAGE,
	DISPLAY_VERSION,
	ENCODE,
	DECODE
};

/** @brief Collection of in- and output files and their corresponding action. */
struct Command
{
	int status; ///< Return codes of internal functions (for later evaluation).

	Action action; ///< Determines what is supposed to be done.

	std::string iniFile; ///< Path and name of a ini-file (human-readable config).
	std::string gpsFile; ///< Path and name of GPS.BIN-file (binary file).
	std::string logFile; ///< Path and name of LOG.BIN-file (binary file).
	std::string sysFile; ///< Path and name of SYS.BIN-file (binary file).

	Command() :
		status( 0 ),
		action( NO_ACTION ),
		iniFile( "" ),
		gpsFile( "" ),
		logFile( "" ),
		sysFile( "" ) {}
};

#endif // COMMAND_H
