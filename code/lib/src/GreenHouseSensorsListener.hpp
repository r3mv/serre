#ifndef SERRE_GREENHOUSE_SENSORS_LISTENER_HPP
#define SERRE_GREENHOUSE_SENSORS_LISTENER_HPP

class GreenHouseSensorsListener
{
public:
  
  virtual
  void newSensorMeasure(double humidity, bool pumpActivated, double temperature, double waterLevel, bool needsRefill) = 0;
  
};

#endif
