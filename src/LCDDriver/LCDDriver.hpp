#ifndef LCDDRIVER_HPP
#define LCDDRIVER_HPP

#include "Adafruit_ILI9341.h"
#include "Global_Information.hpp"

#define TYRE_SCREEN_WIDTH 75
#define TYRE_SCREEN_HEIGHT 100
#define TYRE_TYPE_THICKNESS 5
#define TYRE_TYPE_SCREEN_WIDTH (TYRE_SCREEN_WIDTH + (2 * TYRE_TYPE_THICKNESS))
#define TYRE_TYPE_SCREEN_HEIGHT (TYRE_SCREEN_HEIGHT + (2 * TYRE_TYPE_THICKNESS))
#define TYRE_SCREEN_X_OFFSET (TYRE_TYPE_THICKNESS)
#define TYRE_SCREEN_Y_OFFSET (TYRE_TYPE_THICKNESS)
#define TYRE_WEAR_THICKNESS 12

/**
 * @class LCDDriver
 * @brief Manage the LCD by drawing and writing information on the screen
 * 
 */
class LCDDriver
{
private:
  // Internal variable
  Adafruit_ILI9341 *tft;
  // Prototypes
  void setTextSize(uint8_t size);
  uint16_t getStringWidthOnScreen(String s);
  uint16_t getStringHeightOnScreen(String s);
  void resetScreenPart(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h);
  void displayWelcomeTitle(void);
  static uint16_t convertRGB24toRGB565(uint8_t r, uint8_t g, uint8_t b);

public:
  // Constructor
  LCDDriver(void);
  ~LCDDriver();
  // Prototypes
  void updateLapNumber(uint16_t currentLap, uint16_t totalLap);
  void updateTyreType(uint8_t tyreType);
  void updateTyreWear(uint8_t rearLeft, uint8_t rearRight, uint8_t frontLeft, uint8_t frontRight);
  void updateGearEngaged(int8_t gear);
  void updatePosition(uint8_t position, uint8_t nbDriver);
  void resetScreen(void);
  void updateFirmwareUpdateProgress(uint8_t percentage);
  void updateFirmwareUpdateFinished(void);
  void updateFirmwareUpdateError(String e);
  void updateBatterySOC(uint8_t soc);
};

#endif