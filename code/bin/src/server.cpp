#include <cstdlib>

#include "GreenHouseSensors.hpp"
#include "GreenHouseActuators.hpp"

// use simulator at the moment
#include "GreenHouseSimulator.hpp"

class GreenHouseServer : GreenHouseSensorsListener
{

public:
  GreenHouseServer(GreenHouseSensors &sensors):
    m_sensors(sensors)
  {
    m_sensors.addListener(this);
  }
  ~GreenHouseServer() {}

  void
  newSensorMeasure(double humidity, bool pumpActivated, double temperature, double waterLevel, bool needsRefill) {
    std::cout << "Humidity=" << humidity << ", T°C=" << temperature << ", water level=" << waterLevel << ", pump activated=" << std::boolalpha << pumpActivated << " tank empty=" << needsRefill << std::endl;
  }

private:
  GreenHouseSensors &m_sensors;

};

bool g_running = true;
int
main(int argc, char **argv)
{
  
  GreenHouseSimulator simulator("/dev/shm/greenhouse.dat");


  GreenHouseSensors sensors(simulator, simulator, simulator, simulator, 5000);

  GreenHouseServer server(sensors);

  // todo: make server wait for connections
  // define or use an existing protocol to send sensor values and receive actuators commands
  while (g_running) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  
}
