#include <stdlib.h>
#include "TAPFsWebcam.hpp"

TAPFsWebcam::TAPFsWebcam()
  : m_command("fswebcam -c /tmp/capture.config ~/\"$(date +%Y%m%d_%H%M%S).jpg\" ")
{}

void
TAPFsWebcam::TAP()
{
  // no checks whatsoever
  system(m_command.c_str());
}
