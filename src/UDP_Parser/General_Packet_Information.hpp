#ifndef GENERAL_PACKET_INFORMATION_HPP
#define GENERAL_PACKET_INFORMATION_HPP

enum WheelArray
{
    REAR_LEFT_WHEEL = 0,
    REAR_RIGHT_WHEEL,
    FRONT_LEFT_WHEEL,
    FRONT_RIGHT_WHEEL
};

enum SessionType
{
    SESSION_UNKNOWN = 0,
    SESSION_PRACTICE_1,
    SESSION_PRACTICE_2,
    SESSION_PRACTICE_3,
    SESSION_SHORT_PRACTICE,
    SESSION_QUALIFICATION_1,
    SESSION_QUALIFICATION_2,
    SESSION_QUALIFICATION_3,
    SESSION_SHORT_QUALIFICATION,
    SESSION_ONE_SHOT_QUALIFICATION,
    SESSION_RACE,
    SESSION_R2, // ??
    SESSION_R3, // ??
    SESSION_TIME_TRIAL
};

#endif