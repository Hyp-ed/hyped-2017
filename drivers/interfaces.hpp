#ifndef HYPED_DRIVERS_INTERFACES_HPP_
#define HYPED_DRIVERS_INTERFACES_HPP_

#include "vector3d.hpp"


class Accelerometer
{
  public:
    virtual Vector3D<double> get_acceleration() = 0;
};

class Gyroscope
{
  public:
    virtual void calibrate_gyro(int n) = 0;
    virtual Vector3D<double> get_angular_velocity() = 0;
};

struct ImuData
{
  ImuData(Vector3D<double> accl, Vector3D<double> angv)
  {
    acceleration = accl;
    angular_velocity = angv;
  }
  Vector3D<double> acceleration;
  Vector3D<double> angular_velocity;
};

class Imu : public Accelerometer, public Gyroscope
{
  public:
    virtual ImuData get_imu_data() = 0;
};

class Proxi
{
  public:
    virtual int get_distance() = 0;
};

#endif // HYPED_DRIVERS_INTERFACES_HPP_
