#include "LogDriver.hpp"

/**
 * @brief Construct a new LOGDriver::LOGDriver object
 * 
 */
LOGDriver::LOGDriver(void)
{

}

/**
 * @brief Destroy the LOGDriver::LOGDriver object
 * 
 */
LOGDriver::~LOGDriver(void)
{

}

/**
 * @brief Init the LOGDriver system
 * 
 */
void LOGDriver::init(void)
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

/**
 * @brief Print the log on serial wire
 * 
 * @param s String to print
 */
void LOGDriver::println(String s)
{
#ifdef LOG_SERIAL
  Serial.println(s);
#endif
}