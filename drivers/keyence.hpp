#include "gpio.hpp"

#define CTL_SIG_PIN 29
#define STR_IN_PIN 6


class Keyence
{
  private: 
    bool current_state = false;
    bool prev_state = false;
    GpioPin& config_pin;
    GpioPin& output_pin;

  public:
    Keyence(GpioPinNumber config_pin_num, GpioPinNumber output_pin_num);
    void calibrate();
    void countStripes(int &numStripes);			
};
