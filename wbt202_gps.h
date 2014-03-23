#ifndef WBT202_GPS_H
#define WBT202_GPS_H

// START	END		TYPE		NAME
// 0x0		0x0		uchar1		Dirty flag [0=CLEAN,1=CHANGED]
//                              GPS LED cycle [2;10K (ms)]
//                              GPS LED off-cycle [2;10K (ms)]
//                              SBAS [0=OFF,1=ON]
// 0x1		0x1		uchar		Gps Mode
// 0x2		0xa7				UNKNOWN
// 0xa8		0xa9	uchar2		GPS LED cycle [2;10K (ms)]
// 0xaa		0xab				UNKNOWN
// 0xac		0xae	uchar3		GPS LED off-cycle [2;10K (ms)]
// 0xaf		0xbb				UNKNOWN
// 0xbc		0xbd	uchar2		CHECKSUM ?!?
//                              GPS LED cycle [2;10K (ms)] +
//                              GPS LED off-cycle [2;10K (ms)]
// 0xbe		0xc3				UNKNOWN
// 0xc4		0xc4	uchar		SBAS [0=OFF,1=ON]
// 0xc5		0xcb				UNKNOWN
// 0xcc		0xcd				SBAS [45354=OFF,47403=ON]

// GPVTG	0x2f [0=DISABLED, 1=ENABLED], 0x34 0x35 ushort [18181=DISABLED,19462=ENABLED]
// GPZDA	0x3f [0=DISABLED, 1=ENABLED], 0x44 0x45 ushort [23303=DISABLED,24584=ENABLED]
// GPGLL	0x1f [0=DISABLED, 1=ENABLED], 0x34 0x35 ushort [11009=DISABLED,12290=ENABLED]
#endif // WBT202_GPS_H
