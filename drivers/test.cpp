#include "hydraulics.hpp"


int main()
{
  Hydraulics::set_up_pins();
	Hydraulics::spinup();
	//pressure(ACCUMULATOR_PRESSURE);
	Hydraulics::charge_accumulators();
  Hydraulics::retract(left);
	Hydraulics::retract(right);
	Hydraulics::standby();
	usleep(3000000);
	Hydraulics::extend(left);
	Hydraulics::extend(right);
	usleep(2000000);
	Hydraulics::spinup();
	Hydraulics::retract(left);
	Hydraulics::retract(right);
	Hydraulics::standby();
	Hydraulics::shutdown();

}
