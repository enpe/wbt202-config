/** @file */

#ifndef CONVERSION_H
#define CONVERSION_H

#include "status.h"

#include <string>

/**
 * @brief Encodes ini-file as binary device files.
 * @param gpsFile Abs. path and name of GPS.BIN.
 * @param logFile Abs. path and name of LOG.BIN.
 * @param sysFile Abs. path and name of SYS.BIN.
 * @param iniFile Abs. path and name of the ini-file.
 * @return Status code (possibly multiple errors).
 */
int encode(
	std::string gpsFile,
	std::string logFile,
	std::string sysFile,
	std::string iniFile );

/**
 * @brief Decodes binary device files which are stored as an ini-file.
 * @param iniFile Abs. path and name of the ini-file.
 * @param gpsFile Abs. path and name of GPS.BIN.
 * @param logFile Abs. path and name of LOG.BIN.
 * @param sysFile Abs. path and name of SYS.BIN.
 * @return Status code (possibly multiple errors).
 */
int decode(
	std::string iniFile,
	std::string gpsFile,
	std::string logFile,
	std::string sysFile );

#endif // CONVERSION_H
