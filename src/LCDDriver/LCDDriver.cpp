#include "LCDDriver.hpp"

// Define LCD pins
#define TFT_DC 2
#define TFT_CS 4
#define TFT_RST 0 // TFT RST pin is connected to NodeMCU pin D3 = GPIO 0

LCDDriver::LCDDriver(void)
{
  // Init LCD instance
  tft = new Adafruit_ILI9341(TFT_CS, TFT_DC);
  // Init LCD
  tft->begin();
  tft->setRotation(1); // Landscape position
  tft->fillScreen(ILI9341_BLACK);
  tft->setTextColor(ILI9341_WHITE);
  this->setTextSize(2);
  tft->setSPISpeed(40000000); // Tried setting up new SPI speed for faster refreshing but doesn't seem to work. Guess I'm on the limit of the chip
  // Display welcome message
  displayWelcomeTitle();
}

LCDDriver::~LCDDriver()
{
}

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

// TODO : Redo the tyreType decoding
void LCDDriver::updateTyreType(uint8_t tyreType)
{
  uint16_t colorTyre = 0;
  uint8_t i = 0;

  switch (tyreType)
  {
  case SOFT_TYRE: // Soft
    colorTyre = convertRGB24toRGB565(255, 0, 0);
    break;

  case MEDIUM_TYRE: //Medium
    colorTyre = convertRGB24toRGB565(255, 255, 0);
    break;

  case HARD_TYRE: // Hard
    colorTyre = convertRGB24toRGB565(255, 255, 255);
    break;

  case INTER_TYRE: // Inter
    colorTyre = convertRGB24toRGB565(0, 255, 0);
    break;

  case WET_TYRE: //Wet
    colorTyre = convertRGB24toRGB565(0, 0, 255);
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

void LCDDriver::updateTyreWear(uint8_t rearLeft, uint8_t rearRight, uint8_t frontLeft, uint8_t frontRight)
{
  String rearLeftText = String(rearLeft) + "%";
  String rearRightText = String(rearRight) + "%";
  String frontLeftText = String(frontLeft) + "%";
  String frontRightText = String(frontRight) + "%";

  // Calcul color of the tyre by reading the tyre wear
  // Red color : tyre wear
  // Green color : 100% - tyre wear
  // Blue color : always 0 because don't need
  uint16_t rearLeftColor = convertRGB24toRGB565(map(rearLeft, 0, 100, 0, 255), map(100 - rearLeft, 0, 100, 0, 255), 0);
  uint16_t rearRightColor = convertRGB24toRGB565(map(rearRight, 0, 100, 0, 255), map(100 - rearRight, 0, 100, 0, 255), 0);
  uint16_t frontLeftColor = convertRGB24toRGB565(map(frontLeft, 0, 100, 0, 255), map(100 - frontLeft, 0, 100, 0, 255), 0);
  uint16_t frontRightColor = convertRGB24toRGB565(map(frontRight, 0, 100, 0, 255), map(100 - frontRight, 0, 100, 0, 255), 0);

  // Draw the tyre wear rectangle
  tft->fillRect(TYRE_SCREEN_X_OFFSET, tft->height() - TYRE_SCREEN_HEIGHT - TYRE_SCREEN_Y_OFFSET, TYRE_SCREEN_WIDTH, TYRE_SCREEN_HEIGHT, rearLeftColor);
  tft->fillRect(tft->width() - (TYRE_SCREEN_WIDTH + TYRE_SCREEN_X_OFFSET), tft->height() - TYRE_SCREEN_HEIGHT - TYRE_SCREEN_Y_OFFSET, TYRE_SCREEN_WIDTH, TYRE_SCREEN_HEIGHT, rearRightColor);
  tft->fillRect(TYRE_SCREEN_X_OFFSET, TYRE_SCREEN_Y_OFFSET, TYRE_SCREEN_WIDTH, TYRE_SCREEN_HEIGHT, frontLeftColor);
  tft->fillRect(tft->width() - (TYRE_SCREEN_WIDTH + TYRE_SCREEN_X_OFFSET), TYRE_SCREEN_Y_OFFSET, TYRE_SCREEN_WIDTH, TYRE_SCREEN_HEIGHT, frontRightColor);

  // Print the percentage tyre wear over the tyre wear rectangles
  tft->setTextColor(ILI9341_BLACK);
  this->setTextSize(2);
  tft->setCursor(TYRE_SCREEN_X_OFFSET + (TYRE_SCREEN_WIDTH - getStringWidthOnScreen(rearLeftText)) / 2, tft->height() - ((TYRE_SCREEN_HEIGHT + getStringHeightOnScreen(rearLeftText)) / 2) - TYRE_SCREEN_Y_OFFSET);
  tft->print(rearLeftText);
  tft->setCursor(tft->width() - ((TYRE_SCREEN_WIDTH + getStringWidthOnScreen(rearRightText)) / 2) - TYRE_SCREEN_X_OFFSET, tft->height() - ((TYRE_SCREEN_HEIGHT + getStringHeightOnScreen(rearRightText)) / 2) - TYRE_SCREEN_Y_OFFSET);
  tft->print(rearRightText);
  tft->setCursor(TYRE_SCREEN_X_OFFSET + (TYRE_SCREEN_WIDTH - getStringWidthOnScreen(frontLeftText)) / 2, TYRE_SCREEN_Y_OFFSET + (TYRE_SCREEN_HEIGHT - getStringHeightOnScreen(frontLeftText)) / 2);
  tft->print(frontLeftText);
  tft->setCursor(tft->width() - ((TYRE_SCREEN_WIDTH + getStringWidthOnScreen(frontRightText)) / 2) - TYRE_SCREEN_X_OFFSET, TYRE_SCREEN_Y_OFFSET + (TYRE_SCREEN_HEIGHT - getStringHeightOnScreen(frontRightText)) / 2);
  tft->print(frontRightText);
}

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

void LCDDriver::setTextSize(uint8_t size)
{
  tft->setTextSize(size);
}

void LCDDriver::resetScreen(void)
{
  tft->fillScreen(ILI9341_BLACK);
}

void LCDDriver::resetScreenPart(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h)
{
  tft->fillRect(x0, y0, w, h, ILI9341_BLACK);
}

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

uint16_t LCDDriver::convertRGB24toRGB565(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r / 8) << 11) | ((g / 4) << 5) | (b / 8);
}

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

void LCDDriver::updateFirmwareUpdateFinished(void)
{
  String buffer = "Update finished, restarting...";

  tft->setTextColor(ILI9341_WHITE);
  this->setTextSize(2);

  // Print finished message
  tft->setCursor((tft->width() - getStringWidthOnScreen(buffer)) / 2, (tft->height() - getStringHeightOnScreen(buffer)) / 2);
  tft->print(buffer);
}

void LCDDriver::updateFirmwareUpdateError(String e)
{
  String buffer = "Update error : " + e;

  tft->setTextColor(ILI9341_WHITE);
  this->setTextSize(2);

  // Print error message
  tft->setCursor((tft->width() - getStringWidthOnScreen(buffer)) / 2, (tft->height() - getStringHeightOnScreen(buffer)) / 2);
  tft->print(buffer);  
}