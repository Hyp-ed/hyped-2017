#ifndef MOTION_TRACKER_HPP_
#define MOTION_TRACKER_HPP_

#include <atomic>
#include <functional>
#include <thread>
#include <vector>

#include "data_point.hpp"
#include "interfaces.hpp"
#include "quaternion.hpp"
#include "vector3d.hpp"

#define STD_GRAVITY 9.80665

class MotionTracker
{
  public:
    MotionTracker();
    ~MotionTracker();

    void add_accelerometer(Accelerometer &a);
    void add_gyroscope(Gyroscope &g);
    void add_imu(Imu &imu);
    bool start();
    void stop();
    Vector3D<double> get_angular_velocity();
    Quaternion get_rotor();
    Vector3D<double> get_acceleration();
    Vector3D<double> get_velocity();
    Vector3D<double> get_displacement();

  private:
    std::vector<std::reference_wrapper<Accelerometer>> accelerometers;
    std::vector<std::reference_wrapper<Gyroscope>> gyroscopes;
    std::vector<std::reference_wrapper<Imu>> imus;
    std::atomic_bool stop_flag {true};
    std::thread tracking_thread;
    Vector3D<double> *accelerometer_offsets = nullptr;
    Vector3D<double> *imu_accl_offsets = nullptr;

    std::atomic<Vector3D<double>> angular_velocity; 
    std::atomic<Quaternion> rotor;
    std::atomic<Vector3D<double>> acceleration;
    std::atomic<Vector3D<double>> velocity;
    std::atomic<Vector3D<double>> displacement;

    void track();
    void get_imu_data_points(DataPoint<Vector3D<double>> &acceleration,
        DataPoint<Vector3D<double>> &angular_velocity);
    void get_gyro_data_point(DataPoint<Vector3D<double>> &angular_velocity);
};

#endif // MOTION_TRACKER_HPP_
