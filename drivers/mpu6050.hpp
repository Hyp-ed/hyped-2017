#include <cstdint>
#include <vector>

#include "i2c.hpp"

// Datasheet: https://www.invensense.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf
// Register Descriptions: https://www.invensense.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf

#define ACCL_RANGE_2G  0
#define ACCL_RANGE_6G  1
#define ACCL_RANGE_8G  2
#define ACCL_RANGE_16G 3
#define ACCL_RANGE_MIN ACCL_RANGE_2G
#define ACCL_RANGE_MAX ACCL_RANGE_16G
#define GYRO_RANGE_250DPS  0
#define GYRO_RANGE_500DPS  1
#define GYRO_RANGE_1000DPS 2
#define GYRO_RANGE_2000DPS 3
#define GYRO_RANGE_MIN GYRO_RANGE_250DPS
#define GYRO_RANGE_MAX GYRO_RANGE_2000DPS

const uint8_t DEFAULT_SLAVE_ADDR = 0x68;

template <typename T> struct Vector3D {
  T x, y, z;
};

struct RawAcclData : Vector3D<short> {};
struct RawGyroData : Vector3D<short> {};
struct Acceleration : Vector3D<double> {};
struct AngularVelocity : Vector3D<double> {};

struct RawSensorData {
  RawAcclData accl;
  short temp;
  RawGyroData gyro;
};

struct SensorData {
  Acceleration accl;
  double temp;
  AngularVelocity angv;
};

struct SelfTestResult {
  bool passed;
  double x_dev;
  double y_dev;
  double z_dev;
  const double max_dev = 14.0;
};

class Mpu6050{
 public:
  Mpu6050 (I2C* bus);

  void set_accl_range(int range);
  void set_gyro_range(int range);
  void calibrate_gyro(int num_samples);
  SelfTestResult test_accl();
  SelfTestResult test_gyro();
  short get_raw_accl_x();
  short get_raw_accl_y();
  short get_raw_accl_z();
  short get_raw_gyro_x();
  short get_raw_gyro_y();
  short get_raw_gyro_z();
  RawAcclData get_raw_accl_data();
  RawGyroData get_raw_gyro_data();
  RawSensorData get_raw_sensor_data();
  Acceleration get_acceleration(); //performs accl reading
  Acceleration get_acceleration(RawAcclData accl_reading); //conversion only, no sensor reading
  Acceleration get_acceleration(RawSensorData reading); //conversion only, no sensor reading
  AngularVelocity get_angular_velocity(); //performs gyro reading
  AngularVelocity get_angular_velocity(RawGyroData gyro_reading); //conversion only, no sensor reading
  AngularVelocity get_angular_velocity(RawSensorData reading); //conversion only, no sensor reading
  SensorData get_sensor_data(); //performs all data reading
  SensorData get_sensor_data(RawSensorData reading); //conversion only, no sensor reading

 private:
  void init();
  void write8(char reg_addr, char data);
  uint8_t read8(char reg_addr);
  short read16(char reg_addr);
  std::vector<uint8_t> read_bytes(char reg_addr, short length);

  I2C *bus;
  uint8_t slave_addr = DEFAULT_SLAVE_ADDR;
  double accl_scale;
  double gyro_scale;
  Vector3D<double> gyro_offset;
};
