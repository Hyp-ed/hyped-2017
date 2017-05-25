#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <fstream>
#include "mpu6050.hpp"

using namespace std;

int main()
{
  printf("Initializing MPU6050...\n");
  I2C i2c;
  Mpu6050 sensor(&i2c);
  Mpu6050 sensor2(&i2c, ALTERNATIVE_SLAVE_ADDR);
  SelfTestResult str = sensor.test_accl();
  printf("Accelerometer1 self-test: passed=%d, x_dev=%.1f%%, y_dev=%.1f%%, z_dev=%.1f%%\n",
      str.passed, str.x_dev, str.y_dev, str.z_dev);
  str = sensor2.test_accl();
  printf("Accelerometer2 self-test: passed=%d, x_dev=%.1f%%, y_dev=%.1f%%, z_dev=%.1f%%\n",
      str.passed, str.x_dev, str.y_dev, str.z_dev);
  str = sensor.test_gyro();
  printf("Gyroscope1 self-test: passed=%d, x_dev=%.1f%%, y_dev=%.1f%%, z_dev=%.1f%%\n",
      str.passed, str.x_dev, str.y_dev, str.z_dev);
  str = sensor2.test_gyro();
  printf("Gyroscope2 self-test: passed=%d, x_dev=%.1f%%, y_dev=%.1f%%, z_dev=%.1f%%\n",
      str.passed, str.x_dev, str.y_dev, str.z_dev);
  
  printf("is steady clock: %d\n", chrono::steady_clock::is_steady);

  printf("Calibrating gyro...\n");
  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
  sensor.calibrate_gyro(100000);
  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();  
  chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);  
  printf("time: %fs\n", time_span.count());

  
  int n = 10000;
  //RawSensorData data[n];
  //RawGyroData gdata[n];
  SensorData data[n];
  printf("Taking %d readings...\n", n);
  t1 = chrono::steady_clock::now();
  for (int i = 0; i < n; i++)
  {
    //data[i] = sensor.get_raw_sensor_data();
    //gdata[i] = sensor.get_raw_gyro_data();
    data[i] = sensor.get_sensor_data();
  }
  t2 = chrono::steady_clock::now();  
  time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);  
  printf("time: %fs\n", time_span.count());


  ofstream file("imu-10k_readings.csv");
  for (int i = 0; i < n; i++)
  {
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
  
  str = sensor.test_accl();
  printf("Accelerometer1 self-test: passed=%d, x_dev=%.1f%%, y_dev=%.1f%%, z_dev=%.1f%%\n",
      str.passed, str.x_dev, str.y_dev, str.z_dev);
  str = sensor2.test_accl();
  printf("Accelerometer2 self-test: passed=%d, x_dev=%.1f%%, y_dev=%.1f%%, z_dev=%.1f%%\n",
      str.passed, str.x_dev, str.y_dev, str.z_dev);
  str = sensor.test_gyro();
  printf("Gyroscope1 self-test: passed=%d, x_dev=%.1f%%, y_dev=%.1f%%, z_dev=%.1f%%\n",
      str.passed, str.x_dev, str.y_dev, str.z_dev);
  str = sensor2.test_gyro();
  printf("Gyroscope2 self-test: passed=%d, x_dev=%.1f%%, y_dev=%.1f%%, z_dev=%.1f%%\n",
      str.passed, str.x_dev, str.y_dev, str.z_dev);
}
