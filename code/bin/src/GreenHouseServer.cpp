#include <iostream>
#include "GreenHouseServer.hpp"

GreenHouseServer::GreenHouseServer(GreenHouseSensors &sensors, GreenHouseActuators &actuators):
  m_sensors(sensors),
  m_actuators(actuators),
  m_running(true),
  m_lastSensorMeasure(),
  m_context(1),
  m_socket(m_context, ZMQ_REP)
{
  m_sensors.addListener(this);
  m_socket.bind("tcp://127.0.0.1:6533");

  m_thread = std::thread([this]{
      while (m_running) {
	zmq::message_t request;
	m_socket.recv(&request);
	std::cout << "Request received"<< std::endl;
	zmq::message_t reply(sizeof(GreenHouseSensorMeasure));
	memcpy(reply.data(), &m_lastSensorMeasure, sizeof(GreenHouseSensorMeasure));
	m_socket.send(reply);
      }
    });
  
}

GreenHouseServer::~GreenHouseServer()
{
}


void
GreenHouseServer::newSensorMeasure(const GreenHouseSensorMeasure &data) {
  m_lastSensorMeasure = data;
  std::cout << "Humidity=" << data.humidity << ", T°C=" << data.temperature << ", water level=" << data.waterLevel << ", pump activated=" << std::boolalpha << data.pumpActivated << " tank empty=" << data.needsRefill << std::endl;
}


void
GreenHouseServer::TAP()
{
  m_actuators.TAP();
}


void
GreenHouseServer::stop()
{
  m_running = false;
  if (m_thread.joinable()) {
    m_thread.join();
  }
}
