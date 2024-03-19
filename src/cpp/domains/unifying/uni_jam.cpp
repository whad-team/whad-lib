#include <unifying/jam.hpp>

using namespace whad::unifying;

/**
 * @brief   Parse a message as a JamMode message.
 */

JamMode::JamMode(UnifyingMsg &message) : UnifyingMsg(message)
{
    this->unpack();
}


/**
 * @brief       JamMode message constructor.
 * 
 * @param[in]   AddressType     Unifying device address
 * @param[in]   address         Specify the device address to use
 **/

JamMode::JamMode(uint32_t channel) : UnifyingMsg()
{
    /* Save target address. */
    m_channel = channel;
}


/**
 * @brief   Pack parameters into a UnifyingMsg object
 */

void JamMode::pack()
{
    whad_unifying_jam(
        this->getMessage(),
        m_channel
    );
}


/**
 * @brief   Extract parameters from a UnifyingMsg
 */

void JamMode::unpack()
{
    whad_result_t result;
    uint32_t channel;

    result = whad_unifying_jam_parse(
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
 * @brief   Retrieve the channel to jam
 * 
 * @retval  Channel number
 */

uint32_t JamMode::getChannel()
{
    return m_channel;
}

