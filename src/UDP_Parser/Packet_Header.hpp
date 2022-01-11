#ifndef PACKET_HEADER_HPP
#define PACKET_HEADER_HPP

#include <c_types.h>

#define PACKET_HEADER_SIZE 24

#pragma pack(push, 1)
struct PacketHeader
{
    uint16    m_packetFormat;            // 2021
    uint8     m_gameMajorVersion;        // Game major version - "X.00"
    uint8     m_gameMinorVersion;        // Game minor version - "1.XX"
    uint8     m_packetVersion;           // Version of this packet type, all start from 1
    uint8     m_packetId;                // Identifier for the packet type, see below
    uint64    m_sessionUID;              // Unique identifier for the session
    float     m_sessionTime;             // Session timestamp
    uint32    m_frameIdentifier;         // Identifier for the frame the data was retrieved on
    uint8     m_playerCarIndex;          // Index of player's car in the array
    uint8     m_secondaryPlayerCarIndex; // Index of secondary player's car in the array (splitscreen)
                                         // 255 if no second player
};

enum PacketID
{
    PACKET_ID_MOTION = 0,
    PACKET_ID_SESSION,
    PACKET_ID_LAP_DATA,
    PACKET_ID_EVENT,
    PACKET_ID_PARTICIPANTS,
    PACKET_ID_CAR_SETUPS,
    PACKET_ID_CAR_TELEMETRY,
    PACKET_ID_CAR_STATUS,
    PACKET_ID_FINAL_CLASSIFICATION,
    PACKET_ID_LOBBY_INFO,
    PACKET_ID_CAR_DAMAGE,
    PACKET_ID_SESSION_HISTORY
};
#pragma pack(pop)

#endif