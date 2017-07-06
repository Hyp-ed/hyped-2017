#include "battery.hpp"

#define SLAVE1_I2C_ADDR 0x6a
#define SLAVE2_I2C_ADDR 0x6b

const int SLAVE1_DATA_SIZE = 2 * (7 + 1 + 1 + 5);
const int SLAVE2_DATA_SIZE = 2 * (7 + 1 + 1 + 1);
const int TOTAL_DATA_SIZE = (SLAVE1_DATA_SIZE + SLAVE2_DATA_SIZE) / 2;


Battery::Battery(I2C *bus, int min_refresh_period /*=100ms*/) : refresh_period(min_refresh_period)
{
  this->bus = bus;
  this->refresh();
}

BatteryData Battery::get_data()
{
  this->cond_refresh();
  return this->data;
}


void Battery::cond_refresh()
{
  std::chrono::high_resolution_clock::time_point now =
      std::chrono::high_resolution_clock::now();
  if (now - this->last_refresh > this->refresh_period)
  {
    this->refresh();
  }
}

void Battery::refresh()
{
  this->last_refresh = std::chrono::high_resolution_clock::now();

  char buf1[SLAVE1_DATA_SIZE];
  char buf2[SLAVE2_DATA_SIZE];
  this->bus->read(SLAVE1_I2C_ADDR, SLAVE1_DATA_SIZE, buf1);
  this->bus->read(SLAVE2_I2C_ADDR, SLAVE2_DATA_SIZE, buf2);

  //TODO: checksum

  // Convert to short
  std::array<short, TOTAL_DATA_SIZE> data;
  for (int i = 0; i < SLAVE1_DATA_SIZE / 2; ++i)
    data[i] = (buf1[2*i] << 8) | buf1[2*i + 1];
  for (int i = SLAVE1_DATA_SIZE / 2, j = 0; i < TOTAL_DATA_SIZE; ++i, j += 2)
    data[i] = (buf2[j] << 8) | buf2[j + 1];
  // Populate BatteryData
  auto it = data.begin();
  std::copy(it, it + 7, this->data.big1.cell_voltage.begin());
  this->data.big1.temperature = *(it += 7);
  this->data.big1.current = *(++it);
  ++it;
  std::copy(it, it + 5, this->data.small.cell_voltage.begin());
  it += 5;
  std::copy(it, it + 7, this->data.big2.cell_voltage.begin());
  this->data.big2.temperature = *(it += 7);
  this->data.big2.current = *(++it);
  this->data.small.temperature = *(++it);
}

