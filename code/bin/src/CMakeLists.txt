INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib/src)
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib/src)

ADD_EXECUTABLE(greenhouse_server GreenHouseServer.cpp server.cpp)
TARGET_LINK_LIBRARIES(greenhouse_server ${GREENHOUSE_LIBRARY_NAME} Threads::Threads cppzmq)

ADD_EXECUTABLE(greenhouse_client client.cpp)
TARGET_LINK_LIBRARIES(greenhouse_client cppzmq)


ADD_EXECUTABLE(greenhouseweb greenhouseweb.cpp)
TARGET_LINK_LIBRARIES(greenhouseweb ${GREENHOUSE_LIBRARY_NAME} Threads::Threads cppzmq)
