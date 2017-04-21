#include "i2c.h"

#define I2C_DRIVER_PATH "/dev/i2c-1" // CAUTION: may be determined dynamically at boot

int get_bus()
{
    i2c_bus bus;
    if ((bus = open(I2C_DRIVER_PATH, O_RDWR)) < 0)
    {
        printf("Failed to open the i2c bus\n");
        exit(EXIT_FAILURE);
    }
    return bus;
}

/*int get_bus(char *filename)
{
    i2c_bus bus;
    if ((bus = open(filename, O_RDWR)) < 0)
    {
        printf("Failed to open the i2c bus\n");
        exit(EXIT_FAILURE);
    }
    return bus;
}*/

/* Sends `length` bytes of `buf` to the `device` */
/* Args: bus    - file handle returned by get_bus()
         device - i2c slave address (7 0r 10 bits; 10 bits needs appropriate flag)
         length - number of bytes to be sent to the device (length of the `buf` array)
         buf    - array of bytes to be sent (NOTE: `buf[0]` will probably be a register address) */
void write_bytes(i2c_bus bus, __u16 device, int length, byte *buf)
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
    {
        printf("i2c write failed\n");
        close(bus);
        exit(EXIT_FAILURE);
    }
}

/* Combined I2C transaction - 1 write followed by 1 read (restart in between) */

int write_read_bytes(i2c_bus bus, __u16 device,
                int send_len, byte *send_buf,
                int recv_len, byte *recv_buf)
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
    {
        printf("i2c write-read failed\n");
        close(bus);
        exit(EXIT_FAILURE);
    }
}

void close_bus(i2c_bus bus)
{
    // TODO: exception handling (e.g. bus already closed)
    close(bus);
}