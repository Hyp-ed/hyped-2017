#include "network_proxi.hpp"


NetworkProxi::NetworkProxi(NetworkMaster& slave, std::string proxi_desc)
    : slave(slave), command(proxi_desc)
{}

NetworkProxi::~NetworkProxi()
{}

int NetworkProxi::get_distance()
{
  this->slave.Send(this->command);
  std::string response = slave.receive();
  int reading = std::stoi(response);
  return reading;
}

