#include <iostream>
#include "GreenHouseServer.hpp"

GreenHouseServer::GreenHouseServer(GreenHouseSensors &sensors, GreenHouseActuators &actuators):
  m_sensors(sensors),
  m_actuators(actuators)
{
  m_sensors.addListener(this);
}
void
GreenHouseServer::newSensorMeasure(double humidity, bool pumpActivated, double temperature, double waterLevel, bool needsRefill) {
  std::cout << "Humidity=" << humidity << ", T°C=" << temperature << ", water level=" << waterLevel << ", pump activated=" << std::boolalpha << pumpActivated << " tank empty=" << needsRefill << std::endl;
}


void
GreenHouseServer::TAP()
{
  m_actuators.TAP();
}
