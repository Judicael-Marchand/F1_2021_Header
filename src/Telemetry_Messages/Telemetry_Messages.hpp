#ifndef TELEMETRY_MESSAGES_HPP
#define TELEMETRY_MESSAGES_HPP

#include <c_types.h>
#include "UDP_Parser.hpp"

#pragma pack(push, 1)
struct SessionInformation
{
    uint8_t m_totalLaps;
    uint8_t m_sessionType;
    uint8_t m_carPosition;
    uint8_t m_currentLapNum;
    uint8_t m_finalPosition;
};

struct TyreWear
{
    float m_rearLeft;
    float m_rearRight;
    float m_frontLeft;
    float m_frontRight; 
};

struct CarInformation
{
    TyreWear m_TyreWear;
};

enum MessageID
{
    NO_MESSAGE_ID = 0,
    SESSION_MESSAGE_ID,
    CAR_MESSAGE_ID
};

#pragma pack(pop)

class Telemetry_Messages
{
    private:
    // Internal variables
    UDP_Parser *mUDPParser;
    enum MessageID mMessageID;

    public:
    SessionInformation mSessionInformation;
    CarInformation mCarInformation;
    Telemetry_Messages(void);
    ~Telemetry_Messages(void);
    boolean checkRawDataAvailibility(void);
    void storeAvailableData(void);
    enum MessageID getMessageID(void);
    void setMessageID(enum MessageID messageID);
    void execute(void);
};

#endif