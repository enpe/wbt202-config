/** @file wbt202_utils.h */

#ifndef WBT202_UTILS_H
#define WBT202_UTILS_H

#include <wbt202.h>

#include <iostream>

/**
 * @name Serialize the structs.
 *
 * @{
 */
unsigned char* toBinary( const Wbt202Log * log );
unsigned char* toBinary( const Wbt202Sys * log );
unsigned char* toBinary( const Wbt202Gps * log );
/** @} */

/**
 * @name Deserialize the binary data.
 *
 * @{
 */
Wbt202Gps* toWbt202Gps( unsigned char * data );
Wbt202Log* toWbt202Log( unsigned char * data );
Wbt202Sys* toWbt202Sys( unsigned char * data );
/** @} */

/**
 * @name Overloaded operators for console output.
	*
 * @{
 */
std::ostream& operator<<( std::ostream & os, const Wbt202Gps & gps );
std::ostream& operator<<( std::ostream & os, const Wbt202Log & log );
std::ostream& operator<<( std::ostream & os, const Wbt202Sys & sys );
/** @} */

#endif // WBT202_UTILS_H
