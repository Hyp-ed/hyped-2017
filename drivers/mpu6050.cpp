#include "mpu6050.h"

using namespace std;

class Mpu6050{
    int file_i2c;
    void init(unsigned char slave_addr);
  public:
    Mpu6050 (unsigned char slave_addr = DEFAULT_SLAVE_ADDR) {init(slave_addr);}
    ~Mpu6050 () {close(file_i2c);}
    int get_raw_accl_x();
    int get_raw_accl_y();
    int get_raw_accl_z();
    int get_raw_gyro_x();
    int get_raw_gyro_y();
    int get_raw_gyro_z();
};



Mpu6050::init(unsigned char slave_addr) {
  // Open the I2C bus file
  // (on Linux filesystem, IO devices are mounted as files in /dev directory)
  char filename[] = "/dev/i2c-1";   //CAUTION: may be determined dynamically at boot
  if ((file_i2c = open(filename, O_RDWR)) < 0)
  {
    printf("MPU6050: Failed to open the i2c bus");
    exit(1);
  }

  // Specify which device (sensor) on the I2C bus to communicate with
  if (ioctl(file_i2c, I2C_SLAVE, slave_addr) < 0)
  {
    printf("MPU6050: Failed to acquire bus access and/or talk to slave.\n");
    exit(1);
  }

  // POWER MGMT setup
  if (i2c_write_byte_data(file_i2c, 0x6B, 0x80) < 0) //reset everything
  {
    printf("MPU6050: PWR_MGMT_1 write failed");
  }
  sleep(1);
  if (i2c_write_byte_data(file_i2c, 0x6B, 0x03) < 0) //PWR_MGMT_1 - set gyro z as clock source
  {
    printf("MPU6050: PWR_MGMT_1 write failed");
  }
  if (i2c_write_byte_data(file_i2c, 0x6B, 0x03) < 0) //PWR_MGMT_2 - set gyro z as clock source
  {
    printf("MPU6050: PWR_MGMT_1 write failed");
  }
}

Mpu6050::get_raw_accl_x()
{
  return 0;
}

Mpu6050::get_raw_accl_y()
{
  return 0;
}

Mpu6050::get_raw_accl_z()
{
  return 0;
}

Mpu6050::get_raw_gyro_x()
{
  int x = i2c_read_word_data(file_i2c, 0x43);
  return x;
}

Mpu6050::get_raw_gyro_y()
{
  return 0;
}

Mpu6050::get_raw_gyro_z()
{
  return 0;
}

int main()
{
  Mpu6050 sensor;
  printf("%8X", sensor.get_raw_gyro_x())
}

/*
//----- READ BYTES -----
length = 4;			//<<< Number of bytes to read
if (read(file_i2c, buffer, length) != length)		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
{
    //ERROR HANDLING: i2c transaction failed
    printf("Failed to read from the i2c bus.\n");
}
else
{
    printf("Data read: %s\n", buffer);
}

//----- WRITE BYTES -----
buffer[0] = 0x01;
buffer[1] = 0x02;
length = 2;			//<<< Number of bytes to write
if (write(file_i2c, buffer, length) != length)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
{
    printf("Failed to write to the i2c bus.\n");
}
//*/