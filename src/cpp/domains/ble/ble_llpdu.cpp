#include <ble/ll_pdu.hpp>

using namespace whad::ble;

/**
 * @brief   Create a LinkLayerPdu object from a BLE PDU.
 * 
 * @param[in]   pdu         Pointer to a byte array containing the PDU
 * @param[in]   length      Size in bytes of the PDU
 * @param[in]   direction   Direction of the PDU (host to slave, slave to host, ...)
 **/

LinkLayerPdu::LinkLayerPdu(uint32_t conn_handle, PDU pdu, Direction direction, bool processed, bool decrypted) : BleMsg()
{
    /* Initialize our data pdu message. */
    whad_ble_pdu(this->getMessage(), pdu.getBytes(), pdu.getSize(), (whad_ble_direction_t)direction, conn_handle, processed, decrypted);
}