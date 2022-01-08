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

class WiFiDriver {
  private:
  // Constant
  static const uint16_t MAX_UDP_PACKET_LENGTH = 1464;
  static const uint16_t UDP_PORT = 20777;
  // Wifi Info
  inline static const String ssid = "SSID";
  inline static const String password = "PASSWORD";
  // Internal variables
  char mUDPPacketBuffer[MAX_UDP_PACKET_LENGTH];
  uint16_t mUDPPacketSize;
  WiFiUDP mUDP;
  boolean mIsDataAvailable;

  // Constructor
  WiFiDriver(void);
  ~WiFiDriver(void);

  // Prototypes
  public:
  boolean checkDataAvailibility(void);
  uint16_t getPacketSize(void);
  void getPacketData(char* pPacketData);
};

#endif