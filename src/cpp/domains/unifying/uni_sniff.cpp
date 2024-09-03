#include <unifying/sniff.hpp>

using namespace whad::unifying;

/**
 * @brief   Parse a message as a SniffMode message.
 */

SniffMode::SniffMode(UnifyingMsg &message) : UnifyingMsg(message)
{
    this->unpack();
}


/**
 * @brief       SniffMode message constructor.
 * 
 * @param[in]   address         Specify the device address to use
 * @param[in]   channel         Channel to sniff
 * @param[in]   showAcks        If set to `true`, interface will report packet acknowledgements
 **/

SniffMode::SniffMode(UnifyingAddress &address, uint32_t channel, bool showAcks) : UnifyingMsg()
{
    /* Save target address. */
    m_address = address;
    m_channel = channel;
    m_showAcks = showAcks;
}


/**
 * @brief   Pack parameters into a UnifyingMsg object
 */

void SniffMode::pack()
{
    whad_unifying_address_t address;

    /* Convert our address into a whad_unfying_address_t struct. */
    address.size = m_address.getLength();
    memcpy(address.address, m_address.getBytes(), address.size);

    whad_unifying_sniff(
        this->getMessage(),
        &address,
        m_channel,
        m_showAcks
    );
}


/**
 * @brief   Extract parameters from a UnifyingMsg
 */

void SniffMode::unpack()
{
    whad_result_t result;
    whad_unifying_sniff_params_t params;

    result = whad_unifying_sniff_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_address.set(params.address.address, params.address.size);
        m_channel = params.channel;
        m_showAcks = params.show_acks;
    }
}


/**
 * @brief   Retrieve the unifying node address
 * 
 * @retval  Node address
 */

UnifyingAddress& SniffMode::getAddress()
{
    return m_address;
}


/**
 * @brief   Retrieve the sniffing channel
 * 
 * @retval  Channel number
 */

uint32_t SniffMode::getChannel()
{
    return m_channel;
}


/**
 * @brief   Determine if we must show ACKs
 * 
 * @retval  True if ACKs must be shown, false otherwise
 */

bool SniffMode::mustShowAcks()
{
    return m_showAcks;
}
