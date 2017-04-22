#include <cstdint>
#include "i2c.hpp"

const unsigned char DEFAULT_SLAVE_ADDR = 0x68;

typedef struct {
  short x, y, z;
} RawAcclData;

typedef struct {
  short x, y, z;
} RawGyroData;

typedef struct {
  RawAcclData accl;
  short temp;
  RawGyroData gyro;
} RawSensorData;

class Mpu6050{
 public:
  Mpu6050 (I2C* bus);
  short get_raw_accl_x();
  short get_raw_accl_y();
  short get_raw_accl_z();
  short get_raw_gyro_x();
  short get_raw_gyro_y();
  short get_raw_gyro_z();
  RawSensorData get_raw_sensor_data();

 private:
  I2C* bus;
  uint8_t slave_addr = DEFAULT_SLAVE_ADDR;
  void init();
  void write8(char reg_addr, char data);
  uint8_t read8(char reg_addr);
  short read16(char reg_addr);
  uint8_t* read_bytes(char reg_addr, short length);
};