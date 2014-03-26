#ifndef WBT202_SYS_H
#define WBT202_SYS_H

// Notes on SYS.BIN
//
// Start	End 	Type	Name
// 0x0		0x3		uchar	magic number (0x111111/286331153)
// 0x4		0x17	uchar	Device name
// 0x18		0x2b	uchar	Device info.
// 0x2c		0x2c			GPS Re-Start [1=Cold Start, 2=Warm Start, 3=Hot Start [bug in v4.7]]
// 0x2d		0x36			UNKNOWN (path to newest track?)
// 0x37		0x37	uchar	Shake Mode for Power Saving [0=OFF;1=ON]
// 0x38		0x39			UNKNOWN
// 0x3a		0x3b	ushort	Shake Mode for Power Saving, timeout [1;7200 (s)]
// 0x3c		0x3d	ushort	Bluetooh/Device auto power off setting [60;3600 (s)], 0 = OFF
// 0x3e		0x41			UNKNOWN
// 0x42		0x45			Password (XOR?!)
// 0x46		0x8b			UNKNOWN
// 0x8c		0x8c			GPS Re-Start [1 if button selected in GUI, 0 on next device restart?]
// 0x8d		0x8e	sshort	Reference time zone, fixed-point float: -150 = -1.5h
// 0x8f		0x8f			UNKNOWN
// 0x90		0x90	uchar	Reference unit [0=Metric,1=Imperial]
// 0x91		0x94			UNKNOWN

#include <stdint.h>

static const int BYTE_COUNT_SYS = 149;

enum DeviceStart
{
	NO_START=0,
	COLD_START=1,
	WARM_START=2,
	HOT_START=3
};

#pragma pack(push,1)
struct Wbt202Sys
{
	uint8_t   magic[4];
	uint8_t   device_name[20];
	uint8_t   device_info[20];
	uint8_t   start_mode;  // Cf. DeviceStart
	uint8_t   unknown_01[10];
	uint8_t   shake_mode;
	uint8_t   unknown_02[2]; // 58
	uint16_t  shake_mode_timeout;
	uint16_t  power_off_timeout;
	uint8_t   unknown_03[4];
	uint8_t   password[4];
	uint8_t   unknown_04[70];
	uint8_t   restart_device; // Dirty flag to indicate device restart?
	int8_t    time_zone;
	uint8_t   unknown_05;
	uint8_t   unit;
	uint8_t   unknown_06[4];
};
#pragma pack(pop)

#endif //  WBT202_SYS_H
