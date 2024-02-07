#include <esb/prx.hpp>

using namespace whad::esb;

/**
 * @brief   Constructor, parse an EsbMsg as a PrxMode message
 * 
 * @param[in]   message Message to parse
 */

PrxMode::PrxMode(EsbMsg &message) : EsbMsg(message)
{
    this->unpack();
}


/**
 * @brief   Constructor, create a PrxMode message
 * 
 * @param[in]   channel     ESB channel to listen on
 */

PrxMode::PrxMode(uint32_t channel) : EsbMsg()
{
    m_channel = channel;
}


/**
 * @brief   Retrieve the associated channel
 * 
 * @retval  Channel number
 */

uint32_t PrxMode::getChannel()
{
    return m_channel;
}


/**
 * @brief   Pack parameters into an EsbMsg.
 */

void PrxMode::pack()
{
    whad_esb_prx(
        this->getMessage(),
        m_channel
    );
}


/**
 * @brief   Extract parameters from EsbMsg.
 */

void PrxMode::unpack()
{
    if (whad_esb_prx_parse(this->getMessage(), &m_channel) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}