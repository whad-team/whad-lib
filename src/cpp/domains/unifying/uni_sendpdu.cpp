#include <unifying/sendpdu.hpp>

using namespace whad::unifying;

/**
 * @brief   Parse a message as a SendPdu message.
 */

SendPdu::SendPdu(UnifyingMsg &message) : UnifyingMsg(message)
{
    this->unpack();
}


/**
 * @brief       SendPdu message constructor.
 * 
 * @param[in]   AddressType     Unifying device address
 * @param[in]   address         Specify the device address to use
 **/

SendPdu::SendPdu(uint32_t channel, int retryCount, uint8_t *pPdu, int length) : UnifyingMsg()
{
    /* Save parameters. */
    m_channel = channel;
    m_retrCount = retryCount;
    m_pdu.setBytes(pPdu, length);
}


/**
 * @brief   Pack parameters into a UnifyingMsg object
 */

void SendPdu::pack()
{
    whad_unifying_send(
        this->getMessage(),
        m_channel,
        m_retrCount,
        m_pdu.getBytes(),
        m_pdu.getSize()
    );
}


/**
 * @brief   Extract parameters from a UnifyingMsg
 */

void SendPdu::unpack()
{
    whad_result_t result;
    whad_unifying_send_params_t params;

    result = whad_unifying_send_parse(
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
        m_channel = params.channel;
        m_retrCount = params.retr_count;
        m_pdu.setBytes(params.packet.bytes, params.packet.length);
    }
}


/**
 * @brief   Retrieve the sniffing channel
 * 
 * @retval  Channel number
 */

uint32_t SendPdu::getChannel()
{
    return m_channel;
}


/**
 * @brief   Retrieve the retry counter
 * 
 * @retval  Number of retransmission counter
 */

int SendPdu::getRetrCounter()
{
    return m_retrCount;
}


/**
 * @brief   Retrieve the PDU
 * 
 * @retval  Reference to the PDU
 */

PDU& SendPdu::getPdu()
{
    return m_pdu;
}