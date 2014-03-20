
#include "wbt202.h"

#include <iostream>
#include <fstream>
#include <string>

std::string filename = "WBT202/SYS/LOG.BIN";

int main()
{
  std::fstream file( filename.c_str(), std::ios::in | std::ios::binary );

  if ( ! file.is_open() )
  {
    std::cout << "cannot" << std::endl;
    return -1;
  }

  char buffer[88];
  file.read( buffer, 88 );

  Log * log = reinterpret_cast<Log*>(buffer);
  std::cout << "log_mode            = " << static_cast<int>( log->log_mode ) << std::endl;
  std::cout << "magic               = " << static_cast<int>( log->magic ) << std::endl;
  std::cout << "valid_speed_highest = " << static_cast<int>( log->valid_speed_highest ) << std::endl;
  std::cout << "valid_speed_lowest  = " << static_cast<int>( log->valid_speed_lowest ) << std::endl;


  return 0;
}
