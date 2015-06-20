/** @file wbt202.h */

#ifndef WBT202_H
#define WBT202_H

#include <wbt202/GpsBin.h>
#include <wbt202/LogBin.h>
#include <wbt202/SysBin.h>

struct Wbt202
{
	GpsBin gps;
	LogBin log;
	SysBin sys;
};

#endif // WBT202_H
