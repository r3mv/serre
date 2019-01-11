SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_SYSTEM_PROCESSOR arm7)

SET(CMAKE_C_COMPILER /usr/local/arm-linux-gnueabihf-4.7-20130415/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER /usr/local/arm-linux-gnueabihf-4.7-20130415/bin/arm-linux-gnueabihf-g++)
SET(CMAKE_FIND_ROOT_PATH  /usr/local/arm-linux-gnueabihf-4.7-20130415)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
