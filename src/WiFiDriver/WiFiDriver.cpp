#include "WiFiDriver.hpp"

WiFiDriver::WiFiDriver(void)
{
  WiFi.begin(ssid, password);
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
  mUDPPacketSize = mUDP.parsePacket();

  if(0 < mUDPPacketSize)
  {
    mUDP.read(mUDPPacketBuffer, mUDPPacketSize);
    mIsDataAvailable = true;
  }

  return mIsDataAvailable;
}

uint16_t WiFiDriver::getPacketSize(void)
{
  return mUDPPacketSize;
}

void WiFiDriver::getPacketData(char* pPacketData)
{
  memcpy(pPacketData, mUDPPacketBuffer, mUDPPacketSize);
}