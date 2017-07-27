#ifndef HYPED_DRIVERS_GPIO_HPP_
#define HYPED_DRIVERS_GPIO_HPP_

#include <map>
#include <wiringPi.h>

#define PIN4 7
#define PIN5 21
#define PIN6 22
#define PIN12 26
#define PIN13 23
#define PIN16 27
#define PIN17 0
#define PIN18 1
#define PIN19 24
#define PIN20 28
#define PIN21 29
#define PIN22 3
#define PIN23 4
#define PIN24 5
#define PIN25 6
#define PIN26 25
#define PIN27 2
#define PIN_TXD 15
#define PIN_RXD 16

typedef int GpioPinNumber;

// Input/output setting (possible to add PWM and clock modes)
enum class PinMode
{
  in = INPUT,
  out = OUTPUT
};

// Pull Up/Down control
enum class PudControl
{
  off = PUD_OFF,
  down = PUD_DOWN,
  up = PUD_UP
};

class GpioPin; // Declaring here since used by Gpio

class Gpio
{
  public:
    /// Allocates, configures and returns a reference to the `pin`
    /// If this pin is already in use, a reference to it is return but the pin's configuration is
    /// left unchanged (possibly different from what was requested)
    static GpioPin& get_pin(GpioPinNumber pin, PinMode mode, PudControl pud);
    /// Checks if the `pin` is currently in use
    static bool is_pin_in_use(GpioPinNumber pin);

  private:
    Gpio();
    ~Gpio();

    static Gpio instance;
    std::map<GpioPinNumber, GpioPin*> active_pins;
};

class GpioPin
{
  friend class Gpio; // Gpio needs access to the private constructor
  public:
    /// Returns the value read at this pin (true for HIGH, false for LOW)
    bool read();
    /// If this pin is in output mode, its value is set to `value` otherwise nothing happens
    void write(bool value);
    /// Changes the mode of the pin (input/output)
    void set_mode(PinMode mode);
    /// If this pin is in input mode, PUD is configured for it otherwise nothing happens
    void set_pud(PudControl pud);

    GpioPin()                      = delete;
    GpioPin(GpioPin const&)        = delete;
    void operator=(GpioPin const&) = delete;

  private:
    GpioPin(GpioPinNumber pin, PinMode mode, PudControl pud);

    GpioPinNumber pin_num;
    PinMode mode;
    PudControl pud;
};

#endif // HYPED_DRIVERS_GPIO_HPP_

