#ifndef WBT202_GPS_DETAILS_H
#define WBT202_GPS_DETAILS_H

#include <stdint.h>

// TODO What are good names for the following structs? And for this header file?
// TODO What about macro-magic to reduce the code duplication in struct_0[0-6]?

struct payload_00
{
	uint8_t   unused_00[3];
	uint8_t   gpgll_enabled;
	uint8_t   unused_04[4];
};

struct struct_00
{
	uint16_t   magic;
	uint8_t    unused_01;
	uint8_t    unused_02;
	uint16_t   length;
	payload_00 payload;
	uint8_t    checksum_01;
	uint8_t    checksum_02;
};


struct payload_01
{
	// TODO MISSING IMPLEMENTATION
	// [ struct #1 ]
	// - offset in file: 0x26
	// - payload:
	//     0x00 uint8[3]   <unused>
	//     0x03 uint8      GPVTG [0=DISABLED, 1=ENABLED]
	//     0x04 uint8[4]   <unused>
};

struct struct_01
{
	uint16_t   magic;
	uint8_t    unused_01;
	uint8_t    unused_02;
	uint16_t   length;
	payload_01 payload;
	uint8_t    checksum_01;
	uint8_t    checksum_02;
};


struct payload_02
{
	// TODO MISSING IMPLEMENTATION
	// [ struct #2 ]
	// - offset in file: 0x36
	// - payload:
	//     0x00 uint8[3]   <unused>
	//     0x03 uint8      GPZDA [0=DISABLED, 1=ENABLED]
	//     0x04 uint8[4]   <unused>
};

struct struct_02
{
	uint16_t   magic;
	uint8_t    unused_01;
	uint8_t    unused_02;
	uint16_t   length;
	payload_02 payload;
	uint8_t    checksum_01;
	uint8_t    checksum_02;
};


struct payload_03
{
	// TODO MISSING IMPLEMENTATION
	// [ struct #3 ]
	// - offset in file: 0x46
	// - payload:
	//     0x00 uint8[10]  <unused>
	//     0x0A uint8      Navigation Min. SVs [3;6]
	//     0x0B uint8      <unused>
	//     0x0C uint8      Navigation Signal Min. Strength [5;50 dbHz]
	//     0x0D uint8      <unused>
	//     0x0E uint8      Initial Fix must be 3D [0=OFF, 1=ON]
	//     0x0F uint8[25]  <unused>
};

struct struct_03
{
	uint16_t   magic;
	uint8_t    unused_01;
	uint8_t    unused_02;
	uint16_t   length;
	payload_03 payload;
	uint8_t    checksum_01;
	uint8_t    checksum_02;
};


struct payload_04
{
	// TODO MISSING IMPLEMENTATION
	// [ struct #4 ]
	// - offset in file: 0x76
	// - payload:
	//     0x00 uint8[3]   <unused>
	//     0x03 uint8      Fix Mode [1=2D Only, 2=3D Only, 3=Auto 2D/3D]
	//     0x04 uint32     2D Fix Altitude (stored as mm) [0;18000 (m)]
	//     0x08 uint8[6]   <unused>
	//     0x0E uint16     PDOP Mask, [0;1000] (stored as 10 times the GUI value
	//                     (gets rid of comma))
	//     0x10 uint16     TDOP Mask, [0;1000] (stored as 10 times the GUI value
	//                     (gets rid of comma))
	//     0x12 uint16     P Accuracy Map [0;65535 (m)]
	//     0x14 uint16     T Accuracy Map [0;65535 (m)]
	//     0x16 uint8[14]  <unused>
};

struct struct_04
{
	uint16_t   magic;
	uint8_t    unused_01;
	uint8_t    unused_02;
	uint16_t   length;
	payload_04 payload;
	uint8_t    checksum_01;
	uint8_t    checksum_02;
};

struct payload_05
{
	// TODO MISSING IMPLEMENTATION
	// [ struct #5 ]
	// - offset in file: 0xA2
	// - payload:
	//     0x00 uint32     LED Blink cycle [2;10000 ms] (stored as µs)
	//     0x04 uint32     LED Off cycle [1;9999 ms] (stored as µs)
	//     0x08 uint8[12]  <unused>
};


struct struct_05
{
	uint16_t   magic;
	uint8_t    unused_01;
	uint8_t    unused_02;
	uint16_t   length;
	payload_05 payload;
	uint8_t    checksum_01;
	uint8_t    checksum_02;
};


struct payload_06
{
	// TODO MISSING IMPLEMENTATION
	// [ struct #6 ]
	// - offset in file: 0xBE
	// - payload:
	//     0x00 uint8      SBAS [0=OFF, 1=ON]
	//     0x01 uint8[7]   <unused>

};

struct struct_06
{
	uint16_t   magic;
	uint8_t    unused_01;
	uint8_t    unused_02;
	uint16_t   length;
	payload_06 payload;
	uint8_t    checksum_01;
	uint8_t    checksum_02;
};

#endif // WBT202_GPS_DETAILS_H
