#include "ScreenHandler.hpp"

/**
 * @brief Construct a new Screen Handler:: Screen Handler object
 * 
 */
ScreenHandler::ScreenHandler(void)
{
  mTelemetryMessages = new Telemetry_Messages();
  mLCDDriver = new LCDDriver();
  mBatteryDriver = new BatteryDriver();
}

/**
 * @brief Destroy the Screen Handler:: Screen Handler object
 * 
 */
ScreenHandler::~ScreenHandler()
{

}

/**
 * @brief Execute the ScreenHandler machine
 * @details Read the Telemetry_Messages information and the BatteryDriver information and gives it to the LCDDriver system
 * 
 */
void ScreenHandler::execute(void)
{
  static uint32_t previousTime = 0;
  mTelemetryMessages->execute();

  switch (mTelemetryMessages->getMessageID())
  {
  case NO_MESSAGE_ID:

    break;

  case SESSION_MESSAGE_ID:
    LOGDriver::println("Lap number : " + String(mTelemetryMessages->mSessionInformation.m_currentLapNum) + "/" + String(mTelemetryMessages->mSessionInformation.m_totalLaps));
    LOGDriver::println("Position : " + String(mTelemetryMessages->mSessionInformation.m_carPosition));
    LOGDriver::println("Session type : " + String(mTelemetryMessages->mSessionInformation.m_sessionType));
    LOGDriver::println("Number of active cas : " + String(mTelemetryMessages->mSessionInformation.m_numActiveCars));

    mLCDDriver->updateLapNumber(mTelemetryMessages->mSessionInformation.m_currentLapNum, mTelemetryMessages->mSessionInformation.m_totalLaps);
    mLCDDriver->updatePosition(mTelemetryMessages->mSessionInformation.m_carPosition, mTelemetryMessages->mSessionInformation.m_numActiveCars);

    mTelemetryMessages->setMessageID(NO_MESSAGE_ID);
    break;

  case CAR_MESSAGE_ID:
    LOGDriver::println("Tyre wear : RL : " + String(mTelemetryMessages->mCarInformation.m_TyreWear.m_rearLeft) + " "
                                                                                                                 "RR : " +
                       String(mTelemetryMessages->mCarInformation.m_TyreWear.m_rearRight) + " "
                                                                                            "FL : " +
                       String(mTelemetryMessages->mCarInformation.m_TyreWear.m_frontLeft) + " "
                                                                                            "FR : " +
                       String(mTelemetryMessages->mCarInformation.m_TyreWear.m_frontRight));

    mLCDDriver->updateTyreType(mTelemetryMessages->mCarInformation.m_currentTyreType);
    mLCDDriver->updateTyreWear(mTelemetryMessages->mCarInformation.m_TyreWear.m_rearLeft, mTelemetryMessages->mCarInformation.m_TyreWear.m_rearRight, mTelemetryMessages->mCarInformation.m_TyreWear.m_frontLeft, mTelemetryMessages->mCarInformation.m_TyreWear.m_frontRight);
    mLCDDriver->updateGearEngaged(mTelemetryMessages->mCarInformation.m_gear);

    mTelemetryMessages->setMessageID(NO_MESSAGE_ID);
    break;
  }

  if(millis() > (previousTime + BATTERY_UPDATE_TIME))
  {
    mBatteryDriver->execute();
    mLCDDriver->updateBatterySOC(mBatteryDriver->getBatterySOC());
    previousTime = millis();
  }
}

/**
 * @brief Print the update progress on the screen
 * 
 * @param percentage Percentage of the update progress (0% - 100%)
 */
void ScreenHandler::printUpdateProgress(uint8_t percentage)
{
  mLCDDriver->updateFirmwareUpdateProgress(percentage);
}

/**
 * @brief Print the update finished message on the screen
 * 
 */
void ScreenHandler::printUpdateFinished(void)
{
  mLCDDriver->updateFirmwareUpdateFinished();
}

/**
 * @brief Print the update error message on the screen
 * 
 * @param e String of the error
 */
void ScreenHandler::printUpdateError(String e)
{
  mLCDDriver->updateFirmwareUpdateError(e);
}

/**
 * @brief Reset the screen (screen is completely black)
 * 
 */
void ScreenHandler::resetScreen(void)
{
  mLCDDriver->resetScreen();
}