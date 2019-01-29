#ifndef GREENHOUSE_SERVER_HPP
#define GREENHOUSE_SERVER_HPP

#include <zmq.hpp>

#include "GreenHouseActuators.hpp"
#include "GreenHouseSensors.hpp"
#include "GreenHouseSensorsListener.hpp"


class GreenHouseServer : GreenHouseSensorsListener
{

public:
  GreenHouseServer(GreenHouseSensors &sensors, GreenHouseActuators &actuators);
  
  ~GreenHouseServer() {}

  void
  newSensorMeasure(double humidity, bool pumpActivated, double temperature, double waterLevel, bool needsRefill);

  void
  TAP();

private:
  GreenHouseSensors &m_sensors;
  GreenHouseActuators &m_actuators;

  zmq::context_t m_context;
  zmq::socket_t m_publishSocket;
};

#endif
