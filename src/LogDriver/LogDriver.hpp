#ifndef LOGDRIVER_HPP
#define LOGDRIVER_HPP

#include "Arduino.h"

class LOGDriver 
{
  public:
  LOGDriver();
  ~LOGDriver();
  static void println(String s);
};

#endif