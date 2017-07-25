#ifndef HYPED_DRIVERS_VL6180_HPP_
#define HYPED_DRIVERS_VL6180_HPP_

#include <atomic>
#include <chrono>
#include <cstdio>
#include <map>
#include <thread>

#include "i2c.hpp"

#define DEFAULT_I2C_SLAVE_ADDR 0x29
#define MAX_SENSORS 8 //maximum number of VL6180 units which can be connected to a single i2c bus

typedef int Pin;

class Vl6180Factory
{
  public:
    static Vl6180Factory& instance(I2C* bus);

    Vl6180Factory(Vl6180Factory const&)  = delete;
    void operator=(Vl6180Factory const&) = delete;

    Vl6180& make_sensor(Pin gpio_pin);

  private:
    Vl6180Factory(I2C* bus);

    I2C* bus;
};

class Vl6180
{
  friend class Vl6180Factory;
  public:
    Vl6180& get_instance(I2C *bus, Pin gpio_pin);

    // Retrieves distance in mm
    int get_distance();

  private:
    Vl6180(I2C* bus, Pin gpio_pin, i2c_slave_addr);

    void write8(uint16_t reg_addr, char data);
    uint8_t read8(uint16_t reg_addr);

    I2C *bus;
    Pin gpio_pin;
    uint8_t i2c_slave_addr = DEFAULT_I2C_SLAVE_ADDR;
    int distance = -1;
    
    static const uint8_t i2c_slave_addresses[MAX_SENSORS] =
        {0x20, 0x21, 0x22, 0x23; 0x24, 0x25, 0x26, 0x27, 0x28};
    static Vl6180* sensors[8] =
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
};

#endif //HYPED_DRIVERS_VL6180_HPP_

