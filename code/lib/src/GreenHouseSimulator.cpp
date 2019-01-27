#include "GreenHouseSimulator.hpp"
#include <chrono>
#include <fstream>
#include <sstream>

const std::string GreenHouseSimulator::HUMIDITY_KEY = "humidity";
const std::string GreenHouseSimulator::PUMP_KEY = "pumpActivated";
const std::string GreenHouseSimulator::TEMPERATURE_KEY = "temperature";
const std::string GreenHouseSimulator::WATER_LEVEL_KEY = "waterLevel";


GreenHouseSimulator::GreenHouseSimulator(const std::string &input, int refresh)
  : m_inputFile(input),
    m_map(),
    m_mutex(),
    m_refreshPeriod_ms(refresh),
    m_thread(),
    m_running(true)
{

  // set default values
  setValues(50,false,20,50);
  
  m_thread = std::thread([this] {
      while (m_running) {
	updateValues();
	std::this_thread::sleep_for(std::chrono::milliseconds(m_refreshPeriod_ms));
      }
    });
}

GreenHouseSimulator::~GreenHouseSimulator()
{
  m_running = false;
  if (m_thread.joinable()) {
    m_thread.join();
  }
}

double
GreenHouseSimulator::getHumidity_percent()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  return std::stod(m_map.at(HUMIDITY_KEY));
}

bool
GreenHouseSimulator::getPumpActivated()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  bool b;
  std::istringstream(m_map.at(PUMP_KEY)) >> std::boolalpha >> b;
  return b;
}

double
GreenHouseSimulator::getTemperature_celsius()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  return std::stod(m_map.at(TEMPERATURE_KEY));
}

double
GreenHouseSimulator::getWaterLevel_percent()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  return std::stod(m_map.at(WATER_LEVEL_KEY));
}

bool
GreenHouseSimulator::getHasWater() {
  return getWaterLevel_percent() > 10;
}

void GreenHouseSimulator::activatePump(bool activated)
{
  setValues(getHumidity_percent(), activated, getTemperature_celsius(), getWaterLevel_percent());
}

void
GreenHouseSimulator::setValues(double h, bool p, double t, double wl) {
  std::ofstream outfile(m_inputFile.c_str());
  if (outfile.good()) {
    outfile << GreenHouseSimulator::HUMIDITY_KEY << "=" << h << std::endl
	    << GreenHouseSimulator::PUMP_KEY << "=" << std::boolalpha << p << std::endl
	    << GreenHouseSimulator::TEMPERATURE_KEY << "=" << t << std::endl
	    << GreenHouseSimulator::WATER_LEVEL_KEY << "=" << wl << std::endl;
    outfile.close();
  }
}

void
GreenHouseSimulator::updateValues()
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
