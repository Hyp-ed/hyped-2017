
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <iostream>
using namespace std;

class BaseCommunicator
{
	
	private:
		int sockfd, portno, n;
		struct sockaddr_in serv_addr;
		struct hostent *server;
		char buffer[256];
	
	public:
		BaseCommunicator();
		~BaseCommunicator();
		int sendAcceleration(float accel);
		int sendVelocity(float speed);
		int sendPosition(float position);
		int sendPodTemperature(float temp);
		int sendStripeCount(int stripes);
		int sendGroundProximity(float prox);
		int sendRailProximity(float prox);
		int sendPusherDetection(int detected);
		int sendBattery1Temperature(float temp);
		int sendBattery1Current(float current);
		int sendBattery1Voltage(float voltage);
		int sendBattery2Temperature(float temp);
		int sendBattery2Current(float current);
		int sendBattery2Voltage(float voltage);
		int sendBattery3Temperature(float temp);
		int sendBattery3Voltage(float voltage);
		int sendHydraulicStatus(int status);
		int sendAccum1(int status);
		int sendAccum2(int status);
		int sendAccum3(int status);
		int sendAccum4(int status);
		int sendPodStatus(int status);
		int setName(int name);
		int sendData(string message);
		void receiverThread();
	};