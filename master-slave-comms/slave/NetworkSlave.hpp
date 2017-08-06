#ifndef HYPED_MASTERSLAVECOMMS_SLAVE_NETWORKSLAVE_HPP_
#define HYPED_MASTERSLAVECOMMS_SLAVE_NETWORKSLAVE_HPP_

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>


#define MAXPACKETSIZE 4096

class NetworkSlave
{
  public:
    int sockfd, newsockfd, n, pid;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    pthread_t serverThread;
    char msg[ MAXPACKETSIZE ];
    static std::string Message;

    void setup(int port);
    std::string receive();
    std::string getMessage();
    void Send(std::string msg);
    void detach();
    void clean();

  private:
    static void * Task(void * argv);
};

#endif // HYPED_MASTERSLAVECOMMS_SLAVE_NETWORKSLAVE_HPP_

