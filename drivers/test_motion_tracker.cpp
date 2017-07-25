#include <ncurses.h>
#include <thread>
#include <chrono>
#include <cmath>

#include "i2c.hpp"
#include "mpu6050.hpp"
#include "motion_tracker.hpp"
#include "quaternion.hpp"
#include "vector3d.hpp"

const double PI = 3.1415926535897932;

int main()
{
  initscr();
  raw();
  noecho();
  timeout(0);

  mvprintw(0, 0, "Angular velocity = " );
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
  int stop = getch();
  while (stop == ERR)
  {
    Vector3D<double> v = mt.get_angular_velocity();
    mvprintw(0, 19, "(%10.6f,  %10.6f,  %10.6f)", v.x, v.y, v.z);
    Quaternion r = mt.get_rotor();
    mvprintw(1, 8, "(%12.6f, %12.6f, %12.6f, %12.6f)",
        r.scal, r.vect.x, r.vect.y, r.vect.z);
    Vector3D<double> up(0,0,1);
    up = r*up*Quaternion::inv(r);
    mvprintw(2, 0, "R*k*R^-1 = (%6.3f, %6.3f, %6.3f)   Angle: %6.3f",
        up.x, up.y, up.z, acos(up.z / Quaternion::norm(up)) * 180.0 / PI);

    v = mt.get_acceleration();
    mvprintw(5, 14, "%12.6f  %12.6f  %12.6f   %12.6f", v.x, v.y, v.z,
        Quaternion::norm(v));
    v = mt.get_velocity();
    mvprintw(6, 14, "%12.6f  %12.6f  %12.6f   %12.6f", v.x, v.y, v.z,
        Quaternion::norm(v));
    v = mt.get_displacement();
    mvprintw(7, 14, "%12.6f  %12.6f  %12.6f   %12.6f", v.x, v.y, v.z,
        Quaternion::norm(v));
    move(10, 0);
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    stop = getch();
  }
  mt.stop();

  //getch();
  endwin();
}
