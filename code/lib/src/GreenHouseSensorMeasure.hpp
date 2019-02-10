#ifndef SERRE_GREENHOUSE_SENSORS_MEASURE_HPP
#define SERRE_GREENHOUSE_SENSORS_MEASURE_HPP

#include <iostream>

struct GreenHouseSensorMeasure
{

  virtual
  ~GreenHouseSensorMeasure(){}
  
  double humidity;
  bool pumpActivated;
  double temperature;
  double waterLevel;
  bool needsRefill;
};


std::ostream &operator<<(std::ostream &out, const GreenHouseSensorMeasure &data);
std::ostream &asJson(std::ostream &out, const GreenHouseSensorMeasure &measure);


#endif // SERRE_GREENHOUSE_SENSORS_MEASURE_HPP
