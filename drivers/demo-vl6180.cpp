#include "vl6180.hpp"

#include <chrono>
#include <cstdio>
#include <fstream>
#include <ncurses.h>
#include <string>
#include <thread>
#include <vector>

#include "gpio.hpp"
#include "i2c.hpp"

bool continuous_mode;
std::vector<Vl6180*> sensors;

inline double timestamp()
{
  using namespace std::chrono;
  return duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count() / 1.0e+9;
}

void file_output()
{
  const int n = 10000;
  double* timestamps = new double[n];
  int* data = new int[n];
  std::string filename;
  if (continuous_mode)
    filename = "vl6180-cont_mode-";
  else
    filename = "vl6180-singleshot_mode-";
  filename += std::to_string(n/1000) + "k_readings.csv";

  printf("Initializing...\n");
  double t, t0 = timestamp();
  I2C i2c;
  Vl6180Factory& factory = Vl6180Factory::instance(&i2c);
  Vl6180& sensor = factory.make_sensor(PIN18);
  std::this_thread::sleep_for(std::chrono::seconds(3));
  sensor.turn_on();
  sensor.set_intermeasurement_period(10);
  sensor.set_continuous_mode(continuous_mode);
  t = timestamp();
  printf("took %fs\n\n", t - t0 - 3.0);

  printf("Taking %d readings...\n", n);
  t0 = timestamp();
  for (int i = 0; i < n; ++i)
  {
    timestamps[i] = timestamp();
    data[i] = sensor.get_distance();
  }
  t = timestamp();
  printf("time = %fs\n", t - t0);
  printf("average period = %fms\n", (t - t0) / n * 1000.0);
  printf("average frequency = %fHz\n\n", (double) n / (t - t0));

  printf("Saving to file %s...\n", filename.c_str());
  t0 = timestamp();
  std::ofstream file(filename);
  file.precision(16);
  for (int i = 0; i < n; ++i)
    file << timestamps[i] << "," << data[i] << std::endl;
  file.close();
  t = timestamp();
  printf("took %fs\n", t - t0);

  delete[] timestamps;
  delete[] data;
}

void screen_output()
{
  mvprintw(5, 0, "Distance:    mm");
  mvprintw(6, 0, "Measurement period:    ms");
  refresh();

  I2C i2c;
  Vl6180Factory& factory = Vl6180Factory::instance(&i2c);
  Vl6180& sensor = factory.make_sensor(PIN18);
  std::this_thread::sleep_for(std::chrono::seconds(3));
  sensor.turn_on();
  sensor.set_intermeasurement_period(10);
  sensor.set_continuous_mode(continuous_mode);
  mvprintw(7, 0, "Type any character to exit");
  move(8, 0);
  refresh();
  int stop = getch();
  while (stop == ERR)
  {
    double t0 = timestamp();
    int dist = sensor.get_distance();
    double t = timestamp();
    mvprintw(5, 10, "%3dmm", dist);
    mvprintw(6, 20, "%7.3fms   ", (t - t0) * 1000.0);
    move(8, 0);
    refresh();
    stop = getch();
  }
}

int main()
{
  initscr();
  raw();
  noecho();
  timeout(0);

  mvprintw(0, 0, "Press 'c' for continuous mode or 's' for single-shot mode");
  move(1, 0);
  refresh();
  int opt = getch();
  while(opt != 'c' && opt != 's')
    opt = getch();
  continuous_mode = (opt == 'c');
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
  }//*/



  /*I2C i2c;
  Vl6180Factory& factory = Vl6180Factory::instance(&i2c);
  Vl6180& sensor = factory.make_sensor(PIN18);
  std::this_thread::sleep_for(std::chrono::seconds(3));
  sensor.turn_on();
  //sensor.set_continuous_mode(true);
  while(true)
  {
    double t, t0 = timestamp();
    int d = sensor.get_distance();
    t = timestamp();
    printf("Distance: %3dmm  Time: %fms\n", d, (t - t0) * 1000.0);

  }//*/
}

