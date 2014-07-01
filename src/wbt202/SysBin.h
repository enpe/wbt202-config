/** @file
 *
 * @brief Data types describing the binary file SYS.BIN.
 *
 * General notes
 * -------------
 *
 * - Values are stored in little-endian byte order inside the file
 *   (least significant byte first).
 * - Values in these notes are given most significant byte first.
 *
 * Data fields
 * -----------
 *
 * | Start  |  Type     | Name/Description
 * |--------|-----------|-------------------------------------------------------
 * | 0x00   | uint32    | magic number 0x11111111
 * | 0x04   | uchar[]   | Device name (max. 19 bytes + terminating NULL byte)
 * | 0x18   | uchar[]   | Device info (max. 19 bytes + terminating NULL byte)
 * | 0x2c   | uint8     | GPS Re-Start (1=Cold Start, 2=Warm Start, 3=Hot Start) (bug in WBT_Tool 4.7 will always set "Hot Start" to 2)
 * | 0x2d   | uint16    | CID
 * | 0x2f   | uint16    | PID (must be 0xB202)
 * | 0x31   | uint32    | Device serial number, set to 8271 by the WBT device upon entering CDC mode (its usual operation mode for logging)
 * | 0x35   | uint16    | Device firmware version, displayed in WBT_Tool's window title as "FW_Ver:%d.0"
 * | 0x37   | uint8     | Shake Mode for Power Saving (0=OFF;1=ON)
 * | 0x38   | uint8     | UNKNOWN
 * | 0x39   | uint8     | UNKNOWN
 * | 0x3a   | uint16    | Shake Mode for Power Saving, timeout (60;7200 (s))
 * | 0x3c   | uint16    | Bluetooth/Device auto power off setting (60;3600 (s)), 0 = OFF
 * | 0x3e   | uchar[4]  | UNKNOWN
 * | 0x42   | uint32    | Password, stored as 152 * ( P + 11977 ) or as 0xFFFFFFFF if left empty
 * | 0x46   | uchar[30] | Absolute path to the latest .TES track file the device created, set by the device
 * | 0x64   | uchar[40] | UNKNOWN
 * | 0x8c   | uint8     | Dirty flag, always set to 1 by WBT_Tool prior to writing the file, and set to 0 by the WBT device upon entering CDC mode (its usual operation mode for logging)
 * | 0x8d   | int16     | Reference time zone, 100 * ( difference in hours ): e.g. -150 = -1.5h, range: [-14h, +14h]
 * | 0x8f   | uint8     | Language selected in WBT_Tool (0=English, 1=Traditional Chinese, 2=Simplified Chinese, 3=German, 4=Japanese)
 * | 0x90   | uint8     | Reference unit (0=Metric,1=Imperial)
 * | 0x91   | uint32    | Magic number 0x22222222
 */

#ifndef SYSBIN_H
#define SYSBIN_H

#include <cstdlib>
#include <stdint.h>

/** @brief Size of SYS.BIN in bytes. */
static const size_t   SIZE_SYS_BIN = 149;

/** @brief Default value to indicate that no password has been set. */
static const uint32_t NO_PASSWORD_SET = 0xFFFFFFFF;

/** @brief Default settings according to the WBT_Tool. */
static const uint8_t factorSysBin[ SIZE_SYS_BIN ] =
{
	0x11, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf7, 0x15, 0x02,
	0xb2, 0x4f, 0x20, 0x00, 0x00, 0x11, 0x00, 0x00,
	0x00, 0x01, 0x2c, 0x01, 0x58, 0x02, 0x00, 0x00,
	0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x5c, 0x57,
	0x42, 0x54, 0x32, 0x30, 0x32, 0x5c, 0x32, 0x30,
	0x31, 0x34, 0x30, 0x33, 0x33, 0x30, 0x5c, 0x31,
	0x33, 0x5f, 0x31, 0x34, 0x5f, 0x33, 0x36, 0x2e,
	0x74, 0x65, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x22, 0x22, 0x22, 0x22
};

/** @brief Types of restarts. */
enum RestartMode
{
	AUTOMATIC_START=0,
	COLD_START=1,
	WARM_START=2,
	HOT_START=3
};

enum SystemOfUnits
{
	METRIC = 0,
	IMPERIAL = 1
};

#pragma pack(push, 1) // Change the memory alignment but store previous state.

/** @brief Overlay for the binary data in SYS.BIN. */
struct SysBin
{
	uint32_t  magic_begin;
	uint8_t   device_name[20];
	uint8_t   device_info[20];
	uint8_t   restart_mode;  // Cf. DeviceStart
	uint16_t  cid;
	uint16_t  pid;
	uint32_t  unknown_31;
	uint16_t  unknown_35;
	uint8_t   shake_mode;
	uint8_t   unknown_38;
	uint8_t   unknown_39;
	uint16_t  shake_mode_timeout;
	uint16_t  power_off_timeout;
	uint8_t   unknown_3E[4];
	uint32_t  password;
	uint8_t   unknown_46[30];
	uint8_t   unknown_64[40];
	uint8_t   unknown_8C;
	int16_t   time_zone;
	uint8_t   gui_language;
	uint8_t   unit;
	uint32_t  magic_end;
};

#pragma pack(pop) // Restore previous memory alignment settings.

#ifdef COMPILER_SUPPORTS_CXX11
static_assert( sizeof( SysBin ) == SIZE_SYS_BIN,
	"Size of SYS struct does not match the required byte count." );
#endif // COMPILER_SUPPORTS_CXX11

#endif //  SYSBIN_H
