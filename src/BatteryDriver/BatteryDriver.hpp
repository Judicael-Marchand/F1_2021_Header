#ifndef BATTERYDRIVER_HPP
#define BATTERYDRIVER_HPP

#include "Arduino.h"

#define BATTERY_ADC_PIN A0
#define ADCValueToADCVoltage(adcValue) (adcValue * 1.0 / 1023.0)    // On the ESP8266 ADC, numeric value of 1023 is equaled to an input of 1V
#define ADCRawVoltageToADCInputVoltage(adcRawVoltage) (adcRawVoltage * (390.0 + 100.0) / 100.0)   // Voltage bridge divider with Re = 390komhs and Rs = 100kohms
#define BATTERY_LOW_CHARGE_VOLTAGE 3500
#define BATTERY_FULL_CHARGE_VOLTAGE 4200

/**
 * @class BatteryDriver
 * @brief This classes reads the voltage of the battery and calculs the SOC of the battery
 * 
 */
class BatteryDriver
{
private:
uint8_t mBatteryADCValue;
uint16_t mBatteryVoltageInmV;
uint8_t mBatterySOC;

public:
  BatteryDriver(void);
  ~BatteryDriver();
  void execute(void);
  uint16_t getBatteryVoltageInmV(void);
  uint8_t getBatterySOC(void);
};

#endif