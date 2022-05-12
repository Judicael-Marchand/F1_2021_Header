#include "OTAHandler.hpp"
#include "LogDriver.hpp"

/**
 * @brief Construct a new OTAHandler::OTAHandler object
 * 
 */
OTAHandler::OTAHandler(void)
{

}

/**
 * @brief Destroy the OTAHandler::OTAHandler object
 * 
 */
OTAHandler::~OTAHandler(void)
{

}

/**
 * @brief Init the OTA system. This is taken back from the ArduinoOTA documentation
 * @details LOGDriver and the ScreenHandler are used to inform the user of the advancement
 * 
 */
void OTAHandler::init(void)
{
    // OTA
  ArduinoOTA.onStart([]()
                     {  
                       LOGDriver::println("Update beginning : ");
                       mScreenHandler->resetScreen();
                     });
  ArduinoOTA.onEnd([]()
                   {
                     LOGDriver::println("Update complete, restarting...");
                     mScreenHandler->resetScreen();
                     mScreenHandler->printUpdateFinished();
                   });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                        {                          
                          uint8_t prog = (progress / (total / 100));

                          LOGDriver::println("Updating : " + String(prog) + "%");
                          mScreenHandler->printUpdateProgress(prog);
                        });
  ArduinoOTA.onError([](ota_error_t error)
                     {
                       String str_error;
                       if (error == OTA_AUTH_ERROR)
                         str_error = "Auth Failed";
                       else if (error == OTA_BEGIN_ERROR)
                         str_error = "Begin Failed";
                       else if (error == OTA_CONNECT_ERROR)
                         str_error = "Connect Failed";
                       else if (error == OTA_RECEIVE_ERROR)
                         str_error = "Receive Failed";
                       else if (error == OTA_END_ERROR)
                         str_error = "End Failed";
                       
                       LOGDriver::println("Update error : " + str_error);
                       mScreenHandler->resetScreen();
                       mScreenHandler->printUpdateError(str_error);
                       delay(5000);
                       ESP.restart();
                     });
  ArduinoOTA.begin();
}

/**
 * @brief Handle the ArduinoOTA system
 * 
 */
void OTAHandler::execute(void)
{
  ArduinoOTA.handle();
}