#include <esb/sniff.hpp>

using namespace whad::esb;

/**
 * @brief   Constructor, parse message as a SniffMode message
 * 
 * @param[in]   message     Message to parse
 */

SniffMode::SniffMode(EsbMsg &message) : EsbMsg(message)
{
    this->unpack();
}


/**
 * @brief   Constructor, create a SniffMode message
 * 
 * @param[in]   channel     ESB channel to sniff
 * @param[in]   address     Target ESB address
 * @param[in]   showAcks    Report acknowledgements
 */

SniffMode::SniffMode(uint32_t channel, EsbAddress &address, bool showAcks)
{

    m_channel = channel;
    m_address = address;
    m_showacks = showAcks;
}


/**
 * @brief   Constructor, create a SniffMode message to sniff a specific target
 *          on a specific channel. Acks are not reported.
 * 
 * @param[in]   channel     ESB channel to sniff
 * @param[in]   address     Target ESB address
 */

SniffMode::SniffMode(uint32_t channel, EsbAddress &address) : SniffMode(channel, address, false)
{
}


/**
 * @brief   Constructor, create a SniffMode message to sniff a specific target.
 *           Acks are not reported.
 * 
 * @param[in]   address     Target ESB address
 */

SniffMode::SniffMode(EsbAddress &address) : SniffMode(WHAD_ESB_CHANNEL_AUTO, address, false)
{
}


/**
 * @brief   Constructor, create a SniffMode message to sniff a specific channel.
 *           Acks are not reported.
 * 
 * @param[in]   address     Target ESB address
 */

SniffMode::SniffMode(uint32_t channel) : SniffMode(channel, PromiscAddr, false)
{
}


/**
 * @brief   Constructor, create a SniffMode message to sniff all packets on.
 *          all channels. Acks are not reported.
 * 
 * @param[in]   address     Target ESB address
 */

SniffMode::SniffMode() : SniffMode(WHAD_ESB_CHANNEL_AUTO, PromiscAddr, false)
{
}


/**
 * @brief   Pack parameters into an EsbMsg.
 */

void SniffMode::pack()
{
    whad_esb_address_t addr;

    /* Convert address. */
    addr.size = m_address.getLength();
    memcpy(addr.address, m_address.getAddressBuf(), m_address.getLength());

    whad_esb_sniff(
        this->getMessage(),
        &addr,
        m_channel,
        m_showacks
    );
}


/**
 * @brief   Extract parameters from EsbMsg.
 */

void SniffMode::unpack(void)
{
    whad_result_t result;
    whad_esb_sniff_params_t params;

    result = whad_esb_sniff_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }

    /* Saved parsed parameters. */
    this->m_channel = params.channel;
    this->m_address.setAddress(params.address.address, params.address.size);
    this->m_showacks = params.show_acks;
}

/**
 * @brief   Get the channel number
 * 
 * @retval  Channel number
 */

uint32_t SniffMode::getChannel(void)
{
    return m_channel;
}


/**
 * @brief   Get the target address
 * 
 * @retval  Target ESB address
 */

EsbAddress& SniffMode::getAddress(void)
{
    return m_address;
}


/**
 * @brief   Determine if acks must be reported.
 * 
 * @retval  True if acks must be reported, false otherwise.
 */

bool SniffMode::mustShowAcks(void)
{
    return m_showacks;
}