#include <chrono>
#include <cstdio>
#include <thread>

#include "gpio.hpp"
#include "keyence.hpp"

#define CONFIG_PIN PIN24
#define OUTPUT_PIN PIN23


int main()
{
  Keyence k(CONFIG_PIN, OUTPUT_PIN);
  k.calibrate();
  k.start();
  while (1)
  {
    //printf("Count: %d\n", k.get_count());
    if (k.has_new_stripe())
    {
      printf("Count: %d\n", k.get_count());
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}
