#include "i2c.hpp"

#define I2C_DRIVER_PATH "/dev/i2c-1" // CAUTION: may be determined dynamically at boot

void I2C::open_bus()
{
    if ((bus = open(I2C_DRIVER_PATH, O_RDWR)) < 0)
    {
        printf("Failed to open the i2c bus\n");
        exit(EXIT_FAILURE);
    }
}

void I2C::close_bus()
{
    close(bus);
}

// Sends the `length` bytes of `buf` to the `device`.
// Args: device - i2c slave address (7 or 10 bits; 10 bits needs appropriate flag)
//       length - number of bytes to be sent to the device (length of the `buf` array)
//       buf    - array of bytes to be sent (NOTE: `buf[0]` will probably be a register address)
void I2C::write(uint16_t device, short length, char *buf) const
{
    // structs below defined in /usr/include/linux/i2c-dev.h
    struct i2c_rdwr_ioctl_data data;
    struct i2c_msg msgs[1];

    msgs[0].addr = device;
    msgs[0].flags = 0;
    msgs[0].len = length;
    msgs[0].buf = buf;

    data.msgs = msgs;
    data.nmsgs = 1;

    if (ioctl(bus, I2C_RDWR, &data) < 0)
      throw I2CException("I2C write failed");
}

// Sends the `send_len` bytes of `send_buf` to the `device`, then receives `recv_len` bytes from it.
//
// Performed as a single I2C transaction (using repeated start). The write will usually be used to
// specify the register address within the device, from which data will be retrieved during the read
// part.
//
// Args: device   - i2c slave address (7 or 10 bits; 10 bits needs appropriate flag)
//       send_len - number of bytes to be sent to the device (length of the `send_buf` array)
//       send_buf - array of bytes to be sent
//       recv_len - number of bytes to be received from the device (length of the `recv_buf` array)
//       recv_buf - buffer to be populated by the received bytes
void I2C::write_read(uint16_t device, short send_len, char *send_buf,
                                short recv_len, char *recv_buf) const
{
    // structs below defined in /usr/include/linux/i2c-dev.h
    struct i2c_rdwr_ioctl_data data;
    struct i2c_msg msgs[2];

    msgs[0].addr = device;
    msgs[0].flags = 0;
    msgs[0].len = send_len;
    msgs[0].buf = send_buf;

    msgs[1].addr = device;
    msgs[1].flags = I2C_M_RD; //read
    msgs[1].len = recv_len;
    msgs[1].buf = recv_buf;

    data.msgs = msgs;
    data.nmsgs = 2;

    if (ioctl(bus, I2C_RDWR, &data) < 0)
      throw I2CException("I2C write-read failed");
}

void I2C::read(uint16_t device, short length, char *buf) const
{
  struct i2c_rdwr_ioctl_data data;
  struct i2c_msg msgs[1];

  msgs[0].addr = device;
  msgs[0].flags = I2C_M_RD; //read
  msgs[0].len = length;
  msgs[0].buf = buf;

  data.msgs = msgs;
  data.nmsgs = 1;

  if ( ioctl(bus, I2C_RDWR, &data) < 0 )
    throw I2CException("I2C read failed");
}


I2CException::I2CException(std::string msg) : message(msg)
{}

const char* I2CException::what() const noexcept
{
  return this->message.c_str();
}

