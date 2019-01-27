#ifndef SERRE_GREENHOUSE_SENSORS_LISTENER_HPP
#define SERRE_GREENHOUSE_SENSORS_LISTENER_HPP

class GreenHouseSensorsListener
{

  virtual
  void newTemperature(double temperature_celsius) = 0;

  virtual
  void newHumidity(double humidity_percent) = 0;

  virtual
  void isWatering(bool watering) = 0;

}

#endif
