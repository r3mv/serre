#include "GreenHouseSensors.hpp"

GreenHouseSensors::GreenHouseSensors(TemperatureSensor &ts, HumiditySensor &hs):
  m_temperatureSensor(ts),
  m_humiditySensor(hs),
  m_running(true),
  m_listeners(),
  m_tempThread(),
  m_humidityThread(),
  m_wateringThread()
{
  m_tempThread = std::thread(&GreenHouseSensors::getTemperature, this);
  m_humidityThread = std::thread(&GreenHouseSensors::getHumidity, this);
  m_wateringThread = std::thread(&GreenHouseSensors::getWatering, this);
  
}

GreenHouseSensors::~GreenHouseSensors()
{
  m_running = false;
  if (m_tempThread.isJoinable()) {
    m_tempThread.join();
  }
  if (m_humidityThread.isJoinable()) {
    m_humidityThread.join();
  }
  if (m_wateringThread.isJoinable()) {
    m_wateringThread.join();
  }
}



void
GreenHouseSensors::addListener(GreenHouseSensorsListener* listener)
{
  m_listeners.push_back(listener);
}

void
GreenHouseSensors::fireNewTemperature(double t)
{
  for (GreenHouseSensorsListener* listener : m_listeners) {
    listener->newTemperature(t);
  }
}

void
GreenHouseSensors::fireNewHumidity(double h)
{
  for (GreenHouseSensorsListener* listener : m_listeners){
    listener->newHumidity(h);
  }
}

void
GreenHouseSensors::fireIsWatering(bool w) {
  for (GreenHouseSensorsListener* listener: m_listeners) {
    listener->isWatering(w);
  }
}

void
GreenHouseSensors::getTemperature() {
  while (m_running) {
    double temp = m_temperatureSensor.getTemperature_celsius();
    fireNewTemperature(temp);
  }
}

void
GreenHouseSensors::getHumidity() {
  while(m_running) {
    double humidity = m_humiditySensor.getHumidity_percent();
    fireNewHumidity(humidity);
  }
}

void
GreenHouseSensors::isWatering() {
  while (m_running) {
    bool isWatering = true;
    fireIsWatering(isWatering);
  }
}

