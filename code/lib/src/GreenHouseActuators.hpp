#ifndef GREENHOUSE_ACTUATORS_HPP
#define GREENHOUSE_ACTUATORS_HPP


#include "PumpActuator.hpp"
#include "TAPActuator.hpp"

class GreenHouseActuators
{
public:
  GreenHouseActuators(PumpActuator &pump, TAPActuator &tap);
  
  ~GreenHouseActuators();

  void
  activatePump(bool activated);

  void
  TAP();

private:

  PumpActuator &m_pump;
  TAPActuator &m_tap;

  
};
#endif
