#include <Arduino.h>
#include "OTAHandler.hpp"
#include "LogDriver.hpp"
#include "ScreenHandler.hpp"

ScreenHandler *mScreenHandler;

void setup()
{
  // put your setup code here, to run once:
  LOGDriver::init();
  mScreenHandler = new ScreenHandler();
  OTAHandler::init();
}

void loop()
{
  OTAHandler::execute();
  delay(1);
}