#include <cstdlib>

#include "GreenHouseSensors.hpp"
#include "GreenHouseActuators.hpp"

// use simulator at the moment
#include "GreenHouseSimulator.hpp"

int
main(int argc, char **argv)
{
  
  GreenHouseSimulator simulator("/var/run/greenhouse.dat");

  simulator.getHumidity_percent();

  
}
