#include "wbt202/status.h"

#include <cassert>
#include <iostream>

void wbt202::displayStatusMessages( int status )
{
	struct StatusMessage
	{
		W_Status status;
		std::string message;
	};

	StatusMessage sm[] =
	{
		{ W_DEVICE_NAME_TOO_LONG, "The device name is too long (max. 19 chars)." },
		{ W_DEVICE_INFO_TOO_LONG, "The device info is too long (max. 19 chars)." },
		{ W_RESTART_MODE_INVALID, "Invalid restart mode." },
		{ W_VALUE_OUT_OF_RANGE,   "Value out of range." },
		{ W_UNKNOWN_ERROR,        "Unknown error." }
	};
	int count = static_cast<int>( sizeof( sm ) / sizeof( StatusMessage ) );

	for ( int i = 0; i < count; ++i )
	{
		if ( status & sm[ i ].status )
		{
			std::cerr << sm[ i ].message << std::endl;

			status -= sm[ i ].status;
			assert( status >= 0 );
		}
	}

	assert( status == 0 );
}
