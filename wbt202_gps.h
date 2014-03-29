#ifndef WBT202_GPS_H
#define WBT202_GPS_H

// START	END		TYPE		NAME
// 0x0		0x0		uchar1		Dirty flag [0=CLEAN,1=CHANGED]
//                              GPS LED cycle [2;10K (ms)]
//                              GPS LED off-cycle [2;10K (ms)]
//                              SBAS [0=OFF,1=ON]
// 0x1		0x1		uchar		Gps Mode
// 0x2		0xa7				UNKNOWN
// 0xa8		0xab	uint		GPS LED cycle [2;10K (ms)] (stored as musec)
// 0xac		0xaf	uint		GPS LED off-cycle [2;10K (ms)] (stored as musec)
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

// - the GPS.BIN contains several structs of different sizes, easy to spot by looking for the magic header (see below)
// - values in the following description are big-endian
// - the structs look like this:
//
//  offset  size      value/description
//  0x00    uint16    magic header value 0x62B5
//  0x02    uint8     must be 0 < x < 14
//  0x03    uint8
//  0x04    uint16    N: payload length in bytes
//  0x06    uint8[N]  payload
//  0x06+N  uint8     checksum byte 1
//  0x07+N  uint8     checksum byte 2
//
// - the two checksum bytes are computed as follows:
//   - note that all summands are 8-bit, so they can (and are supposed to) overflow during the additions
//
//   uint8_t * pSrc = address of struct's first byte
//   uint16_t len = value N from the table above
//   uint8_t sum1 = pSrc[ 2 ] + pSrc[ 3 ] + ( len & 0xFF ) + ( ( len & 0xFF00 ) >> 8 );
//   uint8_t sum2 = sum1 + 3 * pSrc[ 2 ] + 2 * pSrc[ 3 ] + ( len & 0xFF );
//   for ( int i = 0; i < len; ++i )
//   {
//       sum1 += pSrc[ i + 6 ]
//       sum2 += sum1
//   }
//
//   ... or, assuming a little-endian machine and unmodified struct data (i.e. the byte stream
//   exactly as in the file), in a more concise form:
//
//   uint8_t sum1 = 0;
//   uint8_t sum2 = 0;
//   for ( int i = 0; i < len + 4; ++i )
//   {
//       sum1 += pSrc[ i + 2 ]
//       sum2 += sum1
//   }


#include <stdint.h>

static const int BYTE_COUNT_GPS = 206;

#pragma pack(push, 1)

/**
 * @brief The Wbt202Gps struct
 *
 * // TODO Move the notes from above to here (in Doxygen-format).
 */
struct Wbt202Gps
{
	uint8_t   dirty;
	uint8_t   gps_mode;
	uint8_t   unknown_01[166];
	uint16_t  led_cycle;
	uint8_t   unknown[2];
	// to be continued ...
};

#pragma pack(pop)

#endif // WBT202_GPS_H
