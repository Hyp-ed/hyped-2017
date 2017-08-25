#include <string>
#include "master-slave-comms/master/NetworkMaster.hpp"
#include "network_proxi.hpp"

int main() {
  NetworkMaster slave1;
  slave1.setup("localhost", 11999);

  NetworkProxi proxi(slave1, "proxi-ground-front");
  std::cout << proxi.get_distance() << std::endl;

}
