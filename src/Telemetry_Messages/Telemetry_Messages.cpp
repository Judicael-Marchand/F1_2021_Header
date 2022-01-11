#include "Telemetry_Messages.hpp"

Telemetry_Messages::Telemetry_Messages(void)
{
    mUDPParser = new UDP_Parser();
    memset(&mCarInformation, 0, sizeof(mCarInformation));
    memset(&mSessionInformation, 0, sizeof(mSessionInformation));
    mMessageID = NO_MESSAGE_ID;
}

Telemetry_Messages::~Telemetry_Messages(void)
{

}

boolean Telemetry_Messages::checkRawDataAvailibility(void)
{
    return mUDPParser->checkDataAvailibility();
}

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

        default:
            // Don't care
        break;
    }
}

enum MessageID Telemetry_Messages::getMessageID(void)
{
    return mMessageID;
}

void Telemetry_Messages::setMessageID(enum MessageID messageID)
{
    mMessageID = messageID;
}

void Telemetry_Messages::execute(void)
{
    mUDPParser->execute();
    if(this->checkRawDataAvailibility())
    {
        this->storeAvailableData();
        mUDPParser->setDataAvailibility(false);
    }
}