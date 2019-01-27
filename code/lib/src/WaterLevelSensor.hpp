#ifndef WATER_LEVEL_SENSOR
#define WATER_LEVEL_SENSOR

class WaterLevelSensor {

public:
  
  virtual ~WaterLevelSensor() {
  }

  virtual double getWaterLevel_percent() = 0;

  virtual bool getHasWater() = 0;
};

#endif
