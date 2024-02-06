#include <ble/send_pdu.hpp>

using namespace whad::ble;

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
    whad_ble_send_pdu(
        this->getRaw(),
        (whad_ble_direction_t)direction,
        connHandle,
        pPdu,
        length,
        encrypt
    );
}