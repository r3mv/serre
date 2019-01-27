#include "SensorsSimulator.hpp"
#include <chrono>
#include <fstream>
#include <sstream>

const std::string SensorsSimulator::HUMIDITY_KEY = "humidity";
const std::string SensorsSimulator::PUMP_KEY = "pumpActivated";
const std::string SensorsSimulator::TEMPERATURE_KEY = "temperature";
const std::string SensorsSimulator::WATER_LEVEL_KEY = "waterLevel";


SensorsSimulator::SensorsSimulator(const std::string &input, int refresh)
  : m_inputFile(input),
    m_map(),
    m_mutex(),
    m_refreshPeriod_ms(refresh),
    m_thread(),
    m_running(true)
{

  m_thread = std::thread([this] {
      while (m_running) {
	updateValues();
	std::this_thread::sleep_for(std::chrono::milliseconds(m_refreshPeriod_ms));
      }
    });
}

SensorsSimulator::~SensorsSimulator()
{
  m_running = false;
  if (m_thread.joinable()) {
    m_thread.join();
  }
}

double
SensorsSimulator::getHumidity_percent()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  return std::stod(m_map.at(HUMIDITY_KEY));
}

bool
SensorsSimulator::getPumpActivated()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  bool b;
  std::istringstream(m_map.at(PUMP_KEY)) >> std::boolalpha >> b;
  return b;
}

double
SensorsSimulator::getTemperature_celsius()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  return std::stod(m_map.at(TEMPERATURE_KEY));
}

double
SensorsSimulator::getWaterLevel_percent()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  return std::stod(m_map.at(WATER_LEVEL_KEY));
}

bool
SensorsSimulator::getHasWater() {
  return getWaterLevel_percent() > 10;
}

void SensorsSimulator::activatePump(bool activated)
{
  setValues(getHumidity_percent(), activated, getTemperature_celsius(), getWaterLevel_percent());
}

void
SensorsSimulator::setValues(double h, bool p, double t, double wl) {
  std::ofstream outfile(m_inputFile.c_str());
  if (outfile.good()) {
    outfile << SensorsSimulator::HUMIDITY_KEY << "=" << h << std::endl
	    << SensorsSimulator::PUMP_KEY << "=" << std::boolalpha << p << std::endl
	    << SensorsSimulator::TEMPERATURE_KEY << "=" << t << std::endl
	    << SensorsSimulator::WATER_LEVEL_KEY << "=" << wl << std::endl;
    outfile.close();
  }
}

void
SensorsSimulator::updateValues()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  std::ifstream infile(m_inputFile);
  if (infile.good()) {
    std::string buffer;
      while (std::getline(infile, buffer)) {
	int index = buffer.find('=');
	if (index == std::string::npos) {
	  continue;
	}
	std::string key = buffer.substr(0,index);
	std::string value = buffer.substr(index+1);
	m_map[key] = value;
      }
      infile.close();
  }
}
