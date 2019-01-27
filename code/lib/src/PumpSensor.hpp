#ifndef PUMP_SENSOR_HPP
#define PUMP_SENSOR_HPP

class PumpSensor {

public:
  

  virtual ~PumpSensor() {}

  /**
   * @return true if pump is active, false otherwise
   */
  virtual bool
  getPumpActivated() = 0;

};
#endif
