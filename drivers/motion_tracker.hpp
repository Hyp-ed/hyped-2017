#ifndef MOTION_TRACKER_HPP_
#define MOTION_TRACKER_HPP_

#include <array>
#include <atomic>
#include <functional>
#include <thread>
#include <vector>

#include "data_point.hpp"
#include "interfaces.hpp"
#include "quaternion.hpp"
#include "vector3d.hpp"

#define BRAKE_PROXI_SEPARATION 250.0 //mm

const double GYRO_WEIGHT = 0.99;
const double PROXI_WEIGHT = 1 - GYRO_WEIGHT;

enum class RailSide
{
  left,
  right
};

struct BrakingSki
{
  BrakingSki(Proxi& front, Proxi& rear) : front(&front), rear(&rear)
  {}
  Proxi *front, *rear;
};

class MotionTracker
{
  public:
    MotionTracker();
    ~MotionTracker();

    void add_accelerometer(Accelerometer &a);
    void add_gyroscope(Gyroscope &g);
    void add_imu(Imu &imu);
    void add_ground_proxi(Proxi& sensor, Vector3D<double> position);
    void add_brake_proxis(Proxi& front, Proxi& rear, RailSide side);
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
    std::vector<Vector3D<double>> ground_proxi_positions;
    std::vector<std::vector< std::reference_wrapper<Proxi>>> ground_proxis;
    std::vector<BrakingSki> left_brakes;
    std::vector<BrakingSki> right_brakes;
    std::atomic_bool stop_flag {true};
    std::thread tracking_thread;
    Vector3D<double> *accelerometer_offsets = nullptr;
    Vector3D<double> *imu_accl_offsets = nullptr;
    double initial_ground_dist = 0;
    double rail_offset = 0;

    std::atomic<Vector3D<double>> angular_velocity; 
    std::atomic<Quaternion> rotor;
    std::atomic<Vector3D<double>> acceleration;
    std::atomic<Vector3D<double>> velocity;
    std::atomic<Vector3D<double>> displacement;

    void track();
    //Quaternion get_proxi_rotor();
    void get_imu_data_points(DataPoint<Vector3D<double>> &acceleration,
        DataPoint<Vector3D<double>> &angular_velocity);
    void get_gyro_data_point(DataPoint<Vector3D<double>> &angular_velocity);
};

#endif // MOTION_TRACKER_HPP_
