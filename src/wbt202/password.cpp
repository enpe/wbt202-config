#include "password.h"
#include "SysBin.h"

uint32_t encodePassword( uint32_t p )
{
	return 152 * ( p + 11977 );
}

uint32_t decodePassword( uint32_t p )
{
	return ( p / 152 ) - 11977;
}

bool enabledPassword( uint32_t p )
{
	return p != NO_PASSWORD_SET;
}
