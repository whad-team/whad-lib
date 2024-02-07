#include "phy/jam.hpp"

using namespace whad::phy;

/**
 * @brief       Create a JamMode message based on raw PHY message.
 * 
 * @param[in]   message     Base PhyMsg message to use.
 **/

JamMode::JamMode(PhyMsg &message) : PhyMsg(message)
{
    this->unpack();
}


/**
 * @brief       Create a JamMode message with specified mode.
 * 
 * @param[in]   mode    Jamming mode to use
 **/

JamMode::JamMode(JammingMode mode) : PhyMsg()
{
    /* Save mode. */
    m_mode = mode;
}


/**
 * @brief       Get the specified jamming mode
 **/

JammingMode JamMode::getMode()
{
    return m_mode;
}


/**
 * @brief   Message pack callback.
 */

void JamMode::pack()
{
    /* Create the corresponding NanoPb message. */
    whad_phy_jam_mode(
        this->getMessage(),
        (whad_phy_jam_mode_t)m_mode
    );
}


/**
 * @brief   Unpack the underlying message parameters.
 */

void JamMode::unpack()
{
    if (whad_phy_jam_mode_parse(this->getMessage(), (whad_phy_jam_mode_t *)&m_mode) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}


/****************************
 * Jammed notification
 * 
 * This notification is sent whenever an existing connection or advertisement
 * has successfully been jammed.
 ***************************/


/**
 * @brief       Create a Jammed message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

Jammed::Jammed(PhyMsg &message) : PhyMsg(message)
{
    this->unpack();
}


/**
 * @brief       Create a Jammed message with its associated timestamp.
 * 
 * @param[in]   timestamp   Timestamp at which the target has been successfully jammed
 **/

Jammed::Jammed(Timestamp &timestamp) : PhyMsg()
{
    m_timestamp = Timestamp(timestamp.getSeconds(),
                            timestamp.getMicroseconds());
}


/**
 * @brief       Get message timestamp.
 * 
 * @param[in]   timestamp   Timestamp at which the target has been successfully jammed
 **/

Timestamp Jammed::getTimestamp()
{
    return m_timestamp;
}


void Jammed::pack()
{
     whad_phy_jammed(
        this->getMessage(),
        m_timestamp.getSeconds(),
        m_timestamp.getMicroseconds()
    );
}

void Jammed::unpack()
{
    whad_phy_timestamp_t timestamp;

    if (whad_phy_jammed_parse(this->getMessage(), &timestamp) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }

    m_timestamp = Timestamp(timestamp.ts_sec, timestamp.ts_usec);
}