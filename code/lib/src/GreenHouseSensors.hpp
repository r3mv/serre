#ifndef GREENHOUSE_SENSORS_HPP
#define GREENHOUSE_SENSORS_HPP

#include <atomic>
#include <thread>
#include <vector>

#include "GreenHouseSensorsListener.hpp"
#include "HumiditySensor.hpp"
#include "PumpSensor.hpp"
#include "TemperatureSensor.hpp"
#include "WaterLevelSensor.hpp"

/**
 * This class must regularly takes measurements on the sensor and inform
 * listeners when of new measurement values
 */
class GreenHouseSensors
{
public:
  GreenHouseSensors(HumiditySensor &hSensor,
		    PumpSensor &pSensor,
		    TemperatureSensor &tempSensor,
		    WaterLevelSensor &sensor,
		    int refreshPeriod_ms = 10000
		    );
  
  virtual
  ~GreenHouseSensors();

  void
  addListener(GreenHouseSensorsListener* listener);

  void
  removeListener(GreenHouseSensorsListener* listener);

private:

  void
  querySensors();
  void
  fireNewSensorMeasure(double h, bool p, double t, double wl, bool nr);
  
private:

  HumiditySensor &m_humiditySensor;
  PumpSensor &m_pumpSensor;
  TemperatureSensor &m_temperatureSensor;
  WaterLevelSensor &m_waterLevelSensor;

  std::atomic_bool m_running;
  std::vector<GreenHouseSensorsListener*> m_listeners;
  std::thread m_thread;
  int m_refreshPeriod_ms;
  
};

#endif
