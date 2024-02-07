#include <esb/ptx.hpp>

using namespace whad::esb;

/**
 * @brief   Constructor, parse a message as a PtxMode message
 * 
 * @param[in]   message     Message to parse
 */

PtxMode::PtxMode(EsbMsg &message) : EsbMsg(message)
{
    this->unpack();
}


/**
 * @brief   Constructor, create a PtxMode message
 * 
 * @param[in]   channel     ESB channel on which messages will be sent
 */

PtxMode::PtxMode(uint32_t channel) : EsbMsg()
{
    m_channel = channel;
}


/**
 * @brief   Retrieve the channel in use
 * 
 * @retval  Channel number
 */

uint32_t PtxMode::getChannel()
{
    return m_channel;
}


/**
 * @brief   Pack parameters into an EsbMsg.
 */

void PtxMode::pack()
{
    whad_esb_ptx(
        this->getMessage(),
        m_channel
    );
}


/**
 * @brief   Extract parameters from an EsbMsg.
 */

void PtxMode::unpack()
{
    if (whad_esb_ptx_parse(this->getMessage(), &m_channel) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}