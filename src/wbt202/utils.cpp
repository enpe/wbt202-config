
#include "wbt202/utils.h"
#include "wbt202/password.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstring>
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
 * @name Validity checks for the configuration data of the WBT202.
 *
 * @{
 */

bool isValid( const GpsBin * gps )
{
	bool valid = true;

	if ( gps )
	{
		// TODO Missing implementation.
	}

	return valid;
}

bool isValid( const LogBin * log )
{
	bool valid = true;

	if ( log )
	{
		// TODO Missing implementation.
	}

	return valid;
}

bool isValid( const SysBin * sys )
{
	bool valid = true;

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

unsigned char* wbt202::toBinary( const GpsBin * gps )
{
	return ::toBinary< GpsBin >( gps );
}

unsigned char* wbt202::toBinary( const LogBin * log )
{
	return ::toBinary< LogBin >( log );}

unsigned char* wbt202::toBinary( const SysBin * sys )
{
	return ::toBinary< SysBin >( sys );
}

GpsBin * wbt202::toGpsBin( const std::vector<char> & data )
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

			convertByteOrder( gps->cfg_sbas.header.length   );
		}
	}

	return gps;
}

LogBin* wbt202::toLogBin( const std::vector<char> & data )
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
			convertByteOrder( log->magic_begin   );
			convertByteOrder( log->speed_highest );
			convertByteOrder( log->speed_low     );
			convertByteOrder( log->speed_middle  );
			convertByteOrder( log->speed_high    );
			convertByteOrder( log->time_lowest   );
			convertByteOrder( log->time_low      );
			convertByteOrder( log->time_middle   );
			convertByteOrder( log->time_high     );
			convertByteOrder( log->seconds_point );
			convertByteOrder( log->meters_point  );
			convertByteOrder( log->magic_end     );
		}
	}

	return log;
}

SysBin* wbt202::toSysBin( const std::vector<char> & data )
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

void wbt202::setChecksum( GpsBin & gps )
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
		{ gps.cfg_sbas.footer.checksum_01, gps.cfg_sbas.footer.checksum_02, reinterpret_cast< const uint8_t* >( &gps.cfg_sbas ), gps.cfg_sbas.header.length }
	};
	int count = sizeof( blocks ) / sizeof( Block );

	for ( int i = 0; i < count; ++i )
	{
		::setChecksum(
			blocks[i].checksum_01,
			blocks[i].checksum_02,
			blocks[i].pSrc,
			blocks[i].len );
	}
}

std::vector<char> wbt202::readFile( const char * filename )
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

void wbt202::writeFile( const char * filename, const std::vector<unsigned char> & data )
{
	std::ofstream file( filename, std::ios::binary );

	if ( ! file.is_open() )
	{
		std::cerr << "Cannot write to " << filename << std::endl;
		return;
	}

	file.write( reinterpret_cast<const char*>( &(data[0]) ), data.size() );
}

std::ostream& wbt202::operator<<( std::ostream & os, const GpsBin & gps )
{
	Field fields[] =
	{
		{ "dirty",                  toString( gps.dirty ? "true" : "false"          ), ""     },
		{ "mode",                   toString( gps.gps_mode                          ), ""     }, // TODO Match value to string.
		{ "gpgll",                  toString( gps.block_16.gpgll ? "on" : "off"     ), ""     },
		{ "gpvtg",                  toString( gps.block_26.gpvtg ? "on" : "off"     ), ""     },
		{ "gpzda",                  toString( gps.block_36.gpzda ? "on" : "off"     ), ""     },
		{ "min_visible_satellites", toString( gps.block_46.min_visible_satellites   ), ""     },
		{ "min_signal_strength",    toString( gps.block_46.min_signal_strength      ), "dbHz" },
		{ "initial_fix_3d",         toString( gps.block_46.initial_fix_3d           ), ""     },
		{ "fix_mode",               toString( gps.block_76.fix_mode                 ), ""     }, // TODO Match value to string.
		{ "fix_altitude_2d",        toString( gps.block_76.fix_altitude_2d          ), "m"    },
		{ "pdop_mask",              toString( gps.block_76.pdop_mask                ), ""     },
		{ "tdop_mask",              toString( gps.block_76.tdop_mask                ), ""     },
		{ "p_accuracy_map",         toString( gps.block_76.p_accuracy_map           ), "m"    },
		{ "t_accuracy_map",         toString( gps.block_76.t_accuracy_map           ), "m"    },
		{ "led_blink_cycle",        toString( gps.block_A2.led_blink_cycle          ), "µs"   },
		{ "led_off_cycle",          toString( gps.block_A2.led_off_cycle            ), "µs"   },
		{ "sbas",                   toString( gps.cfg_sbas.sbas_mode ? "on" : "off" ), ""     }
	};

	int count = ( sizeof(fields) / sizeof(Field) );
	os << std::vector<Field>( fields, fields + count );

	return os;
}

std::ostream & wbt202::operator<<( std::ostream & os, const LogBin & log )
{
	Field fields[] = {
		{ "magic_begin",           toString( log.magic_begin     ), "", },
		{ "log_mode",              toString( log.preset_log_mode ), "", },
		{ "log_mode_user_defined", toString( log.log_mode        ), "", },
		{ "speed_lowest",          toString( log.speed_lowest    ), "", },
		{ "speed_highest",         toString( log.speed_highest   ), "", },
		{ "degrees_point",         toString( log.degrees_point   ), "", },
		{ "speed_low",             toString( log.speed_low       ), "", },
		{ "speed_middle",          toString( log.speed_middle    ), "", },
		{ "speed_high",            toString( log.speed_high      ), "", },
		{ "time_lowest",           toString( log.time_lowest     ), "", },
		{ "time_low",              toString( log.time_low        ), "", },
		{ "time_middle",           toString( log.time_middle     ), "", },
		{ "time_high",             toString( log.time_high       ), "", },
		{ "seconds_point",         toString( log.seconds_point   ), "", },
		{ "meters_point",          toString( log.meters_point    ), "", },
		{ "magic_end",             toString( log.magic_end       ), "", },
	};

	int count = ( sizeof(fields) / sizeof(Field) );
	os << std::vector<Field>( fields, fields + count );

	return os;
}

std::ostream& wbt202::operator<<( std::ostream & os, const SysBin & sys )
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

wbt202::W_Status wbt202::setDeviceName( Wbt202 & wbt202, std::string name )
{
	size_t length = name.length();
	size_t maxLength = 20; // TODO This should not be hard-coded (here).

	if ( length >= maxLength )
		return W_DEVICE_NAME_TOO_LONG;

	memset( wbt202.sys.device_name, 0, maxLength );
	std::copy( name.begin(), name.end(), wbt202.sys.device_name );

	return W_NO_ERROR;
}

wbt202::W_Status wbt202::setDeviceInfo( Wbt202 & wbt202, std::string info )
{
	size_t length = info.length();
	size_t maxLength = 20; // TODO This should not be hard-coded (here).

	if ( length >= maxLength )
		return W_DEVICE_NAME_TOO_LONG;

	memset( wbt202.sys.device_info, 0, maxLength );
	std::copy( info.begin(), info.end(), wbt202.sys.device_info );

	return W_NO_ERROR;
}

wbt202::W_Status wbt202::setRestartMode( Wbt202 & wbt202, int restartMode )
{
	W_Status status = W_UNKNOWN_ERROR;

	switch ( restartMode )
	{
		case AUTOMATIC_START:
		case COLD_START:
		case WARM_START:
		case HOT_START:
			wbt202.sys.restart_mode = restartMode;
			status = W_NO_ERROR;
			break;

		default:
			status = W_RESTART_MODE_INVALID;
			break;
	}

	return status;
}

wbt202::W_Status wbt202::setShakeMode( Wbt202 & wbt202, bool onoff )
{
	W_Status status = W_VALUE_OUT_OF_RANGE;

	wbt202.sys.shake_mode = onoff;
	status = W_NO_ERROR;

	return status;
}


wbt202::W_Status wbt202::setShakeModeTimeout( Wbt202 & wbt202, uint16_t timeout )
{
	W_Status status = W_UNKNOWN_ERROR;
	uint16_t minTimeout = 60;   // TODO This should not be hard-coded (here).
	uint16_t maxTimeout = 7200; // TODO This should not be hard-coded (here).

	if ( timeout < minTimeout || timeout > maxTimeout )
	{
		status = W_VALUE_OUT_OF_RANGE;
	}
	else
	{
		wbt202.sys.shake_mode_timeout = timeout;
		status = W_NO_ERROR;
	}

	return status;
}


wbt202::W_Status wbt202::setPowerOffTimout( Wbt202 & wbt202, uint16_t timeout )
{
	W_Status status = W_UNKNOWN_ERROR;
	uint16_t minTimeout = 0;    // TODO This should not be hard-coded (here).
	uint16_t maxTimeout = 3600; // TODO This should not be hard-coded (here).

	if ( timeout < minTimeout || timeout > maxTimeout )
	{
		status = W_VALUE_OUT_OF_RANGE;
	}
	else
	{
		wbt202.sys.power_off_timeout = timeout;
		status = W_NO_ERROR;
	}

	return status;
}


wbt202::W_Status wbt202::setSystemOfUnits( Wbt202 & wbt202, int systemOfUnits )
{
	W_Status status = W_VALUE_OUT_OF_RANGE;

	if ( systemOfUnits == METRIC || systemOfUnits== IMPERIAL )
	{
		wbt202.sys.unit = systemOfUnits;
		status = W_NO_ERROR;
	}

	return status;
}


wbt202::W_Status wbt202::setTimeZone( Wbt202 & wbt202, int16_t offset )
{
	W_Status status = W_VALUE_OUT_OF_RANGE;

	if ( -1400 <= offset && offset <= 1400 )
	{
		wbt202.sys.time_zone = offset;
		status = W_NO_ERROR;
	}

	return status;
}
