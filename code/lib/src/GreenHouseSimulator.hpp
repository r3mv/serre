#ifndef GREEN_HOUSE_SIMULATOR_HPP
#define GREEN_HOUSE_SIMULATOR_HPP

#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>

#include "HumiditySensor.hpp"
#include "PumpSensor.hpp"
#include "TemperatureSensor.hpp"
#include "WaterLevelSensor.hpp"

#include "PumpActuator.hpp"
#include "TAPActuator.hpp"

/**
 * This class simulates the greenhouse. It reads periodically in a file the sensor values that have to be
 * returned and provide fake implem of the actuators
 */
class GreenHouseSimulator : public HumiditySensor,
			    public PumpSensor,
			    public TemperatureSensor,
			    public WaterLevelSensor,
			    public PumpActuator,
			    public TAPActuator
{
public:

  
  static const std::string HUMIDITY_KEY;
  static const std::string PUMP_KEY;
  static const std::string TEMPERATURE_KEY;
  static const std::string WATER_LEVEL_KEY;
  
public:

  GreenHouseSimulator(const std::string &inputFile, int refreshPeriod_ms = 1000);
  ~GreenHouseSimulator();


  double
  getHumidity_percent();

  bool
  getPumpActivated();

  double
  getTemperature_celsius();
  
  double
  getWaterLevel_percent();

  /**
   * True if waterLevel > 10
   */
  bool
  getHasWater();

  void
  activatePump(bool activated);

  void
  TAP();
  
  void
  setValues(double humidityLevel, bool pumpActivated, double temp, double waterLevel);
  
  
private:

  void
  updateValues();
  
private:
  std::string m_inputFile;
  std::map<std::string, std::string> m_map;
  std::mutex m_mutex;
  int m_refreshPeriod_ms;
  std::thread m_thread;
  bool m_running;
};

#endif
