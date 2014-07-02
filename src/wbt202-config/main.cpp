#include "command.h"
#include "conversion.h"
#include "parse_arguments.h"
#include "usage.h"
#include "status.h"

int main( int argc, char ** argv )
{
	int status = STATUS_NO_ERROR;

	Command cmd = parseArguments( argc, argv );
	status += cmd.status;

	if ( status == STATUS_NO_ERROR )
	{
		switch ( cmd.action )
		{
			case ENCODE:
				status += encode( cmd.gpsFile, cmd.logFile, cmd.sysFile, cmd.iniFile );
				break;

			case DECODE:
				status += decode( cmd.iniFile, cmd.gpsFile, cmd.logFile, cmd.sysFile );
				break;

			case DISPLAY_USAGE:
				displayUsage( argv[0] );
				break;

			case DISPLAY_VERSION:
				displayVersion();
				break;

			case NO_ACTION:
			default:
				status = STATUS_NO_ACTION;
				break;
		}
	}

	displayStatusMessages( status );

	return status;
}
