# Drivers for sensors and low-level interfaces
Drivers:
 - I2C (`i2c.hpp`, `i2c.cpp`)
 - GPIO (`gpio.hpp`, `gpio.cpp`)
 - MPU6050 (`mpu6050.hpp`, `mpu6050.cpp`)
 - VL6180x (`vl6180.hpp`, `vl6180.cpp`)
 - Old battery mgmt system using i2c (`battery.hpp`, `battery.cpp`)
 - Raspberry Pi (`raspberry_pi.hpp`, `raspberry_pi.cpp`)

Not-quite-drivers:
 - Navigation (`motion_tracker.hpp`, `motion_tracker.cpp`)

Utilities:
 - Mathematical 3-dimensional vectors (`vector3d.hpp`)
 - Quaternions (`quaternion.hpp`, `quaternion.cpp`)
 - Interfaces for some kinds sensors implemented by the drivers (`interfaces.hpp`)
 - Timestamped datapoints and basic integration (`data_point.hpp`)

Demos and tests:
 - For MPU6050: `main.cpp`
 - For VL6180: `demo-vl6180.cpp`
 - For Raspberry Pi: `demo-raspberry_pi.cpp`
 - For Motion Tracker: `demo-motion_tracker.cpp`
 - For old battery mgmt system: `demo-battery.cpp`

Other files: (should be categorized or removed)
 - `compile`
 - `hydraulic.c`
 - `hydraulic_control.c`
 - `hydraulic_control.h`
 - `hydraulics.c`
 - `hydraulics.h`
 - `kill.c`
 - `primeMotor.c`
 - `proxi-hydro.cpp`
 - `retract.c`
 - `serialdata.c`
 - `serialData.c`
 - `serialData.h`
 - `serialData.h.gch`
 - `serialTest.c`
 - `setup.c`
 - `test.c`

Executables: (to be removed)
 - `kill`
 - `primeMotor`
 - `retract`
 - `serialTest`
 - `serialTest ; ä ä `
 - `setup`
 - `test`
 - `test_motion_tracker`
 ## Usage and samples
 ### I2C (`i2c.hpp`, `i2c.cpp`)
 ```cpp
 #include "i2c.hpp"
 
 void main()
 {
  I2C i2c;
  
 }
 ```
 ### GPIO (`gpio.hpp`, `gpio.cpp`)
 ```cpp
 #include "gpio.hpp"
 
 void main()
 {
 }
 ```
