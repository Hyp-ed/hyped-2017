#include "vl6180.hpp"
extern "C" {
    #include "hydraulic_control.h"

}

#include <chrono>
#include <ncurses.h>

#include <iostream>
#include <fstream>

#include "i2c.hpp"

#define TARGET 50

int main()
{
  initscr();
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
  chargeAccumulators();
  while (stop == ERR)
  {
    int dist = sensor.get_distance();
    mvprintw(0, 10, "%3d mm         ", dist);
    refresh();
    if(dist < TARGET)
        {
        retract_one();
//	move(10, 10);
       mvprintw(1, 40, "retracting");
       delay(5);
        }
    else if(dist > TARGET)
        {
        extend_one();
//	move(1, 40);
        mvprintw(1, 40, "extending");
	delay(5);
        }
        else
	{
        standby();
	delay(1000);
//	move(1, 40);
	mvprintw(1, 40, "holding");
//	delay(10000);
	}

    stop = getch();
  }

  endwin();
}












//using namespace std;

/*int main()
{
  initscr();
  raw();
  noecho();
  timeout(0);
    
//  mvprintw(0, 0, "Distance: ");
//  move(1, 0);
  refresh();

  I2C i2c;
  Vl6180 sensor(&i2c);
//  mvprintw(1, 0, "Type any character to exit");
//  move(1, 0);
  refresh();
  int stop = getch();
  while (stop == ERR)
//  {
//standby();

{
 int dist = sensor.get_distance();
 printf("Distance %3d mm\n", sensor.get_distance());
 
//  mvprintw(0, 0, "%3d mm         ", dist);
// std::this_thread::sleep_for(std::chrono::milliseconds(50));

//    void standby();
// to record distance in a file
//    ifstream myfile;
//   ofstream file("distance.txt",ios::trunc);
   /* if (myfile.is_open())
    {*/
//	file << dist;
//	file.close();
    //}
    //else cout << "Unable to open file\n";
//    mvprintw(0, 10, "%3d mm         ", dist);
//    move(2, 0);
//    refresh();
//    delay(100);
//    std::this_thread::sleep_for(std::chrono::milliseconds(250));
  //  stop = getch();
//  }
//  standby();
//  getch();
//  endwin();

  /*I2C i2c;
  Vl6180 sensor(&i2c);
  while(true)
  {
    printf("Distance %d mm\n", sensor.get_distance());
  }//*/
//}
