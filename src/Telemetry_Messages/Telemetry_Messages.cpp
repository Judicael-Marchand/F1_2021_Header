#include "Telemetry_Messages.hpp"

/**
 * @brief Construct a new Telemetry_Messages::Telemetry_Messages object
 * 
 */
Telemetry_Messages::Telemetry_Messages(void)
{
    mUDPParser = new UDP_Parser();
    memset(&mCarInformation, 0, sizeof(mCarInformation));
    memset(&mSessionInformation, 0, sizeof(mSessionInformation));
    mMessageID = NO_MESSAGE_ID;
}

/**
 * @brief Destroy the Telemetry_Messages::Telemetry_Messages object
 * 
 */
Telemetry_Messages::~Telemetry_Messages(void)
{

}

/**
 * @brief Check if the UDP_Parser system has any new information or not
 * 
 * @return  True if the UDP_Parser system has new information, False if the UDP_Parser system has no new information
 */
boolean Telemetry_Messages::checkRawDataAvailibility(void)
{
    return mUDPParser->checkDataAvailibility();
}

/**
 * @brief Takes the available data in the UDP_Parser system and stores it in the right stucture
 * 
 */
void Telemetry_Messages::storeAvailableData(void)
{
    switch(mUDPParser->getPacketID())
    {
        case PACKET_ID_SESSION:
            mSessionInformation.m_totalLaps = mUDPParser->mPacketSessionData.m_totalLaps;
            mSessionInformation.m_sessionType = mUDPParser->mPacketSessionData.m_sessionType;
            mMessageID = SESSION_MESSAGE_ID;
        break;

        case PACKET_ID_LAP_DATA:
            mSessionInformation.m_carPosition = mUDPParser->mPacketLapData.m_lapData[mUDPParser->getPlayerCarIndex()].m_carPosition;
            mSessionInformation.m_currentLapNum = mUDPParser->mPacketLapData.m_lapData[mUDPParser->getPlayerCarIndex()].m_currentLapNum;
            mMessageID = SESSION_MESSAGE_ID;
        break;

        case PACKET_ID_FINAL_CLASSIFICATION:
            mSessionInformation.m_finalPosition = mUDPParser->mPacketFinalClassificationData.m_classificationData[mUDPParser->getPlayerCarIndex()].m_position;
            mMessageID = SESSION_MESSAGE_ID;
        break;

        case PACKET_ID_CAR_DAMAGE:
            memcpy(&mCarInformation.m_TyreWear, &mUDPParser->mPacketCarDamageData.m_carDamageData[mUDPParser->getPlayerCarIndex()].m_tyresWear, sizeof(mCarInformation.m_TyreWear));
            mMessageID = CAR_MESSAGE_ID;
        break;

        case PACKET_ID_CAR_STATUS:
            mCarInformation.m_currentTyreType = (TyreType)mUDPParser->mPacketCarStatusData.m_carStatusData[mUDPParser->getPlayerCarIndex()].m_visualTyreCompound;
            mMessageID = CAR_MESSAGE_ID;
        break;

        case PACKET_ID_CAR_TELEMETRY:
            mCarInformation.m_gear = mUDPParser->mPacketCarTelemetryData.m_carTelemetryData[mUDPParser->getPlayerCarIndex()].m_gear;
            mMessageID = CAR_MESSAGE_ID;
        break;

        case PACKET_ID_PARTICIPANTS:
            mSessionInformation.m_numActiveCars = mUDPParser->mPacketParticipantsData.m_numActiveCars;
            mMessageID = SESSION_MESSAGE_ID;
        break;

        default:
            // Don't care
        break;
    }
}

/**
 * @brief Get the message ID of the incame message
 * 
 * @return  The message ID of the incame message
 */
enum MessageID Telemetry_Messages::getMessageID(void)
{
    return mMessageID;
}

/**
 * @brief Set the message ID
 * 
 * @param messageID The message ID to set
 */
void Telemetry_Messages::setMessageID(enum MessageID messageID)
{
    mMessageID = messageID;
}

/**
 * @brief Execute the Telemetry_Messages machine
 * @details This machine executes the UDP_Parser machine and check if any new message is avaible. If so, it manages the new information
 */
void Telemetry_Messages::execute(void)
{
    mUDPParser->execute();
    if(this->checkRawDataAvailibility())
    {
        this->storeAvailableData();
        mUDPParser->setDataAvailibility(false);
    }
}