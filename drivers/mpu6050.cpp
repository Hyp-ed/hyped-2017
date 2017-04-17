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



void Mpu6050::init(unsigned char slave_addr) {
  // Open the I2C bus file
  // (on Linux filesystem, IO devices are mounted as files in /dev directory)
  char filename[] = "/dev/i2c-1";   //CAUTION: may be determined dynamically at boot
  if ((file_i2c = open(filename, O_RDWR)) < 0)
  {
    printf("MPU6050: Failed to open the i2c bus\n");
    exit(1);
  }

  // Specify which device (sensor) on the I2C bus to communicate with
  if (ioctl(file_i2c, I2C_SLAVE, slave_addr) < 0)
  {
    printf("MPU6050: Failed to acquire bus access and/or talk to slave.\n");
    exit(1);
  }

  // POWER MGMT setup
  if (i2c_smbus_write_byte_data(file_i2c, 0x6B, 0x80) < 0) //reset everything
  {
    printf("MPU6050: PWR_MGMT_1 write failed\n");
  }
  sleep(1);
  if (i2c_smbus_write_byte_data(file_i2c, 0x6B, 0x03) < 0) //PWR_MGMT_1 - set gyro z as clock source
  {
    printf("MPU6050: PWR_MGMT_1 write failed\n");
  }
  if (i2c_smbus_write_byte_data(file_i2c, 0x6B, 0x03) < 0) //PWR_MGMT_2 - set gyro z as clock source
  {
    printf("MPU6050: PWR_MGMT_1 write failed\n");
  }
  sleep(1);
}

int Mpu6050::get_raw_accl_x()
{
  return 0;
}

int Mpu6050::get_raw_accl_y()
{
  return 0;
}

int Mpu6050::get_raw_accl_z()
{
  return 0;
}

int Mpu6050::get_raw_gyro_x()
{
  int x = i2c_smbus_read_word_data(file_i2c, 0x43);
  return (int) (short) (((x & 0xFF) << 8) | ((x & 0xFF00) >> 8)); //correct the order of the bytes
}

int Mpu6050::get_raw_gyro_y()
{
  return 0;
}

int Mpu6050::get_raw_gyro_z()
{
  return 0;
}

int main()
{
  Mpu6050 sensor;
  for (int i = 0; i < 10000; i++)
  {
    printf("\r%8d", sensor.get_raw_gyro_x());
  }
  printf("\n");
}

/*
 * LESSONS LEARNED
 *  1. Correct i2c-dev.h
 *
 *  2. Add users to i2c group
 */
