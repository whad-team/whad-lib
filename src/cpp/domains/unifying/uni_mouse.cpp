#include <unifying/mouse.hpp>

using namespace whad::unifying;

/**
 * @brief   Parse a message as a MouseMode message.
 */

MouseMode::MouseMode(UnifyingMsg &message) : UnifyingMsg(message)
{
    this->unpack();
}


/**
 * @brief       MouseMode message constructor.
 * 
 * @param[in]   AddressType     Unifying device address
 * @param[in]   address         Specify the device address to use
 **/

MouseMode::MouseMode(uint32_t channel) : UnifyingMsg()
{
    /* Save target address. */
    m_channel = channel;
}


/**
 * @brief   Pack parameters into a UnifyingMsg object
 */

void MouseMode::pack()
{
    whad_unifying_mouse_mode(
        this->getMessage(),
        m_channel
    );
}


/**
 * @brief   Extract parameters from a UnifyingMsg
 */

void MouseMode::unpack()
{
    whad_result_t result;
    uint32_t channel;

    result = whad_unifying_mouse_mode_parse(
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

uint32_t MouseMode::getChannel()
{
    return m_channel;
}

