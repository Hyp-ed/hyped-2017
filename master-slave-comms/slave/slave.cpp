#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "drivers/i2c.hpp"
#include "drivers/vl6180.hpp"
#include "NetworkSlave.hpp"
#include "hydraulics.hpp"

#define SENSOR1_PIN PIN23
#define SENSOR2_PIN PIN24

NetworkSlave master;
const int SLAVE_PORT = 11999;
const std::string NAME = "Slave:1";
const bool continuous_mode = true;

// initial state of brakes
bool brakes_engaged = false;
bool retracted = true;

std::vector<Vl6180*> sensors;
//Create an I2C instance to represent the bus
I2C i2c;
// Create factory to produce sensor drivers for that bus
Vl6180Factory& factory = Vl6180Factory::instance(&i2c);

// Create instance of hydraulics;
Hydraulics hydraulics;


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

    std::string str = master.getMessage();
    if( str == "proxi" )
    {
      std::string readings = NAME + "\n"; // populate with readings from proxy
      for (unsigned int i = 0; i < sensors.size(); ++i)
      {
        uint64_t t = timestamp();
        int dist = sensors[i]->get_distance();
        readings += "Proximity" + std::to_string(i) + ":"
            + std::to_string(t) + "," + std::to_string(dist)
            + ",OK\n";
      }
      readings += "end";
      std::cout << "Message:" << str << std::endl;
      master.Send(readings); // send the readings
      master.clean();
    }
    if (str == "brake" && !brakes_engaged) {
        brakes_engaged = true;
        retracted = false;

        /* here goes the hydraulics code for braking */
        hydraulics.spin_up();
        hydraulics.extend("left");
        hydraulics.extend("right");
        master.Send("OK");
        master.clean();
    }

    if (str == "retract" && !retracted) {
        brakes_engaged = false;
        retracted = true;

        /* here goes the hydraulics code for retracting */
        hydraulics.spin_up();
        hydraulics.retract("left");
        hydraulics.retract("right");
        master.Send("OK");
        master.clean();
    }

    usleep(1000);
  }
  master.detach();
}

int main()
{
  // Produce driver instance for the sensor with GPIO0 connected to specified pin
  Vl6180& sensor_ref = factory.make_sensor(SENSOR1_PIN);
  // Store pointer to the driver instance
  sensors.push_back(&sensor_ref);
  hydraulics.set_up_pins();
  hydraulics.pressure();

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
