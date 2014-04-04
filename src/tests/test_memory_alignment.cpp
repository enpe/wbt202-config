/**
  * @file test_memory_alignment.cpp
  *
  * @brief Checks the size of the configuration structs.
  *
  * @note Builds based on C++0x and C++11 use @c static_assert and do not
  *       require this test.
  */

#include <wbt202/wbt202.h>

int main( int, char** )
{
	bool passed = true;

	passed &= ( sizeof( Wbt202Gps ) == BYTE_COUNT_GPS );
	passed &= ( sizeof( Wbt202Log ) == BYTE_COUNT_LOG );
	passed &= ( sizeof( SysBin ) == SIZE_SYS_BIN );

	return ( passed ? 0 : 1 );
}
