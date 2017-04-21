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



int Mpu6050::get_raw_accl_x()
{
  return this->read16(0x3B);
}

int Mpu6050::get_raw_accl_y()
{
  return this->read16(0x3D);
}

int Mpu6050::get_raw_accl_z()
{
  return this->read16(0x3F);
}

int Mpu6050::get_raw_gyro_x()
{
  return this->read16(0x43);
}

int Mpu6050::get_raw_gyro_y()
{
  return this->read16(0x45);
}

int Mpu6050::get_raw_gyro_z()
{
  return this->read16(0x47);
}

int main()
{
    Mpu6050 sensor(new I2C);
    for (int i = 0; i < 10000; i++)
    {
        printf("AX=%7d, AY=%7d, AZ=%7d, GX=%7d, GY=%7d, GZ=%7d\n",
            sensor.get_raw_accl_x(),
            sensor.get_raw_accl_y(),
            sensor.get_raw_accl_z(),
            sensor.get_raw_gyro_x(),
            sensor.get_raw_gyro_y(),
            sensor.get_raw_gyro_z());
    }
}
