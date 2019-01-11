#include <cstdio>
#include <iostream>
#include <fstream>
#include <syslog.h>
#include <stdexcept>
#include "GpioHandler.hpp"

namespace serre
{

  const char* GpioHandler::GPIO_EXPORT_PATH = "/sys/class/gpio/export";
  const char* GpioHandler::GPIO_DIRECTION_PATH = "/sys/class/gpio/gpio%d/direction";
  const char* GpioHandler::GPIO_VALUE_PATH = "/sys/class/gpio/gpio%d/value";
  
  GpioHandler::GpioHandler():
    m_buffer(128)
  {}

  GpioHandler::~GpioHandler()
  {}


  void
  GpioHandler::setState(int id, bool state)
  {
    if (!isOutputPin(id)) {
      syslog(LOG_ERR, "GPIO %d is not a valid output pin", id);
      throw std::runtime_error("Setting state on a GPIO that is not properly set up");
    }
    sprintf(&m_buffer[0], GPIO_VALUE_PATH, id);
    std::ofstream outfile(&m_buffer[0]);
    outfile << ((state) ? "1" : "0") << std::endl;
    outfile.close();
  }

  bool
  GpioHandler::getState(int id) {
    sprintf(&m_buffer[0], GPIO_VALUE_PATH, id);
    std::ifstream infile(&m_buffer[0]);
    if (!infile.good()) {
      syslog(LOG_ERR, "Cannot read GPIO %d value. Is it properly set up ?", id);
      throw std::runtime_error("Could not read GPIO value");
    }
    int val = -1;
    infile >> val;
    switch(val) {
    case 0:
      return false;
    case 1:
      return true;
    default:
      syslog(LOG_ERR, "Could not read GPIO %d value", id);
      throw std::runtime_error("Could not read GPIO value");
    }
  }

  void
  GpioHandler::exportPin(int id) {
    std::ofstream outfile(GPIO_EXPORT_PATH);
    outfile << id << std::endl;
    outfile.close();
  }

  void
  GpioHandler::setDirection(int id, bool isOutput)
  {
    sprintf(&m_buffer[0], GPIO_DIRECTION_PATH, id);
    std::ofstream outfile(&m_buffer[0]);
    outfile << isOutput ? "out" : "in";
    outfile.close();
  }

  void
  GpioHandler::setAsInput(int id)
  {
    setDirection(id, false);
  }

  void
  GpioHandler::setAsOutput(int id)
  {
    setDirection(id, true);
  }

  bool
  GpioHandler::isOutputPin(int id) {
    sprintf(&m_buffer[0], GPIO_DIRECTION_PATH, id);
    std::ifstream infile(&m_buffer[0]);
    if (infile.good()) {
      std::string dir;
      infile >> dir;
      infile.close();
      return dir == "out";
    } else {
      syslog(LOG_ERR, "Could not read direction of pin %d", id);
      throw std::runtime_error("Cannot read GPIO direction");
    }
  }
  
}
