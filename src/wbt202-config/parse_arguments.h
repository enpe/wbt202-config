/** @file */

#ifndef PARSE_ARGUMENTS_H
#define PARSE_ARGUMENTS_H

#include "command.h"

/**
 * @brief Parses command-line options and generates a command template from it.
 * @param argc The argc from main( int argc, ... ).
 * @param argv The argv from main( int argc, char ** argv ).
 * @return In-/output filenames and requested action name.
 */
Command parseArguments( int argc, char ** argv );

#endif // PARSE_ARGUMENTS_H
