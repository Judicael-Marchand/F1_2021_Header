#ifndef GLOBAL_INFORMATION_HPP
#define GLOBAL_INFORMATION_CPP

#include <c_types.h>

#pragma pack(push, 1)
struct SessionInformation
{
    uint8_t m_totalLaps;
    uint8_t m_sessionType;
    uint8_t m_carPosition;
    uint8_t m_currentLapNum;
    uint8_t m_finalPosition;
    uint8_t m_numActiveCars;
};

struct TyreWear
{
    float m_rearLeft;
    float m_rearRight;
    float m_frontLeft;
    float m_frontRight; 
};

enum TyreType
{
    INTER_TYRE = 7,
    WET_TYRE,
    SOFT_TYRE = 16,
    MEDIUM_TYRE,
    HARD_TYRE
};

struct CarInformation
{
    TyreWear m_TyreWear;
    TyreType m_currentTyreType;
    int8_t m_gear;
};

enum MessageID
{
    NO_MESSAGE_ID = 0,
    SESSION_MESSAGE_ID,
    CAR_MESSAGE_ID
};

#pragma pack(pop)

#endif