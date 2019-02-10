#include "GreenHouseSensorMeasure.hpp"

std::ostream &operator<<(std::ostream &out, const GreenHouseSensorMeasure &data)
{

  out << "Temperature:" << data.temperature << " °C" << std::endl
      << "Humidity:" << data.humidity << "%" << std::endl
      << "Water level:" << data.waterLevel << "%" << std::endl
      << "Pump [" << (data.pumpActivated ? "activated":"deactivated")  << "]" << std::endl;
  return out;
}

std::ostream &asJson(std::ostream &out, const GreenHouseSensorMeasure &data)
{
  out << "{" << std::endl
      << "'temperature':" << data.temperature << "," << std::endl
      << "'humidity':" << data.humidity << "," << std::endl
      << "'waterLevel':" << data.waterLevel << "," << std::endl
      << "'pumpActivated':" << std::boolalpha << data.pumpActivated << std::endl
      << "}" << std::endl;
  return out;
}
