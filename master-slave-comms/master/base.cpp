#include "BaseCommunicator.hpp"
#include "drivers/i2c.hpp"
#include "drivers/keyence.hpp"
#include "drivers/mpu6050.hpp"
#include "drivers/motion_tracker.hpp"
#include "drivers/raspberry_pi.hpp"
#include "drivers/vector3d.hpp"

#define CONFIG_PIN 29
#define OUTPUT_PIN 6


int main()
{
  // Motion Tracker setup
  I2C i2c;
  Mpu6050 imu1(&i2c);
  Mpu6050 imu2(&i2c, ALTERNATIVE_SLAVE_ADDR);
  MotionTracker mt;

  mt.add_imu(imu1);
  mt.add_imu(imu2);
  mt.start();

  Keyence k(CONFIG_PIN, OUTPUT_PIN);
  k.calibrate();
  k.start();
  RaspberryPi rpi;

  // Base Communicator setup
  BaseCommunicator base("localhost");
  base.setUp();

  //Send data
  while(true)
  {
    Vector3D<double> v = mt.get_acceleration();
    base.sendAcceleration(v.y);

    v = mt.get_velocity();
    base.sendVelocity(v.y);

    v = mt.get_displacement();
    base.sendPosition(v.y);
    base.sendDistance(v.y);

    base.sendStripeCount(k.get_count());
    base.sendPodTemperature(rpi.get_temperature());
  }
}
