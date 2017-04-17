extern "C"{
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
}

const unsigned char DEFAULT_SLAVE_ADDR = 0x68;
