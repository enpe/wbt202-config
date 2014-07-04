/** @file */

#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include <wbt202/wbt202.h>

#include <string>

void saveConfigFile( const std::string filename, const Wbt202 & wbt202 );
void loadConfigFile( Wbt202 & wbt202, const std::string filename );

#endif // CONFIG_FILE_H
