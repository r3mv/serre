INCLUDE_DIRECTORIES(../src)

ADD_EXECUTABLE(TestGreenHouseSimulator TestGreenHouseSimulator.cpp)
TARGET_LINK_LIBRARIES(TestGreenHouseSimulator ${GTEST_LIBRARIES} Threads::Threads ${GREENHOUSE_LIBRARY_NAME})
ADD_TEST(TestGreenHouseSimulator TestGreenHouseSimulator)
