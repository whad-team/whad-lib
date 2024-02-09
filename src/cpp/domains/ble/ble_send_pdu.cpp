#include <ble/send_pdu.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as a SendPdu message
 * 
 * @param[in]   message     Message to parse
 */

SendPdu::SendPdu(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}

/**
 * @brief       SendPdu message constructor.
 * 
 * @param[in]   direction       PDU direction
 * @param[in]   connHandle      Connection handle in which the PDU is to be sent
 * @param[in]   pPdu            Pointer to a byte buffer containing the PDU
 * @param[in]   length          PDU size in bytes (cannot exceed 250 bytes)
 * @param[in]   encrypt         If set to true and encryption enabled, adapter will encrypt the PDU
 **/

SendPdu::SendPdu(Direction direction, uint32_t connHandle, uint8_t *pPdu, int length, bool encrypt) : BleMsg()
{
    m_direction = direction;
    m_connHandle = connHandle;
    m_pdu = PDU(pPdu, length);
    m_encrypt = encrypt;
}

void SendPdu::pack()
{
    whad_ble_send_pdu(
        this->getMessage(),
        (whad_ble_direction_t)m_direction,
        m_connHandle,
        m_pdu.getBytes(),
        m_pdu.getSize(),
        m_encrypt
    ); 
}

void SendPdu::unpack()
{
    whad_result_t result;
    whad_ble_pdu_params_t params;

    result = whad_ble_send_pdu_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
    else
    {
        /* Extract parameters. */
        m_connHandle = params.conn_handle;
        m_direction = (Direction)params.direction;
        m_encrypt = params.encrypt;
        m_pdu.setBytes(params.p_pdu, params.length);
    }
}


/**
 * @brief   Get PDU direction
 * 
 * @retval  PDU direction
 */

Direction SendPdu::getDirection()
{
    return m_direction;
}


/**
 * @brief   Get connection handle
 * 
 * @retval  Connection handle value
 */

uint32_t SendPdu::getConnHandle()
{
    return m_connHandle;
}


/**
 * @brief   Get PDU
 * 
 * @retval  Reference of the PDU to send.
 */

PDU& SendPdu::getPdu()
{
    return m_pdu;
}


/**
 * @brief   Determine if PDU has to be encrypted
 * 
 * @retval  True if encryption is required, false otherwise.
 */

bool SendPdu::isEncrypted()
{
    return m_encrypt;
}