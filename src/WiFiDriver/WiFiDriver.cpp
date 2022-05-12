#include "WiFiDriver.hpp"

/**
 * @brief Construct a new Wi Fi Driver:: Wi Fi Driver object
 * 
 */
WiFiDriver::WiFiDriver(void)
{
  WiFi.begin(ssid, password);
  LOGDriver::println("Connecting to hotspot");
  while(WiFi.status() != WL_CONNECTED)
  {
    LOGDriver::println("Waiting");
    delay(500);
  }

  mUDP.begin(UDP_PORT);
  LOGDriver::println("UDP Client IP Address : " + WiFi.localIP().toString());

  mIsDataAvailable = false;
  mUDPPacketSize = 0;
  memset(mUDPPacketBuffer, 0, MAX_UDP_PACKET_LENGTH);
}

/**
 * @brief Destroy the Wi Fi Driver:: Wi Fi Driver object
 * 
 */
WiFiDriver::~WiFiDriver(void)
{

}

/**
 * @brief Check if any new data is available from WiFi
 * 
 * @return  True of any data is available, False if no data is available
 */
boolean WiFiDriver::checkDataAvailibility(void)
{
  mUDPPacketSize = mUDP.parsePacket();  // parsePacket gives the number of bytes received

  if(0 < mUDPPacketSize)  // Check if a packet was received by checking the number of bytes read (0 = nothing received)
  {
    mUDP.read(mUDPPacketBuffer, mUDPPacketSize);  // Read the packet received and place it in the buffer
    mIsDataAvailable = true;  // Raise the flag
  }

  return mIsDataAvailable;
}

/**
 * @brief Get the packet size
 * 
 * @return  The packet size
 */
uint16_t WiFiDriver::getPacketSize(void)
{
  return mUDPPacketSize;
}

/**
 * @brief Get the packet data
 * 
 * @param pPacketData Pointer to the packet data to fill
 */
void WiFiDriver::getPacketData(uint8_t *pPacketData)
{
  memcpy(pPacketData, mUDPPacketBuffer, mUDPPacketSize);
  mIsDataAvailable = false;
}

/**
 * @brief Get the packet data with a given size
 * 
 * @param pPacketData Pointer to the packet data to fill
 * @param size Size of the wanted packet
 */
void WiFiDriver::getPacketData(uint8_t *pPacketData, uint16_t size)
{
  memcpy(pPacketData, mUDPPacketBuffer, size);
  mIsDataAvailable = false;
}