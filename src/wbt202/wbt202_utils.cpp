
#include "wbt202_utils.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <fstream>
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

/**
 * @brief Encode a password.
 */
uint32_t encodePassword( uint32_t p )
{
	return 152 * ( p + 11977 );
}

/**
 * @brief Decode a password
 */
uint32_t decodePassword( uint32_t p )
{
	return ( p / 152 ) - 11977;
}

/**
 * @brief Check if a password has been set.
 */
bool enabledPassword( uint32_t p )
{
	return p != NO_PASSWORD_SET;
}
/** @} */

/**
 * @name Validity checks for the configuration data of the WBT202.
 *
 * @{
 */

bool isValid( const GpsBin * gps )
{
	bool valid = false;

	if ( gps )
	{
		// TODO Missing implementation.
	}

	return valid;
}

bool isValid( const LogBin * log )
{
	bool valid = false;

	if ( log )
	{
		// TODO Missing implementation.
	}

	return valid;
}

bool isValid( const SysBin * sys )
{
	bool valid = false;

	if ( sys )
	{
		// TODO Missing implementation.
	}

	return valid;
}
/** @} */

/** @brief Helper function to serialize the device settings.
 *
 * @note Only use with @c Wbt202Gps, @c Wbt202Log, and @c SysBin.
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

/** @brief Helper function to compute the checksums in @c Wbt202Gps. */
void setChecksum(
	uint8_t & checksum_01,
	uint8_t & checksum_02,
	const uint8_t * pSrc,
	uint16_t len )
{
	uint8_t sum1 = 0;
	uint8_t sum2 = 0;

	for ( int i = 0; i < len + 4; ++i )
	{
		sum1 += pSrc[ i + 2 ];
		sum2 += sum1;
	}

	checksum_01 = sum1;
	checksum_02 = sum2;
}

} // unnamed namespace

unsigned char* toBinary( const GpsBin * gps )
{
	return toBinary< GpsBin >( gps );
}

unsigned char* toBinary( const LogBin * log )
{
	return toBinary< LogBin >( log );}

unsigned char* toBinary( const SysBin * sys )
{
	return toBinary< SysBin >( sys );
}

GpsBin * toWbt202Gps( const std::vector<char> & data )
{
	assert( ! data.empty() );

	// TODO Missing implementation.
	GpsBin * gps = NULL;

	if ( data.size() == SIZE_GPS_BIN )
	{
		gps = new GpsBin( *(
			reinterpret_cast<const GpsBin*>( data.data() ) ) );

		if ( IS_BIG_ENDIAN )
		{
			convertByteOrder( gps->block_16.header.length   );

			convertByteOrder( gps->block_26.header.length   );

			convertByteOrder( gps->block_36.header.length   );

			convertByteOrder( gps->block_46.header.length   );

			convertByteOrder( gps->block_76.header.length   );
			convertByteOrder( gps->block_76.fix_altitude_2d );
			convertByteOrder( gps->block_76.pdop_mask       );
			convertByteOrder( gps->block_76.tdop_mask       );
			convertByteOrder( gps->block_76.p_accuracy_map  );
			convertByteOrder( gps->block_76.t_accuracy_map  );

			convertByteOrder( gps->block_A2.header.length   );
			convertByteOrder( gps->block_A2.led_blink_cycle );
			convertByteOrder( gps->block_A2.led_off_cycle   );

			convertByteOrder( gps->block_BE.header.length   );
		}
	}

	return gps;
}

LogBin* toWbt202Log( const std::vector<char> & data )
{
	assert( ! data.empty() );
	assert( data.size() == SIZE_LOG_BIN );
	assert( sizeof( LogBin ) == SIZE_LOG_BIN );

	LogBin * log = NULL;

	if ( data.size() == SIZE_LOG_BIN )
	{
		log = new LogBin( *(
			reinterpret_cast<const LogBin*>( data.data() ) ) );

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

SysBin* toSysBin( const std::vector<char> & data )
{
	assert( ! data.empty() );
	assert( data.size() == SIZE_SYS_BIN );
	assert( sizeof( SysBin ) == SIZE_SYS_BIN );

	SysBin * sys = NULL;

	if ( data.size() == SIZE_SYS_BIN )
	{
		sys = new SysBin( *(
			reinterpret_cast<const SysBin*>( data.data() ) ) );

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

void setChecksum( GpsBin & gps )
{
	struct Block
	{
		uint8_t &       checksum_01;
		uint8_t &       checksum_02;
		const uint8_t * pSrc;
		uint16_t        len;

	};

	Block blocks[] =
	{
		{ gps.block_16.footer.checksum_01, gps.block_16.footer.checksum_02, reinterpret_cast< const uint8_t* >( &gps.block_16 ), gps.block_16.header.length },
		{ gps.block_26.footer.checksum_01, gps.block_26.footer.checksum_02, reinterpret_cast< const uint8_t* >( &gps.block_26 ), gps.block_26.header.length },
		{ gps.block_36.footer.checksum_01, gps.block_36.footer.checksum_02, reinterpret_cast< const uint8_t* >( &gps.block_36 ), gps.block_36.header.length },
		{ gps.block_46.footer.checksum_01, gps.block_46.footer.checksum_02, reinterpret_cast< const uint8_t* >( &gps.block_46 ), gps.block_46.header.length },
		{ gps.block_76.footer.checksum_01, gps.block_76.footer.checksum_02, reinterpret_cast< const uint8_t* >( &gps.block_76 ), gps.block_76.header.length },
		{ gps.block_A2.footer.checksum_01, gps.block_A2.footer.checksum_02, reinterpret_cast< const uint8_t* >( &gps.block_A2 ), gps.block_A2.header.length },
		{ gps.block_BE.footer.checksum_01, gps.block_BE.footer.checksum_02, reinterpret_cast< const uint8_t* >( &gps.block_BE ), gps.block_BE.header.length }
	};
	int count = sizeof( blocks ) / sizeof( Block );

	for ( int i = 0; i < count; ++i )
	{
		setChecksum(
			blocks[i].checksum_01,
			blocks[i].checksum_02,
			blocks[i].pSrc,
			blocks[i].len );
	}
}

std::vector<char> readFile( const char * filename )
{
	std::ifstream file( filename, std::ios::binary );

	if ( ! file.is_open() )
	{
		std::cerr << "Cannot open " << filename << std::endl;
		return std::vector<char>();
	}

	return std::vector<char>(
		std::istreambuf_iterator<char>( file ),
		std::istreambuf_iterator<char>() );
}

std::ostream& operator<<( std::ostream & os, const GpsBin & gps )
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
		{ "sbas",                   toString( gps.block_BE.sbas_mode ? "on" : "off"     ), ""     }
	};

	int count = ( sizeof(fields) / sizeof(Field) );
	os << std::vector<Field>( fields, fields + count );

	return os;
}

std::ostream & operator<<( std::ostream & os, const LogBin & log )
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

std::ostream& operator<<( std::ostream & os, const SysBin & sys )
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
		{ "start_mode",         toString( sys.restart_mode       ), "", },
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
