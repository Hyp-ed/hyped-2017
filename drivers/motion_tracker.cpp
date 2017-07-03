#include "motion_tracker.hpp"
#include <chrono>

MotionTracker::MotionTracker() : rotation(Vector3D<double>()), velocity(Vector3D<double>()), displacement(Vector3D<double>())
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

bool MotionTracker::start()
{
  const int n = 10000;
  //Calibrate gyros
  for (Gyroscope &g : this->gyroscopes)
    g.calibrate_gyro(n);
  for (Imu &imu : this->imus)
    imu.calibrate_gyro(n);
  // Calibrate accelerometers
  this->accelerometer_offsets = new Vector3D<double>[this->accelerometers.size()];
  this->imu_accl_offsets = new Vector3D<double>[this->imus.size()];
  for (unsigned int i = 0; i < n; ++i)
  {
    for (unsigned int j = 0; j < this->accelerometers.size(); ++j)
      this->accelerometer_offsets[j] += this->accelerometers[j].get().get_acceleration();
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

Vector3D<double> MotionTracker::get_rotation()
{
  return this->rotation.load(std::memory_order_relaxed);
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
  return duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count() / 1.0e+9;
}

void MotionTracker::track()
{
  Vector3D<double> avg_accl_offset;
  for (unsigned int i = 0; i < this->accelerometers.size(); ++i)
    avg_accl_offset += this->accelerometer_offsets[i];
  for (unsigned int i = 0; i < this->imus.size(); ++i)
    avg_accl_offset += this->imu_accl_offsets[i];
  avg_accl_offset /= (double) (this->accelerometers.size() + this->imus.size());

  Vector3D<double> rotation, displacement;
  DataPoint<Vector3D<double>> velocity, new_velocity;
  DataPoint<Vector3D<double>> accl0, accl, angv0, angv;
  this->get_imu_data_points(accl0, angv0);
  accl0.value -= avg_accl_offset;
  while(!this->stop_flag)
  {
    this->get_imu_data_points(accl, angv);
    accl.value -= avg_accl_offset;
    rotation += DataPoint<Vector3D<double>>::integrate(angv0, angv).value;
    new_velocity = DataPoint<Vector3D<double>>::integrate(accl0, accl);
    new_velocity.value += velocity.value;
    displacement += DataPoint<Vector3D<double>>::integrate(velocity, new_velocity).value;
    velocity = new_velocity;
    this->rotation.store(rotation, std::memory_order_relaxed);
    this->velocity.store(velocity.value, std::memory_order_relaxed);
    this->displacement.store(displacement, std::memory_order_relaxed);
    accl0 = accl;
    angv0 = angv;

    // MPU6050 does 8 gyro readings per 1 acceleration reading (now hardcoded, in the future might add support for arbitrary ratios)
    for (int i = 0; i < 7; ++i)
    {
      get_gyro_data_point(angv);
      rotation += DataPoint<Vector3D<double>>::integrate(angv0, angv).value;
      angv0 = angv;
    }
  }
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
  accl_dp.value *= STD_GRAVITY; // convert from g to m/s^2
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
