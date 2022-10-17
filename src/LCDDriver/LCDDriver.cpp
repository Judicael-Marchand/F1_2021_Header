#include "LCDDriver.hpp"

// Define LCD pins
#define TFT_DC 2
#define TFT_CS 4
#define TFT_RST 0 // TFT RST pin is connected to NodeMCU pin D3 = GPIO 0

/**
 * @brief Construct a new LCDDriver::LCDDriver object
 * @details Init and print a welcome message before resetting the screen
 * 
 */
LCDDriver::LCDDriver(void)
{
  // Init LCD instance
  tft = new Adafruit_ILI9341(TFT_CS, TFT_DC);
  // Init LCD
  tft->begin();
  tft->setRotation(3); // Landscape position
  tft->fillScreen(ILI9341_BLACK);
  tft->setTextColor(ILI9341_WHITE);
  this->setTextSize(2);
  tft->setSPISpeed(40000000); // Tried setting up new SPI speed for faster refreshing but doesn't seem to work. Guess I'm on the limit of the chip
  // Display welcome message
  displayWelcomeTitle();
}

/**
 * @brief Destroy the LCDDriver::LCDDriver object
 * 
 */
LCDDriver::~LCDDriver()
{
  delete tft;
}

/**
 * @brief Update the current and the total lap numbers on the screen
 * 
 * @param currentLap Current lap number
 * @param totalLap Total lap number
 */
void LCDDriver::updateLapNumber(uint16_t currentLap, uint16_t totalLap)
{
  String buffer = "Lap : " + String(currentLap) + "/" + String(totalLap);
  String resetBuffer = "Lap : 00/000"; // Reset buffer is the maximum string size possible (000/000 because of free practice number of laps (200))

  tft->setTextColor(ILI9341_WHITE);
  this->setTextSize(2);

  resetScreenPart((tft->width() - getStringWidthOnScreen(resetBuffer)) / 2, 0, getStringWidthOnScreen(resetBuffer), getStringHeightOnScreen(resetBuffer));

  tft->setCursor((tft->width() - getStringWidthOnScreen(buffer)) / 2, 0);
  tft->print(buffer);
}

/**
 * @brief Update the tyre type (Soft, Medium, Hard, Inter, Wet)
 * 
 * @param tyreType Tyre type to show
 */
void LCDDriver::updateTyreType(uint8_t tyreType)
{
  uint16_t colorTyre = 0;
  uint8_t i = 0;

  switch (tyreType)
  {
  case SOFT_TYRE: // Soft
    colorTyre = convertRGB24toRGB565(255, 0, 0);  // Red
    break;

  case MEDIUM_TYRE: //Medium
    colorTyre = convertRGB24toRGB565(255, 255, 0);  // Yellow
    break;

  case HARD_TYRE: // Hard
    colorTyre = convertRGB24toRGB565(255, 255, 255);  // White
    break;

  case INTER_TYRE: // Inter
    colorTyre = convertRGB24toRGB565(0, 255, 0);  // Green
    break;

  case WET_TYRE: //Wet
    colorTyre = convertRGB24toRGB565(0, 0, 255);  // Blue
    break;
  }

  // Multiple nested rectangles because the rectangle thickness couldn't be changed
  for (i = 0; i < TYRE_TYPE_THICKNESS; i++)
  {
    tft->drawRect(TYRE_SCREEN_X_OFFSET - TYRE_TYPE_THICKNESS + i, tft->height() - TYRE_SCREEN_HEIGHT - TYRE_SCREEN_Y_OFFSET - TYRE_TYPE_THICKNESS + i, TYRE_TYPE_SCREEN_WIDTH - 2 * i, TYRE_TYPE_SCREEN_HEIGHT - 2 * i, colorTyre);
    tft->drawRect(tft->width() - TYRE_SCREEN_WIDTH - TYRE_TYPE_THICKNESS - TYRE_SCREEN_X_OFFSET + i, tft->height() - TYRE_SCREEN_HEIGHT - TYRE_TYPE_THICKNESS - TYRE_SCREEN_Y_OFFSET + i, TYRE_TYPE_SCREEN_WIDTH - 2 * i, TYRE_TYPE_SCREEN_HEIGHT - 2 * i, colorTyre);
    tft->drawRect(TYRE_SCREEN_X_OFFSET - TYRE_TYPE_THICKNESS + i, TYRE_SCREEN_Y_OFFSET - TYRE_TYPE_THICKNESS + i, TYRE_TYPE_SCREEN_WIDTH - 2 * i, TYRE_TYPE_SCREEN_HEIGHT - 2 * i, colorTyre);
    tft->drawRect(tft->width() - TYRE_SCREEN_WIDTH - TYRE_TYPE_THICKNESS - TYRE_SCREEN_X_OFFSET + i, TYRE_SCREEN_Y_OFFSET - TYRE_TYPE_THICKNESS + i, TYRE_TYPE_SCREEN_WIDTH - 2 * i, TYRE_TYPE_SCREEN_HEIGHT - 2 * i, colorTyre);
  }
}

/**
 * @brief Update tyre wear both by drawing colored rectangles and by writing it on the screen
 * 
 * @param rearLeft Tyre wear of the rear left wheel (0% - 100%)
 * @param rearRight Tyre wear of the rear right wheel (0% - 100%)
 * @param frontLeft Tyre wear of the front left wheel (0% - 100%)
 * @param frontRight Tyre wear of the front right wheel (0% - 100%)
 */
void LCDDriver::updateTyreWear(uint8_t rearLeft, uint8_t rearRight, uint8_t frontLeft, uint8_t frontRight)
{
  uint8_t i = 0;

  String resetBuffer = "100%"; // Reset buffer is the maximum string size possible

  String rearLeftText = String(rearLeft) + "%";
  String rearRightText = String(rearRight) + "%";
  String frontLeftText = String(frontLeft) + "%";
  String frontRightText = String(frontRight) + "%";

  // Calcul color of the tyre by reading the tyre wear (mapped from 0% to 50%)
  // Red color : tyre wear 
  // Green color : 100% - tyre wear
  // Blue color : always 0 because don't need
  uint16_t rearLeftColor = convertRGB24toRGB565((rearLeft > 50) ? 255 : map(rearLeft, 0, 50, 0, 255), (rearLeft > 50) ? 0 : map(100 - rearLeft, 0, 50, 0, 255), 0);
  uint16_t rearRightColor = convertRGB24toRGB565((rearRight > 50) ? 255 : map(rearRight, 0, 50, 0, 255), (rearRight > 50) ? 0 : map(100 - rearRight, 0, 50, 0, 255), 0);
  uint16_t frontLeftColor = convertRGB24toRGB565((frontLeft > 50) ? 255 : map(frontLeft, 0, 50, 0, 255), (frontLeft > 50) ? 0 : map(100 - frontLeft, 0, 50, 0, 255), 0);
  uint16_t frontRightColor = convertRGB24toRGB565((frontRight > 50) ? 255 : map(frontRight, 0, 50, 0, 255), (frontRight > 50) ? 0 : map(100 - frontRight, 0, 50, 0, 255), 0);

  // Multiple nested rectangles because the rectangle thickness couldn't be changed
  for (i = 0; i < TYRE_WEAR_THICKNESS; i++)
  {
    tft->drawRect(TYRE_SCREEN_X_OFFSET + i, tft->height() - TYRE_SCREEN_HEIGHT - TYRE_SCREEN_Y_OFFSET + i, TYRE_SCREEN_WIDTH - 2 * i, TYRE_SCREEN_HEIGHT - 2 * i, rearLeftColor);
    tft->drawRect(tft->width() - TYRE_SCREEN_WIDTH - TYRE_SCREEN_X_OFFSET + i, tft->height() - TYRE_SCREEN_HEIGHT - TYRE_SCREEN_Y_OFFSET + i, TYRE_SCREEN_WIDTH - 2 * i, TYRE_SCREEN_HEIGHT - 2 * i, rearRightColor);
    tft->drawRect(TYRE_SCREEN_X_OFFSET + i, TYRE_SCREEN_Y_OFFSET + i, TYRE_SCREEN_WIDTH - 2 * i, TYRE_SCREEN_HEIGHT - 2 * i, frontLeftColor);
    tft->drawRect(tft->width() - TYRE_SCREEN_WIDTH - TYRE_SCREEN_X_OFFSET + i, TYRE_SCREEN_Y_OFFSET + i, TYRE_SCREEN_WIDTH - 2 * i, TYRE_SCREEN_HEIGHT - 2 * i, frontRightColor);
  }

  // Print the percentage tyre wear over the tyre wear rectangles
  tft->setTextColor(ILI9341_WHITE);
  this->setTextSize(2);
  
  // Rear left
  resetScreenPart(TYRE_SCREEN_X_OFFSET + (TYRE_SCREEN_WIDTH - getStringWidthOnScreen(resetBuffer)) / 2, tft->height() - ((TYRE_SCREEN_HEIGHT + getStringHeightOnScreen(resetBuffer)) / 2) - TYRE_SCREEN_Y_OFFSET, getStringWidthOnScreen(resetBuffer), getStringHeightOnScreen(resetBuffer));
  tft->setCursor(TYRE_SCREEN_X_OFFSET + (TYRE_SCREEN_WIDTH - getStringWidthOnScreen(rearLeftText)) / 2, tft->height() - ((TYRE_SCREEN_HEIGHT + getStringHeightOnScreen(rearLeftText)) / 2) - TYRE_SCREEN_Y_OFFSET);
  tft->print(rearLeftText);
  // Rear right
  resetScreenPart(tft->width() - ((TYRE_SCREEN_WIDTH + getStringWidthOnScreen(resetBuffer)) / 2) - TYRE_SCREEN_X_OFFSET, tft->height() - ((TYRE_SCREEN_HEIGHT + getStringHeightOnScreen(resetBuffer)) / 2) - TYRE_SCREEN_Y_OFFSET, getStringWidthOnScreen(resetBuffer), getStringHeightOnScreen(resetBuffer));
  tft->setCursor(tft->width() - ((TYRE_SCREEN_WIDTH + getStringWidthOnScreen(rearRightText)) / 2) - TYRE_SCREEN_X_OFFSET, tft->height() - ((TYRE_SCREEN_HEIGHT + getStringHeightOnScreen(rearRightText)) / 2) - TYRE_SCREEN_Y_OFFSET);
  tft->print(rearRightText);
  // Front left
  resetScreenPart(TYRE_SCREEN_X_OFFSET + (TYRE_SCREEN_WIDTH - getStringWidthOnScreen(resetBuffer)) / 2, TYRE_SCREEN_Y_OFFSET + (TYRE_SCREEN_HEIGHT - getStringHeightOnScreen(resetBuffer)) / 2, getStringWidthOnScreen(resetBuffer), getStringHeightOnScreen(resetBuffer));
  tft->setCursor(TYRE_SCREEN_X_OFFSET + (TYRE_SCREEN_WIDTH - getStringWidthOnScreen(frontLeftText)) / 2, TYRE_SCREEN_Y_OFFSET + (TYRE_SCREEN_HEIGHT - getStringHeightOnScreen(frontLeftText)) / 2);
  tft->print(frontLeftText);
  // Front right
  resetScreenPart(tft->width() - ((TYRE_SCREEN_WIDTH + getStringWidthOnScreen(resetBuffer)) / 2) - TYRE_SCREEN_X_OFFSET, TYRE_SCREEN_Y_OFFSET + (TYRE_SCREEN_HEIGHT - getStringHeightOnScreen(resetBuffer)) / 2, getStringWidthOnScreen(resetBuffer), getStringHeightOnScreen(resetBuffer));
  tft->setCursor(tft->width() - ((TYRE_SCREEN_WIDTH + getStringWidthOnScreen(frontRightText)) / 2) - TYRE_SCREEN_X_OFFSET, TYRE_SCREEN_Y_OFFSET + (TYRE_SCREEN_HEIGHT - getStringHeightOnScreen(frontRightText)) / 2);
  tft->print(frontRightText);
}

/**
 * @brief Update the gear engaged information
 * 
 * @param gear Gear engaged (-1 is rear, 0 is neutral, 1..8 are front gears)
 */
void LCDDriver::updateGearEngaged(int8_t gear)
{
  String buffer = String(gear);
  String resetBuffer = "-1"; // resetBuffer is -1 because it is the largest string possible (rear gear)

  tft->setTextColor(ILI9341_WHITE);
  this->setTextSize(10);

  // Reset the screen part of the gear engaged
  resetScreenPart((tft->width() - getStringWidthOnScreen(resetBuffer)) / 2, (tft->height() - getStringHeightOnScreen(resetBuffer)) / 2, getStringWidthOnScreen(resetBuffer), getStringHeightOnScreen(resetBuffer));

  // Print the new gear engaged
  tft->setCursor((tft->width() - getStringWidthOnScreen(buffer)) / 2, (tft->height() - getStringHeightOnScreen(buffer)) / 2);
  tft->print(buffer);
}

/**
 * @brief Update the position of the player
 * 
 * @param position Position of the player on the grid
 * @param nbDriver Total number of drivers on the grid
 */
void LCDDriver::updatePosition(uint8_t position, uint8_t nbDriver)
{
  String buffer = "Pos : " + String(position) + "/" + String(nbDriver);
  String resetBuffer = "Pos : 00/00"; // Reset buffer is the maximum string size possible

  tft->setTextColor(ILI9341_WHITE);
  this->setTextSize(2);

  // Reset the screen part of the position
  resetScreenPart((tft->width() - getStringWidthOnScreen(resetBuffer)) / 2, tft->height() - getStringHeightOnScreen(resetBuffer), getStringWidthOnScreen(resetBuffer), getStringHeightOnScreen(resetBuffer));

  // Print the new position
  tft->setCursor((tft->width() - getStringWidthOnScreen(buffer)) / 2, tft->height() - getStringHeightOnScreen(buffer));
  tft->print(buffer);
}

/**
 * @brief Display a welcome message during the boot of the system
 * 
 */
void LCDDriver::displayWelcomeTitle(void)
{
  String welcomeMessage = "Welcome <3";

  // Print welcome message
  tft->setCursor((tft->width() - getStringWidthOnScreen(welcomeMessage)) / 2, (tft->height() - getStringHeightOnScreen(welcomeMessage)) / 2);
  tft->print(welcomeMessage);

  // Wait a bit for displaying message
  delay(1000);

  // Reset screen to begin the session from scratch
  resetScreen();
}

/**
 * @brief Set text size
 * 
 * @param size Size of the text
 */
void LCDDriver::setTextSize(uint8_t size)
{
  tft->setTextSize(size);
}

/**
 * @brief Reset the screen (black)
 * 
 */
void LCDDriver::resetScreen(void)
{
  tft->fillScreen(ILI9341_BLACK);
}

/**
 * @brief Reset a part of the screen (black)
 * 
 * @param x0 Origin on the X-grid
 * @param y0 Origin on the Y-grid
 * @param w Width of the part to reset
 * @param h Height of the part to reset
 */
void LCDDriver::resetScreenPart(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h)
{
  tft->fillRect(x0, y0, w, h, ILI9341_BLACK);
}

/**
 * @brief Get the width of a given string on the screen
 * 
 * @param s String to measure
 * @return  Width of the given string
 */
uint16_t LCDDriver::getStringWidthOnScreen(String s)
{
  uint16_t stringWidth = 0;
  int16_t x1 = 0;
  int16_t y1 = 0;
  uint16_t stringHeight = 0;

  // Get the string width on screen
  tft->getTextBounds(s, 0, 0, &x1, &y1, &stringWidth, &stringHeight);

  return stringWidth;
}

/**
 * @brief Get the height of a given string on the screen
 * 
 * @param s String to measure
 * @return  Height of the given string
 */
uint16_t LCDDriver::getStringHeightOnScreen(String s)
{
  uint16_t stringWidth = 0;
  int16_t x1 = 0;
  int16_t y1 = 0;
  uint16_t stringHeight = 0;

  // Get the string height on screen
  tft->getTextBounds(s, 0, 0, &x1, &y1, &stringWidth, &stringHeight);

  return stringHeight;
}

/**
 * @brief Convert a color from a RGB888 system to a RGB565 system
 * 
 * @param r Red color on 8 bits
 * @param g Green color on 8 bits
 * @param b Blue color on 8 bits
 * @return  Color on 16 bits following the RGB565 system
 */
uint16_t LCDDriver::convertRGB24toRGB565(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r / 8) << 11) | ((g / 4) << 5) | (b / 8);
}

/**
 * @brief Update the firmware update progess on the screen
 * 
 * @param percentage Percentage of the update progress
 */
void LCDDriver::updateFirmwareUpdateProgress(uint8_t percentage)
{
  String buffer = "Updating : " + String(percentage) + "%";
  String resetBuffer = "Updating : 100%";

  tft->setTextColor(ILI9341_WHITE);
  this->setTextSize(2);

  // Reset the screen part of the percentage
  resetScreenPart((tft->width() - getStringWidthOnScreen(resetBuffer)) / 2, (tft->height() - getStringHeightOnScreen(resetBuffer)) / 2, getStringWidthOnScreen(resetBuffer), getStringHeightOnScreen(resetBuffer));

  // Print update percentage
  tft->setCursor((tft->width() - getStringWidthOnScreen(buffer)) / 2, (tft->height() - getStringHeightOnScreen(buffer)) / 2);
  tft->print(buffer);
}

/**
 * @brief Write a message on the screen to tell the user that the update is finished
 * 
 */
void LCDDriver::updateFirmwareUpdateFinished(void)
{
  String buffer = "Update finished, restarting...";

  tft->setTextColor(ILI9341_WHITE);
  this->setTextSize(2);

  // Print finished message
  tft->setCursor((tft->width() - getStringWidthOnScreen(buffer)) / 2, (tft->height() - getStringHeightOnScreen(buffer)) / 2);
  tft->print(buffer);
}

/**
 * @brief Write an error message on the screen to tell the user that an error occured during the update
 * 
 * @param e String error of the update
 */
void LCDDriver::updateFirmwareUpdateError(String e)
{
  String buffer = "Update error : " + e;

  tft->setTextColor(ILI9341_WHITE);
  this->setTextSize(2);

  // Print error message
  tft->setCursor((tft->width() - getStringWidthOnScreen(buffer)) / 2, (tft->height() - getStringHeightOnScreen(buffer)) / 2);
  tft->print(buffer);  
}

/**
 * @brief Write the battery SOC on the screen
 * 
 * @param soc SOC of the battery (0% - 100%)
 */
void LCDDriver::updateBatterySOC(uint8_t soc)
{
  String buffer = "Battery SOC : " + String(soc) + "%";
  String resetBuffer = "Battery SOC : 100%";

  tft->setTextColor(ILI9341_WHITE);
  this->setTextSize(1);

  // Reset the screen part of the percentage
  resetScreenPart((tft->width() - getStringWidthOnScreen(resetBuffer)) / 2, getStringHeightOnScreen(resetBuffer) / 2 + 20, getStringWidthOnScreen(resetBuffer), getStringHeightOnScreen(resetBuffer));

  // Print update percentage
  tft->setCursor((tft->width() - getStringWidthOnScreen(buffer)) / 2, getStringHeightOnScreen(buffer) / 2 + 20);
  tft->print(buffer);
}