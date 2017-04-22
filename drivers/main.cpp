#include <cstdlib>
#include <cstdio>
//#include <ctime>
//#include <ratio>
#include <chrono>
#include <fstream>
#include "mpu6050.hpp"

using namespace std;

int main()
{
  //using namespace std::chrono;  
  printf("is steady clock: %d\n", chrono::steady_clock::is_steady);
  int n = 10000;

  ofstream file("imu-10k_readings.csv");
  RawSensorData data[n];

  Mpu6050 sensor(new I2C);
  printf("Taking %d readings...\n", n);
  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

  for (int i = 0; i < n; i++)
  {
    /*data[i].accl.x = sensor.get_raw_accl_x();
    data[i].accl.y = sensor.get_raw_accl_y();
    data[i].accl.z = sensor.get_raw_accl_z();
    data[i].gyro.x = sensor.get_raw_gyro_x();
    data[i].gyro.y = sensor.get_raw_gyro_y();
    data[i].gyro.z = sensor.get_raw_gyro_z();//*/
    data[i] = sensor.get_raw_sensor_data();
  }

  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();  
  chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);  
  printf("time: %f\n", time_span.count());

  for (int i = 0; i < n; i++)
  {
    file << data[i].accl.x << ","
         << data[i].accl.y << ","
         << data[i].accl.z << ","
         << data[i].gyro.x << ","
         << data[i].gyro.y << ","
         << data[i].gyro.z << endl;
  }
  file.close();
}