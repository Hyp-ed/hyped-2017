
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
		char* ipAddress;
	
	public:
		BaseCommunicator();
		BaseCommunicator(char* ip);
		~BaseCommunicator();
		bool setUp();
		int sendAcceleration(float accel);
		int sendVelocity(float speed);
		int sendPosition(float position);
		int sendPodTemperature(float temp);
		int sendStripeCount(int stripes);
		int sendDistance(float distance);
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
		int sendBattery3Current(float current);
		int sendHydraulicStatus(int status);
		int sendAccum1(float pressure);
		int sendAccum2(float pressure);
		int sendPump1(float pressure);
		int sendPump2(float pressure);
		int sendPodStatus(int status);
		
		int sendAccelerationXYZ(float x, float y, float z);
		int sendVelocityXYZ(float x, float y, float z);
		int sendPositionXYZ(float x, float y, float z);
		
		string requestBrakeState();
		string requestReadyState();
		string requestPowerState();
		string requestMotorState();
		
		int setName(int name);
		int sendData(string message);
		
		void sendDataWithoutEcho(string message);
		void receiverThread();
		void receiverThread(string &message);
		//string receive();
	};