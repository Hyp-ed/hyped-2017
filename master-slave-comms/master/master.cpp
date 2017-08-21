#include <iostream>
#include "NetworkMaster.cpp"

int main(int argc, char *argv[])
{
	// Init slaves
	NetworkMaster slave1;
	slave1.setup("192.168.1.108",11998);

	// Request string
  string slave1command = "brake";

  slave1.Send(slave1command);


  // Get response
  string slave1res = slave1.receive();

  // Pring response
  cout << "Slave1 response:" << slave1res << endl;

	exit(0);
	return 0;

}
