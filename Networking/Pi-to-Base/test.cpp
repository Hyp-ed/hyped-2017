
#include "BaseCommunicator.cpp"
	
int main()
{
	std :: thread (receiverThread);
	
	BaseCommunicator baseStation;
	
	int echo = baseStation.setName(0);
	printf("%i\n", echo);
	
	baseStation.sendAcceleration(10.45);
	baseStation.sendVelocity(20.12);
	baseStation.sendPosition(3.14);
	baseStation.sendPodTemperature(50.11);
	baseStation.sendStripeCount(111);
	baseStation.sendGroundProximity(4.1);
	baseStation.sendRailProximity(2.4);
	baseStation.sendPusherDetection(1);
	baseStation.sendBattery1Temperature(74.5);
	baseStation.sendBattery1Current(40);
	baseStation.sendBattery1Voltage(120);
	baseStation.sendBattery2Temperature(30.66);
	baseStation.sendBattery2Current(12);
	baseStation.sendBattery2Voltage(30);
	baseStation.sendBattery3Temperature(65);
	baseStation.sendBattery3Voltage(35.8);
	baseStation.sendHydraulicStatus(1);
	baseStation.sendAccum1(0);
	baseStation.sendAccum2(1);
	baseStation.sendAccum3(1);
	baseStation.sendAccum4(1);
	baseStation.sendPodStatus(2);
	
	return 0;	
}