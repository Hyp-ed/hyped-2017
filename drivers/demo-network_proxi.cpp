#include <string>
#include "master-slave-comms/master/NetworkMaster.hpp"
#include "network_proxi.hpp"

int main() {
  NetworkMaster slave1;
  slave1.setup("localhost", 11999);

  NetworkProxi proxi1(slave1, "proxi-gnd-rearski-rear");
  NetworkProxi proxi3(slave1, "proxi-gnd-rearski-front");
  NetworkProxi proxi2(slave1, "proxi-cylinder-rear");
  NetworkProxi proxi4(slave1, "proxi-cylinder-front");
  NetworkProxi proxi5(slave1, "proxi-gnd-frontski-front");
  NetworkProxi proxi6(slave1, "proxi-gnd-frontski-rear");
  std::cout << proxi1.get_distance() << std::endl;
  std::cout << proxi3.get_distance() << std::endl;
  std::cout << proxi2.get_distance() << std::endl;
  std::cout << proxi4.get_distance() << std::endl;
  std::cout << proxi5.get_distance() << std::endl;
  std::cout << proxi6.get_distance() << std::endl;

}
