#ifndef UDP_PARSER_HPP
#define UDP_PARSER_HPP

#include "Car_Damage_Packet.hpp"
#include "Car_Setup_Packet.hpp"
#include "Car_Status_Packet.hpp"
#include "Car_Telemetry_Packet.hpp"
#include "Event_Packet.hpp"
#include "Final_Classification_Packet.hpp"
#include "Lap_Data_Packet.hpp"
#include "Lobby_Info_Packet.hpp"
#include "Motion_Packet.hpp"
#include "Packet_Header.hpp"
#include "Participants_Packet.hpp"
#include "Session_History_Packet.hpp"
#include "Session_Packet.hpp"
#include "General_Packet_Information.hpp"
#include "LogDriver.hpp"
#include "WiFiDriver.hpp"

/**
 * @class UDP_Parser
 * @brief Take the UDP raw packets from the WiFi system and converts them into the packet structures defined by the game
 * 
 */
class UDP_Parser
{
    private:
    static const uint16_t MAX_UDP_PACKET_LENGTH = MOTION_PACKET_SIZE; // Motion packet is the bigger packet possible
    WiFiDriver *mWiFiDriver;
    boolean mIsDataAvailable;
    uint8_t mUDPRawPacketData[MAX_UDP_PACKET_LENGTH];
    enum PacketID mPacketID;
    uint8_t mPlayerCarIndex;

    public:
    UDP_Parser(void);
    ~UDP_Parser(void);
    boolean checkRawDataAvailibility(void);
    void decodeData(void);
    boolean checkDataAvailibility(void);
    void setDataAvailibility(boolean b);
    enum PacketID getPacketID(void);
    uint8_t getPlayerCarIndex(void);
    void execute(void);

    struct PacketHeader mPacketHeader;
    struct PacketMotionData mPacketMotionData;
    struct PacketSessionData mPacketSessionData;
    struct PacketLapData mPacketLapData;
    struct PacketEventData mPacketEventData;
    struct PacketParticipantsData mPacketParticipantsData;
    struct PacketCarSetupData mPacketCarSetupData;
    struct PacketCarTelemetryData mPacketCarTelemetryData;
    struct PacketCarStatusData mPacketCarStatusData;
    struct PacketFinalClassificationData mPacketFinalClassificationData;
    struct PacketLobbyInfoData mPacketLobbyInfoData;
    struct PacketCarDamageData mPacketCarDamageData;
    struct PacketSessionHistoryData mPacketSessionHistoryData;

};

#endif