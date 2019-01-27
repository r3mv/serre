#ifndef HUMIDITY_SENSOR_HPP
#define HUMIDITY_SENSOR_HPP

/**
 * Interface for humidity sensors
 */

class HumiditySensor {

public:
  
  virtual
  ~HumiditySensor() {};

  /**
   * Return the humidity value, in percent
   */
  virtual double
  getHumidity_percent() = 0;
  

};
#endif
