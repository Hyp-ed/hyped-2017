#include "raspberry_pi.hpp"

#define CPU_TEMP_FILEPATH "/sys/devices/virtual/thermal/thermal_zone0/temp"

double RaspberryPi::get_temperature()
{
  std::ifstream ifs(CPU_TEMP_FILEPATH);
  
  int temp;
  ifs >> temp;
  
  return (double) temp / 1000.0;
}

