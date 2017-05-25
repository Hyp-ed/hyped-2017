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

#include <array>
#include <cstdio>
#include <cmath>

// MPU6050's register addresses
// For more information refer to MPU-6050 Register Map and Descriptions at
//   https://www.invensense.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
#define SELF_TEST_X  0x0D
#define SELF_TEST_Y  0x0E
#define SELF_TEST_Z  0x0F
#define SELF_TEST_A  0x10
#define SMPLRT_DIV   0x19
#define CONFIG       0x1A
#define GYRO_CONFIG  0x1B
#define ACCEL_CONFIG 0x1C
#define FIFO_EN      0x23
#define INT_PIN_CFG  0x37
#define INT_ENABLE   0x38
#define INT_STATUS   0x3A 

#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define TEMP_OUT_H   0x41
#define TEMP_OUT_L   0x42
#define GYRO_XOUT_H  0x43
#define GYRO_XOUT_L  0x44
#define GYRO_YOUT_H  0x45
#define GYRO_YOUT_L  0x46
#define GYRO_ZOUT_H  0x47
#define GYRO_ZOUT_L  0x48

#define SIGNAL_PATH_RES 0x68
#define USER_CTRL       0x6A
#define PWR_MGMT_1      0x6B
#define PWR_MGMT_2      0x6C
#define FIFO_COUNTH     0x72
#define FIFO_COUNTL     0x73
#define FIFO_R_W        0x74
#define WHO_AM_I        0x75

// SETTINGS
// ACCEL_CONFIG flags (combine with each other and with range settings using `|`)
#define XA_ST 0x80 // ST = self-test
#define YA_ST 0x40
#define ZA_ST 0x20

// GYRO_CONFIG flags (combine with each other and with range settings using `|`)
#define XG_ST 0x80
#define YG_ST 0x40
#define ZG_ST 0x20

#define DEFAULT_ACCL_RANGE ACCL_RANGE_2G
#define DEFAULT_GYRO_RANGE GYRO_RANGE_250DPS

using namespace std;

const array<double, 4> ACCL_SCALES = {16384.0, 8192.0, 4096.0, 2048.0};
const array<double, 4> GYRO_SCALES = {131.0, 65.5, 32.8, 16.4};

Mpu6050::Mpu6050(I2C *bus)
{
  this->bus = bus;
  this->gyro_offset.x = 0.0;
  this->gyro_offset.y = 0.0;
  this->gyro_offset.z = 0.0;

  // POWER MGMT setup
  this->write8(PWR_MGMT_1, 0x80); //PWR_MGMT_1 - reset
  sleep(1); //sleep for 1 second, probably not necessary but just in case...
  
  this->write8(PWR_MGMT_1, 0x03); //PWR_MGMT_1 - set gyro z as clock source
  sleep(1); //sleep for 1 second, probably not necessary but just in case...

  this->set_accl_range(DEFAULT_ACCL_RANGE);
  this->set_gyro_range(DEFAULT_GYRO_RANGE);
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

vector<uint8_t> Mpu6050::read_bytes(char reg_addr, short length)
{
  char send_buf[1] = {reg_addr};
  char recv_buf[length];
  this->bus->write_read(this->slave_addr, 1, send_buf, length, recv_buf);
  vector<uint8_t> vec (length); // new vector of size `length`
  for (int i = 0; i < length; i++)
  {
    vec[i] = (uint8_t) recv_buf[i];
  }
  return vec;
}



void Mpu6050::set_accl_range(char range)
{
  if (range < ACCL_RANGE_MIN || range > ACCL_RANGE_MAX)
    range = DEFAULT_ACCL_RANGE;
  // TODO: do not reset the self-test bits (ACCEL_CONFIG[7:5])
  this->write8(ACCEL_CONFIG, range); //range selection in ACCEL_CONFIG[4:3] (3 lsb empty)
  this->accl_scale = ACCL_SCALES[range >> 3];
}

void Mpu6050::set_gyro_range(char range)
{
  if (range < GYRO_RANGE_MIN || range > GYRO_RANGE_MAX)
    range = DEFAULT_GYRO_RANGE;
  // TODO: do not reset the self-test bits (GYRO_CONFIG[7:5])
  this->write8(GYRO_CONFIG, range); //range selection in GYRO_CONFIG[4:3] (3 lsb empty)
  this->gyro_scale = GYRO_SCALES[range >> 3];
}

void Mpu6050::calibrate_gyro(int num_samples)
{
  this->gyro_offset.x = 0.0;
  this->gyro_offset.y = 0.0;
  this->gyro_offset.z = 0.0;
  for (int i = 0; i < num_samples; i++)
  {
    RawGyroData data = this->get_raw_gyro_data();
    this->gyro_offset.x += data.x;
    this->gyro_offset.y += data.y;
    this->gyro_offset.z += data.z;
  }
  this->gyro_offset.x /= num_samples;
  this->gyro_offset.y /= num_samples;
  this->gyro_offset.z /= num_samples;
}

SelfTestResult Mpu6050::test_accl()
{
  uint8_t rng = this->read8(ACCEL_CONFIG) & 0x18; // save current range setting
  
  RawAcclData rad1, rad2;
  
  this->write8(ACCEL_CONFIG, XA_ST | YA_ST | ZA_ST | ACCL_RANGE_8G); // self-test config
  sleep(2);
  rad1 = this->get_raw_accl_data();

  // Get factory trim (FT)
  vector<uint8_t> test = this->read_bytes(SELF_TEST_X, 4);
  /*for (int i = 0; i < 3; i++)
    test[i] = ((test[i] & 0xE0) >> 3) | ((test[4] & (0x3 << (4 - 2*i))) >> (4 - 2*i));//*/
  test[0] = ((test[0] & 0xE0) >> 3) | ((test[4] & 0x30) >> 4);
  test[1] = ((test[1] & 0xE0) >> 3) | ((test[4] & 0x0C) >> 2);
  test[2] = ((test[2] & 0xE0) >> 3) | (test[4] & 0x03);
  array<double, 3> ft;
  for (int i = 0; i < 3; i++)
    if (test[i] != 0)
      ft[i] = 4096 * 0.34 * pow(0.92 / 0.34, (test[i] - 1) / 30); //magic numbers from register desc.
    else
      ft[i] = 0;

  this->write8(ACCEL_CONFIG, ACCL_RANGE_8G); // stop self-test
  sleep(2);
  rad2 = this->get_raw_accl_data();
  this->write8(ACCEL_CONFIG, rng); // restore range setting

  // Calculate percentage deviation from FT
  SelfTestResult result;
  result.x_dev = ((rad1.x - rad2.x) - ft[0]) / ft[0] * 100.0;
  result.y_dev = ((rad1.y - rad2.y) - ft[1]) / ft[1] * 100.0;
  result.z_dev = ((rad1.z - rad2.z) - ft[2]) / ft[2] * 100.0;
  result.passed = abs(result.x_dev) <= result.max_dev &&     
                  abs(result.y_dev) <= result.max_dev &&     
                  abs(result.z_dev) <= result.max_dev;       

  return result;
}

SelfTestResult Mpu6050::test_gyro()
{
  uint8_t rng = this->read8(GYRO_CONFIG) & 0x18; // save current range setting

  RawGyroData rgd1, rgd2;

  this->write8(GYRO_CONFIG, XG_ST | YG_ST | ZG_ST | GYRO_RANGE_250DPS); //all tests, 250dps range
  sleep(1);
  rgd1 = this->get_raw_gyro_data();

  // Get factory trim (FT)
  vector<uint8_t> test = this->read_bytes(SELF_TEST_X, 3);
  for (int i = 0; i < 3; i++) test[i] = test[i] & 0x1F;
  array<double, 3> ft;
  for (int i = 0; i < 3; i++)
    if (test[i] != 0)
      ft[i] = 25 * 131 * pow(1.046, test[i] - 1); // magic numbers from register descriptions doc
    else
      ft[i] = 0;
  ft[1] = -ft[1];

  this->write8(GYRO_CONFIG, GYRO_RANGE_250DPS); // stop self-test
  sleep(1);
  rgd2 = this->get_raw_gyro_data();
  this->write8(GYRO_CONFIG, rng); // restore range setting

  // Calculate percentage deviation from FT
  SelfTestResult result;
  result.x_dev = ((rgd1.x - rgd2.x) - ft[0]) / ft[0] * 100.0;
  result.y_dev = ((rgd1.y - rgd2.y) - ft[1]) / ft[1] * 100.0;
  result.z_dev = ((rgd1.z - rgd2.z) - ft[2]) / ft[2] * 100.0;
  result.passed = abs(result.x_dev) <= result.max_dev &&
                  abs(result.y_dev) <= result.max_dev &&
                  abs(result.z_dev) <= result.max_dev;

  return result;
}

short Mpu6050::get_raw_accl_x()
{
  return this->read16(ACCEL_XOUT_H);
}

short Mpu6050::get_raw_accl_y()
{
  return this->read16(ACCEL_YOUT_H);
}

short Mpu6050::get_raw_accl_z()
{
  return this->read16(ACCEL_ZOUT_H);
}

short Mpu6050::get_raw_gyro_x()
{
  return this->read16(GYRO_XOUT_H);
}

short Mpu6050::get_raw_gyro_y()
{
  return this->read16(GYRO_YOUT_H);
}

short Mpu6050::get_raw_gyro_z()
{
  return this->read16(GYRO_ZOUT_H);
}

RawAcclData Mpu6050::get_raw_accl_data()
{
  vector<uint8_t> bytes = this->read_bytes(ACCEL_XOUT_H, 6); //read all 6 accl output registers
  RawAcclData data;
  data.x = (short) ((bytes[0] << 8) | bytes[1]);
  data.y = (short) ((bytes[2] << 8) | bytes[3]);
  data.z = (short) ((bytes[4] << 8) | bytes[5]);
  return data;
}

RawGyroData Mpu6050::get_raw_gyro_data()
{
  vector<uint8_t> bytes = this->read_bytes(GYRO_XOUT_H, 6); //read all 6 gyro output registers
  RawGyroData data;
  data.x = (short) ((bytes[0] << 8) | bytes[1]);
  data.y = (short) ((bytes[2] << 8) | bytes[3]);
  data.z = (short) ((bytes[4] << 8) | bytes[5]);
  return data;
}

RawSensorData Mpu6050::get_raw_sensor_data()
{
  vector<uint8_t> bytes = this->read_bytes(ACCEL_XOUT_H, 14); //read all 14 output registers
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

Acceleration Mpu6050::get_acceleration()
{
  return this->get_acceleration(this->get_raw_accl_data());
}

Acceleration Mpu6050::get_acceleration(RawAcclData accl_reading)
{
  Acceleration a;
  a.x = accl_reading.x / this->accl_scale;
  a.y = accl_reading.y / this->accl_scale;
  a.z = accl_reading.z / this->accl_scale;
  return a;
}

Acceleration Mpu6050::get_acceleration(RawSensorData reading)
{
  return this->get_acceleration(reading.accl);
}

AngularVelocity Mpu6050::get_angular_velocity()
{
  return this->get_angular_velocity(this->get_raw_gyro_data());
}

AngularVelocity Mpu6050::get_angular_velocity(RawGyroData gyro_reading)
{
  AngularVelocity omega;
  omega.x = (gyro_reading.x - this->gyro_offset.x) / this->gyro_scale;
  omega.y = (gyro_reading.y - this->gyro_offset.y) / this->gyro_scale;
  omega.z = (gyro_reading.z - this->gyro_offset.z) / this->gyro_scale;
  return omega;
}

AngularVelocity Mpu6050::get_angular_velocity(RawSensorData reading)
{
  return this->get_angular_velocity(reading.gyro);
}

SensorData Mpu6050::get_sensor_data()
{
  return this->get_sensor_data(this->get_raw_sensor_data());
}

SensorData Mpu6050::get_sensor_data(RawSensorData reading)
{
  SensorData data;
  data.accl = this->get_acceleration(reading);
  data.temp = reading.temp / 340.0 + 36.53; //calculation from Register Descriptions document p. 30
  data.angv = this->get_angular_velocity(reading);
  return data;
}
