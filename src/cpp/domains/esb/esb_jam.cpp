#include <esb/jam.hpp>

using namespace whad::esb;

/**
 * @brief   Constructor, parses the given message.
 * 
 * @param[in]   message     Message to parse as a JamMode message.
 */

JamMode::JamMode(EsbMsg &message) : EsbMsg(message)
{
    /* Unpack message. */
    this->unpack();
}


/**
 * @brief   Constructor, creates a new JamMode message.
 * 
 * @param[in]   channel     ESB channel to jam
 */

JamMode::JamMode(uint32_t channel) : EsbMsg()
{
    m_channel = channel;
}


/**
 * @brief Get current channel
 * 
 * @retval  Channel number
 */

uint32_t JamMode::getChannel(void)
{
    return m_channel;
}


/**
 * @brief   Pack parameters into an EsbMsg
 */

void JamMode::pack()
{
    whad_esb_jam(
        this->getMessage(),
        m_channel
    );
}


/**
 * @brief   Extract parameters from an EsbMsg.
 */

void JamMode::unpack()
{
    if (whad_esb_jam_parse(this->getMessage(), &m_channel) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}