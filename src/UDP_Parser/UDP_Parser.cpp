#include "UDP_Parser.hpp"

UDP_Parser::UDP_Parser(void)
{
    // Init instances
    mWiFiDriver = new WiFiDriver();
    // Init internal variables
    mIsDataAvailable = false;
    memset(mUDPRawPacketData, 0, MAX_UDP_PACKET_LENGTH);
    mPacketID = PACKET_ID_MOTION;
    mPlayerCarIndex = 0;

    memset(&mPacketHeader, 0 , PACKET_HEADER_SIZE);
    memset(&mPacketMotionData, 0 , MOTION_PACKET_SIZE);
    memset(&mPacketSessionData, 0 , SESSION_PACKET_SIZE);
    memset(&mPacketLapData, 0 , LAP_DATA_PACKET_SIZE);
    memset(&mPacketEventData, 0 , EVENT_PACKET_SIZE);
    memset(&mPacketParticipantsData, 0 , PARTICIPANTS_PACKET_SIZE);
    memset(&mPacketCarSetupData, 0 , CAR_SETUP_PACKET_SIZE);
    memset(&mPacketCarTelemetryData, 0 , CAR_TELEMETRY_PACKET_SIZE);
    memset(&mPacketCarStatusData, 0 , CAR_STATUS_PACKET_SIZE);
    memset(&mPacketFinalClassificationData, 0 , FINAL_CLASSIFICATION_PACKET_SIZE);
    memset(&mPacketLobbyInfoData, 0 , LOBBY_INFO_PACKET_SIZE);
    memset(&mPacketCarDamageData, 0 , CAR_DAMAGE_PACKET_SIZE);
    memset(&mPacketSessionHistoryData, 0 , SESSION_HISTORY_PACKET_SIZE);
}

UDP_Parser::~UDP_Parser(void)
{

}

boolean UDP_Parser::checkRawDataAvailibility(void)
{
    return mWiFiDriver->checkDataAvailibility();
}

void UDP_Parser::decodeData(void)
{
    mWiFiDriver->getPacketData(mUDPRawPacketData, MAX_UDP_PACKET_LENGTH);   // Get the raw packet received from wifi
    memcpy(&mPacketHeader, mUDPRawPacketData, PACKET_HEADER_SIZE);  // Get only the header of the packet
    mPacketID = (enum PacketID)mPacketHeader.m_packetId;    // Check the packet ID to know which type of packet it is
    mPlayerCarIndex = mPacketHeader.m_playerCarIndex;   // Save the player car index to know the wanted array index in the data

    switch(mPacketID)   // Sort the information in the right structure as function of the packet ID received
    {
        case PACKET_ID_MOTION:
            memcpy(&mPacketMotionData, mUDPRawPacketData, MOTION_PACKET_SIZE);
        break;
        
        case PACKET_ID_SESSION:
            memcpy(&mPacketSessionData, mUDPRawPacketData, SESSION_PACKET_SIZE);
        break;

        case PACKET_ID_LAP_DATA:
            memcpy(&mPacketLapData, mUDPRawPacketData, LAP_DATA_PACKET_SIZE);
        break;

        case PACKET_ID_EVENT:
            memcpy(&mPacketEventData, mUDPRawPacketData, EVENT_PACKET_SIZE);
        break;

        case PACKET_ID_PARTICIPANTS:
            memcpy(&mPacketParticipantsData, mUDPRawPacketData, PARTICIPANTS_PACKET_SIZE);
        break;

        case PACKET_ID_CAR_SETUPS:
            memcpy(&mPacketCarSetupData, mUDPRawPacketData, CAR_SETUP_PACKET_SIZE);
        break;

        case PACKET_ID_CAR_TELEMETRY:
            memcpy(&mPacketCarTelemetryData, mUDPRawPacketData, CAR_TELEMETRY_PACKET_SIZE);
        break;

        case PACKET_ID_CAR_STATUS:
            memcpy(&mPacketCarStatusData, mUDPRawPacketData, CAR_STATUS_PACKET_SIZE);
        break;

        case PACKET_ID_FINAL_CLASSIFICATION:
            memcpy(&mPacketFinalClassificationData, mUDPRawPacketData, FINAL_CLASSIFICATION_PACKET_SIZE);
        break;

        case PACKET_ID_LOBBY_INFO:
            memcpy(&mPacketLobbyInfoData, mUDPRawPacketData, LOBBY_INFO_PACKET_SIZE);
        break;

        case PACKET_ID_CAR_DAMAGE:
            memcpy(&mPacketCarDamageData, mUDPRawPacketData, CAR_DAMAGE_PACKET_SIZE);
        break;

        case PACKET_ID_SESSION_HISTORY:
            memcpy(&mPacketSessionHistoryData, mUDPRawPacketData, SESSION_HISTORY_PACKET_SIZE);
        break;
    }

    mIsDataAvailable = true;    // Raise the flag
}

boolean UDP_Parser::checkDataAvailibility(void)
{
    return mIsDataAvailable;
}

enum PacketID UDP_Parser::getPacketID(void)
{
    return mPacketID;
}

uint8_t UDP_Parser::getPlayerCarIndex(void)
{
    return mPlayerCarIndex;
}