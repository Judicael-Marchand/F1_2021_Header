#ifndef EVENT_PACKET_HPP
#define EVENT_PACKET_HPP

#include "Packet_Header.hpp"

#define EVENT_PACKET_SIZE 36

#define SESSION_STARTED			"SSTA"	// Sent when the session starts
#define SESSION_ENDED			"SEND"	// Sent when the session ends
#define FASTEST_LAP				"FTLP"	// When a driver achieves the fastest lap
#define RETIREMENT				"RTMT"	// When a driver retires
#define DRS_ENABLED				"DRSE"	// Race control have enabled DRS
#define DRS_DISABLED			"DRSD"	// Race control have disabled DRS
#define TEAM_MATE_IN_PITS		"TMPT"	// Your team mate has entered the pits
#define CHEQUERED_FLAG			"CHQF"	// The chequered flag has been waved
#define RACE_WINNER				"RCWN"	// The race winner is announced
#define PENALTY_ISSUED			"PENA"	// A penalty has been issued – details in event
#define SPEED_TRAP_TRIGGERED    "SPTP"	// Speed trap has been triggered by fastest speed
#define START_LIGHTS			"STLG"	// Start lights – number shown
#define LIGHTS_OUT				"LGOT"	// Lights out
#define DRIVE_THROUGH_SERVED    "DTSV"	// Drive through penalty served
#define STOP_GO_SERVED			"SGSV"	// Stop go penalty served
#define FLASHBACK				"FLBK"	// Flashback activated
#define BUTTON_STATUS			"BUTN"	// Button status changed


// The event details packet is different for each type of event.
// Make sure only the correct type is interpreted.
union EventDataDetails
{
    struct
    {
        uint8	vehicleIdx; // Vehicle index of car achieving fastest lap
        float	lapTime;    // Lap time is in seconds
    } FastestLap;

    struct
    {
        uint8   vehicleIdx; // Vehicle index of car retiring
    } Retirement;

    struct
    {
        uint8   vehicleIdx; // Vehicle index of team mate
    } TeamMateInPits;

    struct
    {
        uint8   vehicleIdx; // Vehicle index of the race winner
    } RaceWinner;

    struct
    {
    	uint8 penaltyType;		// Penalty type – see Appendices
        uint8 infringementType;		// Infringement type – see Appendices
        uint8 vehicleIdx;         	// Vehicle index of the car the penalty is applied to
        uint8 otherVehicleIdx;    	// Vehicle index of the other car involved
        uint8 time;               	// Time gained, or time spent doing action in seconds
        uint8 lapNum;             	// Lap the penalty occurred on
        uint8 placesGained;       	// Number of places gained by this
    } Penalty;

    struct
    {
        uint8 vehicleIdx;		// Vehicle index of the vehicle triggering speed trap
        float speed;      		// Top speed achieved in kilometres per hour
        uint8 overallFastestInSession;   // Overall fastest speed in session = 1, otherwise 0
        uint8 driverFastestInSession;    // Fastest speed for driver in session = 1, otherwise 0
    } SpeedTrap;

    struct
    {
        uint8 numLights;		// Number of lights showing
    } StartLIghts;

    struct
    {
        uint8 vehicleIdx;                 // Vehicle index of the vehicle serving drive through
    } DriveThroughPenaltyServed;

    struct
    {
        uint8 vehicleIdx;                 // Vehicle index of the vehicle serving stop go
    } StopGoPenaltyServed;

    struct
    {
        uint32 flashbackFrameIdentifier;  // Frame identifier flashed back to
        float flashbackSessionTime;       // Session time flashed back to
    } Flashback;

    struct
    {
        uint32         m_buttonStatus;    // Bit flags specifying which buttons are being pressed
                                          // currently - see appendices
    } Buttons;
};

struct PacketEventData
{
    PacketHeader    	m_header;               	// Header
    
    uint8           	m_eventStringCode[4];   	// Event string code, see below
    EventDataDetails	m_eventDetails;         	// Event details - should be interpreted differently
                                                 // for each type
};

#endif