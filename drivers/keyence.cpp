#include "keyence.hpp"

#include <chrono>
#include <cstdio>


Keyence::Keyence(GpioPinNumber config_pin_num, GpioPinNumber output_pin_num)
    : config_pin { Gpio::get_pin(config_pin_num, PinMode::out, PudControl::off) },
    output_pin { Gpio::get_pin(output_pin_num, PinMode::in, PudControl::down) },
    count(0), stop_flag(true)
{}

void Keyence::calibrate()
{
  this->config_pin.write(false);
  std::this_thread::sleep_for(std::chrono::milliseconds(3500));
  this->config_pin.write(true);
  printf("Setup complete\n");	
}

int Keyence::get_count()
{
  return this->count.load(std::memory_order_relaxed);
}

void Keyence::count_stripes()
{
  int count = 0;
  bool current, previous = false;
  while (!this->stop_flag)
  {
    current = this->output_pin.read();
    if (current && !previous)
    {
      // Stripe started
      printf("Stripe started\n");
    }	
    if (current && previous)
    {
      // Stripe in progress
      printf("Stripe still present\n");
    }
    if (!current && previous)
    {
      ++count;
      printf("Stripe finished. Stripe Count = %d\n", count);
    }

    this->count.store(count, std::memory_order_relaxed);
    previous = current;
    //Change delay to vary the reading frequency
    std::this_thread::sleep_for(std::chrono::microseconds(10000));
  }
}
