#include "keyence.hpp"

#include <chrono>
#include <cstdio>


const int stripe_locations[63] =
    {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 
    1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 
    2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 
    3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, 
    4000, 4008, 4016, 4024, 4032, 4040, 4048, 4056, 4064, 4072,
    4100, 4200, 4300, 4400, 
    4500, 4508, 4516, 4524, 4532,
    4600, 4700, 4800, 4900};

Keyence::Keyence(GpioPinNumber config_pin_num, GpioPinNumber output_pin_num)
    : config_pin { Gpio::get_pin(config_pin_num, PinMode::out, PudControl::off) },
    output_pin { Gpio::get_pin(output_pin_num, PinMode::in, PudControl::down) },
    count(0), new_stripe(false), stop_flag(true)
{}

Keyence::~Keyence()
{
  this->stop();
}

void Keyence::calibrate()
{
  this->config_pin.write(false);
  std::this_thread::sleep_for(std::chrono::milliseconds(3500));
  this->config_pin.write(true);
  printf("Setup complete\n");	
}

void Keyence::start()
{
  this->stop_flag = false;
  this->counting_thread = std::thread(&Keyence::count_stripes, this);
}

void Keyence::stop()
{
  this->stop_flag = false;
  this->counting_thread.join();
}

bool Keyence::has_new_stripe()
{
  return this->new_stripe.load(std::memory_order_relaxed);
}

int Keyence::get_count()
{
  this->new_stripe.store(false, std::memory_order_relaxed);
  return this->count.load(std::memory_order_relaxed);
}

double Keyence::get_distance()
{
  return this->get_count() * 30.0;
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
      //printf("Stripe started\n");
    }	
    if (current && previous)
    {
      // Stripe in progress
      //printf("Stripe still present\n");
    }
    if (!current && previous)
    {
      ++count;
      this->count.store(count, std::memory_order_relaxed);
      this->new_stripe.store(true, std::memory_order_relaxed);
      //printf("Stripe finished. Stripe Count = %d\n", count);
    }

    previous = current;
    //Change delay to vary the reading frequency
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
  }
}
