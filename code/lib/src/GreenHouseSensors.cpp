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
GreenHouseSensors::fireNewSensorMeasure(const GreenHouseSensorMeasure &data)
{
  for (GreenHouseSensorsListener *l : m_listeners) {
    l->newSensorMeasure(data);
  }
}

void
GreenHouseSensors::querySensors() {
  GreenHouseSensorMeasure data;
  data.humidity = m_humiditySensor.getHumidity_percent();
  data.pumpActivated = m_pumpSensor.getPumpActivated();
  data.temperature = m_temperatureSensor.getTemperature_celsius();
  data.waterLevel = m_waterLevelSensor.getWaterLevel_percent();
  data.needsRefill = ! m_waterLevelSensor.getHasWater();
  fireNewSensorMeasure(data);
}
