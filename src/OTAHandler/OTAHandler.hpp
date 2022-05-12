#ifndef OTAHANDLER_HPP
#define OTAHANDLER_HPP

#include "ArduinoOTA.h"
#include "ScreenHandler.hpp"

extern ScreenHandler *mScreenHandler;

/**
 * @class OTAHandler
 * @brief Manage the OTA update to avoid putting the system into flash mode each time
 * 
 */
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