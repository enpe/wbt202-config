/** @file */

#ifndef CONVERSION_H
#define CONVERSION_H

#include "status.h"

#include <string>

/**
 * @brief Stores configuration of ini-file as binary device files.
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
 * @brief Stores binary device files as an human-readable ini-file.
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
