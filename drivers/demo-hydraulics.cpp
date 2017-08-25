#include "hydraulics.hpp"
#include <string>

int main()
{

	std::string left = "left";
	std::string right = "right";

	Hydraulics hydraulics;

	hydraulics.spin_up();
	hydraulics.charge_accumulators();
	hydraulics.retract(left);
	hydraulics.retract(right);
	hydraulics.stand_by();

	usleep(3000000); // 2000 milliseconds

	hydraulics.extend(left);
	hydraulics.extend(right);

	usleep(2000000); // 2000 milliseconds

	hydraulics.spin_up();
	hydraulics.retract(left);
	hydraulics.retract(right);
	hydraulics.stand_by();
	hydraulics.shut_down();

}
