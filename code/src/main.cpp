#include <cstdlib>
#include <iostream>
#include <signal.h>
#include "GpioHandler.hpp"

const int GPIO_PUMP_PIN = 4;


bool g_running = true;

void
sigHandler(int signum)
{
  g_running = false;
}


double
getTemperature()
{
  return 0.0;
}


double
getHumidity()
{
  return 0.0;
}

bool
isWatering(serre::GpioHandler &handler) {
  return handler.getState(GPIO_PUMP_PIN);
}

/**
 * This function should call the humidity sensor to detect if the plant needs watering
 */
bool
needWater(serre::GpioHandler &handler) {
  if (isWatering(handler)) {
    return false;
  }
  // call sensor and see if below threshold
 
}

bool
needsWaterRefill(serre::GpiHandler &handler)
{

}

// todo: add a tempo to water for a certain time
bool
water(serre::GpioHandler &handler) {
    handler.setState(GPIO_PUMP_PIN, true);
}


int
main(int argc, char **argv)
{
  // initialization
  serre::GpioHandler handler;
  handler.exportPin(GPIO_PUMP_PIN);
  handler.setAsOutput(GPIO_PUMP_PIN);
  signal(SIGINT, sigHandler);

  // main processing loop
  while (g_running) {
    
  }

}
