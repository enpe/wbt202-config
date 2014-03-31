#ifndef WBT202_GPS_DETAILS_H
#define WBT202_GPS_DETAILS_H

#include <stdint.h>

// TODO What are good names for the following structs? And for this header file?
// TODO Should the payload_0*-structs be inlined into the struct_0*-structs?
// TODO What about macro-magic to reduce the code duplication in struct_0[0-6]?

#pragma pack(push, 1) // Change the memory alignment but store previous state.

#if 0
struct BlockHeader
{
	uint16_t   magic;       ///< 0x00    uint16    magic header value 0x62B5
	uint8_t    unused_01;   ///< 0x02    uint8     <unused>, must be 0 < x < 14
	uint8_t    unused_02;   ///< 0x03    uint8     <unused>
	uint16_t   length;      ///< 0x04    uint16    N: payload length in bytes
};

struct BlockFooter
{
	uint8_t    checksum_01; ///< 0x06+N  uint8     checksum byte 1
	uint8_t    checksum_02; ///< 0x07+N  uint8     checksum byte 2
};

struct Block_16
{
	BlockHeader header;

	// Payload
	uint8_t   unused_00[3];  ///< 0x00 <unused>
	uint8_t   gpgll;         ///< 0x03 GPGLL [0=DISABLED, 1=ENABLED]
	uint8_t   unused_04[4];  ///< 0x04 <unused>

	BlockFooter footer;
};

#else
struct Payload_16
{
	uint8_t   unused_00[3];  ///< 0x00 <unused>
	uint8_t   gpgll;         ///< 0x03 GPGLL [0=DISABLED, 1=ENABLED]
	uint8_t   unused_04[4];  ///< 0x04 <unused>
};

struct Block_16
{
	uint16_t   magic;       ///< 0x00    uint16    magic header value 0x62B5
	uint8_t    unused_01;   ///< 0x02    uint8     <unused>, must be 0 < x < 14
	uint8_t    unused_02;   ///< 0x03    uint8     <unused>
	uint16_t   length;      ///< 0x04    uint16    N: payload length in bytes
	Payload_16 payload;     ///< 0x06    uint8[N]  payload
	uint8_t    checksum_01; ///< 0x06+N  uint8     checksum byte 1
	uint8_t    checksum_02; ///< 0x07+N  uint8     checksum byte 2
};
#endif


struct Payload_26
{
	uint8_t   unused_00[3]; ///< 0x00 <unused>
	uint8_t   gpvtg;        ///< 0x03 GPVTG [0=DISABLED, 1=ENABLED]
	uint8_t   unused_04[4]; ///< 0x04 <unused>
};

struct Block_26
{
	uint16_t   magic;       ///< 0x00    uint16    magic header value 0x62B5
	uint8_t    unused_01;   ///< 0x02    uint8     <unused>, must be 0 < x < 14
	uint8_t    unused_02;   ///< 0x03    uint8     <unused>
	uint16_t   length;      ///< 0x04    uint16    N: payload length in bytes
	Payload_26 payload;     ///< 0x06    uint8[N]  payload
	uint8_t    checksum_01; ///< 0x06+N  uint8     checksum byte 1
	uint8_t    checksum_02; ///< 0x07+N  uint8     checksum byte 2
};


struct Payload_36
{
	uint8_t   unused_00[3];  ///< 0x00 <unused>
	uint8_t   gpzda;         ///< 0x03 GPZDA [0=DISABLED, 1=ENABLED]
	uint8_t   unused_04[4];  ///< 0x04 <unused>
};

struct Block_36
{
	uint16_t   magic;       ///< 0x00    uint16    magic header value 0x62B5
	uint8_t    unused_01;   ///< 0x02    uint8     <unused>, must be 0 < x < 14
	uint8_t    unused_02;   ///< 0x03    uint8     <unused>
	uint16_t   length;      ///< 0x04    uint16    N: payload length in bytes
	Payload_36 payload;     ///< 0x06    uint8[N]  payload
	uint8_t    checksum_01; ///< 0x06+N  uint8     checksum byte 1
	uint8_t    checksum_02; ///< 0x07+N  uint8     checksum byte 2
};


struct Payload_46
{
	uint8_t   unused_00[10];          ///< 0x00 <unused>
	uint8_t   min_visible_satellites; ///< 0x0A Navigation Min. SVs [3;6]
	uint8_t   unused_0B;              ///< 0x0B <unused>
	uint8_t   min_signal_strength;    ///< 0x0C Navigation Signal Min. Strength [5;50 dbHz]
	uint8_t   unused_0D;              ///< 0x0D <unused>
	uint8_t   initial_fix_3d;         ///< 0x0E Initial Fix must be 3D [0=OFF, 1=ON]
	uint8_t   unused_0F[25];          ///< 0x0F <unused>
};

struct Block_46
{
	uint16_t   magic;       ///< 0x00    uint16    magic header value 0x62B5
	uint8_t    unused_01;   ///< 0x02    uint8     <unused>, must be 0 < x < 14
	uint8_t    unused_02;   ///< 0x03    uint8     <unused>
	uint16_t   length;      ///< 0x04    uint16    N: payload length in bytes
	Payload_46 payload;     ///< 0x06    uint8[N]  payload
	uint8_t    checksum_01; ///< 0x06+N  uint8     checksum byte 1
	uint8_t    checksum_02; ///< 0x07+N  uint8     checksum byte 2
};


struct Payload_76
{
	uint8_t   unused_00[3];    ///< 0x00 <unused>
	uint8_t   fix_mode;        ///< 0x03 Fix Mode [1=2D Only, 2=3D Only, 3=Auto 2D/3D]
	uint32_t  fix_altitude_2d; ///< 0x04 2D Fix Altitude (stored as mm) [0;18000 (m)]
	uint8_t   unused_08[6];    ///< 0x08 <unused>
	uint16_t  pdop_mask;       ///< 0x0E PDOP Mask, floor(10*[0;1000])
	uint16_t  tdop_mask;       ///< 0x10 TDOP Mask, floor(10*[0;1000])
	uint16_t  p_accuracy_map;  ///< 0x12 P Accuracy Map [0;65535 (m)]
	uint16_t  t_accuracy_map;  ///< 0x14 T Accuracy Map [0;65535 (m)]
	uint8_t   unused_16[14];   ///< 0x16 <unused>
};

struct Block_76
{
	uint16_t   magic;       ///< 0x00    uint16    magic header value 0x62B5
	uint8_t    unused_01;   ///< 0x02    uint8     <unused>, must be 0 < x < 14
	uint8_t    unused_02;   ///< 0x03    uint8     <unused>
	uint16_t   length;      ///< 0x04    uint16    N: payload length in bytes
	Payload_76 payload;     ///< 0x06    uint8[N]  payload
	uint8_t    checksum_01; ///< 0x06+N  uint8     checksum byte 1
	uint8_t    checksum_02; ///< 0x07+N  uint8     checksum byte 2
};

struct Payload_A2
{
	uint32_t  led_blink_cycle; ///< 0x00 LED Blink cycle [2;10000 ms] (stored as µs)
	uint32_t  led_off_cycle;   ///< 0x04 LED Off cycle [1;9999 ms] (stored as µs)
	uint8_t   unused_08[12];   ///< 0x08 <unused>
};


struct Block_A2
{
	uint16_t   magic;       ///< 0x00    uint16    magic header value 0x62B5
	uint8_t    unused_01;   ///< 0x02    uint8     <unused>, must be 0 < x < 14
	uint8_t    unused_02;   ///< 0x03    uint8     <unused>
	uint16_t   length;      ///< 0x04    uint16    N: payload length in bytes
	Payload_A2 payload;     ///< 0x06    uint8[N]  payload
	uint8_t    checksum_01; ///< 0x06+N  uint8     checksum byte 1
	uint8_t    checksum_02; ///< 0x07+N  uint8     checksum byte 2
};


struct Payload_BE
{
	uint8_t   sbas;         ///< 0x00 SBAS [0=OFF, 1=ON]
	uint8_t   unused_01[7]; ///< 0x01 <unused>
};

struct Block_BE
{
	uint16_t   magic;       ///< 0x00    uint16    magic header value 0x62B5
	uint8_t    unused_01;   ///< 0x02    uint8     <unused>, must be 0 < x < 14
	uint8_t    unused_02;   ///< 0x03    uint8     <unused>
	uint16_t   length;      ///< 0x04    uint16    N: payload length in bytes
	Payload_BE payload;     ///< 0x06    uint8[N]  payload
	uint8_t    checksum_01; ///< 0x06+N  uint8     checksum byte 1
	uint8_t    checksum_02; ///< 0x07+N  uint8     checksum byte 2
};

#pragma pack(pop) // Restore previous memory alignment settings.

#endif // WBT202_GPS_DETAILS_H
