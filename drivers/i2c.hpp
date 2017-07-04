#ifndef HYPED_DRIVERS_I2C_H_
#define HYPED_DRIVERS_I2C_H_

extern "C"{
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
}
#include <cstdlib>
#include <cstdio>
#include <cstdint>

typedef int i2c_bus; //file handle

class I2C {
  private:
    i2c_bus bus;
    void open_bus();
    void close_bus();

  public:
    I2C () { open_bus(); }
    ~I2C () { close_bus(); }
    void write(uint16_t device, short length, char *buf);
    void write_read(uint16_t device, short send_len, char *send_buf,
                                     short recv_len, char *recv_buf);
    void read(uint16_t device, short length, char *buf);
};

#endif // HYPED_DRIVERS_I2C_H_

