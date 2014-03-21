#ifndef WBT202_SYS_H
#define WBT202_SYS_H

// Notes on SYS.BIN
//
// Start	End 	Type	Name
// 0x0		0x3		uchar	magic	number? (FFFF)
// 0x4		0x16	string	Device name
// 0x17		0x17	uchar	\0
// 0x18		0x2a	string	Device info.
// 0x2b		0x2b	uchar	\0
// 0x2c		0x36	UNKNOWN
// 0x37		0x38	ushort	Shake Mode for Power Saving (ON/OFF,1/0)
// 0x39		0x39	uchar	1 [unknown]
// 0x3a		0x3b	ushort	Shake Mode for Power Saving [1;120]
// 0x3b		0x3c	ushort	Bluetooh/Device auto power off setting [0;3600], 0 = OFF
// 0x3e		0x8c	UNKNOWN
// 0x42		0x45			Password
// 0x46		0x8c	UNKNOWN
// 0x8d		0x8e	int		Reference zone, time zone, fixed-point float: 150 = 1.5h
// 0x8f		0x8f	uchar	0 [unknown]
// 0x90		0x90	uchar	Reference unit [Metric,Imperial]
// 0x91		0x94	UNKNOWN

struct Sys
{
	unsigned char magic[4];
	unsigned char device_name[20];
	unsigned char device_info[20];
};

#endif //  WBT202_SYS_H
