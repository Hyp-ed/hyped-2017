#ifndef HYPED_DRIVERS_I2C_HPP_
#define HYPED_DRIVERS_I2C_HPP_

extern "C"{
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
}
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <exception>
#include <string>

typedef int i2c_bus; //file handle

class I2C
{
  public:
    I2C () { open_bus(); }
    ~I2C () { close_bus(); }

    void write(uint16_t device, short length, char *buf) const;
    void write_read(uint16_t device, short send_len, char *send_buf,
                                     short recv_len, char *recv_buf) const;
    void read(uint16_t device, short length, char *buf) const;

  private:
    void open_bus();
    void close_bus();

    i2c_bus bus;
};

class I2CException : public std::exception
{
  public:
    I2CException(std::string message);
    virtual const char* what() const noexcept override;

  private:
    const std::string message;
};

#endif // HYPED_DRIVERS_I2C_HPP_

