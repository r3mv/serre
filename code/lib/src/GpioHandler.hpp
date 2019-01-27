#ifndef SERRE_GPIO_HANDLER_HPP
#define SERRE_GPIO_HANDLER_HPP

#include <vector>


/**
 * GPIO Handler using sysfs
 */
class GpioHandler {

public:
  GpioHandler();
  ~GpioHandler();

  /**
   * Set GPIO PIN to the given state
   * @param id: id of the GPIO to set
   * @param state: GPIO state, true = PIN HIGH (switch on), false = PIN LOW (switch off)
   * @throws exception if PIN is set to output
   */
  void
  setState(int id, bool state);

  /**
   * Get the state of the given GPIO
   * @return true if state is HIGH, false otherwise
   */
  bool
  getState(int id);


  /**
   * "Export" the GPIO so that it can be used
   */
  void
  exportPin(int id);

  /**
   * Set the direction of the GPIO PIN
   * @param id the ID of the PIN
   * @param isOutput if true, GPIO is set as an output PIN, otherwise as an input pin
   */
  void
  setDirection(int id, bool isOutput);

  void
  setAsOutput(int id);

  void
  setAsInput(int id);
    
  /**
   * Check if GPIO is exported
   */
  bool
  isOutputPin(int id);

private:

  std::vector<char> m_buffer;

  static const char* GPIO_EXPORT_PATH;
  static const char* GPIO_DIRECTION_PATH;
  static const char* GPIO_VALUE_PATH;

};

#endif
