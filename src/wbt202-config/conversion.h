#ifndef CONVERSION_H
#define CONVERSION_H

#include "status.h"

#include <string>

Status encode(
	std::string gpsFile,
	std::string logFile,
	std::string sysFile,
	std::string iniFile );

Status decode(
	std::string iniFile,
	std::string gpsFile,
	std::string logFile,
	std::string sysFile );

#endif // CONVERSION_H
