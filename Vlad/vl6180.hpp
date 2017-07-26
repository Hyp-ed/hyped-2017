#ifndef HYPED_DRIVERS_VL6180_HPP_
#define HYPED_DRIVERS_VL6180_HPP_

#include <atomic>
#include <chrono>
#include <cstdio>
#include <thread>

#include "i2c.hpp"

#define DEFAULT_I2C_SLAVE_ADDR 0x29

class Vl6180
{
  public:
    Vl6180(I2C *bus, uint8_t i2c_slave_addr = DEFAULT_I2C_SLAVE_ADDR);

    // Retrieves distance in mm
    int get_distance();

  private:
    void write8(uint16_t reg_addr, char data);
    uint8_t read8(uint16_t reg_addr);

    I2C *bus;
    uint8_t i2c_slave_addr = DEFAULT_I2C_SLAVE_ADDR;
    int distance;
};

#endif //HYPED_DRIVERS_VL6180_HPP_