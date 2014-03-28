#include "wbt202_utils.h"

#include <cassert>
#include <cstddef>
#include <iomanip>
#include <iostream>

// Check taken from http://esr.ibiblio.org/?p=5095
// TODO: Replace this runtime check of machine's endianness with a compile-time check. This
//       does not seem to be too easy to do reliably though.
#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)
#define IS_LITTLE_ENDIAN !IS_BIG_ENDIAN


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

uint32_t decodePassword( uint32_t p )
{
	return ( p / 152 ) - 11977;
}

} // unnamed namespace



unsigned char* serializeLog( const Wbt202Log * log )
{
	assert( log );

	// TODO Missing implementation.

	return NULL;
}

Wbt202Log* deserializeLog( unsigned char * data )
{
	Wbt202Log * log = NULL;
	int size_data = sizeof(data) / sizeof(char);

	assert( size_data = BYTE_COUNT_LOG );
	if ( size_data == BYTE_COUNT_LOG )
	{
		log = new Wbt202Log( *( reinterpret_cast<Wbt202Log*>( data ) ) );

		// If we are not running on a little-endian machine, we must explicitely convert the data to
		// big-endian byte order.
		if ( ! IS_LITTLE_ENDIAN )
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

Wbt202Sys* deserializeSys( unsigned char * data )
{
	Wbt202Sys * sys = NULL;
	int size_data = sizeof(data) / sizeof(char);

	assert( size_data = BYTE_COUNT_SYS );
	if ( size_data == BYTE_COUNT_SYS )
	{
		sys = new Wbt202Sys( *( reinterpret_cast<Wbt202Sys*>( data ) ) );

		// If we are not running on a little-endian machine, we must explicitely convert the data to
		// big-endian byte order.
		if ( ! IS_LITTLE_ENDIAN )
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

	// TODO: Check if the encoded password is 0xFFFFFFFF and, if it is, do not try to decode but
	//       signal "password not used" instead.
	uint32_t password = decodePassword( sys.password );

	Field fields[] = {
		{ "magic_begin",        static_cast< int >( sys.magic_begin        ) },
		{ "start_mode",         static_cast< int >( sys.start_mode         ) },
		{ "cid",                static_cast< int >( sys.cid                ) },
		{ "pid",                static_cast< int >( sys.pid                ) },
		{ "shake_mode",         static_cast< int >( sys.shake_mode         ) },
		{ "shake_mode_timeout", static_cast< int >( sys.shake_mode_timeout ) },
		{ "power_off_timeout",  static_cast< int >( sys.power_off_timeout  ) },
		{ "password",           static_cast< int >( password               ) },
		{ "time_zone",          static_cast< int >( sys.time_zone          ) },
		{ "gui_language",       static_cast< int >( sys.gui_language       ) },
		{ "unit",               static_cast< int >( sys.unit               ) },
		{ "magic_end",          static_cast< int >( sys.magic_end          ) },
	};
	int count = sizeof( fields ) / sizeof( Field );

	os << std::left << std::setw( 30 ) << std::setfill( '.' )
		<< "device_name"
		<< sys.device_name
		<< std::endl;

	os << std::left << std::setw( 30 ) << std::setfill( '.' )
		<< "device_info"
		<< sys.device_info
		<< std::endl;

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
