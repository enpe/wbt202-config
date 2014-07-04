/** @file */

#ifndef WBT202_STATUS_H
#define WBT202_STATUS_H

#include <string>

namespace wbt202
{

enum W_Status
{
	W_NO_ERROR             =     0,
	W_DEVICE_NAME_TOO_LONG =     1,
	W_DEVICE_INFO_TOO_LONG =     2,
	W_RESTART_MODE_INVALID =     4,
	W_VALUE_OUT_OF_RANGE   =     8,
	W_UNKNOWN_ERROR        = 65536
};

void displayStatusMessages( int status );

} // namespace wbt202

#endif // WBT202_STATUS_H
