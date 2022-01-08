#include "LogDriver.hpp"

LOGDriver::LOGDriver(void)
{
#ifdef LOG_SERIAL
  Serial.begin(115200);
  Serial.setTimeout(2000);

  // Wait for serial to initialize.
  while (!Serial)
  {
  }
#endif
}

LOGDriver::~LOGDriver(void)
{

}

void LOGDriver::println(String s)
{
#ifdef LOG_SERIAL
  Serial.println(s);
#endif
}