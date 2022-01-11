#ifndef MOTORCONTROLL_HPP
#define MOTORCONTROL_HPP

#include <Arduino.h>
#include <string.h>
#if defined(ESP32)
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <WiFiUdp.h>
#include "LogDriver.hpp"
#include "WiFi_Info.hpp"

class WiFiDriver {
  private:
  // Constant
  static const uint16_t MAX_UDP_PACKET_LENGTH = 1464;
  static const uint16_t UDP_PORT = 20777;
  // Wifi Info
  inline static const String ssid = WIFI_SSID;
  inline static const String password = WIFI_PASSWORD;
  // Internal variables
  uint8_t mUDPPacketBuffer[MAX_UDP_PACKET_LENGTH];
  uint16_t mUDPPacketSize;
  WiFiUDP mUDP;
  boolean mIsDataAvailable;

  public:
  // Constructor
  WiFiDriver(void);
  ~WiFiDriver(void);
  // Prototypes
  boolean checkDataAvailibility(void);
  uint16_t getPacketSize(void);
  void getPacketData(uint8_t *pPacketData);
  void getPacketData(uint8_t *pPacketData, uint16_t size);
};

#endif