/** @file wbt202_utils.h */

#ifndef WBT202_UTILS_H
#define WBT202_UTILS_H

#include <wbt202.h>

#include <iostream>
#include <vector>

/** @name Serialize the configuration data.
 * @{
 */

/** @brief Convert GPS data to binary array.
 *
 * Returns a NULL pointer if settings fail the internal sanity check.
 */
unsigned char* toBinary( const Wbt202Gps * gps );

/** @brief Convert LOG data to binary array.
 *
 * Returns a NULL pointer if settings fail the internal sanity check.
 */
unsigned char* toBinary( const Wbt202Log * log );

/** @brief Convert SYS data to binary array.
 *
 * Returns a NULL pointer if settings fail the internal sanity check.
 */
unsigned char* toBinary( const Wbt202Sys * sys );

/** @} */

/** @name Deserialize the binary configuration data.
 * @{
 */

/** @brief Interpret array as GPS data.
 *
 * The array must be @c BYTE_COUNT_GPS bytes long. If it isn't, a NULL pointer
 * is returned.
 */
Wbt202Gps* toWbt202Gps( const std::vector<char> & data );

/** @brief Interpret array as LOG data.
 *
 * The array must be @c BYTE_COUNT_LOG bytes long. If it isn't, a NULL pointer
 * is returned.
 */
Wbt202Log* toWbt202Log( const std::vector<char> & data );

/** @brief Interpret array as SYS data.
 *
 * The array must be @c BYTE_COUNT_SYS bytes long. If it isn't, a NULL pointer
 * is returned.
 */
Wbt202Sys* toWbt202Sys( const std::vector<char> & data );

/** @} */

/** @brief Computes the checksums for GPS.BIN.
 *
 * Computes the checksum for each block in GPS.BIN and stores the results in the
 * corresponding variables (cf. @c BlockFooter) of the @c Wbt202Gps instance.
 *
 * Details on how the checksum is computed can be found in the source of
 * @c wbt202_gps.h.
 */
void setChecksum( Wbt202Gps & gps );

std::vector<char> readFile( const char * filename );

/** @name Overloaded operators for console output.
 * @{
 */
std::ostream& operator<<( std::ostream & os, const Wbt202Gps & gps );
std::ostream& operator<<( std::ostream & os, const Wbt202Log & log );
std::ostream& operator<<( std::ostream & os, const Wbt202Sys & sys );
/** @} */

#endif // WBT202_UTILS_H
