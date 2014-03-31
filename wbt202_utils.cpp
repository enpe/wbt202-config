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

/** @brief Stores a name, value, and unit of a WBT202 data field (for cout). */
struct Field
{
	std::string name;
	std::string value;
	std::string unit;
};


std::ostream& operator<<( std::ostream & os, const std::vector<Field> & fields )
{
	int count = static_cast<int>( fields.size() );

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

} // unnamed namespace

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
			convertByteOrder( gps->block_16.header.magic    );
			convertByteOrder( gps->block_16.header.length   );

			convertByteOrder( gps->block_26.header.magic    );
			convertByteOrder( gps->block_26.header.length   );

			convertByteOrder( gps->block_36.header.magic    );
			convertByteOrder( gps->block_36.header.length   );

			convertByteOrder( gps->block_46.header.magic    );
			convertByteOrder( gps->block_46.header.length   );

			convertByteOrder( gps->block_76.header.magic    );
			convertByteOrder( gps->block_76.header.length   );
			convertByteOrder( gps->block_76.fix_altitude_2d );
			convertByteOrder( gps->block_76.pdop_mask       );
			convertByteOrder( gps->block_76.tdop_mask       );
			convertByteOrder( gps->block_76.p_accuracy_map  );
			convertByteOrder( gps->block_76.t_accuracy_map  );

			convertByteOrder( gps->block_A2.header.magic    );
			convertByteOrder( gps->block_A2.header.length   );
			convertByteOrder( gps->block_A2.led_blink_cycle );
			convertByteOrder( gps->block_A2.led_off_cycle   );

			convertByteOrder( gps->block_BE.header.magic    );
			convertByteOrder( gps->block_BE.header.length   );
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
	Field fields[] =
	{
		{ "dirty",                  toString( gps.dirty ? "true" : "false"         ), ""     },
		{ "mode",                   toString( gps.gps_mode                         ), ""     }, // TODO Match value to string.
		{ "gpgll",                  toString( gps.block_16.gpgll ? "on" : "off"    ), ""     },
		{ "gpvtg",                  toString( gps.block_26.gpvtg ? "on" : "off"    ), ""     },
		{ "gpzda",                  toString( gps.block_36.gpzda ? "on" : "off"    ), ""     },
		{ "min_visible_satellites", toString( gps.block_46.min_visible_satellites  ), ""     },
		{ "min_signal_strength",    toString( gps.block_46.min_signal_strength     ), "dbHz" },
		{ "initial_fix_3d",         toString( gps.block_46.initial_fix_3d          ), ""     },
		{ "fix_mode",               toString( gps.block_76.fix_mode                ), ""     }, // TODO Match value to string.
		{ "fix_altitude_2d",        toString( gps.block_76.fix_altitude_2d         ), "m"    },
		{ "pdop_mask",              toString( gps.block_76.pdop_mask               ), ""     },
		{ "tdop_mask",              toString( gps.block_76.tdop_mask               ), ""     },
		{ "p_accuracy_map",         toString( gps.block_76.p_accuracy_map          ), "m"    },
		{ "t_accuracy_map",         toString( gps.block_76.t_accuracy_map          ), "m"    },
		{ "led_blink_cycle",        toString( gps.block_A2.led_blink_cycle         ), "µs"   },
		{ "led_off_cycle",          toString( gps.block_A2.led_off_cycle           ), "µs"   },
		{ "sbas",                   toString( gps.block_BE.sbas ? "on" : "off"     ), ""     }
	};

	int count = ( sizeof(fields) / sizeof(Field) );
	os << std::vector<Field>( fields, fields + count );

	return os;
}

std::ostream & operator<<( std::ostream & os, const Wbt202Log & log )
{
	Field fields[] = {
		{ "magic_begin",           toString( log.magic_begin           ), "", },
		{ "log_mode",              toString( log.log_mode              ), "", },
		{ "log_mode_user_defined", toString( log.log_mode_user_defined ), "", },
		{ "valid_speed_lowest",    toString( log.valid_speed_lowest    ), "", },
		{ "valid_speed_highest",   toString( log.valid_speed_highest   ), "", },
		{ "deg_point",             toString( log.deg_point             ), "", },
		{ "valid_speed_low",       toString( log.valid_speed_low       ), "", },
		{ "valid_speed_middle",    toString( log.valid_speed_middle    ), "", },
		{ "valid_speed_high",      toString( log.valid_speed_high      ), "", },
		{ "time_interval_lowest",  toString( log.time_interval_lowest  ), "", },
		{ "time_interval_low",     toString( log.time_interval_low     ), "", },
		{ "time_interval_middle",  toString( log.time_interval_middle  ), "", },
		{ "time_interval_high",    toString( log.time_interval_high    ), "", },
		{ "seconds_point",         toString( log.seconds_point         ), "", },
		{ "meters_point",          toString( log.meters_point          ), "", },
		{ "magic_end",             toString( log.magic_end             ), "", },
	};

	int count = ( sizeof(fields) / sizeof(Field) );
	os << std::vector<Field>( fields, fields + count );

	return os;
}

std::ostream& operator<<( std::ostream & os, const Wbt202Sys & sys )
{

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
		{ "magic_begin",        toString( sys.magic_begin        ), "", },
		{ "device_name",        device_name,                        "", },
		{ "device_info",        device_info,                        "", },
		{ "start_mode",         toString( sys.start_mode         ), "", },
		{ "cid",                toString( sys.cid                ), "", },
		{ "pid",                toString( sys.pid                ), "", },
		{ "shake_mode",         toString( sys.shake_mode         ), "", },
		{ "shake_mode_timeout", toString( sys.shake_mode_timeout ), "", },
		{ "power_off_timeout",  toString( sys.power_off_timeout  ), "", },
		{ "password",           password,                           "", },
		{ "time_zone",          toString( sys.time_zone          ), "", },
		{ "gui_language",       toString( sys.gui_language       ), "", },
		{ "unit",               toString( sys.unit               ), "", },
		{ "magic_end",          toString( sys.magic_end          ), "", },
	};

	int count = ( sizeof(fields) / sizeof(Field) );
	os << std::vector<Field>( fields, fields + count );

	return os;
}
