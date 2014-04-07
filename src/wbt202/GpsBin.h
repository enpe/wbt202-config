/** @file
 *
 * @brief Data types describing the binary file LOG.BIN.
 *
 * General notes
 * -------------
 *
 * - Values are stored in little-endian byte order inside the file
 *   (least significant byte first).
 * - Values in these notes are given most significant byte first.
 * - NOTE: the marker "<unused>" means:
 *     - these bytes are not represented by any option in the WBT_Tool
 *     - these bytes are not modified (only exception is overwrite by hard-coded
 *       default, see below)
 *     - these bytes, unless mentioned otherwise, can have arbitrary values as
 *       long as the checksum is correct
 *     -> we cannot deduce these bytes' meaning from the WBT_Tool
 *
 * Data fields
 * -----------
 *
 * | Start  | Type      | Name/Description
 * |--------|-----------|-------------------------------------------------------
 * | 0x00   | uint8     | Dirty flag, always set to 1 by WBT_Tool prior to writing the file, and set to 0 by the WBT device upon entering CDC mode (its usual operation mode for logging)
 * | 0x01   | uint8     | GPS Mode (see table below).
 * | 0x02   | uint8[]   | UNKNOWN, not used by WBT_Tool 4.6
 * | 0x16   | ...       | see detailed description of structs below
 *
 * | GPS Mode | Description
 * |----------|-------------------------
 * | 0        | High Accuracy
 * | 1        | Middle Accuracy
 * | 2        | Factory setting
 * | 3        | Middle Acquisition time
 * | 4        | Fast Acquisition time
 * | 5        | User define
 *
 * - the file contains several structs of different sizes, easy to spot by
 *   looking for the magic header (see below)
 * - these structs are 1:1 representations of UBX packets as used by the
 *   u-blox 5 chipset for communication with the WBT-202
 * - the UBX protocol is defined in [ref1, pp. 63]
 *
 * | Offset  | Size     |  Value/Description
 * |---------|----------|--------------
 * | 0x00    | uint8    |  sync char 1, magic header value 0xB5
 * | 0x01    | uint8    |  sync char 2, magic header value 0x62
 * | 0x02    | uint8    |  message class, must be 0 < x < 14
 * | 0x03    | uint8    |  message ID
 * | 0x04    | uint16   |  N: payload length in bytes
 * | 0x06    | uint8[N] |  payload
 * | 0x06+N  | uint8    |  checksum byte 1
 * | 0x07+N  | uint8    |  checksum byte 2
 *
 * - the two checksum bytes are computed as follows:
 *     - NOTE: all summands are 8-bit, so they can (and are supposed to)
 *             overflow during the additions
 *     - NOTE: We are assuming a little-endian machine and unmodified struct
 *             data, i.e. the byte stream exactly as in the file. Keep this in
 *             mind when writing for big-endian machines!
 *     - NOTE: this is the "Fletcher-16" checksum algorithm [ref2]:
 * ~~~~~~~~~~~~~~~{.cpp}
 *   uint8_t * pSrc = // address of struct's first byte
 *   uint16_t len = value N from the table above
 *   uint8_t sum1 = 0;
 *   uint8_t sum2 = 0;
 *   for ( int i = 0; i < len + 4; ++i )
 *   {
 *       sum1 += pSrc[ i + 2 ]
 *       sum2 += sum1
 *   }
 * ~~~~~~~~~~~~~~~
 *
 *
 * - details about the contents of the 7 structs inside the file:
 *     - NOTE: the byte offsets listed for the "payload" are relative to the
 *             payload's first byte, i.e. offset 0x06 in the struct
 *
 * [ struct #0 ]
 * -------------
 * - offset in file: 0x16
 * - payload:
 *     0x00 uint8[3]   <unused>
 *     0x03 uint8      GPGLL [0=DISABLED, 1=ENABLED]
 *     0x04 uint8[4]   <unused>
 *
 * [ struct #1 ]
 * -------------
 * - offset in file: 0x26
 * - payload:
 *     0x00 uint8[3]   <unused>
 *     0x03 uint8      GPVTG [0=DISABLED, 1=ENABLED]
 *     0x04 uint8[4]   <unused>
 *
 * [ struct #2 ]
 * -------------
 * - offset in file: 0x36
 * - payload:
 *     0x00 uint8[3]   <unused>
 *     0x03 uint8      GPZDA [0=DISABLED, 1=ENABLED]
 *     0x04 uint8[4]   <unused>
 *
 * [ struct #3 ]
 * -------------
 * - configures: Navigation Engine (Expert Settings)
 * - offset in file: 0x46
 * - name: CFG-NAVX5 [ref1, pp. 121]
 * - payload:
 *     0x00 uint16     Message version (must be 0)
 *     0x02 uint16     Settings selector (bitmask)
 *                         .... .... .... .x..  Apply min/max SVs settings
 *                         .... .... .... x...  Apply minimum C/N0 setting
 *                         .... .... .x.. ....  Apply initial 3D fix settings
 *                         .... ..x. .... ....  Apply GPS weeknumber rollover settings
 *     0x04 uint32     <reserved> (set to 0)
 *     0x08 uint8      <reserved> (set to 0)
 *     0x09 uint8      <reserved> (set to 0)
 *     0x0A uint8      Minimum number of satellites for navigation (#SVs)
 *     0x0B uint8      Maximum number of satellites for navigation (#SVs)
 *     0x0C uint8      Minimum satellite signal level for navigation (dbHz), "min CN/0" for short
 *     0x0D uint8      <reserved> (set to 0)
 *     0x0E uint8      Initial fix must be 3D [0=OFF, 1=ON]
 *     0x0F uint8      <reserved> (set to 0)
 *     0x10 uint8      <reserved> (set to 0)
 *     0x11 uint8      <reserved> (set to 0)
 *     0x12 uint16     GPS week rollover number, 0 means firmware default
 *     0x14 uint32     <reserved> (set to 0)
 *     0x18 uint32     <reserved> (set to 0)
 *     0x1C uint32     <reserved> (set to 0)
 *     0x20 uint32     <reserved> (set to 0)
 *     0x24 uint32     <reserved> (set to 0)
 *
 * [ struct #4 ]
 * -------------
 * - configures: Navigation Engine [ref1, pp. 25]
 * - offset in file: 0x76
 * - name: CFG-NAV5 [ref1, pp. 122]
 * - payload:
 *     0x00 uint16    Settings selector (bitmask)
 *                        .... .... .... ...x  Apply dynamic model settings
 *                        .... .... .... ..x.  Apply minimum elevation settings
 *                        .... .... .... .x..  Apply fix mode settings
 *                        .... .... .... x...  Apply DR limit settings
 *                        .... .... ...x ....  Apply position mask settings
 *                        .... .... ..x. ....  Apply time mask settings
 *                        .... .... .x.. ....  Apply static hold settings
 *     0x02 uint8     Dynamic platform model
 *                        0=Portable
 *                        2=Stationary
 *                        3=Pedestrian
 *                        4=Automotive
 *                        5=Sea
 *                        6=Airborne with <1g Acceleration
 *                        7=Airborne with <2g Acceleration
 *                        8=Airborne with <4g Acceleration
 *     0x03 uint8      Position fixing mode [1=2D Only, 2=3D Only, 3=Auto 2D/3D]
 *     0x04 int32      Fixed altitude (cm), only for "Position fixing mode" set to 1
 *     0x08 uint32     Fixed altitude variance (cm²), only for "Position fixing mode" set to 1
 *     0x0C uint8      Minimum SV elevation (deg)
 *     0x0D uint8      Dead reckoning timeout (s)
 *     0x0E uint16     PDOP Mask (stored as 10 times the GUI value)
 *     0x10 uint16     TDOP Mask (stored as 10 times the GUI value)
 *     0x12 uint16     Position Accuracy Mask (m)
 *     0x14 uint16     Time Accuracy Mask (m)
 *     0x16 uint8      Static hold threshold (cm/s)
 *     0x17 uint8      <reserved> (set to zero)
 *     0x18 uint32     <reserved> (set to zero)
 *     0x1C uint32     <reserved> (set to zero)
 *     0x20 uint32     <reserved> (set to zero)
 *
 * [ struct #5 ]
 * -------------
 * - configures: Time Pulse [ref1, pp. 9]
 * - offset in file: 0xA2
 * - name: CFG-TP [ref1, p. 107]
 * - payload:
 *     0x00 uint32     Pulse period (µs)
 *     0x04 uint32     Pulse length (µs)
 *     0x08 int8       Pulse mode [-1=Falling edge, 0=Disabled, 1=Rising edge]
 *     0x09 uint8      Time source [0=UTC time, 1=GPS time, 2=Local time]
 *     0x0A uint8      Sync mode
 *                         0=Time pulse always synchronized and only available if time is valid
 *                         1=Time pulse allowed to be asynchronized and available even when time is not valid
 *     0x0B uint8      <reserved> (set to zero)
 *     0x0C int16      Cable delay (ns)
 *     0x0E int16      RF group delay (ns), does not seem to be editable
 *     0x10 int32      User delay (ns)
 * - notes:
 *     - The u-blox GPS chip inside the WBT-202 seems to feature a dedicated
 *       timepulse pin (see http://electronics.stackexchange.com/questions/30750
 *       for why that can be a useful thing to have).
 *     - This config section allows us to change the timepulse setting, i.e. set
 *       the pulse interval, the pulse mode etc.
 *     - In the WBT-202, the timepulse pin is probably only used for making the
 *       GPS LED blink (I have not checked) -- whatever the need for a
 *       configurable LED blink cycle may be.
 *
 *          ├───┤ Pulse length
 *          ┌───┐              ┌───┐
 *       ───┘   └──────────────┘   └────────
 *          ├── Pulse period ──┤
 * 
 *     - The timepulse pin going high turns the LED off, i.e. "Pulse mode" set
 *       to "Rising edge" -> "Pulse length" is the time that the LED is off
 *
 * [ struct #6 ]
 * -------------
 * - configures: Space Based Augmentation Systems (SBAS)
 * - name: CFG-SBAS [ref1, pp. 115]
 * - offset in file: 0xBE
 * - payload:
 *     0x00 uint8      SBAS mode (bitmask)
 *                         .... ...x  Enable SBAS [0=OFF, 1=ON]
 *                         .... ..x.  Allow test mode usage (Msg 0) [0=OFF, 1=ON]
 *     0x01 uint8      SBAS usage (bitmask)
 *                         .... ...x  Ranging (use SBAS for navigation) [0=OFF, 1=ON]
 *                         .... ..x.  Apply SBAS correction data [0=OFF, 1=ON]
 *                         .... .x..  Apply integrity information [0=OFF, 1=ON]
 *     0x02 uint8      Number of search channels [0,1,2,3]
 *     0x03 uint8      scanmode2 (bitmask)
 *     0x04 uint32     scanmode1 (bitmask)
 *                         - each bit represents a PRN number, for a list see [ref1, p. 116]
 *                         - see http://www.losangeles.af.mil/library/factsheets/factsheet.asp?id=8618)
 *                         - setting all bits to 0 enables "Auto Scan"
 *
 *
 * - for a struct to pass the validity check:
 *     - the magic header value must match, and
 *     - the byte at offset 0x02 must be be 0 < x < 14, and
 *     - the computed checksum bytes must match the checksum bytes at the end of
 *       the struct
 * - if the check fails, WBT_Tool 4.6 replaces the offending struct with a
 *   hard-coded default upon application startup:
 *     - struct #0: B5 62 06 01 08 00 F0 01 00 00 00 00 00 01 01 2B
 *     - struct #1: B5 62 06 01 08 00 F0 05 00 00 00 00 00 01 05 47
 *     - struct #2: B5 62 06 01 08 00 F0 08 00 00 00 00 00 00 07 5B
 *     - struct #3: B5 62 06 23 28 00 00 00 4C 06 00 00 00 00 00 00 03 10 14 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 CA F9
 *     - struct #4: B5 62 06 24 24 00 FF FF 00 03 00 00 00 00 10 27 00 00 05 00 FA 00 FA 00 64 00 2C 01 1C 00 00 00 00 00 00 00 00 00 00 00 00 00 2C 98
 *     - struct #5: B5 62 06 07 14 00 40 42 0F 00 00 35 0C 00 01 01 00 00 32 00 00 00 00 00 00 00 27 47
 *     - struct #6: B5 62 06 16 08 00 00 03 03 00 00 00 00 00 2A B1
 *
 *
 * - the flags GPRMC, GPGGA, GPGSA, GPGSV in group "NMEA Output" cannot be
 *   changed in the GUI
 *     - none of the bytes in the file seems to affect them either
 *     - the WBT manual says they are activated by default because they are
 *       basic requirements for GPS operation
 *
 *
 * References
 * ----------
 *
 *   [ref1] u-blox AG: "u-blox 5 Receiver Description", document number
 *          GPS.G5-X-07036-G
 *   [ref2] Fletcher, J.: "An Arithmetic Checksum for Serial Transmissions,"
 *          IEEE Transactions on Communications , vol. 30, no. 1, pp. 247--252,
 *          January 1982
 */

#ifndef GPSBIN_H
#define GPSBIN_H



#include <wbt202/GpsBinBlocks.h>

#include <cstdlib>
#include <stdint.h>

/** @brief Size of LOG.BIN in bytes. */
static const size_t SIZE_GPS_BIN = 206;

/** @brief Default settings according to the WBT_Tool. */
static const uint8_t factoryGpsBin[ SIZE_GPS_BIN ] =
{
	0x01, 0x02, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb5, 0x62,
	0x06, 0x01, 0x08, 0x00, 0xf0, 0x01, 0x00, 0x01,
	0x00, 0x00, 0x00, 0x01, 0x02, 0x30, 0xb5, 0x62,
	0x06, 0x01, 0x08, 0x00, 0xf0, 0x05, 0x00, 0x01,
	0x00, 0x00, 0x00, 0x01, 0x06, 0x4c, 0xb5, 0x62,
	0x06, 0x01, 0x08, 0x00, 0xf0, 0x08, 0x00, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x08, 0x60, 0xb5, 0x62,
	0x06, 0x23, 0x28, 0x00, 0x00, 0x00, 0x4c, 0x06,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x10,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xc3, 0x37, 0xb5, 0x62,
	0x06, 0x24, 0x24, 0x00, 0xff, 0xff, 0x00, 0x03,
	0x50, 0xc3, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00,
	0x05, 0x00, 0xe6, 0x00, 0xe6, 0x00, 0x64, 0x00,
	0x2c, 0x01, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x17, 0xed, 0xb5, 0x62, 0x06, 0x07, 0x14, 0x00,
	0x40, 0x42, 0x0f, 0x00, 0x00, 0x35, 0x0c, 0x00,
	0x01, 0x01, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x27, 0x47, 0xb5, 0x62,
	0x06, 0x16, 0x08, 0x00, 0x01, 0x03, 0x03, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x2b, 0xb9
};

#pragma pack(push, 1) // Change the memory alignment but store previous state.

/** @brief Overlay for the binary data in SYS.BIN. */
struct GpsBin
{
	uint8_t   dirty;          ///< 0x00 dirty flag
	uint8_t   gps_mode;       ///< 0x01 GPS mode
	uint8_t   unknown_02[20]; ///< 0x02 <unknown>
	Block_16  block_16;       ///< 0x16 struct #0
	Block_26  block_26;       ///< 0x26 struct #1
	Block_36  block_36;       ///< 0x36 struct #2
	Block_46  block_46;       ///< 0x46 struct #3
	Block_76  block_76;       ///< 0x76 struct #4
	Block_A2  block_A2;       ///< 0xA2 struct #5
	Cfg_SBAS  cfg_sbas;       ///< 0xBE struct #6
};

#pragma pack(pop) // Restore previous memory alignment settings.

#ifdef COMPILER_SUPPORTS_CXX11
static_assert( sizeof( GpsBin ) == SIZE_GPS_BIN,
	"Size of GPS struct does not match the required byte count." );
#endif // COMPILER_SUPPORTS_CXX11

#endif // GPSBIN_H
