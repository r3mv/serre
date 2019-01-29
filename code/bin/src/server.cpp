#include <cstdlib>

#include "GreenHouseSensors.hpp"
#include "GreenHouseActuators.hpp"

#include "GreenHouseServer.hpp"
// use simulator at the moment
#include "GreenHouseSimulator.hpp"


bool g_running = true;
int
main(int argc, char **argv)
{
  
  GreenHouseSimulator simulator("/dev/shm/greenhouse.dat");


  GreenHouseSensors sensors(simulator, simulator, simulator, simulator, 5000);

  GreenHouseActuators actuators(simulator, simulator);

  
  GreenHouseServer server(sensors, actuators);


  
  
  // todo: make server wait for connections
  // define or use an existing protocol to send sensor values and receive actuators commands
  int cpt = 0;
  while (g_running && ++cpt < 100) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //    server.TAP();
  }
  
}
