#ifndef LOGDRIVER_HPP
#define LOGDRIVER_HPP

#include "Arduino.h"

/**
 * class LOGDriver
 * @brief Manages the log system
 * 
 */
class LOGDriver 
{
  public:
  static void init(void);
  static void println(String s);

  private:
  LOGDriver();
  ~LOGDriver();
};

#endif