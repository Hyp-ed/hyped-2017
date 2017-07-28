#include "vl6180.hpp"

#include <chrono>
#include <ncurses.h>
#include <thread>

#include "gpio.hpp"
#include "i2c.hpp"


int main()
{
  /*initscr();
  raw();
  noecho();
  timeout(0);
    
  mvprintw(0, 0, "Distance: ");
  move(1, 0);
  refresh();

  I2C i2c;
  Vl6180 sensor(&i2c);
  mvprintw(1, 0, "Type any character to exit");
  move(2, 0);
  refresh();
  int stop = getch();
  while (stop == ERR)
  {
    int dist = sensor.get_distance();
    mvprintw(0, 10, "%3d mm         ", dist);
    move(2, 0);
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    stop = getch();
  }

  //getch();
  endwin();//*/

  I2C i2c;
  Vl6180Factory& factory = Vl6180Factory::instance(&i2c);
  Vl6180& sensor = factory.make_sensor(PIN18);
  std::this_thread::sleep_for(std::chrono::seconds(3));
  sensor.turn_on();
  sensor.set_continuous_mode(true);
  while(true)
  {
    printf("Distance %d mm\n", sensor.get_distance());
  }//*/
}
