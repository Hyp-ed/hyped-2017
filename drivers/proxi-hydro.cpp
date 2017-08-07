#include "vl6180.hpp"

#include "vl6180.hpp"
//extern "C" {
 //   #include "hydraulic_control.h"
#include "hydraulics.h"
//}


#include <chrono>
#include <cstdio>
#include <fstream>
#include <ncurses.h>
#include <string>
#include <thread>
#include <vector>

#include "gpio.hpp"
#include "i2c.hpp"

#define SENSOR_RIGHT_PIN 15
#define SENSOR_LEFT_PIN 16

#define TARGET 110
#define accumulator_pressure 50

bool continuous_mode;
std::vector<Vl6180*> sensors;
//Create an I2C instance to represent the bus
I2C i2c;
// Create factory to produce sensor drivers for that bus
Vl6180Factory& factory = Vl6180Factory::instance(&i2c);

inline double timestamp()
{
  using namespace std::chrono;
  return duration_cast<nanoseconds>(
      steady_clock::now().time_since_epoch()).count() / 1.0e+9;
}

void setup()
{
  // Produce driver instance for the sensor with GPIO0 connected to specified pin
  Vl6180& sensor_ref = factory.make_sensor(SENSOR_RIGHT_PIN);
  // Store pointer to the driver instance
  sensors.push_back(&sensor_ref);

  // Uncoment the following line and possibly add more to use more sensors
  sensors.push_back( &(factory.make_sensor(SENSOR_LEFT_PIN)) );

  for (unsigned int i = 0; i < sensors.size(); ++i)
  {
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    sensors[i]->turn_on();
    sensors[i]->set_intermeasurement_period(10);
    sensors[i]->set_continuous_mode(continuous_mode);
  }
}

void file_output()
{
  // Initialize sensors
  printf("Initializing...\n");
  double t, t0 = timestamp();
  setup();
  t = timestamp();
  printf("took %fs\n\n", t - t0);

  // Setup datastructures
  const int n = 10000;
  std::string filename;
  if (continuous_mode)
    filename = "vl6180-cont_mode-";
  else
    filename = "vl6180-singleshot_mode-";
  filename += std::to_string(n/1000) + "k_readings.csv";
  std::vector<std::vector<double>> times(sensors.size());
  std::vector<std::vector<int>> data(sensors.size());

  // Take readings
  printf("Taking %d readings from each of the %d sensors...\n",
      n, sensors.size());
  t0 = timestamp();
  for (int i = 0; i < n; ++i)
  {
    for (unsigned int j = 0; j < sensors.size(); ++j)
    {
      times[j].push_back(timestamp());
      data[j].push_back(sensors[j]->get_distance());
    }
  }
  t = timestamp();
  printf("time = %fs\n", t - t0);
  printf("average period = %fms\n", (t - t0) / (n * sensors.size()) * 1000.0);
  printf("average frequency = %fHz\n\n",
      (double) (n * sensors.size()) / (t - t0));

  // Store readings
  printf("Saving to file %s...\n", filename.c_str());
  t0 = timestamp();
  std::ofstream file(filename);
  file.precision(16);
  for (int i = 0; i < n; ++i)
  {
    file << times[0][i] << "," << data[0][i];
    for (unsigned int j = 1; j < sensors.size(); ++j)
      file << ",," << times[j][i] << "," << data[j][i];
    file << std::endl;
  }
  file.close();
  t = timestamp();
  printf("took %fs\n", t - t0);
}

void screen_output()
{
  setup();
  mvprintw(7 + 3*sensors.size(), 0, "Type any character to exit");
  move(8 + 3*sensors.size(), 0);
  refresh();
  int stop = getch();
  int proxiright_dist = 0;
  int proxileft_dist = 0;
  bool target_ach_1 = FALSE;
  bool target_ach_2 = FALSE;
  spinup("front");
  while (stop == ERR)
  {
  int sum = 0;
  if(target_ach_1 == FALSE)
  {
      proxiright_dist = sensors[0]->get_distance();
  }
  if(target_ach_2 == FALSE)
    {
      proxileft_dist = sensors[1]->get_distance();
}
      sum = proxiright_dist + proxileft_dist;
      mvprintw(5, 0, "#%d Distance right 1: %3dmm", 1, proxiright_dist);
      mvprintw(6, 0, "#%d Distance left 2: %3dmm", 2, proxileft_dist);

    mvprintw(5 + 3*sensors.size(), 0, "Average distance: %5.1fmm",
        (double) sum / sensors.size());
    move(8 + 3*sensors.size(), 0);
    mvprintw(8 + 3*sensors.size(), 0, "hydr test");
    move(11 + 3*sensors.size(), 0);
    //Added to move Hydraulics
////////////////////////////////////////////////////////////////////


    if(proxiright_dist +2 < TARGET)
        {
        extend("front", "right");
	// delay(40);
	// hold("front", "right");
	// delay(100);
        mvprintw(11 + 3*sensors.size(), 0, "extending", 1);
        }
    else if(proxiright_dist - 2> TARGET)
        {
        retract("front", "right");
	// delay(40);
	// hold("front", "right");
	// delay(100);
  mvprintw(11 + 3*sensors.size(), 0, "retracting", 1);
        }
    else
        {
        hold("front", "right");
  	mvprintw(11 + 3*sensors.size(), 0, "holding", 1);
  	target_ach_1 = TRUE;
//	delay(100);
//	target_ach_1 = FALSE;
        }

    if(proxileft_dist + 2 < TARGET)
        {
        extend("front", "left");
        mvprintw(11 + 3*sensors.size(), 20, "extending", 2);
        }
    else if(proxileft_dist - 2 > TARGET)
        {
        retract("front", "left");
        mvprintw(11 + 3*sensors.size(), 20, "retracting", 2);
        }
    else
        {
        hold("front", "left");
        mvprintw(11 + 3*sensors.size(), 10, "holding", 2);
  	target_ach_2 = TRUE;
//	delay(100);
//	target_ach_2 = FALSE;
        }
    if(target_ach_1 == TRUE && target_ach_2 == TRUE)
  {
  standby("front");
  mvprintw(20, 0, "Brakes at correct position");
  
  }
////////////////////////////////////////////////////////////////////
    refresh();
    stop = getch();
  }

  shutDown("front");
}

int main()
{
wiringPiSetup();
  initscr();
  raw();
  noecho();
  timeout(0);

  mvprintw(0, 0, "Press 'c' for continuous mode or 's' for single-shot mode");
  move(1, 0);
  refresh();
  int opt = getch();
  while(opt != 'c' && opt != 's')
    {
      opt = getch();
    }
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

