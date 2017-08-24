#include <atomic>
#include <thread>

#include "gpio.hpp"

#define CTL_SIG_PIN 29
#define STR_IN_PIN 6


class Keyence
{
  public:
    Keyence(GpioPinNumber config_pin_num, GpioPinNumber output_pin_num);
    void calibrate();
    void start();
    int get_count();
  
  private:
    void count_stripes();

    GpioPin& config_pin;
    GpioPin& output_pin;
    std::atomic<int> count;
    std::atomic_bool stop_flag;
    std::thread counting_thread;
};
