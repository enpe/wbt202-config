#ifndef WBT202_SYS_H
#define WBT202_SYS_H

// Notes on SYS.BIN
//
// - values are stored in little-endian byte order inside the file (least significant byte first)
// - values in these notes are given most significant byte first
//
// Start    Type	    Name/Description
// 0x00     uint32      magic number 0x11111111
// 0x04     uchar[]     Device name (max. 19 bytes + terminating NULL byte)
// 0x18     uchar[]     Device info (max. 19 bytes + terminating NULL byte)
// 0x2c     uint8       GPS Re-Start
//                          1=Cold Start
//                          2=Warm Start
//                          3=Hot Start (bug in WBT_Tool 4.7 will always set this to 2)
// 0x2d     uint16      CID
// 0x2f     uint16      PID (must be 0xB202)
// 0x31     uint32      UNKNOWN, seems to be used only in export to TimeMachineX's TK2 format
// 0x35     uint16      displayed in WBT_Tool's window title as "FW_Ver:%d.0"
// 0x37     uint8       Shake Mode for Power Saving [0=OFF;1=ON]
// 0x38                 UNKNOWN
// 0x39     uint8       UNKNOWN
// 0x3a     uint16      Shake Mode for Power Saving, timeout [60;7200 (s)]
// 0x3c     uint16      Bluetooth/Device auto power off setting [60;3600 (s)], 0 = OFF
// 0x3e                 UNKNOWN
// 0x42     uint32      Password, stored as 152 * ( P + 11977 ) or as 0xFFFFFFFF if left empty
// 0x46     uchar[]     UNKNOWN, absolute path to some .TES track file
// 0x64                 UNKNOWN
// 0x8c     uint8       always set to 1 by WBT_Tool prior to writing the SYS.BIN file
//                        Maybe a dirty flag to indicate device restart?
// 0x8d     int16       Reference time zone, 100 * ( difference in hours ): e.g. -150 = -1.5h
// 0x8f     uint8       Language selected in WBT_Tool
//                          0=English
//                          1=Traditional Chinese
//                          2=Simplified Chinese
//                          3=German
//                          4=Japanese
// 0x90     uint8       Reference unit [0=Metric,1=Imperial]
// 0x91     uint32      magic number 0x22222222

#include <cstdlib>
#include <stdint.h>

static const size_t   BYTE_COUNT_SYS   = 149;
static const uint32_t DEFAULT_PASSWORD = 0xFFFFFFFF;

/**
 * @brief The DeviceStart enum
 */
enum DeviceStart
{
	NO_START=0,
	COLD_START=1,
	WARM_START=2,
	HOT_START=3
};

#pragma pack(push,1)

/**
 * @brief The Wbt202Sys struct
 *
 * // TODO Move the notes from above to here (in Doxygen-format).
 */
struct Wbt202Sys
{
	uint32_t  magic_begin;
	uint8_t   device_name[20];
	uint8_t   device_info[20];
	uint8_t   start_mode;  // Cf. DeviceStart
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

#pragma pack(pop)

#ifdef COMPILER_SUPPORTS_CXX11
static_assert( sizeof( Wbt202Sys ) == BYTE_COUNT_SYS,
	"Size of SYS struct does not match the required byte count." );
#endif // COMPILER_SUPPORTS_CXX11

#endif //  WBT202_SYS_H
