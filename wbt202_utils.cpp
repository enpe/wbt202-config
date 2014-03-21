#include "wbt202_utils.h"

#include <iomanip>

std::ostream &operator<<(std::ostream &os, const Log &log)
{
	struct Field
	{
		const char * name;
		int value;
	};

	Field fields[] = {
		{ "magic", *( reinterpret_cast<const int*>( log.magic ) ) },
		{ "log_mode",              static_cast<int>( log.log_mode ) },
		{ "log_mode_user_defined", static_cast<int>( log.log_mode_user_defined ) },
		{ "valid_speed_lowest",    static_cast<int>( log.valid_speed_lowest ) },
		{ "valid_speed_highest",   static_cast<int>( log.valid_speed_highest ) },
		{ "deg_point",             static_cast<int>( log.deg_point ) },
		{ "valid_speed_low",       static_cast<int>( log.valid_speed_low ) },
		{ "valid_speed_middle",    static_cast<int>( log.valid_speed_middle ) },
		{ "valid_speed_high",      static_cast<int>( log.valid_speed_high ) },
		{ "time_interval_lowest",  static_cast<int>( log.time_interval_lowest ) },
		{ "time_interval_low",     static_cast<int>( log.time_interval_low ) },
		{ "time_interval_middle",  static_cast<int>( log.time_interval_middle ) },
		{ "time_interval_high",    static_cast<int>( log.time_interval_high ) },
		{ "seconds_point",         static_cast<int>( log.seconds_point ) },
		{ "meters_point",          static_cast<int>( log.meters_point ) }
	};
	int count = sizeof( fields ) / sizeof( Field );

	for ( int i = 0; i < count; ++i )
	{
		os << std::left << std::setw( 30 ) << std::setfill( '.' )
		   << fields[i].name
		   << fields[i].value
		   << std::endl;
	}

	return os;
}
