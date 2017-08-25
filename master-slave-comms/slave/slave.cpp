#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "drivers/i2c.hpp"
#include "drivers/vl6180.hpp"
#include "NetworkSlave.hpp"

#define SENSOR1_PIN PIN4
#define SENSOR2_PIN PIN24

NetworkSlave master;
const int SLAVE_PORT = 11999;
const std::string NAME = "Slave:1";
const bool continuous_mode = true;

std::vector<Vl6180*> sensors;
//Create an I2C instance to represent the bus
I2C i2c;
// Create factory to produce sensor drivers for that bus
Vl6180Factory& factory = Vl6180Factory::instance(&i2c);

int proxiMap(std::string command) {
  if (command == "proxi-ground-front") {
    return 0;
  }
}

inline uint64_t timestamp()
{
  using namespace std::chrono;
  return duration_cast<microseconds>(
      steady_clock::now().time_since_epoch()).count();
}





void * loop(void * m)
{
  pthread_detach(pthread_self());
  while(1)
  {
    // Listen for commands from master
    std::string command = master.getMessage();

    if (command.substr(0, 6) == "proxi-")
    {
      std::string readings = NAME + "\n"; // populate with readings from proxy
      int dist = sensors[proxiMap(command)]->get_distance();
      std::string res = std::to_string(dist);  
      
      std::cout << "Message:" << command << std::endl;
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
  // Produce driver instance for the sensor with GPIO0 connected to specified pin
  Vl6180& sensor_ref = factory.make_sensor(SENSOR1_PIN);
  // Store pointer to the driver instance
  sensors.push_back(&sensor_ref);

  // Uncoment the following line and possibly add more to use more sensors
  //sensors.push_back( &(factory.make_sensor(SENSOR2_PIN)) );

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
