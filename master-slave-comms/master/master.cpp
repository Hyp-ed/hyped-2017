#include <iostream>
#include "NetworkMaster.cpp"

int main(int argc, char *argv[])
{
	// Init slaves
	NetworkMaster slave1;
        NetworkMaster slave2;

        // Set the IP/Port of each slave
        slave1.setup("192.168.1.108",11999);
	slave2.setup("192.168.1.108",11998);
	
	// Request string
        string slave1msg = "Request message";
	string slave2msg = "Request message";

        // Send message
        slave1.Send(slave1msg);
	slave2.Send(slave2msg);

        // Get response
        string slave1res = slave1.receive();
	string slave2res = slave2.receive();
	
        // Pring response
        cout << "Slave1 response:" << slave1res << endl;
        cout << "Slave2 response:" << slave2res << endl;

	exit(0);
	return 0;
	
}
