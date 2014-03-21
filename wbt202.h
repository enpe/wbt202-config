#ifndef WBT202_H
#define WBT202_H

#include <wbt202_gps.h>
#include <wbt202_log.h>
#include <wbt202_sys.h>

/**
 * @brief serializeLog
 * @param log
 * @return
 */
unsigned char* serializeLog( const Log * log );

/**
 * @brief deserializeLog
 * @param data
 * @return
 */
Log* deserializeLog( unsigned char *data );



#endif // WBT202_H
