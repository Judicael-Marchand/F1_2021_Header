#ifndef SCREENHANDLER_HPP
#define SCREENHANDLER_HPP

#include "Arduino.h"
#include "Telemetry_Messages.hpp"
#include "LCDDriver.hpp"
#include "LogDriver.hpp"
#include "BatteryDriver.hpp"

#define BATTERY_UPDATE_TIME 1000  // 1000ms

class ScreenHandler
{
private:
  Telemetry_Messages *mTelemetryMessages;
  LCDDriver *mLCDDriver;
  BatteryDriver *mBatteryDriver;

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