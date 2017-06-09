#ifndef INTERFACES_H_
#define INTERFACES_H_

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

#endif // INTERFACES_H_