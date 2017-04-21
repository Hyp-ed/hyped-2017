#include <cstdlib>
#include <cstdio>
#include "i2c.hpp"

const unsigned char DEFAULT_SLAVE_ADDR = 0x68;

class Mpu6050{
    public:
        Mpu6050 (I2C* bus);
        int get_raw_accl_x();
        int get_raw_accl_y();
        int get_raw_accl_z();
        int get_raw_gyro_x();
        int get_raw_gyro_y();
        int get_raw_gyro_z();
    private:
        I2C* bus;
        uint8_t slave_addr = DEFAULT_SLAVE_ADDR;
        void init();
        void write8(char reg_addr, char data);
        uint8_t read8(char reg_addr);
        short read16(char reg_addr);
};
