#ifndef HYDRAULICS_HPP
#define HYDRAULICS_HPP

#include "gpio.hpp"
#include <string>
#include <unistd.h>

#define SOL_1 0 // PIN 17
#define SOL_2 1 // PIN 18
#define SOL_3 2 // PIN 21
#define SOL_4 3 // PIN 22
#define SOL_5 4 // PIN 23
#define SOL_6 5 // PIN 24
#define SOL_7 6 // PIN 25
#define PUMP 7  // PIN  4

class Hydraulics {
    public:
        void set_up_pins();
        void spin_up();
        void hold(const std::string& side);
        void retract(const std::string& side);
        void extend(const std::string& side);
        void stand_by();
        void shut_down();
        void charge_accumulators();
        // void start_up(std::string frontrear); not implemented in .c driver
        void safety_check(std::string frontrear);
        void pressure(); // not in original .h file but implemented in .c file
        // void charge(std::string frontrear, int pressure); not implemented in .c driver
        Hydraulics();
    private:
        GpioPin& solenoid_1;
        GpioPin& solenoid_2;
        GpioPin& solenoid_3;
        GpioPin& solenoid_4;
        GpioPin& solenoid_5;
        GpioPin& solenoid_6;
        GpioPin& solenoid_7;
        GpioPin& pump;
};

#endif
