#include <iostream>
#include "GreenHouseServer.hpp"

GreenHouseServer::GreenHouseServer(GreenHouseSensors &sensors, GreenHouseActuators &actuators):
  m_sensors(sensors),
  m_actuators(actuators),
  m_context(1),
  m_publishSocket(m_context, ZMQ_PUB)
{
  m_sensors.addListener(this);
  m_publishSocket.bind("tcp://127.0.0.1:6533");
}
void
GreenHouseServer::newSensorMeasure(double humidity, bool pumpActivated, double temperature, double waterLevel, bool needsRefill) {
  std::cout << "Humidity=" << humidity << ", T°C=" << temperature << ", water level=" << waterLevel << ", pump activated=" << std::boolalpha << pumpActivated << " tank empty=" << needsRefill << std::endl;

  std::stringstream ss(std::ios::in|std::ios::out);
  ss  << "Humidity=" << humidity << ", T°C=" << temperature << ", water level=" << waterLevel << ", pump activated=" << std::boolalpha << pumpActivated << " tank empty=" << needsRefill << std::endl;
  std::string s(ss.str());
  zmq::message_t message(s.begin(), s.end());
  m_publishSocket.send(message);
}


void
GreenHouseServer::TAP()
{
  m_actuators.TAP();
}
