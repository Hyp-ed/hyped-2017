#ifndef NETWORK_PROXI_HPP_
#define NETWORK_PROXI_HPP_

#include <string>
#include "interfaces.hpp"
#include "master-slave-comms/master/NetworkMaster.hpp"

class NetworkProxi : public Proxi
{
  public:
    NetworkProxi(NetworkMaster& slave, std::string proxi_desc);
    virtual ~NetworkProxi();
    virtual int get_distance();

  private:
    NetworkMaster& slave;
    std::string command;
};

#endif // NETWORK_PROXI_HPP_
