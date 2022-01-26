#include "OTAHandler.hpp"

OTAHandler::OTAHandler(void)
{

}

OTAHandler::~OTAHandler(void)
{

}

void OTAHandler::init(void)
{
    // OTA
  ArduinoOTA.onStart([]()
                     {  
                       
                     });
  ArduinoOTA.onEnd([]()
                   {
                     Serial.println("Update complete, restarting...");
                   });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                        {
                          Serial.println("Updating...");
                          
                          int prog = (progress / (total / 100));
                          String str_progress;
                          str_progress += prog;
                          str_progress += (char)37;
                          Serial.println(str_progress);
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
                       
                       Serial.println("Update Error");
                       Serial.println(str_error);
                       delay(5000);
                       ESP.restart();
                     });
  ArduinoOTA.begin();
}

void OTAHandler::execute(void)
{
  ArduinoOTA.handle();
}