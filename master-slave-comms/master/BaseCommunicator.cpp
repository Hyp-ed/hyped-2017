
#include "BaseCommunicator.hpp"
#include <sstream>
#include <thread>
using namespace std;

int sockfd, portNo, n;
struct sockaddr_in serv_addr;
struct hostent *server;
char buffer[256];
char* ipAddress = "localHost";
		
BaseCommunicator :: BaseCommunicator()
{
	
}

BaseCommunicator :: BaseCommunicator(char* ip)
{
	ipAddress = ip;
}

bool BaseCommunicator :: setUp()
{
	portNo = 5695;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		printf("ERROR: CANNOT OPEN SOCKET.");
		return false;
	}
	server = gethostbyname(ipAddress);	// Declare static IP constant when known
	
	if (server == NULL) 
	{ 
		fprintf
			(
				stderr,
				"ERROR: INCORRECT BASE-STATION IP, OR BASE-STATION S/W NOT RUNNING.\n"
			);
		return 0;
	}	
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portNo);
	
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{	
		printf("ERROR: CANNOT ESTABLISH CONNECTION TO BASE-STATION.");
		return false;
	}
	
	return true;
}

BaseCommunicator :: ~BaseCommunicator()
{
	// DESTRUCTOR: upon deletion of pointer to object (instance of this class), socket to base will be closed.
	close(sockfd);
}

int BaseCommunicator :: setName(int name)
{
	string nameList[6] = 
		{
			"Master\n", "Slave_0\n", "Slave_1\n", "Slave_2\n", "Slave_3\n", "Slave_4\n"
		};
	
	return sendData(nameList[name]);
		
}

/* 
** Currently unsure if temperature values should be sent in deg. C or deg. C / 10.
** SpaceX require dimensions of tenths of a degree. We could work with this, or display
** our temeprature values on base s/w in degrees, and from there send temperature 
** data in units of deg. C / 10. To be discussed.
*/

int BaseCommunicator :: sendAcceleration(float accel)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << accel;
	
	return sendData("CMD01" + ss.str() + "\n");
}

int BaseCommunicator :: sendVelocity(float speed)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << speed;
	
	return sendData("CMD02" + ss.str() + "\n");
}

int BaseCommunicator :: sendPosition(float position)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << position;
	
	return sendData("CMD03" + ss.str() + "\n");
}

int BaseCommunicator :: sendPodTemperature(float temp)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << temp;
	
	return sendData("CMD04" + ss.str() + "\n");
}

int BaseCommunicator :: sendStripeCount(int stripes)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << stripes;
	
	return sendData("CMD05" + ss.str() + "\n");
}

int BaseCommunicator :: sendGroundProximity(float prox)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << prox;
	
	return sendData("CMD06" + ss.str() + "\n");
}

int BaseCommunicator :: sendRailProximity(float prox)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << prox;
	
	return sendData("CMD07" + ss.str() + "\n");
}

int BaseCommunicator :: sendPusherDetection(int detected)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << detected;
	
	return sendData("CMD08" + ss.str() + "\n");
}

int BaseCommunicator :: sendBattery1Temperature(float temp)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << temp;
	
	return sendData("CMD09" + ss.str() + "\n");
}

int BaseCommunicator :: sendBattery1Current(float current)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << current;
	
	return sendData("CMD10" + ss.str() + "\n");
}

int BaseCommunicator :: sendBattery1Voltage(float voltage)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << voltage;
	
	return sendData("CMD11" + ss.str() + "\n");
}

int BaseCommunicator :: sendBattery2Temperature(float temp)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << temp;
	
	return sendData("CMD12" + ss.str() + "\n");
}

int BaseCommunicator :: sendBattery2Current(float current)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << current;
	
	return sendData("CMD13" + ss.str() + "\n");
}

int BaseCommunicator :: sendBattery2Voltage(float voltage)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << voltage;
	
	return sendData("CMD14" + ss.str() + "\n");
}

int BaseCommunicator :: sendBattery3Temperature(float temp)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << temp;
	
	return sendData("CMD15" + ss.str() + "\n");
}

int BaseCommunicator :: sendBattery3Voltage(float voltage)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << voltage;
	
	return sendData("CMD16" + ss.str() + "\n");
}

int BaseCommunicator :: sendHydraulicStatus(int status)
{
	// Pass 1 if hyrdraulics are 'ACTUATED', 0 if 'OFF'. All values other than 1 will be interpreted by base-station as 'OFF'
	
	stringstream ss (stringstream::in | stringstream::out);
	ss << status;
	
	return sendData("CMD17" + ss.str() + "\n");
}

int BaseCommunicator :: sendAccum1(float pressure)
{	
	stringstream ss (stringstream::in | stringstream::out);
	ss << pressure;
	
	return sendData("CMD18" + ss.str() + "\n");
}

int BaseCommunicator :: sendAccum2(float pressure)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << pressure;
	
	return sendData("CMD19" + ss.str() + "\n");
}

int BaseCommunicator :: sendPump1(float pressure)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << pressure;
	
	return sendData("CMD20" + ss.str() + "\n");
}

int BaseCommunicator :: sendPump2(float pressure)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << pressure;
	
	return sendData("CMD21" + ss.str() + "\n");
}

int BaseCommunicator :: sendPodStatus(int status)
{
	// Pass 0 to report 'FAULT' status to base-station. Status codes are as enumerated in the SpaceX documentation.
	
	stringstream ss (stringstream::in | stringstream::out);
	ss << status;
	
	return sendData("CMD22" + ss.str() + "\n");
}

int BaseCommunicator :: sendDistance(float distance)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << distance;
	
	return sendData("CMD23" + ss.str() + "\n");
}

int BaseCommunicator :: sendBattery3Current(float current)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << current;
	
	return sendData("CMD24" + ss.str() + "\n");
}

int BaseCommunicator :: sendData(string message)
{
	// Incoming strings should be terminated by "...\n".
	bzero(buffer,256);
	const char *data = message.c_str();
	n = write(sockfd, data, strlen(data));
	if (n < 0) printf("ERROR: CANNOT WRITE TO SOCKET.");
	n = read(sockfd, buffer, 255);
	if (n < 0) printf("ERROR: CANNOT READ FROM SOCKET.");
	return atoi(buffer);
}

void BaseCommunicator :: sendDataWithoutEcho(string message)
{
	// Incoming strings should be terminated by "...\n".
	bzero(buffer,256);
	const char *data = message.c_str();
	n = write(sockfd, data, strlen(data));
	if (n < 0) printf("ERROR: CANNOT WRITE TO SOCKET.");
	//n = read(sockfd, buffer, 255);
	//if (n < 0) printf("ERROR: CANNOT READ FROM SOCKET.");
}

int BaseCommunicator :: sendAccelerationXYZ(float x, float y, float z)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << "x:" << x << "y:" << y << "z:" << z;
	
	return sendData("CMD25" + ss.str() + "\n");
}

int BaseCommunicator :: sendVelocityXYZ(float x, float y, float z)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << "x:" << x << "y:" << y << "z:" << z;
	
	return sendData("CMD26" + ss.str() + "\n");
}

int BaseCommunicator :: sendPositionXYZ(float x, float y, float z)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << "x:" << x << "y:" << y << "z:" << z;
	
	return sendData("CMD27" + ss.str() + "\n");
}

string BaseCommunicator :: requestBrakeState()
{
	// returns "BRK1" 0 to to retract brakes, "BRK1" to deploy
	char readBuffer[512];
	memset(readBuffer, 0x00, sizeof(readBuffer));
	sendDataWithoutEcho("CMD28\n");
	int n = read(sockfd, readBuffer, sizeof(readBuffer)); 
	if (strcmp(readBuffer, "-1") == 0) requestBrakeState();
	string output = readBuffer;
	return output;
}

string BaseCommunicator :: requestReadyState()
{
	// returns "RDY1" when ready to launch
	char readBuffer[512];
	memset(readBuffer, 0x00, sizeof(readBuffer));
	sendDataWithoutEcho("CMD29\n");
	int n = read(sockfd, readBuffer, sizeof(readBuffer));
	if (strcmp(readBuffer, "-1") == 0) requestReadyState();
	string output = readBuffer;
	return output;
}

string BaseCommunicator :: requestPowerState()
{
	// returns "PWR1" when batteries should be online,
	//	"PWR0" to take batteries offline
	char readBuffer[512];
	memset(readBuffer, 0x00, sizeof(readBuffer));
	sendDataWithoutEcho("CMD30\n");
	int n = read(sockfd, readBuffer, sizeof(readBuffer));
	if (strcmp(readBuffer, "-1") == 0) requestPowerState();
	string output = readBuffer;
	return output;
}

string BaseCommunicator :: requestMotorState()
{
	// returns "STOP" for service propulsion OFF,
	//	"FRWD" to PWM motor forward, and "BACK" for reverse
	char readBuffer[512];
	memset(readBuffer, 0x00, sizeof(readBuffer));
	sendDataWithoutEcho("CMD31\n");
	int n = read(sockfd, readBuffer, sizeof(readBuffer));
	if (strcmp(readBuffer, "-1") == 0) requestMotorState();
	string output = readBuffer;
	return output;
}

// Thread must be declared and joined within calling code.
void BaseCommunicator :: receiverThread()
{
	 char readBuffer[512];
	while (true) 
	{
		memset(readBuffer, 0x00, sizeof(readBuffer));
		int n = read(sockfd, readBuffer, sizeof(readBuffer));
		if (n <= 0) /*return*/break;
		if ( strcmp(readBuffer, "1") != 0 )
			cout<<readBuffer;
	}
}

void BaseCommunicator :: receiverThread(string &message)
{
	char readBuffer[512];
	 
	/*while (true) 
	{*/
		memset(readBuffer, 0x00, sizeof(readBuffer));
		int n = read(sockfd, readBuffer, sizeof(readBuffer));
		if (n <= 0) return/*break*//*message = "-1"*/;
		if ( strcmp(readBuffer, "1") != 0 )
			//cout<<readBuffer;
		{
			message = readBuffer;
		}
	//}
}

/*string BaseCommunicator :: receive()
{
	string brake = requestBrakeState();
	//cout << brake << "\n";
	return brake;
	
}*/
