#include <unifying/keyboard.hpp>

using namespace whad::unifying;

/**
 * @brief   Parse a message as a KeyboardMode message.
 */

KeyboardMode::KeyboardMode(UnifyingMsg &message) : UnifyingMsg(message)
{
    this->unpack();
}


/**
 * @brief       KeyboardMode message constructor.
 * 
 * @param[in]   channel     Channel to use
 **/

KeyboardMode::KeyboardMode(uint32_t channel) : UnifyingMsg()
{
    /* Save target address. */
    m_channel = channel;
}


/**
 * @brief   Pack parameters into a UnifyingMsg object
 */

void KeyboardMode::pack()
{
    whad_unifying_keyboard_mode(
        this->getMessage(),
        m_channel
    );
}


/**
 * @brief   Extract parameters from a UnifyingMsg
 */

void KeyboardMode::unpack()
{
    whad_result_t result;
    uint32_t channel;

    result = whad_unifying_keyboard_mode_parse(
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

uint32_t KeyboardMode::getChannel()
{
    return m_channel;
}

