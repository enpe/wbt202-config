#ifndef WBT202_H
#define WBT202_H

//LOG.BIN

//Start	End 	Type	Name
//0x0	0x3		magical number?
//0x4	0x4	uchar	LOG Mode [0=User define, 1=Walk, 2=Bicycle, 3=Car]
//0x5	0x5	uchar	User Define LOG Mode:
//				0=Disable LOG function,
//				3=By Time Interval,
//				4=By Distance Interval,
//				1=By Heading Change,
//				2=By Speed Change,
//				5=Mix Mode (implicitly LOGMODE_MIX_HTDS)
//				6=LOGMODE_MIX_HTS (Mix Mode only)
//				7=LOGMODE_MIX_HTD (Mix Mode only)
//				8=LOGMODE_MIX_HDS (Mix Mode only)
//				9=LOGMODE_MIX_TDS (Mix Mode only)
//				A=LOGMODE_MIX_HT (Mix Mode only)
//				B=LOGMODE_MIX_HD (Mix Mode only)
//				C=LOGMODE_MIX_HS (Mix Mode only)
//				D=LOGMODE_MIX_TD (Mix Mode only)
//				E=LOGMODE_MIX_TS (Mix Mode only)
//				F=LOGMODE_MIX_DS (Mix Mode only)
//0x6	0x6	uchar	Lowest (Valid Speed for Record (km/hr), min=0,max=255)
//0x7	0x8	ushort	Highest (Valid Speed for Record (km/hr), min=5,max=2000)
//0x9	0x9	uchar	Deg/point (By Heading Change, max=179)
//0xa	0xb	ushort	Low (Valid Speed for Record (km/hr), min=2,max=[0xc]-1)
//0xc	0xd	ushort	Middle (Valid Speed for Record (km/hr), min=3,max=[0xe]-1)
//0xe	0xf	ushort	High (Valid Speed for Record (km/hr), min=4,max=[0x7]-1)
//0x10	0x11	ushort	Lowest (Log Time Interval (second), min=1,max=3600)
//0x12	0x13	ushort	Low (Log Time Interval (second), min=1,max=3600)
//0x14	0x15	ushort	Middle (Log Time Interval (second), min=1,max=3600)
//0x16	0x17	ushort	High (Log Time Interval (second), min=1,max=3600)
//0x18	0x19	ushort	seconds/point (By Time Interval, max=65535)`
//0x1a	0x1b	ushort	meters/point (By Distance Interval, max=5000)
//0x1c	0x57		UNKNOWN

enum LogMode
{
  LOG_MODE_USER_DEFINED=0,
  LOG_MODE_WALK=1,
  LOG_MODE_BICYCLE=2,
  LOG_MODE_CAR=3
};

enum UserDefinedLogMode
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
  int           magic;
  unsigned char log_mode;
  unsigned char log_mode_user_defined;
  unsigned char valid_speed_lowest; // [0;255]
  unsigned short  valid_speed_highest;
  //0x7	0x8	ushort	Highest (Valid Speed for Record (km/hr), min=5,max=2000)
  //0x9	0x9	uchar	Deg/point (By Heading Change, max=179)
  //0xa	0xb	ushort	Low (Valid Speed for Record (km/hr), min=2,max=[0xc]-1)
  //0xc	0xd	ushort	Middle (Valid Speed for Record (km/hr), min=3,max=[0xe]-1)
  //0xe	0xf	ushort	High (Valid Speed for Record (km/hr), min=4,max=[0x7]-1)
  //0x10	0x11	ushort	Lowest (Log Time Interval (second), min=1,max=3600)
  //0x12	0x13	ushort	Low (Log Time Interval (second), min=1,max=3600)
  //0x14	0x15	ushort	Middle (Log Time Interval (second), min=1,max=3600)
  //0x16	0x17	ushort	High (Log Time Interval (second), min=1,max=3600)
  //0x18	0x19	ushort	seconds/point (By Time Interval, max=65535)`
  //0x1a	0x1b	ushort	meters/point (By Distance Interval, max=5000)
  unsigned char unknown[78];
};

#endif // WBT202_H
