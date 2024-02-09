#include <ble/send_raw_pdu.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as a SendRawPdu
 * 
 * @param[in]   message     Message to parse
 */

SendRawPdu::SendRawPdu(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}

/**
 * @brief       SendRawPdu message constructor.
 * 
 * @param[in]   direction       PDU direction
 * @param[in]   connHandle      Connection handle in which the PDU is to be sent
 * @param[in]   accessAddress   Connection access address
 * @param[in]   pPdu            Pointer to a byte buffer containing the PDU
 * @param[in]   length          PDU size in bytes (cannot exceed 250 bytes)
 * @param[in]   crc             PDU CRC value
 * @param[in]   encrypt         If set to true and encryption enabled, adapter will encrypt the PDU
 **/

SendRawPdu::SendRawPdu(Direction direction, uint32_t connHandle, uint32_t accessAddress, uint8_t *pPdu,
                       int length, uint32_t crc, bool encrypt) : BleMsg()
{
    m_direction = direction;
    m_connHandle = connHandle;
    m_accessAddr = accessAddress;
    m_pdu = PDU(pPdu, length);
    m_crc = crc;
    m_encrypt = encrypt;
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void SendRawPdu::pack()
{
    whad_ble_send_raw_pdu(
        this->getMessage(),
        (whad_ble_direction_t)m_direction,
        m_connHandle,
        m_accessAddr,
        m_pdu.getBytes(),
        m_pdu.getSize(),
        m_crc,
        m_encrypt
    ); 
}


/**
 * @brief   Extract parameters from a BleMsg
 */

void SendRawPdu::unpack()
{
    whad_result_t result;
    whad_ble_pdu_params_t params;

    result = whad_ble_send_raw_pdu_parse(
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
        m_accessAddr = params.access_address;
        m_connHandle = params.conn_handle;
        m_direction = (Direction)params.direction;
        m_crc = params.crc;
        m_encrypt = params.encrypt;
        m_pdu = PDU(params.p_pdu, params.length);
    }
}