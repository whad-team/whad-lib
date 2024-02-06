#include "phy/jam.hpp"

using namespace whad::phy;

/** jam mode **/

/**
 * @brief       Create a JamMode message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

JamMode::JamMode(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a JamMode message with specified mode.
 * 
 * @param[in]   mode    Jamming mode to use
 **/

JamMode::JamMode(JammingMode mode) : PhyMsg()
{
    whad_phy_jam_mode(
        this->getRaw(),
        (whad_phy_jam_mode_t)mode
    );
}


/**
 * @brief       Get the specified jamming mode
 * 
 * @param[in]   mode    Jamming mode to use
 **/

JammingMode JamMode::getMode()
{
    whad_phy_jam_mode_t mode = PHY_JAM_MODE_CONTINUOUS;

    whad_phy_jam_mode_parse(
        this->getRaw(),
        &mode
    );

    return (JammingMode)mode;
}


/** Jammed notification **/

/**
 * @brief       Create a Jammed message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

Jammed::Jammed(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a Jammed message with its associated timestamp.
 * 
 * @param[in]   timestamp   Timestamp at which the target has been successfully jammed
 **/

Jammed::Jammed(Timestamp &timestamp) : PhyMsg()
{
    whad_phy_jammed(
        this->getRaw(),
        timestamp.getSeconds(),
        timestamp.getMicroseconds()
    );
}


/**
 * @brief       Get message timestamp.
 * 
 * @param[in]   timestamp   Timestamp at which the target has been successfully jammed
 **/

Timestamp Jammed::getTimestamp()
{
    whad_phy_timestamp_t timestamp;

    whad_phy_jammed_parse(
        this->getRaw(),
        &timestamp
    );

    return Timestamp(timestamp.ts_sec, timestamp.ts_usec);
}
