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
    memset(mMeanBatteryADCValue, BATTERY_ADC_INVALID_VALUE_U16, sizeof(mMeanBatteryADCValue));
    mMeanBatteryADCIndex = 0;
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
    addBatteryADCValue(analogRead(BATTERY_ADC_PIN));
    mBatteryADCValue = getBatteryADCMean();
    mBatteryVoltageInmV = ADCRawVoltageToADCInputVoltage_mV(ADCValueToADCVoltage_mV(mBatteryADCValue));
    // Window the battery voltage
    if(BATTERY_FULL_CHARGE_VOLTAGE < mBatteryVoltageInmV)
    {
        mBatteryVoltageInmV = BATTERY_FULL_CHARGE_VOLTAGE;
    }
    else if(BATTERY_LOW_CHARGE_VOLTAGE > mBatteryVoltageInmV)
    {
        mBatteryVoltageInmV = BATTERY_LOW_CHARGE_VOLTAGE;
    }
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

/**
 * @brief Add ADC battery value to the data array to calculate the average value
 * 
 * @param value ADC value to add
 */
void BatteryDriver::addBatteryADCValue(uint16_t value)
{
    mMeanBatteryADCIndex = (mMeanBatteryADCIndex + 1) % NB_SAMPLE_BATTERY_AVERAGE;
    mMeanBatteryADCValue[mMeanBatteryADCIndex] = value;
}

/**
 * @brief Calculate and return the battery mean ADC measure
 * 
 * @return  The battery mean ADC measure
 */
uint16_t BatteryDriver::getBatteryADCMean(void)
{
    uint8_t i = 0;
    uint8_t currentIndex = mMeanBatteryADCIndex;
    uint8_t nbMeasure = 0;
    uint32_t meanValue = 0;

    do
    {
        if(BATTERY_ADC_INVALID_VALUE_U16 != mMeanBatteryADCValue[currentIndex]) // Check data validity
        {
            meanValue += mMeanBatteryADCValue[currentIndex];
            ++nbMeasure;
        }
        // else BATTERY_ADC_INVALID_VALUE_U16 == mMeanBatteryADCValue[currentIndex] --> Don't take invalid data

        // Check if we are at the origin of the array
        if(0 == currentIndex)
            currentIndex = NB_SAMPLE_BATTERY_AVERAGE - 1; // Reset the index to the end of the array

        ++i;

    } while (i < NB_SAMPLE_BATTERY_AVERAGE);
    
    if(0 != nbMeasure)
        meanValue /= nbMeasure;
    
    return meanValue;
}