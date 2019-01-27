#ifndef TAP_ACTUATOR_HPP
#define TAP_ACTUATOR_HPP

/**
 * Interface to take pictures
 */
class TAPActuator
{

public:

  virtual ~TAPActuator() {}

  /**
   * Take a picture
   */
  virtual void TAP() = 0;

};
#endif
