#ifndef TAP_FSWEBCAM_HPP
#define TAP_FSWEBCAM_HPP

#include <string>
#include "TAPActuator.hpp"

/**
 * Implements "Take a Picture" using a system call to fswebcam.
 * This is highly not portable, it is designed to be run on a Pi with raspbian
 * Note that fswebcam returns 0 even if it has no device connected
 * This command does not check the return value of the child process
 *
 */
class TAPFsWebcam : public TAPActuator
{

public:

  TAPFsWebcam();
  ~TAPFsWebcam(){};

  void
  TAP();

private:

  std::string m_command;
};
#endif
