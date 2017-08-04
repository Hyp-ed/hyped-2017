#include <chrono>
#include <cmath>
#include <ncurses.h>
#include <thread>

#include "i2c.hpp"
#include "mpu6050.hpp"
#include "motion_tracker.hpp"
#include "quaternion.hpp"
#include "vector3d.hpp"

#define GYRO_POS 5
#define ACCL_POS 9 

bool two_imus;
I2C i2c;
Mpu6050 imu1(&i2c);
Mpu6050* imu2 = nullptr;
MotionTracker mt;

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
  finalize();//*/

  /*mvprintw(0, 0, "Angular velocity = " );
  mvprintw(1, 0, "Rotor = ");
  mvprintw(2, 0, "R*k*R^-1 = ( 0.000,  0.000,  1.000)   Angle: ");
  mvprintw(4, 0, "                 x          y          z          total");
  mvprintw(5, 0, "Acceleration  ");
  mvprintw(6, 0, "Velocity      ");
  mvprintw(7, 0, "Displacement  ");
  move(8, 0);
  refresh();

  I2C i2c;
  Mpu6050 imu1(&i2c);
  Mpu6050 imu2(&i2c, ALTERNATIVE_SLAVE_ADDR); //uncomment to use 2 imus
  MotionTracker mt;
  mt.add_imu(imu1);
  mt.add_imu(imu2); //uncomment to use 2 imus
  mt.start();
  mvprintw(9, 0, "Type any character to exit");
  move(10, 0);
  refresh();
  mt.stop();

  //getch();
  endwin();//*/
}

void setup()
{
  mt.add_imu(imu1);
  if (two_imus)
  {
    imu2 = new Mpu6050(&i2c, ALTERNATIVE_SLAVE_ADDR);
    mt.add_imu(*imu2);
  }
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
}

