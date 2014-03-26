#ifndef WBT202_UTILS_H
#define WBT202_UTILS_H

#include <wbt202.h>

#include <iostream>

/**
 * @brief serializeLog
 * @param log
 * @return
 */
unsigned char* serializeLog( const Wbt202Log * log );

/**
 * @brief deserializeLog
 * @param data
 * @return
 */
Wbt202Log* deserializeLog( unsigned char *data );

Wbt202Sys* deserializeSys( unsigned char *data );

std::ostream& operator<<( std::ostream & os, const Wbt202Log & log );
std::ostream& operator<<( std::ostream & os, const Wbt202Sys & sys );
#endif // WBT202_UTILS_H
