/** @file */

#ifndef USAGE_H
#define USAGE_H

#include <string>

/**
 * @brief Displays usage instructions.
 * @param argv0 The name of the executable (usually argv[0], cf. main(...)).
 */
void displayUsage( std::string argv0 = "wbt202-config" );

/** @brief Displays the version tag, CVS revision, and build date. */
void displayVersion();

#endif // USAGE_H
