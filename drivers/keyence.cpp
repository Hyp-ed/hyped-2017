#include "keyence.hpp"

#include <chrono>
#include <thread>


Keyence::Keyence(GpioPinNumber config_pin_num, GpioPinNumber output_pin_num)
    : config_pin { Gpio::get_pin(config_pin_num, PinMode::out, PudControl::off) },
    output_pin { Gpio::get_pin(output_pin_num, PinMode::in, PudControl::down) }
{
	setUp();
	countStripes(stripes);
}

void Keyence::calibrate()
{
  this->config_pin.write(false);
  //:delay(3500);
  this->config_pin.write(true);
  //printf("\nSetup complete");	
}

void keyence :: countStripes(int &numStripes)
{
	while (1) 
	{
		current_state = digitalRead(28);
		printf("\noutput = %d", current_state);
		if (current_state == 0 && prev_state == 0)
		{
			prev_state = 1;
			//numStripes += 0;
			printf("\n Stripe started");
		}	
		else if (current_state == 0 && prev_state == 1)
		{
			prev_state = 1;
			printf("\n Stripe still present");
		}
		else if (current_state == 1 && prev_state == 1)
		{
			prev_state = 0;
			numStripes += 1;
			printf("\n Stripe finished. Stripe Count = %d", numStripes);
		}
  		//Change delay to vary the reading frequency
  		delayMicroseconds(1000);
  		
	}
}
