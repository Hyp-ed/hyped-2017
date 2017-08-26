#ifndef HYPED_DRIVERS_VL6180_HPP_
#define HYPED_DRIVERS_VL6180_HPP_

#include <atomic>
#include <chrono>
#include <cstdio>
#include <exception>
#include <map>
#include <string>
#include <thread>

#include "gpio.hpp"
#include "i2c.hpp"
#include "interfaces.hpp"

#define DEFAULT_I2C_SLAVE_ADDR 0x29
#define MAX_SENSORS 9 //maximum number of VL6180 units which can be connected to a single i2c bus

class Vl6180;

class Vl6180Factory
{
  public:
    static Vl6180Factory& instance(I2C* bus);

    Vl6180Factory()                      = delete;
    Vl6180Factory(Vl6180Factory const&)  = delete;
    void operator=(Vl6180Factory const&) = delete;

    Vl6180& make_sensor(GpioPinNumber gpio_pin);

  private:
    Vl6180Factory(I2C* bus);
    ~Vl6180Factory();

    I2C* bus; 
    static constexpr uint8_t i2c_slave_addresses[MAX_SENSORS] =
        {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28};
    static Vl6180* sensors[MAX_SENSORS];
};

class Vl6180 : public Proxi
{
  friend class Vl6180Factory;
  public:
    void turn_on();
    void turn_off();
    bool is_on();
    void set_intermeasurement_period(int msec);
    void calibrate(int true_distance, int num_measurements);
    void set_continuous_mode(bool enabled);
    bool is_continuous_mode();
    /// Retrieves distance in mm (blocks if not in continuous mode)
    virtual int get_distance();

    Vl6180()                      = delete;
    Vl6180(Vl6180 const&)         = delete;
    void operator=(Vl6180 const&) = delete;

  private:
    Vl6180(I2C* bus, GpioPinNumber gpio_pin_num, uint8_t i2c_slave_addr);

    bool wait_device_ready();
    uint8_t poll_measurement();
    uint8_t get_measurement();
    bool is_fresh_out_of_reset();
    void write8(uint16_t reg_addr, char data);
    uint8_t read8(uint16_t reg_addr);

    I2C *bus;
    GpioPin& gpio_pin;
    uint8_t i2c_slave_addr = DEFAULT_I2C_SLAVE_ADDR;
    bool cont_mode = false;
    bool on;
    int offset = 0;
};

class Vl6180Exception : public std::exception
{
  public:
    Vl6180Exception(std::string message, int wpi_pin_num);
    virtual const char* what() const noexcept override;

    const int wpi_pin_num;

  private:
    const std::string message;
};

#endif //HYPED_DRIVERS_VL6180_HPP_

