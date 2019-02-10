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
  
  ~GreenHouseServer();

  void
  newSensorMeasure(const GreenHouseSensorMeasure &data);

  void
  TAP();

  void
  stop();
  
private:
  GreenHouseSensors &m_sensors;
  GreenHouseActuators &m_actuators;

  bool m_running;
  std::thread m_thread;
  
  GreenHouseSensorMeasure m_lastSensorMeasure;
  
  zmq::context_t m_context;
  zmq::socket_t m_socket;
};

#endif
