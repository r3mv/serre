#ifndef GREENHOUSE_SENSORS_HPP
#define GREENHOUSE_SENSORS_HPP

#include <atomic>
#include <thread>

#include "HumiditySensor.hpp"
#include "TemperatureSensor.hpp"
/**
 * This class must regularly takes measurements on the sensor and inform
 * listeners when of new measurement values
 */
class GreenHouseSensors
{
public:
  GreenHouseSensors(TemperatureSensor &tempSensor, HumiditySensor &hSensor);

  virtual
  ~GreenHouseSensors();

  void
  addListener(GreenHouseSensorsListener* listener);


private:
  void
  fireNewTemperature(double temp);

  void
  fireNewHumidity(double humidity);

  void
  fireIsWatering(bool watering);
  
private:

  TemperatureSensor &m_temperatureSensor;
  HumiditySensor &m_humiditySensor;
  
  std::atomic_bool m_running;
  std::vector<GreenHouseSensorsListener*> m_listeners;

  std::thread m_tempThread;
  std::thread m_humidityThread;
  std::thread m_wateringThread;
  
};

#endif
