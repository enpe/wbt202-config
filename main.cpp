// Memory alignment
//http://stackoverflow.com/a/9852749
//http://solidsmoke.blogspot.com.br/2010/07/woes-of-structure-packing-pragma-pack.html
//#pragma pack(1)

#include "wbt202_log.h"

#include <iostream>
#include <fstream>
#include <string>

#define OFFSET( p1, p2 ) reinterpret_cast<size_t>( p1 ) - reinterpret_cast<size_t>( p2 )

std::string filename = "WBT202/SYS/LOG.BIN";

int main( int argc, char ** argv )
{
	if ( argc == 2 )
		filename = argv[1];

	std::fstream file( filename.c_str(), std::ios::in | std::ios::binary );

	if ( ! file.is_open() )
	{
		std::cerr << "Cannot open <" << filename << ">!" << std::endl;
		return -1;
	}

	char buffer[88];
	file.read( buffer, 88 );

	Log * log = reinterpret_cast<Log*>(buffer);
	std::cout << "magic                   = " << *(reinterpret_cast<int*>( log->magic )) << std::endl;
	std::cout << "log_mode                = " << static_cast<int>( log->log_mode ) << std::endl;
	std::cout << "log_mode_user_defined   = " << static_cast<int>( log->log_mode_user_defined ) << std::endl;
	std::cout << "valid_speed_lowest      = " << static_cast<int>( log->valid_speed_lowest ) << std::endl;
	std::cout << "valid_speed_highest     = " << static_cast<int>( log->valid_speed_highest ) << std::endl;
	std::cout << "deg_point               = " << static_cast<int>( log->deg_point ) << std::endl;
	std::cout << "valid_speed_low         = " << static_cast<int>( log->valid_speed_low ) << std::endl;
	std::cout << "valid_speed_middle      = " << static_cast<int>( log->valid_speed_middle ) << std::endl;
	std::cout << "valid_speed_high        = " << static_cast<int>( log->valid_speed_high ) << std::endl;
	std::cout << "time_interval_lowest    = " << static_cast<int>( log->time_interval_lowest ) << std::endl;
	std::cout << "time_interval_low       = " << static_cast<int>( log->time_interval_low ) << std::endl;
	std::cout << "time_interval_middle    = " << static_cast<int>( log->time_interval_middle ) << std::endl;
	std::cout << "time_interval_high      = " << static_cast<int>( log->time_interval_high ) << std::endl;
	std::cout << "seconds_point           = " << static_cast<int>( log->seconds_point ) << std::endl;
	std::cout << "meters_point            = " << static_cast<int>( log->meters_point ) << std::endl;

	std::cout << std::endl;
	std::cout << "buffer[6]               = " << (int) *(reinterpret_cast<unsigned char*>( buffer+6 )) << std::endl;
	std::cout << "buffer[7]+1             = " << *(reinterpret_cast<unsigned short*>( buffer+7 )) << std::endl;
	std::cout << "buffer[8]+1             = " << *(reinterpret_cast<unsigned short*>( buffer+8 )) << std::endl;

	std::cout << std::endl;
	std::cout << "offset(magic)                 = " << std::hex << OFFSET( &(log->magic),                 log ) << std::endl;
	std::cout << "offset(log_mode)              = " << std::hex << OFFSET( &(log->log_mode),              log ) << std::endl;
	std::cout << "offset(log_mode_user_defined) = " << std::hex << OFFSET( &(log->log_mode_user_defined), log ) << std::endl;
	std::cout << "offset(valid_speed_lowest)    = " << std::hex << OFFSET( &(log->valid_speed_lowest),    log ) << std::endl;
	std::cout << "offset(valid_speed_highest)   = " << std::hex << OFFSET( &(log->valid_speed_highest),   log ) << std::endl;
	std::cout << "offset(deg_point)             = " << std::hex << OFFSET( &(log->deg_point),             log ) << std::endl;
	std::cout << "offset(valid_speed_low)       = " << std::hex << OFFSET( &(log->valid_speed_low),       log ) << std::endl;
	std::cout << "offset(valid_speed_middle)    = " << std::hex << OFFSET( &(log->valid_speed_middle),    log ) << std::endl;
	std::cout << "offset(valid_speed_high)      = " << std::hex << OFFSET( &(log->valid_speed_high),      log ) << std::endl;
	std::cout << "offset(valid_speed_lowest)    = " << std::hex << OFFSET( &(log->valid_speed_lowest),    log ) << std::endl;
	std::cout << "offset(time_interval_low)     = " << std::hex << OFFSET( &(log->time_interval_low),     log ) << std::endl;
	std::cout << "offset(time_interval_middle)  = " << std::hex << OFFSET( &(log->time_interval_middle),  log ) << std::endl;
	std::cout << "offset(time_interval_high)    = " << std::hex << OFFSET( &(log->time_interval_high),    log ) << std::endl;
	std::cout << "offset(seconds_point)         = " << std::hex << OFFSET( &(log->seconds_point),         log ) << std::endl;
	std::cout << "offset(meters_point)          = " << std::hex << OFFSET( &(log->meters_point),          log ) << std::endl;

	return 0;
}
