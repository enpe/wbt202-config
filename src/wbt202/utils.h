/** @file wbt202_utils.h */

#ifndef WBT202_UTILS_H
#define WBT202_UTILS_H

#include <wbt202/wbt202.h>
#include <wbt202/status.h>

#include <iostream>
#include <vector>

namespace wbt202
{

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

/** @name Modifiers (LOG.BIN)
 * @{ */
W_Status setLogMode( LogModeUserDefined mode );
W_Status setSpeed( uint8_t lowest, uint16_t low, uint16_t middle, uint16_t high, uint16_t highest );
W_Status setTime( uint16_t lowest, uint16_t low, uint16_t middle, uint16_t high );
W_Status setDegrees( uint8_t degrees_point );
W_Status setSeconds( uint16_t seconds_point );
W_Status setMeters( uint16_t meters_point );
/** @} */

/** @name Modifiers (GPS.BIN)
 * @{ */
W_Status setGPSMode( GpsMode mode = HighAccuracy );
W_Status setSBASEnabled( bool enabled );
// gpgll
// gpvtg
// gpzda
// min_visible_satellites
// min_signal_strength
// initial_fix_3d
// fix_mode
// fix_altitude_2d
// pdop_mask
// tdop_mask
// p_accuracy_map
// t_accuracy_map
// led_blink_cycle
// led_off_cycle
// sbas_mode
// sbas_usage
// (sbas_)channels
// scanmode_02
// scanmode_01
/** @} */


/** @name Modifiers (SYS.BIN)
 * @{ */
W_Status setDeviceName( struct Wbt202 & wbt202, std::string name = "" );
W_Status setDeviceInfo( struct Wbt202 & wbt202, std::string info = "" );
W_Status setRestartMode( struct Wbt202 & wbt202, int restartMode = AUTOMATIC_START );
W_Status setShakeMode(struct Wbt202 & wbt202, bool onoff = false );
W_Status setShakeModeTimeout( struct Wbt202 & wbt202, uint16_t timeout = 300 );
W_Status setPowerOffTimout( struct Wbt202 & wbt202, uint16_t timeout = 600 );
W_Status setSystemOfUnits( struct Wbt202 & wbt202, int systemOfUnits = METRIC );
W_Status setTimeZone( struct Wbt202 & wbt202, int16_t offset = 0 );
/** @} */

std::vector<char> readFile( const char * filename );
void writeFile( const char * filename, const std::vector<unsigned char> & data );

/** @name Overloaded operators for console output.
 * @{
 */
std::ostream& operator<<( std::ostream & os, const GpsBin & gps );
std::ostream& operator<<( std::ostream & os, const LogBin & log );
std::ostream& operator<<( std::ostream & os, const SysBin & sys );
/** @} */

} // namespace wbt202

#endif // WBT202_UTILS_H
