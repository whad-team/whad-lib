#include <dot15d4/jam.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a JamMode message.
 */

JamMode::JamMode(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       JamMode message constructor.
 * 
 * @param[in]   channel         Specify the ZigBee channel to jam
 **/

JamMode::JamMode(uint32_t channel) : Dot15d4Msg()
{
    /* Save channel. */
    m_channel = channel;
}


/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void JamMode::pack()
{
    whad_dot15d4_jam(
        this->getMessage(),
        m_channel
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void JamMode::unpack()
{
    whad_result_t result;
    uint32_t channel;

    result = whad_dot15d4_jam_parse(
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
