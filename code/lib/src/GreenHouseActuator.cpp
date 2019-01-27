#include "GreenHouseActuators.hpp"

GreenHouseActuators::GreenHouseActuators(PumpActuator &pump, TAPActuator &tap)
  : m_pump(pump),
    m_tap(tap)
{}


GreenHouseActuators::~GreenHouseActuators()
{}

void
GreenHouseActuators::activatePump(bool activated)
{
  m_pump.activatePump(activated);
}

void
GreenHouseActuators::TAP()
{
  m_tap.TAP();
}
