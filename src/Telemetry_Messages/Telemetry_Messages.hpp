#ifndef TELEMETRY_MESSAGES_HPP
#define TELEMETRY_MESSAGES_HPP

#include "UDP_Parser.hpp"
#include "Global_Information.hpp"

/**
 * @class Telemetry_Messages
 * @brief Take only the wanted information from the UDP_Parser and gives it to the screen handler
 * 
 */
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