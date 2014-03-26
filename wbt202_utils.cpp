#include "wbt202_utils.h"

#include <cassert>
#include <cstddef>
#include <iomanip>
#include <iostream>

// Check taken from http://esr.ibiblio.org/?p=5095
#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)
#define IS_LITTLE_ENDIAN !IS_BIG_ENDIAN


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
		if ( ! IS_LITTLE_ENDIAN )
		{
			log = new Wbt202Log( *( reinterpret_cast<Wbt202Log*>( data ) ) );
		}
		else
		{
			log = new Wbt202Log();

			for ( int i = 0; i < 4; ++i )
				log->magic[i] = data[i];

			log->log_mode              = data[0x4];
			log->log_mode_user_defined = data[0x5];
			log->valid_speed_lowest    = data[0x6];
			log->valid_speed_highest   = data[0x8] << 8 | data[0x7];
			log->deg_point             = data[0x9];
			log->valid_speed_low       = data[0xb] << 8 | data[0xa];
			log->valid_speed_middle    = data[0xd] << 8 | data[0xc];
			log->valid_speed_high      = data[0xf] << 8 | data[0xe];
			log->time_interval_lowest  = data[0x11] << 8 | data[0x10];
			log->time_interval_low     = data[0x13] << 8 | data[0x12];
			log->time_interval_middle  = data[0x15] << 8 | data[0x14];
			log->time_interval_high    = data[0x17] << 8 | data[0x16];
			log->seconds_point         = data[0x19] << 8 | data[0x18];
			log->meters_point          = data[0x1b] << 8 | data[0x1a];

			for ( int i = 0; i < 60; ++i )
				log->unknown[i] = data[0x1b + i];
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
		if ( ! IS_LITTLE_ENDIAN )
		{
			sys = new Wbt202Sys( *( reinterpret_cast<Wbt202Sys*>( data ) ) );
		}
		else
		{
			sys = new Wbt202Sys();

			for ( int i = 0; i < 4; ++i )
				sys->magic[i] = data[i];

			for ( int i = 0; i < 20; ++i )
				sys->device_name[i] = data[0x4+i];

			for ( int i = 0; i < 20; ++i )
				sys->device_name[i] = data[0x18+i];

			// UNKNOWN 01
			sys->start_mode = data[0x2c];
			sys->shake_mode = data[0x37];
			// UNKNOWN 02
			sys->shake_mode_timeout = ( data[0x3b] << 8 | data[0x3a] );
			sys->power_off_timeout = ( data[0x3d] << 8 | data[0x3c] );
			// UNKNOWN 03

			for ( int i = 0; i < 4; ++i )
				sys->password[i] = data[0x42+i];

			sys->restart_device = data[0x8c];
			sys->time_zone = ( data[0x8f] << 8 | data[0x8d] );
			// UNKNOWN 04
			sys->unit = data[0x90];
			// UNKNOWN 05
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

	Field fields[] = {
		{ "magic", *( reinterpret_cast<const int*>( sys.magic ) ) },
//		{ "device_name", sys.device_name },
//		{ "device_info", sys.device_info },
		{ "start_mode", sys.start_mode },
		{ "shake_mode", sys.shake_mode },
		{ "shake_mode_timeout", sys.shake_mode_timeout },
		{ "power_off_timeout", sys.power_off_timeout },
//		{ "password", sys.password },
		{ "restart_device", sys.restart_device },
		{ "time_zone", sys.time_zone },
		{ "unit", sys.unit }
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
