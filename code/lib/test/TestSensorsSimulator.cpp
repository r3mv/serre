#include <fstream>
#include <iostream>
#include <gtest/gtest.h>
#include "SensorsSimulator.hpp"

void
updateValues(const std::string file, double humidityLevel, bool pumpActivated, double temp, double waterLevel)
{
  std::ofstream outfile(file.c_str());
  if (outfile.good()) {
    outfile << SensorsSimulator::HUMIDITY_KEY << "=" << humidityLevel << std::endl
	    << SensorsSimulator::PUMP_KEY << "=" << std::boolalpha << pumpActivated << std::endl
	    << SensorsSimulator::TEMPERATURE_KEY << "=" << temp << std::endl
	    << SensorsSimulator::WATER_LEVEL_KEY << "=" << waterLevel << std::endl;
    outfile.close();
  }
}

TEST(SensorsSimulator, ChangeValues)
{
  try {
    const std::string file = "sensors.txt";
    const int refresh_ms = 100;
    updateValues(file, 50, false, 20, 50);
    SensorsSimulator simulator(file, refresh_ms);
    std::this_thread::sleep_for(std::chrono::milliseconds(2*refresh_ms));
    ASSERT_EQ(50, simulator.getHumidity_percent());
    ASSERT_EQ(false, simulator.getPumpActivated());
    ASSERT_EQ(20, simulator.getTemperature_celsius());
    ASSERT_EQ(50, simulator.getWaterLevel_percent());
    ASSERT_TRUE(simulator.getHasWater());
    updateValues(file, 80, true, 18, 10);
    std::this_thread::sleep_for(std::chrono::milliseconds(refresh_ms));
    ASSERT_EQ(80, simulator.getHumidity_percent());
    ASSERT_EQ(true, simulator.getPumpActivated());
    ASSERT_EQ(18, simulator.getTemperature_celsius());
    ASSERT_EQ(10, simulator.getWaterLevel_percent());
    ASSERT_FALSE(simulator.getHasWater());

    simulator.activatePump(false);
    std::this_thread::sleep_for(std::chrono::milliseconds(refresh_ms));
    ASSERT_FALSE(simulator.getPumpActivated());
    
  } catch (std::exception &e) {
    FAIL() << e.what();
  }
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
