#ifndef OTAHANDLER_HPP
#define OTAHANDLER_HPP

#include "ArduinoOTA.h"

class OTAHandler
{
  private:
  OTAHandler(void);
  ~OTAHandler(void);

  public:
  static void init(void);
  static void execute(void);
};

#endif