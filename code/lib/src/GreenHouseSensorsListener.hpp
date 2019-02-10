#ifndef SERRE_GREENHOUSE_SENSORS_LISTENER_HPP
#define SERRE_GREENHOUSE_SENSORS_LISTENER_HPP
#include "GreenHouseSensorMeasure.hpp"

class GreenHouseSensorsListener
{
public:
  
  virtual
  void newSensorMeasure(const GreenHouseSensorMeasure &measure) = 0;
  
};

#endif
