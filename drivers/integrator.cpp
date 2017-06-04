#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <fstream>
#include <iostream>
#include "vector3d.hpp"
#include "mpu6050.hpp"

long long timestamp() {
  using namespace std::chrono;
  return duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
}

using namespace std;

int main()
{
  printf("Initializing MPU6050...");
  I2C i2c;
  Mpu6050 sensor(&i2c);
  Mpu6050 sensor2(&i2c, ALTERNATIVE_SLAVE_ADDR);
  printf(" done\n");

  printf("Calibrating gyros...\n");
  long long t1 = timestamp();
  sensor.calibrate_gyro(100000);
  sensor2.calibrate_gyro(100000);
  long long t2 = timestamp(); 
  printf("time: %fs\n", (t2 - t1)/1.0e+9);

  Vector3D<double> accl_offset;
  Vector3D<double> accl2_offset;
  printf("Calibrating accelerometers...\n");
  t1 = timestamp();
  for (int i = 0; i < 100000; i++)
  {
    accl_offset += sensor.get_acceleration();
    accl2_offset += sensor2.get_acceleration();
  }
  accl_offset /= 1.0e+5;
  accl2_offset /= 1.0e+5;
  t2 = timestamp(); 
  printf("time: %fs\n", (t2 - t1)/1.0e+9);

  const int n = 100000;
  long long *times = new long long[n];
  SensorData **readings = new SensorData*[2];
  readings[0] = new SensorData[n];
  readings[1] = new SensorData[n];
  Vector3D<double> *rotation = new Vector3D<double>[n]; // degrees
  Vector3D<double> *velocity = new Vector3D<double>[n]; // m/s
  Vector3D<double> *position = new Vector3D<double>[n]; // m
  double dt;

  cout << rotation[0].x << ", " << rotation[0].y << ", " << rotation[0].z << endl;
  cout << velocity[0].x << ", " << velocity[0].y << ", " << velocity[0].z << endl;
  cout << position[0].x << ", " << position[0].y << ", " << position[0].z << endl;
  printf("Taking %d readings...\n", n);
  readings[0][0] = sensor.get_sensor_data();
  times[0] = timestamp();
  readings[1][0] = sensor2.get_sensor_data();
  for (int i = 1; i < n; i++)
  {
    //printf("test\n");
    readings[0][i] = sensor.get_sensor_data();
    times[i] = timestamp();
    readings[1][i] = sensor2.get_sensor_data();

    dt = (times[i] - times[i-1]) / 1e+9;
    //printf("test\n");
    rotation[i] = rotation[i-1] +
        dt * (readings[0][i-1].angv + readings[1][i-1].angv +
        readings[0][i].angv + readings[1][i].angv) / 4.0;
    velocity[i] = velocity[i-1] +
        dt * ((readings[0][i-1].accl + readings[1][i-1].accl +
        readings[0][i].accl + readings[1][i].accl) / 4.0 - accl_offset / 2.0 - accl2_offset / 2.0);
    
    position[i] = position[i-1] + dt * (velocity[i-1] + velocity[i]) / 2.0;
    //printf("test\n");
  }
  printf("time: %fs\n", (times[n-1] - times[0])/1.0e+9);

  ofstream file("double_imu-10k_integration_test.csv");
  for (int i = 0; i < n; i++)
  {
    file << times[i] << ",,"
         << readings[0][i].accl.x << ","
         << readings[0][i].accl.y << ","
         << readings[0][i].accl.z << ","
         << readings[0][i].temp << ","
         << readings[0][i].angv.x << ","
         << readings[0][i].angv.y << ","
         << readings[0][i].angv.z << ",,"

         << readings[1][i].accl.x << ","
         << readings[1][i].accl.y << ","
         << readings[1][i].accl.z << ","
         << readings[1][i].temp << ","
         << readings[1][i].angv.x << ","
         << readings[1][i].angv.y << ","
         << readings[1][i].angv.z << ",,"
         
         << rotation[i].x << ","
         << rotation[i].y << ","
         << rotation[i].z << ",,"
         
         << velocity[i].x << ","
         << velocity[i].y << ","
         << velocity[i].z << ",,"
         
         << position[i].x << ","
         << position[i].y << ","
         << position[i].z << endl;
  }
  file.close();

  delete[] times;
  delete[] readings[0];
  delete[] readings[1];
  delete[] readings;
  delete[] rotation;
  delete[] velocity;
  delete[] position;
}