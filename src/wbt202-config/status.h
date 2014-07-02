/** @file */

#ifndef STATUS_H
#define STATUS_H

/** @brief Error codes. */
enum Status
{
	STATUS_NO_ERROR             =     0,
	STATUS_INCORRECT_PARAMETERS =     1,
	STATUS_CONFIG_FILE_MISSING  =     2,
	STATUS_BINARIES_MISSING     =     4,
	STATUS_NO_ACTION            =     8,
	STATUS_ACTION_MISMATCH      =    16,
	STATUS_UNKNOWN_ERROR        = 65536
};

/**
 * @brief Converts the value of status variable in human-readable messages.
 * @param status Variable containing error codes.
 */
void displayStatusMessages( int status );

#endif // STATUS_H
