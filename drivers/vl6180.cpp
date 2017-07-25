#include "vl6180.hpp"

// Register addresses
#define IDENTIFICATION__MODEL_ID              0x0000
#define IDENTIFICATION__MODEL_REV_MAJOR       0x0001
#define IDENTIFICATION__MODEL_REV_MINOR       0x0002
#define IDENTIFICATION__MODULE_REV_MAJOR      0x0003
#define IDENTIFICATION__MODULE_REV_MINOR      0x0004
#define IDENTIFICATION__DATE_HI               0x0006
#define IDENTIFICATION__DATE_LO               0x0007
#define IDENTIFICATION__TIME                  0x0008
#define SYSTEM__MODE_GPIO0                    0x0010
#define SYSTEM__MODE_GPIO1                    0x0011
#define SYSTEM__HISTORY_CTRL                  0x0012
#define SYSTEM__INTERRUPT_CONFIG_GPIO         0x0014 // See also SYSTEM__GROUPED_PARAMETER_HOLD
#define SYSTEM__INTERRUPT_CLEAR               0x0015
#define SYSTEM__FRESH_OUT_OF_RESET            0x0016
#define SYSTEM__GROUPED_PARAMETER_HOLD        0x0017
#define SYSRANGE__START                       0x0018
#define SYSRANGE__THRESH_HIGH                 0x0019 // See also SYSTEM__GROUPED_PARAMETER_HOLD
#define SYSRANGE__THRESH_LOW                  0x001A // See also SYSTEM__GROUPED_PARAMETER_HOLD
#define SYSRANGE__INTERMEASUREMENT_PERIOD     0x001B
#define SYSRANGE__MAX_CONVERGENCE_TIME        0x001C
#define SYSRANGE__CROSSTALK_COMPENSATION_RATE 0x001E
#define SYSRANGE__CROSSTALK_VALID_HEIGHT      0x0021
#define SYSRANGE__EARLY_CONVERGENCE_ESTIMATE  0x0022
#define SYSRANGE__PART_TO_PART_RANGE_OFFSET   0x0024
#define SYSRANGE__RANGE_IGNORE_VALID_HEIGHT   0x0025
#define SYSRANGE__RANGE_IGNORE_THRESHOLD      0x0026
#define SYSRANGE__MAX_AMBIENT_LEVEL_MULT      0x002C
#define SYSRANGE__RANGE_CHECK_ENABLES         0x002D
#define SYSRANGE__VHV_RECALIBRATE             0x002E
#define SYSRANGE__VHV_REPEAT_RATE             0x0031
#define SYSALS__START                         0x0038
#define SYSALS__THRESH_HIGH                   0x003A // See also SYSTEM__GROUPED_PARAMETER_HOLD
#define SYSALS__THRESH_LOW                    0x003C // See also SYSTEM__GROUPED_PARAMETER_HOLD
#define SYSALS__INTERMEASUREMENT_PERIOD       0x003E // See also SYSTEM__GROUPED_PARAMETER_HOLD
#define SYSALS__ANALOGUE_GAIN                 0x003F // See also SYSTEM__GROUPED_PARAMETER_HOLD
#define SYSALS__INTEGRATION_PERIOD            0x0040
#define RESULT__RANGE_STATUS                  0x004D
#define RESULT__ALS_STATUS                    0x004E
#define RESULT__INTERRUPT_STATUS_GPIO         0x004F
#define RESULT__ALS_VAL                       0x0050
#define RESULT__HISTORY_BUFFER_x              0x0052
#define RESULT__RANGE_VAL                     0x0062
#define RESULT__RANGE_RAW                     0x0064
#define RESULT__RANGE_RETURN_RATE             0x0066
#define RESULT__RANGE_REFERENCE_RATE          0x0068
#define RESULT__RANGE_RETURN_SIGNAL_COUNT     0x006C
#define RESULT__RANGE_REFERENCE_SIGNAL_COUNT  0x0070
#define RESULT__RANGE_RETURN_AMB_COUNT        0x0074
#define RESULT__RANGE_REFERENCE_AMB_COUNT     0x0078
#define RESULT__RANGE_RETURN_CONV_TIME        0x007C
#define RESULT__RANGE_REFERENCE_CONV_TIME     0x0080
#define READOUT__AVERAGING_SAMPLE_PERIOD      0x010A
#define FIRMWARE__BOOTUP                      0x0119
#define FIRMWARE__RESULT_SCALER               0x0120
#define I2C_SLAVE__DEVICE_ADDRESS             0x0212
#define INTERLEAVED_MODE__ENABLE              0x02A3

// SYSTEM__INTERRUPT_CLEAR options (combine with `|`)
#define CLEAR_RANGE_INT 0x01
#define CLEAR_ALS_INT   0x02
#define CLEAR_ERROR_INT 0x04

// SYSRANGE__START options
#define RANGING_MODE_CONT   0x02
#define SYSRANGE__STARTSTOP 0x01


Vl6180& Vl6180::get_instance(I2C *bus, Pin gpio_pin)
{
  
}

Vl6180::Vl6180(I2C *bus, uint8_t i2c_slave_addr /*= DEFAULT_I2C_SLAVE_ADDR*/)
{
  this->bus = bus;

  // Set the I2C slave address
  if(i2c_slave_addr != DEFAULT_I2C_SLAVE_ADDR)
  {
    this->write8(I2C_SLAVE__DEVICE_ADDRESS, i2c_slave_addr);
  }
  this->i2c_slave_addr = i2c_slave_addr;

  // Disable GPIO0 XSHUTDOWN
  this->write8(SYSTEM__MODE_GPIO0, 0x20);
  //TODO: enable GPIO1 interrupt output

  //TODO: set up New Sample Ready interrupt (SYSTEM__INTERRUPT_CONFIG_GPIO)

  // Set continuous ranging mode and start measurements
  this->write8(SYSRANGE__START, RANGING_MODE_CONT | SYSRANGE__STARTSTOP);

  // Set intermeasurement period 10ms
  this->write8(SYSRANGE__INTERMEASUREMENT_PERIOD, 0x00);

  //TODO: SYSRANGE__EARLY_CONVERGENCE_ESTIMATE, SYSRANGE__RANGE_CHECK_ENABLES,...

  //TODO: VHV recalibration

  this->write8(SYSTEM__FRESH_OUT_OF_RESET, 0x00);
}

int Vl6180::get_distance()
{
  //TODO: Check for errors (e.g. in RESULT__RANGE_STATUS, RESULT__INTERRUPT_STATUS_GPIO)
  uint16_t status = this->read8(RESULT__INTERRUPT_STATUS_GPIO);
  this->write8(SYSTEM__INTERRUPT_CLEAR, CLEAR_RANGE_INT);
  if ((status & 0x07) == 4)
  {
    // New sample ready
    this->distance = (int) this->read8(RESULT__RANGE_VAL);
  }
  return this->distance;
}

void Vl6180::write8(uint16_t reg_addr, char data)
{
  char buf[3];
  buf[0] = (reg_addr & 0xff00) >> 8; // MSB
  buf[1] = reg_addr & 0xff; // LSB
  buf[2] = data;
  this->bus->write(this->i2c_slave_addr, 3, buf);
}

uint8_t Vl6180::read8(uint16_t reg_addr)
{
  char send_buf[2];
  send_buf[0] = (reg_addr & 0xff00) >> 8; // MSB
  send_buf[1] = reg_addr & 0xff; // LSB
  char recv_buf[1];
  this->bus->write_read(this->i2c_slave_addr, 2, send_buf, 1, recv_buf);
  return (uint8_t) recv_buf[0];
}
