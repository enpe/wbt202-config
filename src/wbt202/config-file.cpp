#include "config-file.h"
#include "wbt202_utils.h"
#include "password.h"

#include <SimpleIni.h>

#include <cassert>
#include <fstream>
#include <sstream>


void saveConfigFile( const std::string filename, const Wbt202 & wbt202 )
{
	// TODO What is a good data structure to represent the data fields, their description, comments, units, range, etc.?
	// TODO Add checks before writing the data to the file.
	// TODO What are the relevant field that we want to have in the ini-files?
	// TODO Return value of this function: bool vs. enum?

	CSimpleIniA ini;

	const GpsBin & gps = wbt202.gps;
	const LogBin & log = wbt202.log;

	// SYS.BIN
	const SysBin & sys = wbt202.sys;
	std::string device_name = "";
	std::string device_info = "";
	std::string password    = "";

	// Check if a device name has been set.
	if ( sys.device_name[0] != '\0' )
		device_name = reinterpret_cast<const char*>( sys.device_name );

	// Check if a device description has been set.
	if ( sys.device_info[0] != '\0' )
		device_info = reinterpret_cast<const char*>( sys.device_info );

	// Check if a password has been set.
	if ( enabledPassword( sys.password ) )
	{
		uint32_t decoded = decodePassword( sys.password );
		assert( sys.password == encodePassword( decoded ) );

		std::ostringstream oss;
		oss << decodePassword( sys.password );

		password = oss.str();
	}

	ini.SetValue(     "GPS", NULL,                   NULL,                   "# GPS-specific settings." );
	// TODO continue ...

	ini.SetValue(     "LOG", NULL,                   NULL,                   "# LOG-specific settings." );
	// TODO continue ...

	ini.SetValue(     "SYS", NULL,                   NULL,                   "# Device-specific settings." );
	ini.SetValue(     "SYS", "device_name",          device_name.c_str(),    "# Name of the device when connected to the computer using the mass storage mode (max. 19 characters)." );
	ini.SetValue(     "SYS", "device_info",          device_info.c_str(),    "# A short description of the device (max. 19 characters)." );
	ini.SetLongValue( "SYS", "restart_mode",         sys.restart_mode,       "# Mode used to get a first fix on the next start of the device." );
	ini.SetLongValue( "SYS", "shake_mode",           sys.shake_mode,         "# Activate the tracker when shaking the device." );
	ini.SetLongValue( "SYS", "shake_mode_timeout",   sys.shake_mode_timeout, "# Time out for the deactivation of the device, if it is not moved (in s/h/...)." );
	ini.SetValue(     "SYS", "password",             password.c_str(),       "# Password. Its use is not suggested ..." );
	ini.SetLongValue( "SYS", "time_zone",            sys.time_zone,          "# Offset in hours from UTC to your local time zone." );
	ini.SetLongValue( "SYS", "unit",                 sys.unit,               "# Units: metric or imperial." );

	ini.SaveFile( filename.c_str(), true );
}

void loadConfigFile( Wbt202 & wbt202, const std::string filename )
{
	CSimpleIniA ini;
	SI_Error status = ini.LoadFile( filename.c_str() );

	assert( status == SI_OK );
	if ( status != SI_OK )
	{
		std::cerr << "Could not load ini-file <" << filename << ">." << std::endl;
		return;
	}

	setDeviceName(       wbt202, ini.GetValue(     "SYS", "device_name",        ""              ) );
	setDeviceInfo(       wbt202, ini.GetValue(     "SYS", "device_info",        ""              ) );
	setRestartMode(      wbt202, ini.GetLongValue( "SYS", "restart_mode",       AUTOMATIC_START ) );
	setShakeMode(        wbt202, ini.GetBoolValue( "SYS", "shake_mode",         false           ) );
	setShakeModeTimeout( wbt202, ini.GetLongValue( "SYS", "shake_mode_timeout", 7200            ) );

	std::string password = ini.GetValue( "SYS", "password", "" );
	if ( ! password.empty() )
		wbt202.sys.password = encodePassword( atoi( password.c_str() ) );

	setTimeZone(         wbt202, ini.GetLongValue( "SYS", "time_zone",          0 ) );
	setSystemOfUnits(    wbt202, ini.GetLongValue( "SYS", "unit",               0 ) );
}
