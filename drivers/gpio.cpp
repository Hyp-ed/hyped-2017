#include "gpio.hpp"

Gpio Gpio::instance;

GpioPin& Gpio::get_pin(GpioPinNumber pin, PinMode mode, PudControl pud)
{
  // Check if already in use
  if (instance.active_pins.count(pin) > 0)
    return *instance.active_pins[pin];

  // Requested pin number not used so allocate the pin
  instance.active_pins[pin] = new GpioPin(pin, mode, pud);
  return *instance.active_pins[pin];
}

bool Gpio::is_pin_in_use(GpioPinNumber pin)
{
  return (instance.active_pins.count(pin) > 0);
}

Gpio::Gpio()
{
  wiringPiSetup();
}

Gpio::~Gpio()
{
  // Clear active pins
  for (auto it = this->active_pins.begin(); it != this->active_pins.end(); ++it)
    delete (it->second);
  this->active_pins.clear();
}


bool GpioPin::read()
{
  return (digitalRead(this->pin_num) != LOW);
}

void GpioPin::write(bool value)
{
  if (this->mode == PinMode::out)
    digitalWrite(this->pin_num, value);
}

void GpioPin::set_mode(PinMode mode)
{
  if (this->mode != mode)
  {
    // Disable PUD if going to output mode (probably not necessary)
    if (mode == PinMode::out)
      this->set_pud(PudControl::off);
    // Change mode
    pinMode(this->pin_num, static_cast<int>(mode));
    this->mode = mode;
  }
}

void GpioPin::set_pud(PudControl pud)
{
  if (this->mode == PinMode::in && this->pud != pud)
  {
    pullUpDnControl(this->pin_num, static_cast<int>(pud));
    this->pud = pud;
  }
}

GpioPin::GpioPin(GpioPinNumber pin, PinMode mode, PudControl pud)
    : pin_num(pin), mode(mode)
{
  // Set pin mode
  pinMode(this->pin_num, static_cast<int>(mode));
  if (mode == PinMode::out)
    pud = PudControl::off;
  // Set PUD
  pullUpDnControl(this->pin_num, static_cast<int>(pud));
  this->pud = pud;
}

