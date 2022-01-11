#include "WiFiDriver.hpp"

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

WiFiDriver::~WiFiDriver(void)
{

}

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

uint16_t WiFiDriver::getPacketSize(void)
{
  return mUDPPacketSize;
}

void WiFiDriver::getPacketData(uint8_t *pPacketData)
{
  memcpy(pPacketData, mUDPPacketBuffer, mUDPPacketSize);
  mIsDataAvailable = false;
}

void WiFiDriver::getPacketData(uint8_t *pPacketData, uint16_t size)
{
  memcpy(pPacketData, mUDPPacketBuffer, size);
  mIsDataAvailable = false;
}