#ifndef HYPED_DRIVERS_BATTERY_HPP_
#define HYPED_DRIVERS_BATTERY_HPP_

#include <array>
#include <chrono>

#include "i2c.hpp"

struct BigBatteryData
{
  std::array<short, 7> cell_voltage; // voltage of each cell in mV
  short temperature; // degC
  short current; // total current in A
};

struct SmallBatteryData
{
  std::array<short, 5> cell_voltage; // voltage of each cell in mV
  short temperature; // degC
};

struct BatteryData
{
  BigBatteryData big1;
  BigBatteryData big2;
  SmallBatteryData small;
};

class Battery
{
  public:
    Battery(I2C *bus, int min_refresh_period = 100 /*ms*/);

    BatteryData get_data();
    
  private:
    I2C *bus;
    std::chrono::high_resolution_clock::time_point last_refresh;
    std::chrono::milliseconds refresh_period;
    BatteryData data;

    void refresh();
};

#endif //HYPED_DRIVERS_BATTERY_HPP_

