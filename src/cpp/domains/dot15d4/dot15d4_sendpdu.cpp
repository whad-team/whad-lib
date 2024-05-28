#include <dot15d4/sendpdu.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a SendPdu message.
 */

SendPdu::SendPdu(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       SendPdu message constructor.
 * 
 * @param[in]   channel         Specify the ZigBee channel to use
 * @param[in]   pdu             PDU to send
 **/

SendPdu::SendPdu(uint32_t channel, uint8_t *pPdu, int length) : Dot15d4Msg()
{
    /* Save channel. */
    m_channel = channel;

    /* Save PDU. */
    m_pdu = PDU(pPdu, length);
}


/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void SendPdu::pack()
{
    whad_dot15d4_send(
        this->getMessage(),
        m_channel,
        m_pdu.getBytes(),
        m_pdu.getSize()
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void SendPdu::unpack()
{
    whad_result_t result;
    whad_dot15d4_send_params_t params;

    result = whad_dot15d4_send_parse(
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
        m_pdu.setBytes(params.packet.bytes, params.packet.length);
    }
}


/**
 * @brief   Retrieve the zigbee channel to use
 * 
 * @retval  Channel number
 */

uint32_t SendPdu::getChannel()
{
    return m_channel;
}


/**
 * @brief   Retrieve the PDU to send
 * 
 * @retval  Reference to the PDU object containing the bytes to send
 */

PDU& SendPdu::getPdu()
{
    return m_pdu;
}
