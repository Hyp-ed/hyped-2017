#include "i2c.hpp"
#include "mpu6050.hpp"
#include "motion_tracker.hpp"
#include "vector3d.hpp"

#include <ncurses.h>
#include <thread>
#include <chrono>

int main()
{
  initscr();
  raw();
  noecho();
  timeout(0);
    
  mvprintw(0, 0, "                 x          y          z");
  mvprintw(1, 0, "Rotation     ");
  mvprintw(2, 0, "Velocity     ");
  mvprintw(3, 0, "Displacement ");
  move(4, 0);
  refresh();

  I2C i2c;
  Mpu6050 imu1(&i2c);
  //Mpu6050 imu2(&i2c, ALTERNATIVE_SLAVE_ADDR); //uncomment to use 2 imus
  MotionTracker mt;
  mt.add_imu(imu1);
  //mt.add_imu(imu2); //uncomment to use 2 imus
  mt.start();
  mvprintw(4, 0, "Type any character to exit");
  move(5, 0);
  refresh();
  int stop = getch();
  while (stop == ERR)
  {
    Vector3D<double> v = mt.get_rotation();
    mvprintw(1, 13, "%9.6f  %9.6f  %9.6f", v.x, v.y, v.z);
    v = mt.get_velocity();
    mvprintw(2, 13, "%9.6f  %9.6f  %9.6f", v.x, v.y, v.z);
    v = mt.get_displacement();
    mvprintw(3, 13, "%9.6f  %9.6f  %9.6f", v.x, v.y, v.z);
    move(5, 0);
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    stop = getch();
  }
  mt.stop();

  //getch();
  endwin();
}