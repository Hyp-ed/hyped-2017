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
#define RANGING_MODE_SINGLESHOT 0x00
#define RANGING_MODE_CONT       0x02
#define SYSRANGE__STARTSTOP     0x01

// RESULT__RANGE_STATUS masks
#define RESULT__RANGE_DEVICE_READY_MASK 0x01
#define RESULT__RANGE_ERROR_CODE_MASK   0xF0

// RESULT__INTERRUPT_STATUS_GPIO masks
#define RESULT_INT_ERROR_GPIO_MASK 0xC0
#define RESULT_INT_ALS_GPIO_MASK   0x38
#define RESULT_INT_RANGE_GPIO_MASK 0x07

// SYSTEM__FRESH_OUT_OF_RESET masks
#define FRESH_OUT_OF_RESET_MASK 0x01


// Factory class definitions
Vl6180Factory& Vl6180Factory::instance(I2C* bus)
{
  static Vl6180Factory factory(bus); //static here means it's only called once
  return factory;
}

Vl6180& Vl6180Factory::make_sensor(GpioPinNumber gpio_pin)
{
  //check if exists
  int free_spot = -1;
  for (int i = 0; i < MAX_SENSORS; ++i)
  {
    if (sensors[i] != NULL && sensors[i]->gpio_pin.pin_num == gpio_pin)
      return *(sensors[i]);
    if (free_spot == -1 && sensors[i] == NULL)
      free_spot = i;
  }

  //check space
  //if (free_spot == -1) error;

  //construct
  sensors[free_spot] = new Vl6180(this->bus,
                                  gpio_pin,
                                  i2c_slave_addresses[free_spot]);
  return *(sensors[free_spot]);
}

Vl6180Factory::Vl6180Factory(I2C* bus)
{
  this->bus = bus;
}

Vl6180Factory::~Vl6180Factory()
{
  for (int i = 0; i < MAX_SENSORS; ++i)
    delete sensors[i];
}

constexpr uint8_t Vl6180Factory::i2c_slave_addresses[];

Vl6180* Vl6180Factory::sensors[MAX_SENSORS] =
    {nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr, nullptr};


// Sensor class definitions
void Vl6180::turn_on()
{
  if (this->on)
    return;
  // Wait in case the sensor has just been turned off
  std::this_thread::sleep_for(std::chrono::milliseconds(100)); //datasheet mentions 100ns but not sure
  // Turn on and wait for MCU boot
  this->gpio_pin.write(true);
  std::this_thread::sleep_for(std::chrono::milliseconds(2)); //datasheet says minimum 1.4ms
  this->on = true;

  // Set the I2C slave address
  uint8_t temp = this->i2c_slave_addr;
  this->i2c_slave_addr = DEFAULT_I2C_SLAVE_ADDR;
  this->write8(I2C_SLAVE__DEVICE_ADDRESS, temp);
  this->i2c_slave_addr = temp;

  // Do magic (taken from ST Microelectronics API; no explanation exists)
  this->write8(0x0207, 0x01);
  this->write8(0x0208, 0x01);
  this->write8(0x0096, 0x00);
  this->write8(0x0097, 0xfd);
  this->write8(0x00e3, 0x00);
  this->write8(0x00e4, 0x04);
  this->write8(0x00e5, 0x02);
  this->write8(0x00e6, 0x01);
  this->write8(0x00e7, 0x03);
  this->write8(0x00f5, 0x02);
  this->write8(0x00d9, 0x05);
  this->write8(0x00db, 0xce);
  this->write8(0x00dc, 0x03);
  this->write8(0x00dd, 0xf8);
  this->write8(0x009f, 0x00);
  this->write8(0x00a3, 0x3c);
  this->write8(0x00b7, 0x00);
  this->write8(0x00bb, 0x3c);
  this->write8(0x00b2, 0x09);
  this->write8(0x00ca, 0x09);
  this->write8(0x0198, 0x01);
  this->write8(0x01b0, 0x17);
  this->write8(0x01ad, 0x00);
  this->write8(0x00ff, 0x05);
  this->write8(0x0100, 0x05);
  this->write8(0x0199, 0x05);
  this->write8(0x01a6, 0x1b);
  this->write8(0x01ac, 0x3e);
  this->write8(0x01a7, 0x1f);
  this->write8(0x0030, 0x00);

  // Keep default GPIO0 settings
  
  // Enable GPIO1 interrupt output
  this->write8(SYSTEM__MODE_GPIO1, 0x30);

  // Set up New Sample Ready interrupt
  this->write8(SYSTEM__GROUPED_PARAMETER_HOLD, 0x01);
  this->write8(SYSTEM__INTERRUPT_CONFIG_GPIO, 0x04);
  this->write8(SYSTEM__GROUPED_PARAMETER_HOLD, 0x00);

  //TODO: SYSRANGE__EARLY_CONVERGENCE_ESTIMATE, SYSRANGE__RANGE_CHECK_ENABLES,...

  // VHV recalibration
  this->write8(SYSRANGE__VHV_RECALIBRATE, 0x01); // Manually recalibrate once
  uint8_t vhv_calib;
  do
    vhv_calib = this->read8(SYSRANGE__VHV_RECALIBRATE) & 0x01; // Wait for completion
  while (vhv_calib);
  this->write8(SYSRANGE__VHV_REPEAT_RATE, 0x80); // Auto-repeat after every 128 measurements

  // Set intermeasurement period of 1000ms
  this->set_intermeasurement_period(1000);

  // Config done, not fresh out of reset anymore
  this->write8(SYSTEM__FRESH_OUT_OF_RESET, 0x00);

  this->wait_device_ready();
}

void Vl6180::turn_off()
{
  this->gpio_pin.write(false);
  this->on = false;
}

bool Vl6180::is_on()
{
  return this->on;
}

void Vl6180::set_intermeasurement_period(int msec)
{
  msec = msec / 10 - 1;
  if (msec < 0)
    msec = 0;
  if (msec > 255)
    msec = 255;
  this->write8(SYSRANGE__INTERMEASUREMENT_PERIOD, msec);
}

void Vl6180::calibrate(int dist, int n)
{
  bool was_cont = this->cont_mode;
  this->set_continuous_mode(false);
  int sum = 0;
  for (int i = 0; i < n; ++i)
    sum += this->get_distance();
  this->offset = sum/n - dist;
  this->set_continuous_mode(was_cont);
}

void Vl6180::set_continuous_mode(bool enabled)
{
  if (enabled == this->cont_mode)
    return;
  this->wait_device_ready();
  if (enabled)
  {
    this->write8(SYSRANGE__START, RANGING_MODE_CONT | SYSRANGE__STARTSTOP);
  }
  else
  {
    //TODO: stop continuous ranging first?
    this->write8(SYSRANGE__START, RANGING_MODE_SINGLESHOT);
  }
  this->cont_mode = enabled;
}

bool Vl6180::is_continuous_mode()
{
  return this->cont_mode;
}

int Vl6180::get_distance()
{
  if (this->cont_mode)
    return (int) this->get_measurement() - this->offset;
  else
    return (int) this->poll_measurement() - this->offset;
}

Vl6180::Vl6180(I2C *bus, GpioPinNumber gpio_pin_num, uint8_t i2c_slave_addr)
    : bus {bus},
    gpio_pin {Gpio::get_pin(gpio_pin_num, PinMode::out, PudControl::off)},
    i2c_slave_addr {i2c_slave_addr}
{
  this->turn_off();
}

bool Vl6180::wait_device_ready()
{
  while(true)
  {
    uint8_t status = this->read8(RESULT__RANGE_STATUS);
    if (status & RESULT__RANGE_DEVICE_READY_MASK)
      return true;
  }
  return false;
}

uint8_t Vl6180::poll_measurement()
{
  this->write8(SYSRANGE__START, RANGING_MODE_SINGLESHOT | SYSRANGE__STARTSTOP);
  uint8_t status;
  do
  {
    status = this->read8(RESULT__INTERRUPT_STATUS_GPIO);
  }
  while ((status & RESULT_INT_RANGE_GPIO_MASK) != 4);
  this->write8(SYSTEM__INTERRUPT_CLEAR, CLEAR_RANGE_INT);
  return this->get_measurement();
}

uint8_t Vl6180::get_measurement()
{
  return this->read8(RESULT__RANGE_VAL);
}

bool Vl6180::is_fresh_out_of_reset()
{
  return (this->read8(SYSTEM__FRESH_OUT_OF_RESET) & FRESH_OUT_OF_RESET_MASK);
}

void Vl6180::write8(uint16_t reg_addr, char data)
{
  char buf[3];
  buf[0] = (reg_addr & 0xFF00) >> 8; // MSB
  buf[1] = reg_addr & 0xFF; // LSB
  buf[2] = data;
  this->bus->write(this->i2c_slave_addr, 3, buf);
}

uint8_t Vl6180::read8(uint16_t reg_addr)
{
  char send_buf[2];
  send_buf[0] = (reg_addr & 0xFF00) >> 8; // MSB
  send_buf[1] = reg_addr & 0xFF; // LSB
  char recv_buf[1];
  this->bus->write_read(this->i2c_slave_addr, 2, send_buf, 1, recv_buf);
  return (uint8_t) recv_buf[0];
}

