#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "GpioHandler.hpp"


int
main(int argc, char** argv)
{

  if (geteuid()) {
    std::cout << "This executable must be run as root" << std::endl;
    return EXIT_FAILURE;
  }
  
  GpioHandler handler;

  handler.exportPin(4);
  handler.setAsOutput(4);
  handler.setState(4, false);

  std::cout << "Switch state of GPIO 4, 10 times" << std::endl;
  for (int i = 0; i < 10; ++i) {
    handler.setState(4, true);
    sleep(1);
    handler.setState(4, false);
    sleep(1);
  }
  
  return EXIT_SUCCESS;

}
