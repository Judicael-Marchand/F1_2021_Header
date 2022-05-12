#include "ScreenHandler.hpp"

ScreenHandler::ScreenHandler(void)
{
  mTelemetryMessages = new Telemetry_Messages();
  mLCDDriver = new LCDDriver();
  mBatteryDriver = new BatteryDriver();
}

ScreenHandler::~ScreenHandler()
{

}

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

void ScreenHandler::printUpdateProgress(uint8_t percentage)
{
  mLCDDriver->updateFirmwareUpdateProgress(percentage);
}

void ScreenHandler::printUpdateFinished(void)
{
  mLCDDriver->updateFirmwareUpdateFinished();
}

void ScreenHandler::printUpdateError(String e)
{
  mLCDDriver->updateFirmwareUpdateError(e);
}

void ScreenHandler::resetScreen(void)
{
  mLCDDriver->resetScreen();
}