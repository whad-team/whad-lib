#include <ble/send_raw_pdu.hpp>

using namespace whad::ble;

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
    whad_ble_send_raw_pdu(
        this->getMessage(),
        (whad_ble_direction_t)direction,
        connHandle,
        accessAddress,
        pPdu,
        length,
        crc,
        encrypt
    );
}