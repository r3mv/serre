#ifndef TEMPERATURE_SENSOR_HPP
#define TEMPERATURE_SENSOR_HPP

/**
 * Interface for temperature sensors
 */

class TemperatureSensor {

public:
  
  virtual
  ~TemperatureSensor() {};

  /**
   * Return the temperature value, in celsius degrees
   */
  virtual double
  getTemperature_celsius() = 0;

};
#endif
