#ifndef HYPED_DRIVERS_MPU6050_H_
#define HYPED_DRIVERS_MPU6050_H_

#include <cstdint>
#include <vector>

#include "i2c.hpp"
#include "vector3d.hpp"
#include "interfaces.hpp"

// Datasheet: https://www.invensense.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf
// Register Descriptions: https://www.invensense.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf

#define ACCL_RANGE_2G  0x00
#define ACCL_RANGE_6G  0x08
#define ACCL_RANGE_8G  0x10
#define ACCL_RANGE_16G 0x18
#define ACCL_RANGE_MIN ACCL_RANGE_2G
#define ACCL_RANGE_MAX ACCL_RANGE_16G
#define GYRO_RANGE_250DPS  0x00
#define GYRO_RANGE_500DPS  0x08
#define GYRO_RANGE_1000DPS 0x10
#define GYRO_RANGE_2000DPS 0x18
#define GYRO_RANGE_MIN GYRO_RANGE_250DPS
#define GYRO_RANGE_MAX GYRO_RANGE_2000DPS

#define DEFAULT_SLAVE_ADDR     0x68 // AD0 pin is low (0V)
#define ALTERNATIVE_SLAVE_ADDR 0x69 // AD0 pin is high (3.3V)

class RawAcclData : public Vector3D<short> {};
class RawGyroData : public Vector3D<short> {};
class Acceleration : public Vector3D<double> {};
class AngularVelocity : public Vector3D<double> {};

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
  // Deviations of self-test response (STR) from factory trim (FT) in %
  // (STR = difference between outputs with self-test enabled and disabled)
  double x_dev;
  double y_dev;
  double z_dev;
  double max_dev = 14.0;
};

class Mpu6050 : public Imu{
 public:
  Mpu6050 (I2C* bus, uint8_t slave_addr = DEFAULT_SLAVE_ADDR);

  void set_accl_range(char range);
  void set_gyro_range(char range);
  virtual void calibrate_gyro(int num_samples);
  SelfTestResult test_accl();
  SelfTestResult test_gyro();
  RawAcclData get_raw_accl_data();
  RawGyroData get_raw_gyro_data();
  RawSensorData get_raw_sensor_data();
  virtual Vector3D<double> get_acceleration(); //performs accl reading
  Acceleration get_acceleration(RawAcclData accl_reading); //conversion only, no sensor reading
  Acceleration get_acceleration(RawSensorData reading); //conversion only, no sensor reading
  virtual Vector3D<double> get_angular_velocity(); //performs gyro reading
  AngularVelocity get_angular_velocity(RawGyroData gyro_reading); //conversion only, no sensor reading
  AngularVelocity get_angular_velocity(RawSensorData reading); //conversion only, no sensor reading
  SensorData get_sensor_data(); //performs all data reading
  SensorData get_sensor_data(RawSensorData reading); //conversion only, no sensor reading
  virtual ImuData get_imu_data(); // calls get_sensor_data()

 private:
  void write8(char reg_addr, char data);
  uint8_t read8(char reg_addr);
  short read16(char reg_addr);
  std::vector<uint8_t> read_bytes(char reg_addr, short length);

  I2C *bus;
  uint8_t slave_addr;
  double accl_scale;
  double gyro_scale;
  Vector3D<double> gyro_offset;
};

#endif // HYPED_DRIVERS_MPU6050_H_
