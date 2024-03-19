#include <zigbee/jam.hpp>

using namespace whad::zigbee;

/**
 * @brief   Parse a message as a JamMode message.
 */

JamMode::JamMode(ZigbeeMsg &message) : ZigbeeMsg(message)
{
    this->unpack();
}


/**
 * @brief       JamMode message constructor.
 * 
 * @param[in]   channel         Specify the ZigBee channel to jam
 **/

JamMode::JamMode(uint32_t channel) : ZigbeeMsg()
{
    /* Save channel. */
    m_channel = channel;
}


/**
 * @brief   Pack parameters into a ZigbeeMsg object
 */

void JamMode::pack()
{
    whad_zigbee_jam(
        this->getMessage(),
        m_channel
    );
}


/**
 * @brief   Extract parameters from a ZigbeeMsg
 */

void JamMode::unpack()
{
    whad_result_t result;
    uint32_t channel;

    result = whad_zigbee_jam_parse(
        this->getMessage(),
        &channel
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_channel = channel;
    }
}


/**
 * @brief   Retrieve the zigbee channel to jam
 * 
 * @retval  Channel number
 */

uint32_t JamMode::getChannel()
{
    return m_channel;
}
