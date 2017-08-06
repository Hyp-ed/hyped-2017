#include <iostream>
#include "NetworkSlave.cpp"

NetworkSlave master;
int SLAVE_PORT = 11999;

void * loop(void * m)
{
        pthread_detach(pthread_self());
	while(1)
	{
		string str = master.getMessage();
		if( str != "" )
		{
			cout << "Message:" << str << endl;
			master.Send("OK");
			master.clean();
		}
		usleep(1000);
	}
	master.detach();
}

int main()
{
	pthread_t msg;
	master.setup(SLAVE_PORT);
	if( pthread_create(&msg, NULL, loop, (void *)0) == 0)
	{
		master.receive();
	}
	return 0;
}
