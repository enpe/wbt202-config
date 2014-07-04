/** @file wbt202.h */

#ifndef WBT202_H
#define WBT202_H

#include <wbt202/gps.h>
#include <wbt202/log.h>
#include <wbt202/sys.h>

namespace wbt202
{

struct Wbt202
{
	GpsBin gps;
	LogBin log;
	SysBin sys;
};

} // namespace wbt202

#endif // WBT202_H
