/**
  * @file test_endianness.cpp
  *
  * @brief Ensures that the macro @c IS_BIG_ENDIAN is working correctly.
  */

#include <wbt202/wbt202.h>

bool testEndianness()
{
	union {
		uint32_t i;
		char c[4];
	} bint = { 0x01020304 };

	if ( IS_BIG_ENDIAN )
		return bint.c[0] == 1;
	else
		return bint.c[0] == 4;
}

int main( int, char ** )
{
	return ( testEndianness() ? 0 : 1 );
}
