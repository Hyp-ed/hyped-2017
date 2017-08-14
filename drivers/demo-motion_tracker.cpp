#include <array>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <functional>
#include <ncurses.h>
#include <string>
#include <thread>

#include "i2c.hpp"
#include "mpu6050.hpp"
#include "motion_tracker.hpp"
#include "quaternion.hpp"
#include "vector3d.hpp"
#include "vl6180.hpp"

#define GYRO_POS 5
#define ACCL_POS 9 

#define SENSOR1_PIN PIN22
#define SENSOR2_PIN PIN23
#define SENSOR3_PIN PIN24
#define SENSOR4_PIN PIN25
#define SENSOR5_PIN PIN4
#define SENSOR6_PIN PIN18


bool two_imus;
I2C i2c;
Mpu6050 imu1(&i2c);
Mpu6050* imu2 = nullptr;
MotionTracker mt;
Vl6180Factory& factory = Vl6180Factory::instance(&i2c);

void setup();
void finalize();
void file_output();
void screen_output();

int main()
{
  initscr();
  raw();
  noecho();
  timeout(0);

  mvprintw(0, 0, "Enter the number of MPU6050 sensors to be used (1 or 2)");
  move(1, 0);
  refresh();
  int opt = getch();
  while(opt != '1' && opt != '2')
    opt = getch();
  two_imus = (opt == '2');
  mvaddch(1, 0, opt);
  refresh();

  mvprintw(2, 0, "Press 'f' for output to file or 's' for output on screen");
  move(3, 0);
  refresh();
  opt = getch();
  while(opt != 'f' && opt != 's')
    opt = getch();
  mvaddch(3, 0, opt);
  move(4, 0);
  refresh();
  if (opt == 'f')
  {
    endwin();
    file_output();
  }
  else
  {
    screen_output();
    endwin();
  }
  finalize();
}

void setup()
{
  mt.add_imu(imu1);
  if (two_imus)
  {
    imu2 = new Mpu6050(&i2c, ALTERNATIVE_SLAVE_ADDR);
    mt.add_imu(*imu2);
  }

  std::array<Vl6180*, 6> sensors;
  sensors[0] = &(factory.make_sensor(SENSOR1_PIN));
  sensors[1] = &(factory.make_sensor(SENSOR2_PIN));
  sensors[2] = &(factory.make_sensor(SENSOR3_PIN));
  sensors[3] = &(factory.make_sensor(SENSOR4_PIN));
  sensors[4] = &(factory.make_sensor(SENSOR5_PIN));
  sensors[5] = &(factory.make_sensor(SENSOR6_PIN));
  for (int i = 0; i < 6; ++i)
  {
    sensors[i]->turn_on();
    sensors[i]->set_intermeasurement_period(10);
    sensors[i]->set_continuous_mode(true);
  }
  mt.add_ground_proxi(*sensors[0], Vector3D<double>(500, 1000, 0));
  mt.add_ground_proxi(*sensors[1], Vector3D<double>(500, -1000, 0));
  mt.add_ground_proxi(*sensors[2], Vector3D<double>(-500, -1000, 0));
  mt.add_ground_proxi(*sensors[3], Vector3D<double>(-500, 1000, 0));
  mt.add_brake_proxis(*sensors[4], *sensors[5], RailSide::left);

  mt.start();
}

void finalize()
{
  mt.stop();
  if (two_imus)
    delete imu2;
}

void screen_output()
{
  mvprintw(GYRO_POS, 0, "Calibrating, please wait...");
  move(GYRO_POS + 1, 0);
  refresh();
  setup();
  mvprintw(ACCL_POS + 5, 0, "Type any character to exit");
  mvprintw(ACCL_POS, 0,
      "                    x             y             z             total");
  move(ACCL_POS + 6, 0);
  refresh();
  int stop = getch();
  while (stop == ERR)
  {
    Vector3D<double> v = mt.get_angular_velocity();
    mvprintw(GYRO_POS, 0, "Angular velocity: (%10.6f,  %10.6f,  %10.6f)",
        v.x, v.y, v.z);
    Quaternion r = mt.get_rotor();
    mvprintw(GYRO_POS + 1, 0,
        "Rotor: (%12.6f, %12.6f, %12.6f, %12.6f)   Norm: %12.6f",
        r.scal, r.vect.x, r.vect.y, r.vect.z, Quaternion::norm(r));
    Vector3D<double> up(0,0,1);
    up = r*up*Quaternion::inv(r);
    double norm = Quaternion::norm(up);
    mvprintw(GYRO_POS + 2, 0,
        "R*k*R^-1 = (%6.3f, %6.3f, %6.3f)   Norm:%6.3f   Angle: %6.3f",
        up.x, up.y, up.z, norm, acos(up.z / norm) * 180.0 / PI);

    v = mt.get_acceleration();
    mvprintw(ACCL_POS + 1, 0, "Acceleration  %12.6f  %12.6f  %12.6f   %12.6f",
        v.x, v.y, v.z, Quaternion::norm(v));
    v = mt.get_velocity();
    mvprintw(ACCL_POS + 2, 0, "Velocity      %12.6f  %12.6f  %12.6f   %12.6f",
        v.x, v.y, v.z, Quaternion::norm(v));
    v = mt.get_displacement();
    mvprintw(ACCL_POS + 3, 0, "Displacement  %12.6f  %12.6f  %12.6f   %12.6f",
        v.x, v.y, v.z, Quaternion::norm(v));
    move(ACCL_POS + 6, 0);
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    stop = getch();
  }
}

void file_output()
{
  std::string filename;
  if (two_imus)
    filename = "motion_tracker-double_IMU-data.csv";
  else
    filename = "motion_tracker-single_IMU-data.csv";
  std::ofstream file(filename);

  Vector3D<double> v;
  Quaternion q;
  int n = 0;
  std::chrono::seconds test_duration(120); //specifies for how long samples will be taken
  std::chrono::milliseconds sampling_period(10); //timeout between taking two samples
  std::chrono::time_point<std::chrono::steady_clock> t0, t;

  printf("Calibrating...\n");
  t0 = std::chrono::steady_clock::now();
  setup();
  t = std::chrono::steady_clock::now();
  printf("took %fs\n\n",
      (double) std::chrono::duration_cast<std::chrono::microseconds>(t - t0)
          .count()
      / 1.0e+6);

  printf("Collecting data for about %lld seconds\n", test_duration.count());
  t = t0 = std::chrono::steady_clock::now();
  while (t - t0 < test_duration)
  {
    ++n;
    file << n << ",";
    t = std::chrono::steady_clock::now();
    file <<
        std::chrono::duration_cast<std::chrono::microseconds>(t - t0).count()
        << ",";
    v = mt.get_angular_velocity();
    file << v.x << "," << v.y << "," << v.z << ",";
    q = mt.get_rotor();
    file << q.scal << ","
         << q.vect.x << ","
         << q.vect.y << ","
         << q.vect.z << ",";
    v = mt.get_acceleration();
    file << v.x << "," << v.y << "," << v.z << ",";
    v = mt.get_velocity();
    file << v.x << "," << v.y << "," << v.z << ",";
    v = mt.get_displacement();
    file << v.x << "," << v.y << "," << v.z << std::endl;

    std::this_thread::sleep_for(sampling_period);
  }
  printf("Stored %d samples to the file %s\n", n, filename.c_str());
  std::chrono::milliseconds time =
      std::chrono::duration_cast<std::chrono::milliseconds>(t - t0);
  printf("Desired time: %llds\n", test_duration.count());
  printf("Actual time:  %fs\n", (double) time.count() / 1000.0);
  printf("Desired sampling period: %lldms\n", sampling_period.count());
  printf("Actual sampling period:  %fms\n\n", (double) time.count() / n);

  file.close();
}

