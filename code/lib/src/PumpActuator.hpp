#ifndef PUMP_ACTUATOR_HPP
#define PUMP_ACTUATOR_HPP


/**
 * Interface for class actuating the pump
 */
class PumpActuator {

public:

  virtual
  ~PumpActuator(){}

  virtual
  void activatePump(bool activated) = 0;

};
  

#endif
