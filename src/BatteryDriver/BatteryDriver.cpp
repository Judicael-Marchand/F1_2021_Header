#include "BatteryDriver.hpp"

/**
 * @brief Construct a new Battery Driver:: Battery Driver object
 * 
 */
BatteryDriver::BatteryDriver(void)
{
    mBatteryADCValue = 0;
    mBatteryVoltageInmV = 0;
    mBatterySOC = 0;
}

BatteryDriver::~BatteryDriver(void)
{

}

/**
 * @brief Execute the BatteryDriver machine
 * 
 * @details The machine reads the ADC pin, converts it in the battery voltage and then, calculs the SOC of the battery
 * 
 */
void BatteryDriver::execute(void)
{
    mBatteryADCValue = analogRead(BATTERY_ADC_PIN);
    mBatteryVoltageInmV = ADCRawVoltageToADCInputVoltage(ADCValueToADCVoltage(mBatteryADCValue));
    mBatterySOC = map(mBatteryVoltageInmV, BATTERY_LOW_CHARGE_VOLTAGE, BATTERY_FULL_CHARGE_VOLTAGE, 0, 100);
}

/**
 * @brief Return the battery voltage in mV
 * 
 * @return Battery voltage in mV
 */
uint16_t BatteryDriver::getBatteryVoltageInmV(void)
{
    return mBatteryVoltageInmV;
}

/**
 * @brief Return the SOC of the battery. SOC is estimated linear in the used range of the battery
 * 
 * @return Battery SOC (0% - 100%)
 */

uint8_t BatteryDriver::getBatterySOC(void)
{
    return mBatterySOC;
}