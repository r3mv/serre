#include <zmq.hpp>
#include <iostream>
#include <sstream>
int
main(int argc, char **argv)
{

  
  zmq::context_t context(1);
  zmq::socket_t subscriber (context, ZMQ_SUB);
  subscriber.connect("tcp://localhost:6533");
  std::cout << "Listening to server messages" << std::endl;
  subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

  int update_nbr;
  long total_temp = 0;
  while (true) {
    zmq::message_t update;
    subscriber.recv(&update);
    // std::istringstream iss(static_cast<char*>(update.data()));
    // std::cout << iss.str() << std::endl;
    std::cout << "Message received: " << std::endl
	      << update << std::endl;
  }
  
  return 0;
}
