#include "hydraulics.hpp"


int main()
{
  set_up_pins();
	hydraulics.spinup();
	//pressure(ACCUMULATOR_PRESSURE);
	hydraulics.charge_accumulators();
  hydraulics.retract(left);
	hydraulics.retract(right);
	hydraulics.standby();
	usleep(3000000);
	hydraulics.extend(left);
	hydraulics.extend(right);
	usleep(2000000);
	hydraulics.spinup();
	hydraulics.retract(left);
	hydraulics.retract(right);
	hydraulics.standby();
	hydraulics.shutdown();

}
