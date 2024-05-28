#include <dot15d4/sendrawpdu.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a SendRawPdu message.
 */

SendRawPdu::SendRawPdu(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       SendRawPdu message constructor.
 * 
 * @param[in]   channel         Specify the ZigBee channel to use
 * @param[in]   pdu             PDU to send
 **/

SendRawPdu::SendRawPdu(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs) : Dot15d4Msg()
{
    /* Save channel. */
    m_channel = channel;

    /* Save FCS. */
    m_fcs = fcs;

    /* Save PDU. */
    m_pdu = PDU(pPdu, length);
}


/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void SendRawPdu::pack()
{
    whad_dot15d4_send_raw(
        this->getMessage(),
        m_channel,
        m_pdu.getBytes(),
        m_pdu.getSize(),
        m_fcs
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void SendRawPdu::unpack()
{
    whad_result_t result;
    whad_dot15d4_send_params_t params;

    result = whad_dot15d4_send_raw_parse(
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
        m_fcs = params.fcs;
        m_pdu.setBytes(params.packet.bytes, params.packet.length);
    }
}


/**
 * @brief   Retrieve the dot15d4 channel to use
 * 
 * @retval  Channel number
 */

uint32_t SendRawPdu::getChannel()
{
    return m_channel;
}


/**
 * @brief   Retrieve the PDU to send
 * 
 * @retval  Reference to the PDU object containing the bytes to send
 */

PDU& SendRawPdu::getPdu()
{
    return m_pdu;
}


/**
 * @brief   Retrieve the Frame Check Sequence value
 * 
 * @retval  FCS value
 */

uint32_t SendRawPdu::getFcs()
{
    return m_fcs;
}
