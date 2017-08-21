#include "hydraulics.hpp"

#define PUMP_SPINUP 400000 // microseconds = 400 miliseconds 
#define INRUSH_LIMIT 100
#define LOW_BATTERY 23
#define OVER_CURRENT 150
#define OVER_PRESSURE_ACCUMULATORS 100
#define OVER_PRESSURE_PUMP 200


void Hydraulics::set_up_pins() {
    this->solenoid_1 = Gpio::get_pin(SOL_1, PinMode::out, PudControl::off);
    this->solenoid_2 = Gpio::get_pin(SOL_2, PinMode::out, PudControl::off);
    this->solenoid_3 = Gpio::get_pin(SOL_3, PinMode::out, PudControl::off);
    this->solenoid_4 = Gpio::get_pin(SOL_4, PinMode::out, PudControl::off);
    this->solenoid_5 = Gpio::get_pin(SOL_5, PinMode::out, PudControl::off);
    this->solenoid_6 = Gpio::get_pin(SOL_6, PinMode::out, PudControl::off);
    this->solenoid_7 = Gpio::get_pin(SOL_7, PinMode::out, PudControl::off);
    this->pump = Gpio::get_pin(PUMP, PinMode::out, PudControl::off);
}

void Hydraulics::spin_up() {
    this->pump.write(false);
    usleep(PUMP_SPINUP);
    this->solenoid_5.write(false);
    this->solenoid_7.write(false);
}

void Hydraulics::hold(const std::string& side) {
    if (side == "right") {
        this->solenoid_2.write(false);
        this->solenoid_1.write(true);
    } else if (side == "left") {
        this->solenoid_6.write(false);
        this->solenoid_4.write(true);
    }
}

void Hydraulics::retract(const std::string& side) {
    if (side == "right") {
        this->solenoid_1.write(false);
        this->solenoid_2.write(false);
    } else if (side == "left") {
        this->solenoid_6.write(false);
        this->solenoid_4.write(false);
    } else {
        this->pump.write(true);
        this->solenoid_7.write(true);
    }
}

void Hydraulics::extend(const std::string& side) {
    if (side == "right") {
        this->solenoid_2.write(true);
    } else if (side == "left") {
        this->solenoid_6.write(true);
    }
}

void Hydraulics::shut_down() {
    this->solenoid_1.write(true);
    this->solenoid_2.write(true);
    this->solenoid_3.write(true);
    this->solenoid_4.write(true);
    this->solenoid_5.write(true);
    this->solenoid_6.write(true);
    this->solenoid_7.write(true);
    this->pump.write(true);
}

void Hydraulics::stand_by() {
    this->hold("left");
    this->hold("right");
    usleep(50000); // 50 millisecondsi
    this->solenoid_1.write(false);
    this->solenoid_2.write(false);
    this->solenoid_3.write(true);
    this->solenoid_4.write(false);
    this->solenoid_5.write(true);
    this->solenoid_6.write(false);
    this->solenoid_7.write(true);
    this->pump.write(true);
}

void Hydraulics::charge_accumulators() {
    this->pump.write(false);
    
    this->solenoid_1.write(true);
    this->solenoid_2.write(true);
    this->solenoid_3.write(false);
    this->solenoid_4.write(true);
    this->solenoid_5.write(true);
    this->solenoid_6.write(true);
    this->solenoid_7.write(false);

    usleep(1500000); // 1500 milliseconds

    this->solenoid_1.write(true);
    this->solenoid_2.write(true);
    this->solenoid_3.write(true);
    this->solenoid_4.write(true);
    this->solenoid_5.write(true);
    this->solenoid_6.write(true);
    this->solenoid_7.write(true);
    this->pump.write(true);
}

void Hydraulics::pressure(const char frontrear, int pressure)
{
    this->pump.write(false);
    
    delay(PUMP_SPINUP);
    
    this->solenoid_1.write(true);
    this->solenoid_2.write(true);
    this->solenoid_3.write(false);
    this->solenoid_4.write(true);
    this->solenoid_5.write(true);
    this->solenoid_6.write(true);
    this->solenoid_7.write(false);
    
    float p = 0;
       while(p < pressure || p != -1)//ADD WHEN CURRENT SENSOR WORKS!
    {
        p = getData("accumulator_pressure");
        printf("%f", p);
        delay(50);
    }

    this->solenoid_1.write(true);
    this->solenoid_2.write(true);
    this->solenoid_3.write(true);
    this->solenoid_4.write(true);
    this->solenoid_5.write(true);
    this->solenoid_6.write(true);
    this->solenoid_7.write(true);
    this->pump.write(true);
    
}

