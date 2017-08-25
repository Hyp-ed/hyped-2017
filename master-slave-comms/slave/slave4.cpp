#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "drivers/i2c.hpp"
#include "drivers/vl6180.hpp"
#include "NetworkSlave.hpp"

#define PROXI1_PIN 11 // CE1
#define PROXI2_PIN PIN6
#define PROXI3_PIN PIN5
#define PROXI4_PIN PIN13
#define PROXI5_PIN PIN19
#define PROXI6_PIN PIN21

NetworkSlave master;
const int SLAVE_PORT = 11999;
const bool continuous_mode = true;

std::vector<Vl6180*> sensors;
//Create an I2C instance to represent the bus
I2C i2c;
// Create factory to produce sensor drivers for that bus
Vl6180Factory& factory = Vl6180Factory::instance(&i2c);

int proxiMap(std::string command) {
  if (command == "proxi-gnd-rearski-rear") {
    return 0;
  }
  if (command == "proxi-gnd-rearski-front") {
    return 2;
  }
  if (command == "proxi-cylinder-rear") {
    return 1;
  }
  if (command == "proxi-cylinder-front") {
    return 3;
  }
  if (command == "proxi-gnd-frontski-front") {
    return 4;
  }
  if (command == "proxi-gnd-frontski-rear") {
    return 5;
  }
  return -1;
}

/*inline uint64_t timestamp()
{
  using namespace std::chrono;
  return duration_cast<microseconds>(
      steady_clock::now().time_since_epoch()).count();
}*/





void * loop(void * m)
{
  pthread_detach(pthread_self());
  while(1)
  {
    // Listen for commands from master
    std::string command = master.getMessage();

    int proxi_idx = proxiMap(command);
    if (proxi_idx >= 0)
    {
      int dist = sensors[proxi_idx]->get_distance();
      std::string res = std::to_string(dist);  
      
      //std::cout << "Message:" << command << std::endl;
      master.Send(res); // send the readings
      master.clean();
    }

    if (command == "") {
      // check custom commands here
    }

  }

  usleep(1000);
  master.detach();

}
  

int main()
{
  // Produce proximity
  sensors.push_back( &(factory.make_sensor(PROXI1_PIN)) );
  sensors.push_back( &(factory.make_sensor(PROXI2_PIN)) );
  sensors.push_back( &(factory.make_sensor(PROXI3_PIN)) );
  sensors.push_back( &(factory.make_sensor(PROXI4_PIN)) );
  sensors.push_back( &(factory.make_sensor(PROXI5_PIN)) );
  sensors.push_back( &(factory.make_sensor(PROXI6_PIN)) );

  for (unsigned int i = 0; i < sensors.size(); ++i)
  {
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    sensors[i]->turn_on();
    sensors[i]->set_intermeasurement_period(10);
    sensors[i]->set_continuous_mode(continuous_mode);
  }

  pthread_t msg;
  master.setup(SLAVE_PORT);
  if( pthread_create(&msg, NULL, loop, (void *)0) == 0)
  {
    master.receive();
  }
   return 0;
}
