#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <fstream>
#include "mpu6050.hpp"

using namespace std;

int main()
{
  printf("Initializing MPU6050...\n");
  Mpu6050 sensor(new I2C);
  SelfTestResult at = sensor.test_accl();
  printf("Accelerometer self-test: passed=%d, x_dev=%f%%, y_dev=%f%%, z_dev=%f%%\n",
      at.passed, at.x_dev, at.y_dev, at.z_dev);
  SelfTestResult gt = sensor.test_gyro();
  printf("Gyroscope self-test: passed=%d, x_dev=%f%%, y_dev=%f%%, z_dev=%f%%\n",
      gt.passed, gt.x_dev, gt.y_dev, gt.z_dev);
  
  printf("is steady clock: %d\n", chrono::steady_clock::is_steady);
  int n = 10000;

  ofstream file("imu-10k_readings.csv");
  //RawSensorData data[n];
  //RawGyroData gdata[n];
  SensorData data[n];

  printf("Calibrating gyro...\n");
  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
  sensor.calibrate_gyro(100000);
  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();  
  chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);  
  printf("time: %fs\n", time_span.count());

  printf("Taking %d readings...\n", n);
  t1 = chrono::steady_clock::now();
  for (int i = 0; i < n; i++)
  {
    /*data[i].accl.x = sensor.get_raw_accl_x();
    data[i].accl.y = sensor.get_raw_accl_y();
    data[i].accl.z = sensor.get_raw_accl_z();
    data[i].gyro.x = sensor.get_raw_gyro_x();
    data[i].gyro.y = sensor.get_raw_gyro_y();
    data[i].gyro.z = sensor.get_raw_gyro_z();//*/
    //data[i] = sensor.get_raw_sensor_data();
    //gdata[i] = sensor.get_raw_gyro_data();
    data[i] = sensor.get_sensor_data();
  }
  t2 = chrono::steady_clock::now();  
  time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);  
  printf("time: %fs\n", time_span.count());

  for (int i = 0; i < n; i++)
  {
    /*file << data[i].accl.x << ","
         << data[i].accl.y << ","
         << data[i].accl.z << ","
         << data[i].gyro.x << ","
         << data[i].gyro.y << ","
         << data[i].gyro.z << endl;//*/
    /*file << gdata[i].x << ","
         << gdata[i].y << ","
         << gdata[i].z << endl;//*/
   file << data[i].accl.x << ","
         << data[i].accl.y << ","
         << data[i].accl.z << ","
         << data[i].temp << ","
         << data[i].angv.x << ","
         << data[i].angv.y << ","
         << data[i].angv.z << endl;
  }
  file.close();//*/
  
  SelfTestResult at2 = sensor.test_accl();
  printf("Accelerometer self-test: passed=%d, x_dev=%f%%, y_dev=%f%%, z_dev=%f%%\n",
      at2.passed, at2.x_dev, at2.y_dev, at2.z_dev);
  SelfTestResult gt2 = sensor.test_gyro();
  printf("Gyroscope self-test: passed=%d, x_dev=%f%%, y_dev=%f%%, z_dev=%f%%\n",
      gt2.passed, gt2.x_dev, gt2.y_dev, gt2.z_dev);
}
