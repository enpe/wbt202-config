#include "wbt202.h"

#include <cassert>
#include <cstddef>

unsigned char* serializeLog( const Log * log )
{
	assert( log );

	// TODO Missing implementation.

	return NULL;
}

Log* deserializeLog( unsigned char * data )
{
	Log * log = NULL;
	int size_data = sizeof(data) / sizeof(char);

	assert( size_data = BYTE_COUNT_LOG );
	if ( size_data == BYTE_COUNT_LOG )
	{
#ifdef USE_MEMORY_ALIGNMENT_WORKAROUND
		// TODO Test this work-around with clang.

		// Directly mapping the struct to the binary data is likely fail to due
		// to memory alignment problems. According to [1], when the type of
		// struct-member variables changes, the compiler adds (empty) padding
		// bytes. As a result the following member variable will use a wrong
		// offset and the output will be garbled.
		//
		// A work-around suggested by [2] makes use of a #pragma-statement,
		// which (temporarily) changes the memory alignment. According to that
		// source, this work-around works for GNU, Microsoft and Borland
		// compilers. Not sure how and if it works with, e.g., clang.
		//
		// [1] http://stackoverflow.com/a/9852749
		// [2] http://solidsmoke.blogspot.com.br/2010/07/woes-of-structure-packing-pragma-pack.html

		// Push current alignment rules to internal stack and for 1-byte
		// alignment.
		#pragma pack(push,1)

		log = new Log( *( reinterpret_cast<Log*>( data ) ) );

		// Restore original memory.
		#pragma pack(pop)
#else
		// Manual assignment of all variables, which is longer but works without
		// the use of #pragma-statements.
		log = new Log();

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
#endif // USE_MEMORY_ALIGNMENT_WORKAROUND
	}

	return log;
}
