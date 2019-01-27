INCLUDE_DIRECTORIES(../src)

ADD_EXECUTABLE(TestSensorsSimulator TestSensorsSimulator.cpp)
TARGET_LINK_LIBRARIES(TestSensorsSimulator ${GTEST_LIBRARIES} Threads::Threads ${GREENHOUSE_SENSORS_LIB_NAME})
