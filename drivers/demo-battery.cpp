#include "battery.hpp"

#include <chrono>
#include <ncurses.h>
#include <thread>

#include "i2c.hpp"

int main()
{
  initscr();
  raw();
  noecho();
  timeout(0);

  mvprintw(0, 0, "Initializing... Please wait.");
  move(1, 0);
  refresh();
  
  I2C bus;
  Battery bat(&bus);
  int stop = getch();
  mvprintw(16, 0, "Type any letter to exit");
  move(17, 0);
  while (stop == ERR)
  {
    BatteryData bd = bat.get_data();

    mvprintw(0, 0, "Big battery 1");
    mvprintw(1, 0, "  Voltages [mV]:%6d,%6d,%6d,%6d,%6d,%6d,%6d", bd.big1.cell_voltage[0],
        bd.big1.cell_voltage[1], bd.big1.cell_voltage[2], bd.big1.cell_voltage[3],
        bd.big1.cell_voltage[4], bd.big1.cell_voltage[5], bd.big1.cell_voltage[6]);
    mvprintw(2, 0, "  Temperature [degC]:%6d", bd.big1.temperature);
    mvprintw(3, 0, "  Current [A]:%6d", bd.big1.current);
    mvprintw(5, 0, "Big battery 2");
    mvprintw(6, 0, "  Voltages [mV]:%6d,%6d,%6d,%6d,%6d,%6d,%6d", bd.big2.cell_voltage[0],
        bd.big2.cell_voltage[1], bd.big2.cell_voltage[2], bd.big2.cell_voltage[3],
        bd.big2.cell_voltage[4], bd.big2.cell_voltage[5], bd.big2.cell_voltage[6]);
    mvprintw(7, 0, "  Temperature [degC]:%6d", bd.big2.temperature);
    mvprintw(8, 0, "  Current [A]:%6d", bd.big2.current);
    mvprintw(10, 0, "Small battery");
    mvprintw(11, 0, "  Voltages [mV]:%6d,%6d,%6d,%6d,%6d", bd.big1.cell_voltage[0],
        bd.big1.cell_voltage[1], bd.big1.cell_voltage[2], bd.big1.cell_voltage[3],
        bd.big1.cell_voltage[4]);
    mvprintw(12, 0, "  Temperature [degC]:%6d", bd.small.temperature);
    move(17, 0); 
    refresh();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    stop = getch();
  }

  endwin();
}

