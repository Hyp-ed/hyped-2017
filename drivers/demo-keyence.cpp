#include <chrono>
#include <cstdio>
#include <thread>

#include "gpio.hpp"
#include "keyence.hpp"

#define CONFIG_PIN PIN21
#define OUTPUT_PIN PIN26


int main()
{
  Keyence k(CONFIG_PIN, OUTPUT_PIN);
  k.calibrate();
  void start();
  while (1)
  {
    printf("Count: %d\n", k.get_count());
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}
