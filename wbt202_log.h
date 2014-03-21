#ifndef WBT202_LOG_H
#define WBT202_LOG_H

static const int BYTE_COUNT_LOG = 88;

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

struct Log
{
  unsigned char     magic[4];                   // 0x0  - 0x3
  unsigned char     log_mode;                   // 0x4  - 0x4
  unsigned char     log_mode_user_defined;      // 0x5  - 0x5
  unsigned char     valid_speed_lowest;         // 0x6  - 0x6  Lowest (Valid Speed for Record [0;255 km/h])
  unsigned short    valid_speed_highest;        // 0x7  - 0x8  Highest (Valid Speed for Record [5;2000 km/h])
  unsigned char     deg_point;                  // 0x9  - 0x9  Deg/point (By Heading Change, [0;179])
  unsigned short    valid_speed_low;            // 0xa  - 0xb  Valid Speed for Record [2;valid_speed_middle-1 km/h]
  unsigned short    valid_speed_middle;         // 0xc  - 0xd  Valid Speed for Record [3;valid_speed_high-1 km/h]
  unsigned short    valid_speed_high;           // 0xe  - 0xf  Valid Speed for Record [4;valid_speed_highest-1 km/h]
  unsigned short	time_interval_lowest;       // 0x10	- 0x11 Lowest (Log Time Interval, [1;3600 s])
  unsigned short	time_interval_low;          // 0x12	- 0x13 Low (Log Time Interval, [1;3600 s])
  unsigned short	time_interval_middle;       // 0x14	- 0x15 Middle (Log Time Interval, [1;3600 s])
  unsigned short	time_interval_high;         // 0x16	- 0x17 High (Log Time Interval, [1;3600 s])
  unsigned short	seconds_point;              // 0x18	- 0x19 seconds/point (By Time Interval, [1;65535 s])
  unsigned short	meters_point;               // 0x1a	- 0x1b meters/point (By Distance Interval, [1;5000 m])
  unsigned char     unknown[60];				// 0x1c - 0x57 unknown
};

#endif // WBT202_LOG_H
