#ifndef WBT202_UTILS_H
#define WBT202_UTILS_H

#include <wbt202.h>

#include <iostream>


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

Sys* deserializeSys( unsigned char *data );

std::ostream& operator<<( std::ostream & os, const Log & log );
std::ostream& operator<<( std::ostream & os, const Sys & sys );
#endif // WBT202_UTILS_H
