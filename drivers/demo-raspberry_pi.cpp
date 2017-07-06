#include "raspberry_pi.hpp"

#include <chrono>
#include <ncurses.h>
#include <thread>

int main()
{
  initscr();
  raw();
  noecho();
  timeout(0);

  mvprintw(0, 0, "CPU Temperature: ");
  move(1, 0);
  refresh();

  RaspberryPi rpi;
  mvprintw(1, 0, "Type any letter to exit");
  move(2, 0);
  refresh();
  int stop = getch();
  while (stop == ERR)
  {
    mvprintw(0, 0, "CPU Temperature: %7.3f\n", rpi.get_temperature());
    move(2, 0);
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    stop = getch();
  }

  endwin();
}
