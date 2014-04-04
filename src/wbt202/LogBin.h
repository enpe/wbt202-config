/** @file */

#ifndef LOGBIN_H
#define LOGBIN_H

// Notes on LOG.BIN
//
// - values are stored in little-endian byte order inside the file (least
//   significant byte first)
// - values in these notes are given most significant byte first
//
// Start    Type        Name/Description
// 0x00     uint32      magic number 0x33333333
// 0x04     uint8       LOG Mode [0=User define, 1=Walk, 2=Bicycle, 3=Car]
// 0x05     uint8       User Define LOG Mode:
//                          0=Disable LOG function
//                          1=By Heading Change
//                          2=By Speed Change
//                          3=By Time Interval
//                          4=By Distance Interval
//                          5=Mix Mode (implicitly LOGMODE_MIX_HTDS)
//                          6=LOGMODE_MIX_HTS (Mix Mode only)
//                          7=LOGMODE_MIX_HTD (Mix Mode only)
//                          8=LOGMODE_MIX_HDS (Mix Mode only)
//                          9=LOGMODE_MIX_TDS (Mix Mode only)
//                          A=LOGMODE_MIX_HT (Mix Mode only)
//                          B=LOGMODE_MIX_HD (Mix Mode only)
//                          C=LOGMODE_MIX_HS (Mix Mode only)
//                          D=LOGMODE_MIX_TD (Mix Mode only)
//                          E=LOGMODE_MIX_TS (Mix Mode only)
//                          F=LOGMODE_MIX_DS (Mix Mode only)
// 0x06     uint8       Lowest (Valid Speed for Record [0;255 (km/hr)])
// 0x07     uint16      Highest (Valid Speed for Record [5;2000 (km/hr)])
// 0x09     uint8       Deg/point (By Heading Change, max=179)
// 0x0a     uint16      Low (Valid Speed for Record, [2,[0xc]-1 (km/hr)])
// 0x0c     uint16      Middle (Valid Speed for Record, [3,[0xe]-1 (km/hr)])
// 0x0e     uint16      High (Valid Speed for Record, [4,[0x7]-1 (km/hr)])
// 0x10     uint16      Lowest (Log Time Interval, [1;3600 (s)])
// 0x12     uint16      Low (Log Time Interval, [1;3600 (s)])
// 0x14     uint16      Middle (Log Time Interval, [1;3600 (s)])
// 0x16     uint16      High (Log Time Interval, [1;3600 (s)])
// 0x18     uint16      seconds/point (By Time Interval, max=65535)
// 0x1a     uint16      meters/point (By Distance Interval, max=5000)
// 0x1c                 UNKNOWN
// 0x53     uint8       always set to 1 by WBT_Tool prior to writing the file
//                        Maybe a dirty flag to indicate device restart?
// 0x54     uint32      magic number 0x44444444

#include <cstdlib>
#include <stdint.h>

static const size_t BYTE_COUNT_LOG = 88;

enum LogMode
{
	LOG_MODE_USER_DEFINED=0,
	LOG_MODE_WALK=1,
	LOG_MODE_BICYCLE=2,
	LOG_MODE_CAR=3
};

enum LogModeUserDefined
{
	LOG_MODE_DISABLED=0,
	LOG_MODE_HEADING_CHANGE=1,
	LOG_MODE_SPEED_CHANGE=2,
	LOG_MODE_TIME_INTERVAL=3,
	LOG_MODE_DISTANCE_INTERVAL=4,
	LOG_MODE_MIXED_HTDS=5,
	LOG_MODE_MIXED_HTS=6,
	LOG_MODE_MIXED_HTD=7,
	LOG_MODE_MIXED_HDS=8,
	LOG_MODE_MIXED_TDS=9,
	LOG_MODE_MIXED_HT=10,
	LOG_MODE_MIXED_HD=11,
	LOG_MODE_MIXED_HS=12,
	LOG_MODE_MIXED_TD=13,
	LOG_MODE_MIXED_TS=14,
	LOG_MODE_MIXED_DS=15
};

#pragma pack(push, 1) // Change the memory alignment but store previous state.

struct LogBin
{
	uint32_t  magic_begin;            //  0x00 - 0x03
	uint8_t   log_mode;               //  0x04 - 0x04
	uint8_t   log_mode_user_defined;  //  0x05 - 0x05
	uint8_t   valid_speed_lowest;     //  0x06 - 0x06 Lowest (Valid Speed for Record [0;255 km/h])
	uint16_t  valid_speed_highest;    //  0x07 - 0x08 Highest (Valid Speed for Record [5;2000 km/h])
	uint8_t   deg_point;              //  0x09 - 0x09 Deg/point (By Heading Change, [0;179])
	uint16_t  valid_speed_low;        //  0x0a - 0x0b Valid Speed for Record [2;valid_speed_middle-1 km/h]
	uint16_t  valid_speed_middle;     //  0x0c - 0x0d Valid Speed for Record [3;valid_speed_high-1 km/h]
	uint16_t  valid_speed_high;       //  0x0e - 0x0f Valid Speed for Record [4;valid_speed_highest-1 km/h]
	uint16_t  time_interval_lowest;   //  0x10 - 0x11 Lowest (Log Time Interval, [1;3600 s])
	uint16_t  time_interval_low;      //  0x12 - 0x13 Low (Log Time Interval, [1;3600 s])
	uint16_t  time_interval_middle;   //  0x14 - 0x15 Middle (Log Time Interval, [1;3600 s])
	uint16_t  time_interval_high;     //  0x16 - 0x17 High (Log Time Interval, [1;3600 s])
	uint16_t  seconds_point;          //  0x18 - 0x19 seconds/point (By Time Interval, [1;65535 s])
	uint16_t  meters_point;           //  0x1a - 0x1b meters/point (By Distance Interval, [1;5000 m])
	uint8_t   unknown_1C[55];         //  0x1c - 0x53 unknown
	uint8_t   unknown_53;             //  0x53 - 0x53 unknown
	uint32_t  magic_end;              //  0x54 - 0x57
};

#pragma pack(pop) // Restore previous memory alignment settings.

#ifdef COMPILER_SUPPORTS_CXX11
static_assert( sizeof( LogBin ) == BYTE_COUNT_LOG,
    "Size of LOG struct does not match the required byte count." );
#endif // COMPILER_SUPPORTS_CXX11

#endif //  LOGBIN_H
