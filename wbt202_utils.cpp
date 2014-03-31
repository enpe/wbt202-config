/** @file wbt202_utils.cpp */

#include "wbt202_utils.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace
{

/**
 * @brief Convert between little-endian and big-endian byte order.
 */
void convertByteOrder( uint16_t & n )
{
	n =
		  ( ( n & 0x00FF ) << 8 )
		| ( ( n & 0xFF00 ) >> 8 );
}

/**
 * @brief Convert between little-endian and big-endian byte order.
 */
void convertByteOrder( int16_t & n )
{
	n =
		  ( ( n & 0x00FF ) << 8 )
		| ( ( n & 0xFF00 ) >> 8 );
}

/**
 * @brief Convert between little-endian and big-endian byte order.
 */
void convertByteOrder( uint32_t & n )
{
	n =
		  ( ( n & 0x000000FF ) << 24 )
		| ( ( n & 0x0000FF00 ) <<  8 )
		| ( ( n & 0x00FF0000 ) >>  8 )
		| ( ( n & 0xFF000000 ) >> 24 );
}

/**
 * @name Password utilities.
 *
 * @{
 */

/** @brief Encode a password. */
uint32_t encodePassword( uint32_t p )
{
	return 152 * ( p + 11977 );
}

/** @brief Decode a password */
uint32_t decodePassword( uint32_t p )
{
	return ( p / 152 ) - 11977;
}

/** @brief Check if a password has been set. */
bool enabledPassword( uint32_t p )
{
	return p != DEFAULT_PASSWORD;
}
/** @} */

bool isValid( const Wbt202Gps * gps )
{
	bool valid = false;

	if ( gps )
	{
		// TODO Missing implementation.
	}

	return valid;
}

bool isValid( const Wbt202Log * log )
{
	bool valid = false;

	if ( log )
	{
		// TODO Missing implementation.
	}

	return valid;
}

bool isValid( const Wbt202Sys * sys )
{
	bool valid = false;

	if ( sys )
	{
		// TODO Missing implementation.
	}

	return valid;
}

/** @brief Serialize the device settings.
 *
 * @note Only use with @c Wbt202Gps, @c Wbt202Log, and @c Wbt202Sys.
 */
template <typename T>
unsigned char* toBinary( const T * t )
{
	assert( t );

	unsigned char * data = NULL;

	if ( isValid( t ) )
	{
		int byteCount = sizeof( T );
		data = new unsigned char[ byteCount ];

		const unsigned char * src = reinterpret_cast<const unsigned char*>( t );
		std::copy( &(src[0]), &(src[0]) + byteCount, &(data[0]) );
	}

	return data;
}

template <typename T>
std::string toString( T value )
{
	std::ostringstream oss;
	oss << value;

	return oss.str();
}

template <>
std::string toString<uint8_t>( uint8_t value )
{
	return toString( static_cast<int>( value ) );
}

} // unnamed namespace


unsigned char* toBinary( const Wbt202Gps * gps )
{
	return toBinary< Wbt202Gps >( gps );
}

unsigned char* toBinary( const Wbt202Log * log )
{
	return toBinary< Wbt202Log >( log );}

unsigned char* toBinary( const Wbt202Sys * sys )
{
	return toBinary< Wbt202Sys >( sys );
}

Wbt202Gps * toWbt202Gps( const std::vector<char> & data )
{
	assert( ! data.empty() );

	// TODO Missing implementation.
	Wbt202Gps * gps = NULL;

	if ( data.size() == BYTE_COUNT_GPS )
	{
		gps = new Wbt202Gps( *(
			reinterpret_cast<const Wbt202Gps*>( data.data() ) ) );

		if ( IS_BIG_ENDIAN )
		{
			convertByteOrder( gps->block_16.magic                   );
			convertByteOrder( gps->block_16.length                  );

			convertByteOrder( gps->block_26.magic                   );
			convertByteOrder( gps->block_26.length                  );

			convertByteOrder( gps->block_36.magic                   );
			convertByteOrder( gps->block_36.length                  );

			convertByteOrder( gps->block_46.magic                   );
			convertByteOrder( gps->block_46.length                  );

			convertByteOrder( gps->block_76.magic                   );
			convertByteOrder( gps->block_76.length                  );
			convertByteOrder( gps->block_76.payload.fix_altitude_2d );
			convertByteOrder( gps->block_76.payload.pdop_mask       );
			convertByteOrder( gps->block_76.payload.tdop_mask       );
			convertByteOrder( gps->block_76.payload.p_accuracy_map  );
			convertByteOrder( gps->block_76.payload.t_accuracy_map  );

			convertByteOrder( gps->block_A2.magic                   );
			convertByteOrder( gps->block_A2.length                  );
			convertByteOrder( gps->block_A2.payload.led_blink_cycle );
			convertByteOrder( gps->block_A2.payload.led_off_cycle   );

			convertByteOrder( gps->block_BE.magic                   );
			convertByteOrder( gps->block_BE.length                  );
		}
	}

	return gps;
}

Wbt202Log* toWbt202Log( const std::vector<char> & data )
{
	assert( ! data.empty() );
	assert( data.size() == BYTE_COUNT_LOG );
	assert( sizeof( Wbt202Log ) == BYTE_COUNT_LOG );

	Wbt202Log * log = NULL;

	if ( data.size() == BYTE_COUNT_LOG )
	{
		log = new Wbt202Log( *(
			reinterpret_cast<const Wbt202Log*>( data.data() ) ) );

		// If we are not running on a little-endian machine, we must explicitely
		// convert the data to big-endian byte order.
		if ( IS_BIG_ENDIAN )
		{
			convertByteOrder( log->magic_begin          );
			convertByteOrder( log->valid_speed_highest  );
			convertByteOrder( log->valid_speed_low      );
			convertByteOrder( log->valid_speed_middle   );
			convertByteOrder( log->valid_speed_high     );
			convertByteOrder( log->time_interval_lowest );
			convertByteOrder( log->time_interval_low    );
			convertByteOrder( log->time_interval_middle );
			convertByteOrder( log->time_interval_high   );
			convertByteOrder( log->seconds_point        );
			convertByteOrder( log->meters_point         );
			convertByteOrder( log->magic_end            );
		}
	}

	return log;
}

Wbt202Sys* toWbt202Sys( const std::vector<char> & data )
{
	assert( ! data.empty() );
	assert( data.size() == BYTE_COUNT_SYS );
	assert( sizeof( Wbt202Sys ) == BYTE_COUNT_SYS );

	Wbt202Sys * sys = NULL;

	if ( data.size() == BYTE_COUNT_SYS )
	{
		sys = new Wbt202Sys( *(
			reinterpret_cast<const Wbt202Sys*>( data.data() ) ) );

		// If we are not running on a little-endian machine, we must explicitly
		// convert the data to big-endian byte order.
		if ( IS_BIG_ENDIAN )
		{
			convertByteOrder( sys->magic_begin        );
			convertByteOrder( sys->cid                );
			convertByteOrder( sys->pid                );
			convertByteOrder( sys->unknown_31         );
			convertByteOrder( sys->unknown_35         );
			convertByteOrder( sys->shake_mode_timeout );
			convertByteOrder( sys->power_off_timeout  );
			convertByteOrder( sys->password           );
			convertByteOrder( sys->time_zone          );
			convertByteOrder( sys->magic_end          );
		}
	}

	return sys;
}

std::ostream& operator<<( std::ostream & os, const Wbt202Gps & gps )
{
	struct Field
	{
		std::string name;
		std::string value;
		std::string unit;
	};

	const Payload_16 & p_16 = gps.block_16.payload;
	const Payload_26 & p_26 = gps.block_26.payload;
	const Payload_36 & p_36 = gps.block_36.payload;
	const Payload_46 & p_46 = gps.block_46.payload;
	const Payload_76 & p_76 = gps.block_76.payload;
	const Payload_A2 & p_A2 = gps.block_A2.payload;
	const Payload_BE & p_BE = gps.block_BE.payload;

	Field fields[] =
	{
		{ "dirty",                  toString( gps.dirty ? "true" : "false" ), ""     },
		{ "mode",                   toString( gps.gps_mode                 ), ""     }, // TODO Match value to string.
		{ "gpgll",                  toString( p_16.gpgll ? "on" : "off"    ), ""     },
		{ "gpvtg",                  toString( p_26.gpvtg ? "on" : "off"    ), ""     },
		{ "gpzda",                  toString( p_36.gpzda ? "on" : "off"    ), ""     },
		{ "min_visible_satellites", toString( p_46.min_visible_satellites  ), ""     },
		{ "min_signal_strength",    toString( p_46.min_signal_strength     ), "dbHz" },
		{ "initial_fix_3d",         toString( p_46.initial_fix_3d          ), ""     },
		{ "fix_mode",               toString( p_76.fix_mode                ), ""     }, // TODO Match value to string.
		{ "fix_altitude_2d",        toString( p_76.fix_altitude_2d         ), "m"    },
		{ "pdop_mask",              toString( p_76.pdop_mask               ), ""     },
		{ "tdop_mask",              toString( p_76.tdop_mask               ), ""     },
		{ "p_accuracy_map",         toString( p_76.p_accuracy_map          ), "m"    },
		{ "t_accuracy_map",         toString( p_76.t_accuracy_map          ), "m"    },
		{ "led_blink_cycle",        toString( p_A2.led_blink_cycle         ), "µs"   },
		{ "led_off_cycle",          toString( p_A2.led_off_cycle           ), "µs"   },
		{ "sbas",                   toString( p_BE.sbas ? "on" : "off"     ), ""     }
	};
	int count = sizeof( fields ) / sizeof( Field );

	for ( int i = 0; i < count; ++i )
	{
		os << std::left << std::setw( 30 ) << std::setfill( '.' )
			<< fields[i].name
			<< fields[i].value
			<< " " << fields[i].unit;

		if ( i < (count-1) )
			os << std::endl;

	}

	return os;
}

std::ostream &operator<<(std::ostream &os, const Wbt202Log &log)
{
	struct Field
	{
		const char * name;
		int value;
	};

	Field fields[] = {
		{ "magic_begin",           static_cast<int>( log.magic_begin           ) },
		{ "log_mode",              static_cast<int>( log.log_mode              ) },
		{ "log_mode_user_defined", static_cast<int>( log.log_mode_user_defined ) },
		{ "valid_speed_lowest",    static_cast<int>( log.valid_speed_lowest    ) },
		{ "valid_speed_highest",   static_cast<int>( log.valid_speed_highest   ) },
		{ "deg_point",             static_cast<int>( log.deg_point             ) },
		{ "valid_speed_low",       static_cast<int>( log.valid_speed_low       ) },
		{ "valid_speed_middle",    static_cast<int>( log.valid_speed_middle    ) },
		{ "valid_speed_high",      static_cast<int>( log.valid_speed_high      ) },
		{ "time_interval_lowest",  static_cast<int>( log.time_interval_lowest  ) },
		{ "time_interval_low",     static_cast<int>( log.time_interval_low     ) },
		{ "time_interval_middle",  static_cast<int>( log.time_interval_middle  ) },
		{ "time_interval_high",    static_cast<int>( log.time_interval_high    ) },
		{ "seconds_point",         static_cast<int>( log.seconds_point         ) },
		{ "meters_point",          static_cast<int>( log.meters_point          ) },
		{ "magic_end",             static_cast<int>( log.magic_end             ) },
	};
	int count = sizeof( fields ) / sizeof( Field );

	for ( int i = 0; i < count; ++i )
	{
		os << std::left << std::setw( 30 ) << std::setfill( '.' )
			<< fields[i].name
			<< fields[i].value;

		if ( i < (count-1) )
			os << std::endl;
	}

	return os;
}

std::ostream& operator<<( std::ostream & os, const Wbt202Sys & sys )
{
	struct Field
	{
		const char * name;
		int value;
	};

	std::string device_name = "<not set>";
	std::string device_info = "<not set>";
	std::string password    = "<not set>";

	// Check if a device name has been set.
	if ( sys.device_name[0] != '\0' )
		device_name = reinterpret_cast<const char*>( sys.device_name );

	// Check if a device description has been set.
	if ( sys.device_info[0] != '\0' )
		device_info = reinterpret_cast<const char*>( sys.device_info );

	// Check if a password has been set.
	if ( enabledPassword( sys.password ) )
	{
		uint32_t decoded = decodePassword( sys.password );
		assert( sys.password == encodePassword( decoded ) );

		std::ostringstream oss;
		oss << decodePassword( sys.password );

		password = oss.str();
	}

	Field fields[] = {
		{ "magic_begin",        static_cast< int >( sys.magic_begin        ) },
		{ "start_mode",         static_cast< int >( sys.start_mode         ) },
		{ "cid",                static_cast< int >( sys.cid                ) },
		{ "pid",                static_cast< int >( sys.pid                ) },
		{ "shake_mode",         static_cast< int >( sys.shake_mode         ) },
		{ "shake_mode_timeout", static_cast< int >( sys.shake_mode_timeout ) },
		{ "power_off_timeout",  static_cast< int >( sys.power_off_timeout  ) },
		{ "time_zone",          static_cast< int >( sys.time_zone          ) },
		{ "gui_language",       static_cast< int >( sys.gui_language       ) },
		{ "unit",               static_cast< int >( sys.unit               ) },
		{ "magic_end",          static_cast< int >( sys.magic_end          ) },
	};

	// Device name
	os << std::left << std::setw( 30 ) << std::setfill( '.' )
		<< "device_name"
		<< device_name
		<< std::endl;

	// Device info
	os << std::left << std::setw( 30 ) << std::setfill( '.' )
		<< "device_info"
		<< device_info
		<< std::endl;

	// Password
	os << std::left << std::setw( 30 ) << std::setfill( '.' )
		<< "password"
		<< password
		<< std::endl;

	int count = sizeof( fields ) / sizeof( Field );
	for ( int i = 0; i < count; ++i )
	{
		os << std::left << std::setw( 30 ) << std::setfill( '.' )
			<< fields[i].name
			<< fields[i].value;

		if ( i < (count-1) )
			os << std::endl;
	}

	return os;
}
