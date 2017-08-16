#include "motion_tracker.hpp"
#include <chrono>
#include <cmath>
#include <cstdio>
#include <Eigen/Dense>
#include <Eigen/SVD>

MotionTracker::MotionTracker()
    : angular_velocity(Vector3D<double>()),
    rotor(Quaternion(1, 0, 0, 0)),
    acceleration(Vector3D<double>()),
    velocity(Vector3D<double>()),
    displacement(Vector3D<double>())
{}

MotionTracker::~MotionTracker()
{
  this->stop();
}

void MotionTracker::add_accelerometer(Accelerometer &a)
{
  this->accelerometers.push_back(a);
}

void MotionTracker::add_gyroscope(Gyroscope &g)
{
  this->gyroscopes.push_back(g);
}

void MotionTracker::add_imu(Imu &imu)
{
  this->imus.push_back(imu);
}

void MotionTracker::add_ground_proxi(Proxi& sensor, Vector3D<double> position)
{
  for (unsigned int i = 0; i < this->ground_proxi_positions.size(); ++i)
    if (this->ground_proxi_positions[i] == position)
    {
      this->ground_proxis[i].push_back(sensor);
      return;
    }
  this->ground_proxi_positions.push_back(position);
  this->ground_proxis.emplace_back(); //add new vector
  this->ground_proxis.back().push_back(sensor);
}

void MotionTracker::add_brake_proxis(Proxi& front, Proxi& rear, RailSide side)
{
  if (side == RailSide::left)
    this->brakes.emplace_back(front, rear);
  else if (side == RailSide::right)
    this->brakes.emplace_back(rear, front);
}

bool MotionTracker::start()
{
  //TODO: check not already started
  //TODO: check enough sensors configured

  const int n = 10000;
  //Calibrate gyros
  for (Gyroscope &g : this->gyroscopes)
    g.calibrate_gyro(n);
  for (Imu &imu : this->imus)
    imu.calibrate_gyro(n);
  // Calibrate accelerometers
  this->accelerometer_offsets =
      new Vector3D<double>[this->accelerometers.size()];
  this->imu_accl_offsets = new Vector3D<double>[this->imus.size()];
  for (unsigned int i = 0; i < n; ++i)
  {
    for (unsigned int j = 0; j < this->accelerometers.size(); ++j)
      this->accelerometer_offsets[j] +=
          this->accelerometers[j].get().get_acceleration();
    for (unsigned int j = 0; j < this->imus.size(); ++j)
      this->imu_accl_offsets[j] += this->imus[j].get().get_acceleration();
  }
  for (unsigned int i = 0; i < this->accelerometers.size(); ++i)
    this->accelerometer_offsets[i] /= (double) n;
  for (unsigned int i = 0; i < this->imus.size(); ++i)
    this->imu_accl_offsets[i] /= (double) n;

  this->stop_flag = false;
  this->tracking_thread = std::thread(&MotionTracker::track, this);

  return true;
}

void MotionTracker::stop()
{
  this->stop_flag = true;
  this->tracking_thread.join();
  delete[] this->accelerometer_offsets;
  this->accelerometer_offsets = nullptr;
  delete[] this->imu_accl_offsets;
  this->imu_accl_offsets = nullptr;
}

Vector3D<double> MotionTracker::get_angular_velocity()
{
  return this->angular_velocity.load(std::memory_order_relaxed);
}

Quaternion MotionTracker::get_rotor()
{
  return this->rotor.load(std::memory_order_relaxed);
}

Vector3D<double> MotionTracker::get_acceleration()
{
  return this->acceleration.load(std::memory_order_relaxed);
}

Vector3D<double> MotionTracker::get_velocity()
{
  return this->velocity.load(std::memory_order_relaxed);
}

Vector3D<double> MotionTracker::get_displacement()
{
  return this->displacement.load(std::memory_order_relaxed);
}



inline double timestamp()
{
  using namespace std::chrono;
  return duration_cast<nanoseconds>
    (steady_clock::now().time_since_epoch()).count() / 1.0e+9;
}



void MotionTracker::track()
{
  Vector3D<double> avg_accl_offset;
  for (unsigned int i = 0; i < this->accelerometers.size(); ++i)
    avg_accl_offset += this->accelerometer_offsets[i];
  for (unsigned int i = 0; i < this->imus.size(); ++i)
    avg_accl_offset += this->imu_accl_offsets[i];
  avg_accl_offset /= (double) (this->accelerometers.size() + this->imus.size());

  Quaternion rotor(1, 0, 0, 0);
  Vector3D<double> dist(0.0, 0.0, 0.0);
  DataPoint<Vector3D<double>> velocity, new_velocity;
  DataPoint<Vector3D<double>> accl0, accl, angv0, angv;
  this->get_imu_data_points(accl0, angv0);
  accl0.value -= avg_accl_offset;
  velocity.timestamp = accl0.timestamp;
  double t0 = accl0.timestamp;
  while(!this->stop_flag)
  {
    this->get_imu_data_points(accl, angv);
    
    // Update R(t)
    double l = Quaternion::norm(angv0.value);
    double theta = (angv.timestamp - angv0.timestamp) * l / 2.0;
    rotor = cos(theta) * rotor + sin(theta) * rotor * angv0.value / l;
    
    // Rotate acceleration
    accl.value = rotor * accl.value * Quaternion::inv(rotor) - avg_accl_offset;
    // Update velocity and displacement
    new_velocity = DataPoint<Vector3D<double>>::integrate(accl0, accl);
    new_velocity.value += velocity.value;
    dist +=
        DataPoint<Vector3D<double>>::integrate(velocity, new_velocity).value;
    velocity = new_velocity;
    this->angular_velocity.store(angv.value, std::memory_order_relaxed);
    this->rotor.store(rotor, std::memory_order_relaxed);
    this->acceleration.store(accl.value, std::memory_order_relaxed);
    this->velocity.store(velocity.value, std::memory_order_relaxed);
    this->displacement.store(dist, std::memory_order_relaxed);
    accl0 = accl;
    angv0 = angv;

    // MPU6050 does 8 gyro readings per 1 acceleration reading (now hardcoded, in the future might add support for arbitrary ratios)
    for (int i = 0; i < 7; ++i)
    {
      // Update R(t)
      get_gyro_data_point(angv);
      l = Quaternion::norm(angv0.value);
      theta = (angv.timestamp - angv0.timestamp) * l / 2.0;
      rotor = cos(theta) * rotor + sin(theta) * rotor * angv0.value / l;
      angv0 = angv;
    }

    if (angv0.timestamp - t0 > 0.01 && this->ground_proxis.size() >= 3)
    {
      rotor *= Quaternion::pow(Quaternion::inv(rotor) * this->get_proxi_rotor(),
          PROXI_WEIGHT);
      t0 = angv0.timestamp;
    }
  }
}

Quaternion MotionTracker::get_proxi_rotor()
{
  Eigen::Matrix<double, 3, Eigen::Dynamic> m(3, this->ground_proxis.size());
  for (unsigned int i = 0; i < this->ground_proxis.size(); ++i)
  {
    double avg_dist = 0.0;
    for (Proxi& p : this->ground_proxis[i])
      avg_dist += p.get_distance();
    avg_dist /= this->ground_proxis[i].size();
    m.col(i) << this->ground_proxi_positions[i].x,
                this->ground_proxi_positions[i].y,
                this->ground_proxi_positions[i].z + avg_dist;
  }
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(m, Eigen::ComputeThinU);
  // Normal vector of the best-fit plane:
  Eigen::Vector3d n = svd.matrixU().col(svd.matrixU().cols() - 1);
  if (n(2) < 0.0)
    n = -n;
  double angle = acos(n(2) / n.norm());
  Vector3D<double> axis(n(1), -n(0), 0); //cross product of n and (0, 0, 1)
  double l = Quaternion::norm(axis);
  Quaternion r1(cos(angle/2.0), sin(angle/2.0) * ((l == 0.0) ? axis : axis / l));
  
  angle = 0.0;
  for (unsigned int i = 0; i < this->brakes.size(); ++i)
    angle += atan((double) (this->brakes[i].front->get_distance()
          - this->brakes[i].rear->get_distance()) / BRAKE_PROXI_SEPARATION);
  angle /= this->brakes.size();
  Quaternion r2(cos(angle/2.0), Vector3D<double>(0, 0, sin(angle/2.0)));

  return r2*r1;
}

void MotionTracker::get_imu_data_points(
    DataPoint<Vector3D<double>> &accl_dp,
    DataPoint<Vector3D<double>> &angv_dp)
{
  accl_dp.value.x = 0.0;
  accl_dp.value.y = 0.0;
  accl_dp.value.z = 0.0;
  angv_dp.value.x = 0.0;
  angv_dp.value.y = 0.0;
  angv_dp.value.z = 0.0;
  accl_dp.timestamp = timestamp();
  for (Accelerometer &a : this->accelerometers)
    accl_dp.value += a.get_acceleration();
  angv_dp.timestamp = timestamp();
  for (Imu &imu : this->imus)
  {
    ImuData data = imu.get_imu_data();
    accl_dp.value += data.acceleration;
    angv_dp.value += data.angular_velocity;
  }
  double t = timestamp();
  for (Gyroscope &g : this->gyroscopes)
    angv_dp.value += g.get_angular_velocity();
  angv_dp.timestamp += timestamp();
  angv_dp.timestamp /= 2.0;
  accl_dp.timestamp = (accl_dp.timestamp + t) / 2.0;
  accl_dp.value /= (double) (this->accelerometers.size() + this->imus.size());
  angv_dp.value /= (double) (this->gyroscopes.size() + this->imus.size());
}

void MotionTracker::get_gyro_data_point(DataPoint<Vector3D<double>> &angv_dp)
{
  angv_dp.value.x = 0.0;
  angv_dp.value.y = 0.0;
  angv_dp.value.z = 0.0;
  angv_dp.timestamp = timestamp();
  for (Gyroscope &g : this->gyroscopes)
    angv_dp.value += g.get_angular_velocity();
  for (Imu &imu : this->imus)
    angv_dp.value += imu.get_angular_velocity();
  angv_dp.timestamp += timestamp();
  angv_dp.timestamp /= 2.0;
  angv_dp.value /= (double) (this->gyroscopes.size() + this->imus.size());
}

