#ifndef WBT202_SYS_H
#define WBT202_SYS_H

// Notes on SYS.BIN
//
// Start	End 	Type	Name
// 0x0		0x3		uchar	magic number (0x111111/286331153)
// 0x4		0x17	uchar	Device name
// 0x18		0x2b	uchar	Device info.
// 0x2c		0x36			UNKNOWN (path to newest track?)
// 0x37		0x37	uchar	Shake Mode for Power Saving [0=OFF;1=ON]
// 0x38		0x39			UNKNOWN
// 0x3a		0x3b	ushort	Shake Mode for Power Saving, timeout [1;7200 (s)]
// 0x3c		0x3d	ushort	Bluetooh/Device auto power off setting [60;3600 (s)], 0 = OFF
// 0x3e		0x41			UNKNOWN
// 0x42		0x45			Password (XOR?!)
// 0x46		0x8c			UNKNOWN
// 0x8d		0x8e	sshort	Reference time zone, fixed-point float: -150 = -1.5h
// 0x8f		0x8f			UNKNOWN
// 0x90		0x90	uchar	Reference unit [0=Metric,1=Imperial]
// 0x91		0x94			UNKNOWN

static const int BYTE_COUNT_SYS = 150;

#pragma pack(push,1)
struct Sys
{
	unsigned char	magic[4];
	unsigned char   device_name[20];
	unsigned char   device_info[20];
	unsigned char   unknown_01[11];
	unsigned char   shake_mode;
	unsigned char   unknown_02[2]; // 58
	unsigned short  shake_mode_timeout;
	unsigned short  power_off_timeout;
	unsigned char   unknown_03[4];
	unsigned char   password[4];
	unsigned char   unknown_04[71]; // 142
	signed short    time_zone;
	unsigned char   unknown_05;
	unsigned char	unit;
	unsigned char   unknown_06[4];
};
#pragma pack(pop)

#endif //  WBT202_SYS_H
