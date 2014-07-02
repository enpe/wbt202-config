#ifndef STATUS_H
#define STATUS_H

enum Status
{
	STATUS_NO_ERROR             =   0,
	STATUS_INCORRECT_PARAMETERS =   1,
	STATUS_CONFIG_FILE_MISSING  =   2,
	STATUS_BINARIES_MISSING     =   4,
	STATUS_NO_ACTION            =   8,
	STATUS_ACTION_MISMATCH      =  16
};

void displayStatusMessages( int status );

#endif // STATUS_H
