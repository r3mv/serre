#include <algorithm>
#include "GreenHouseSensors.hpp"

GreenHouseSensors::GreenHouseSensors(HumiditySensor &hs,
				     PumpSensor &ps,
				     TemperatureSensor &ts,
				     WaterLevelSensor &wls,
				     int refreshPeriod_ms):
  m_humiditySensor(hs),
  m_pumpSensor(ps),
  m_temperatureSensor(ts),
  m_waterLevelSensor(wls),
  m_running(true),
  m_listeners(),
  m_thread(),
  m_refreshPeriod_ms(refreshPeriod_ms)
{
  m_thread = std::thread([this] {
      while (m_running) {
	querySensors();
	std::this_thread::sleep_for(std::chrono::milliseconds(m_refreshPeriod_ms));
      }
    });
}

GreenHouseSensors::~GreenHouseSensors()
{
  m_running = false;
  if (m_thread.joinable()) {
    m_thread.join();
  }
}



void
GreenHouseSensors::addListener(GreenHouseSensorsListener* listener)
{
  m_listeners.push_back(listener);
}

void
GreenHouseSensors::removeListener(GreenHouseSensorsListener *listener)
{
  std::vector<GreenHouseSensorsListener*>::const_iterator it = std::find(m_listeners.begin(), m_listeners.end(), listener);
  if (it != m_listeners.end()) {
    m_listeners.erase(it);
  }
}


void
GreenHouseSensors::fireNewSensorMeasure(double h, bool p, double t, double wl, bool nr)
{
  for (GreenHouseSensorsListener *l : m_listeners) {
    l->newSensorMeasure(h, p, t, wl, nr);
  }
}

void
GreenHouseSensors::querySensors() {
  double h = m_humiditySensor.getHumidity_percent();
  bool p = m_pumpSensor.getPumpActivated();
  double t = m_temperatureSensor.getTemperature_celsius();
  double wl = m_waterLevelSensor.getWaterLevel_percent();
  bool nr = ! m_waterLevelSensor.getHasWater();
  fireNewSensorMeasure(h, p, t, wl, nr);
}
