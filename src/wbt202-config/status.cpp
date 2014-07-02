#include "status.h"

#include <cassert>
#include <iostream>

void displayStatusMessages( int status )
{
	struct StatusMessage
	{
		Status status;
		std::string message;
	};

	StatusMessage sm[] =
	{
		{ STATUS_INCORRECT_PARAMETERS, "Incorrect parameters; Try the -h switch." },
		{ STATUS_CONFIG_FILE_MISSING,  "The .ini-file is missing." },
		{ STATUS_BINARIES_MISSING,     "No .BIN-files in the specified folder." },
		{ STATUS_NO_ACTION,            "No action selected. Try the -h switch." },
		{ STATUS_ACTION_MISMATCH,      "Use either -e (x)or -d, but not both." },
		{ STATUS_UNKNOWN_ERROR,        "An unknown error occured." }
	};
	int count = static_cast<int>( sizeof( sm ) / sizeof( StatusMessage ) );

	for ( int i = 0; i < count; ++i )
	{
		if ( status & sm[ i ].status )
		{
			std::cerr << sm[ i ].message << std::endl;
		}
	}
}
