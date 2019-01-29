SET(GREENHOUSE_SENSORS_SRCS
  GpioHandler.cpp
  GreenHouseActuators.cpp
  GreenHouseSensors.cpp
  GreenHouseSimulator.cpp
  TAPFsWebcam.cpp
  )

ADD_LIBRARY(${GREENHOUSE_LIBRARY_NAME} SHARED ${GREENHOUSE_SENSORS_SRCS})

