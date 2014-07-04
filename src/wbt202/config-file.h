/** @file */

#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include <wbt202/wbt202.h>

#include <string>

namespace wbt202
{

/**
 * @brief Saves device configuration as an ini-file.
 * @param filename Name of the ini-file.
 * @param wbt202   Storage location of the loaded device configuration.
 */
void saveConfigFile( const std::string filename, const Wbt202 & wbt202 );

/**
 * @brief Loads device configuration from an ini-file.
 * @param wbt202   Device configuration that will be saved to file.
 * @param filename Name of the ini-file.
 */
void loadConfigFile( Wbt202 & wbt202, const std::string filename );

} // namespace wbt202

#endif // CONFIG_FILE_H
