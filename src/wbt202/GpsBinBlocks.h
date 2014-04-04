/** @file */

#ifndef GPSBINBLOCKS_H
#define GPSBINBLOCKS_H

#include <stdint.h>

#pragma pack(push, 1)

/** @brief Contains variables that appear in all blocks before their payload. */
struct BlockHeader
{
	uint8_t    sync_01;     ///< 0x00 sync char 1, magic header value 0xB5
	uint8_t    sync_02;     ///< 0x01 sync char 2, magic header value 0x62
	uint8_t    msg_class;   ///< 0x02 message class, must be 0 < x < 14
	uint8_t    msg_id;      ///< 0x03 message ID
	uint16_t   length;      ///< 0x04 N: payload length in bytes
};

/** @brief Contains variables that appear in all blocks after their payload. */
struct BlockFooter
{
	uint8_t    checksum_01; ///< 0x06+N checksum byte 1
	uint8_t    checksum_02; ///< 0x07+N checksum byte 2
};

struct Block_16
{
	BlockHeader header;

	// Payload
	uint8_t   unused_00[3];  ///< 0x00 <unused>
	uint8_t   gpgll;         ///< 0x03 GPGLL [0=DISABLED, 1=ENABLED]
	uint8_t   unused_04[4];  ///< 0x04 <unused>

	BlockFooter footer;

	Block_16();
};

struct Block_26
{
	BlockHeader header;

	// Payload
	uint8_t   unused_00[3]; ///< 0x00 <unused>
	uint8_t   gpvtg;        ///< 0x03 GPVTG [0=DISABLED, 1=ENABLED]
	uint8_t   unused_04[4]; ///< 0x04 <unused>

	BlockFooter footer;
};

struct Block_36
{
	BlockHeader header;

	// Payload
	uint8_t   unused_00[3];  ///< 0x00 <unused>
	uint8_t   gpzda;         ///< 0x03 GPZDA [0=DISABLED, 1=ENABLED]
	uint8_t   unused_04[4];  ///< 0x04 <unused>

	BlockFooter footer;
};

struct Block_46
{
	BlockHeader header;

	// Payload
	uint8_t   unused_00[10];          ///< 0x00 <unused>
	uint8_t   min_visible_satellites; ///< 0x0A Navigation Min. SVs [3;6]
	uint8_t   unused_0B;              ///< 0x0B <unused>
	uint8_t   min_signal_strength;    ///< 0x0C Navigation Signal Min. Strength [5;50 dbHz]
	uint8_t   unused_0D;              ///< 0x0D <unused>
	uint8_t   initial_fix_3d;         ///< 0x0E Initial Fix must be 3D [0=OFF, 1=ON]
	uint8_t   unused_0F[25];          ///< 0x0F <unused>

	BlockFooter footer;
};

struct Block_76
{
	BlockHeader header;

	// Payload
	uint8_t   unused_00[3];    ///< 0x00 <unused>
	uint8_t   fix_mode;        ///< 0x03 Fix Mode [1=2D Only, 2=3D Only, 3=Auto 2D/3D]
	uint32_t  fix_altitude_2d; ///< 0x04 2D Fix Altitude (stored as mm) [0;18000 (m)]
	uint8_t   unused_08[6];    ///< 0x08 <unused>
	uint16_t  pdop_mask;       ///< 0x0E PDOP Mask, floor(10*[0;1000])
	uint16_t  tdop_mask;       ///< 0x10 TDOP Mask, floor(10*[0;1000])
	uint16_t  p_accuracy_map;  ///< 0x12 P Accuracy Map [0;65535 (m)]
	uint16_t  t_accuracy_map;  ///< 0x14 T Accuracy Map [0;65535 (m)]
	uint8_t   unused_16[14];   ///< 0x16 <unused>

	BlockFooter footer;
};

struct Block_A2
{
	BlockHeader header;

	// Payload
	uint32_t  led_blink_cycle; ///< 0x00 LED Blink cycle [2;10000 ms] (stored as µs)
	uint32_t  led_off_cycle;   ///< 0x04 LED Off cycle [1;9999 ms] (stored as µs)
	uint8_t   unused_08[12];   ///< 0x08 <unused>

	BlockFooter footer;
};

struct Cfg_SBAS
{
	BlockHeader header;

	// Payload
	uint8_t   sbas_mode;   ///< 0x00 SBAS [0=OFF, 1=ON] (cf. notes for details)
	uint8_t   sbas_usage;  ///< 0x01 SBAS usage (cf. notes for details)
	uint8_t   channels;    ///< 0x02 Number of search channels [0,1,2,3]
	uint8_t   scanmode_02; ///< 0x03 scanmode2 (bitmask) (cf. notes for details)
	uint32_t  scanmode_01; ///< 0x03 scanmode1 (bitmask) (cf. notes for details)

	BlockFooter footer;
};

/** @name Sanity checks for the internal structs of GPS.BIN.
 * @{
 */
bool check( Block_16 & block );
bool check( Block_26 & block );
bool check( Block_36 & block );
bool check( Block_46 & block );
bool check( Block_76 & block );
bool check( Block_A2 & block );
bool check( Cfg_SBAS & block );
/** @} */
#pragma pack(pop)

#endif // GPSBINBLOCKS_H
