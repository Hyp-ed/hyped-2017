/*
 * LESSONS LEARNED
 *  1. Correct i2c-dev.h
 *    The default `/usr/include/linux/i2c-dev.h` is only meant to be used by the kernel and does not
 *    contain the `i2c_smbus_...()` functions.
 *    Fixed by `sudo apt install libi2c-dev`.
 *  2. Add users to i2c group
 *    By default, users do not have permission to access the `/dev/i2c-1` file, hence error on
 *    opening it here.
 *    Fixed by `usermod -aG i2c <username>`.
 */


#include "mpu6050.hpp"

using namespace std;

Mpu6050::Mpu6050(I2C *bus)
{
  this->bus = bus;
  init();
}

void Mpu6050::init() {
  // POWER MGMT setup
  char buf[2];
  buf[0] = 0x6B; buf[1] = 0x80;
  this->bus->write(slave_addr, 2, buf); //PWR_MGMT_1 - reset
  sleep(1);
  
  buf[0] = 0x6B; buf[1] = 0x03;
  this->bus->write(slave_addr, 2, buf); //PWR_MGMT_1 - set gyro z as clock source
  buf[0] = 0x6C; buf[1] = 0;
  this->bus->write(slave_addr, 2, buf); //PWR_MGMT_2
  sleep(1);
}

void Mpu6050::write8(char reg_addr, char data)
{
  char buf[2] = {reg_addr, data};
  this->bus->write(this->slave_addr, 2, buf);
}

uint8_t Mpu6050::read8(char reg_addr)
{
  char send_buf[1] = {reg_addr};
  char recv_buf[1];
  this->bus->write_read(this->slave_addr, 1, send_buf, 1, recv_buf);
  return (uint8_t) recv_buf[0];
}

short Mpu6050::read16(char reg_addr)
{
  char send_buf[1] = {reg_addr};
  char recv_buf[2];
  this->bus->write_read(this->slave_addr, 1, send_buf, 2, recv_buf);
  return (short) ((recv_buf[0] << 8) | recv_buf[1]); //little-endian
}

uint8_t* Mpu6050::read_bytes(char reg_addr, short length)
{
  char send_buf[1] = {reg_addr};
  char recv_buf[length];
  this->bus->write_read(this->slave_addr, 1, send_buf, length, recv_buf);
  return (uint8_t*) recv_buf;
}



short Mpu6050::get_raw_accl_x()
{
  return this->read16(0x3B);
}

short Mpu6050::get_raw_accl_y()
{
  return this->read16(0x3D);
}

short Mpu6050::get_raw_accl_z()
{
  return this->read16(0x3F);
}

short Mpu6050::get_raw_gyro_x()
{
  return this->read16(0x43);
}

short Mpu6050::get_raw_gyro_y()
{
  return this->read16(0x45);
}

short Mpu6050::get_raw_gyro_z()
{
  return this->read16(0x47);
}

RawSensorData Mpu6050::get_raw_sensor_data()
{
  uint8_t *bytes = this->read_bytes(0x3B, 14); //array of length 14
  RawSensorData data;
  data.accl.x = (short) ((bytes[0] << 8) | bytes[1]);
  data.accl.y = (short) ((bytes[2] << 8) | bytes[3]);
  data.accl.z = (short) ((bytes[4] << 8) | bytes[5]);
  data.temp = (short) ((bytes[6] << 8) | bytes[7]);
  data.gyro.x = (short) ((bytes[8] << 8) | bytes[9]);
  data.gyro.y = (short) ((bytes[10] << 8) | bytes[11]);
  data.gyro.z = (short) ((bytes[12] << 8) | bytes[13]);
  return data;
}
