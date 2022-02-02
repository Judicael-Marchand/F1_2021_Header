#ifndef SCREENHANDLER_HPP
#define SCREENHANDLER_HPP

#include "Telemetry_Messages.hpp"
#include "LCDDriver.hpp"
#include "LogDriver.hpp"

class ScreenHandler
{
private:
  Telemetry_Messages *mTelemetryMessages;
  LCDDriver *mLCDDriver;

public:
  ScreenHandler(void);
  ~ScreenHandler();
  void execute(void);
  void printUpdateProgress(uint8_t percentage);
  void printUpdateFinished(void);
  void printUpdateError(String e);
  void resetScreen(void);
};

#endif