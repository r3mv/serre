#ifndef SERRE_GREENHOUSE_SENSORS_LISTENER_HPP
#define SERRE_GREENHOUSE_SENSORS_LISTENER_HPP

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

class GreenHouseSensorsListener
{
public:
  
  virtual
  void newSensorMeasure(const GreenHouseSensorMeasure &measure) = 0;
  
};

#endif
