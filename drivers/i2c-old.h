#ifndef I2C_H
#define I2C_H

#ifdef __cplusplus
extern "C"{
#endif

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <stdio.h>

typedef int i2c_bus; //file handle
typedef unsigned char byte;

int get_bus();
void write_bytes(i2c_bus bus, __u16 device, int length, byte *buf);
int write_read_bytes(i2c_bus bus, __u16 device,
                int send_len, byte *send_buf,
                int recv_len, byte *recv_buf);
void close_bus(i2c_bus bus);

#ifdef __cplusplus
}
#endif

#endif // !I2C_H