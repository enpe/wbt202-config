/** @file wbt202_utils.h */

#ifndef WBT202_UTILS_H
#define WBT202_UTILS_H

#include <wbt202/wbt202.h>

#include <iostream>
#include <vector>

/** @name Serialize the configuration data.
 * @{
 */

/** @brief Convert GPS data to binary array.
 *
 * Returns a NULL pointer if settings fail the internal sanity check.
 */
unsigned char* toBinary( const GpsBin * gps );

/** @brief Convert LOG data to binary array.
 *
 * Returns a NULL pointer if settings fail the internal sanity check.
 */
unsigned char* toBinary( const LogBin * log );

/** @brief Convert SYS data to binary array.
 *
 * Returns a NULL pointer if settings fail the internal sanity check.
 */
unsigned char* toBinary( const SysBin * sys );

/** @} */

/** @name Deserialize the binary configuration data.
 * @{
 */

/** @brief Interpret array as GPS data.
 *
 * The array must be @c BYTE_COUNT_GPS bytes long. If it isn't, a NULL pointer
 * is returned.
 */
GpsBin* toGpsBin( const std::vector<char> & data );

/** @brief Interpret array as LOG data.
 *
 * The array must be @c BYTE_COUNT_LOG bytes long. If it isn't, a NULL pointer
 * is returned.
 */
LogBin* toLogBin( const std::vector<char> & data );

/** @brief Interpret array as SYS data.
 *
 * The array must be @c BYTE_COUNT_SYS bytes long. If it isn't, a NULL pointer
 * is returned.
 */
SysBin* toSysBin( const std::vector<char> & data );

/** @} */

/** @brief Computes the checksums for GPS.BIN.
 *
 * Computes the checksum for each block in GPS.BIN and stores the results in the
 * corresponding variables (cf. @c BlockFooter) of the @c Wbt202Gps instance.
 *
 * Details on how the checksum is computed can be found in the source of
 * @c GpsBin.h.
 */
void setChecksum( GpsBin & gps );

enum Wbt202OnOff
{
	OFF = 0,
	ON  = 1
};

enum Wbt202Status
{
	WBT202_SUCCESS = 0,
	WBT202_DEVICE_NAME_TOO_LONG,
	WBT202_DEVICE_INFO_TOO_LONG,
	WBT202_RESTART_MODE_INVALID,
	WBT202_VALUE_OUT_OF_RANGE,
	WBT202_UNKNOWN_ERROR
};

std::string getWbt202StatusString( Wbt202Status status );

Wbt202Status setDeviceName( struct Wbt202 & wbt202, std::string name = "" );
Wbt202Status setDeviceInfo( struct Wbt202 & wbt202, std::string info = "" );
Wbt202Status setRestartMode( struct Wbt202 & wbt202, RestartMode mode = AUTOMATIC_START );
Wbt202Status setShakeMode( struct Wbt202 & wbt202, Wbt202OnOff onoff = OFF );
Wbt202Status setShakeModeTimeout( struct Wbt202 & wbt202, uint16_t timeout = 300 );
Wbt202Status setPowerOffTimout( struct Wbt202 & wbt202, uint16_t timeout = 600 );
Wbt202Status setSystemOfUnits( struct Wbt202 & wbt202, SystemOfUnits unit = METRIC );
Wbt202Status setTimeZone( struct Wbt202 & wbt202, int16_t offset = 0 );



std::vector<char> readFile( const char * filename );

/** @name Overloaded operators for console output.
 * @{
 */
std::ostream& operator<<( std::ostream & os, const GpsBin & gps );
std::ostream& operator<<( std::ostream & os, const LogBin & log );
std::ostream& operator<<( std::ostream & os, const SysBin & sys );
/** @} */

void saveIni( const std::string filename, const Wbt202 & wbt202 );
void loadIni( Wbt202 & wbt202, const std::string filename );

#endif // WBT202_UTILS_H
