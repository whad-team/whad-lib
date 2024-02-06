#include <ble/rawpdu.hpp>

using namespace whad::ble;

/**
 * @brief   Raw PDU constructor, including timestamp.
 * 
 * @param[in]       channel             Channel on which this PDU has been received
 * @param[in]       rssi                Received Signal Strength Indicator
 * @param[in]       conn_handle         Connection handle
 * @param[in]       access_address      Access Address of the connection
 * @param[in]       p_pdu               Pointer to a byte array containing the PDU
 * @param[in]       length              Length of the data PDU, in bytes
 * @param[in]       crc                 PDU CRC value
 * @param[in]       crc_validity        Set to true if CRC matches the expected value, false otherwise
 * @param[in]       timestamp           PDU timestamp (in micro-seconds)
 * @param[in]       relative_timestamp  PDU relative timestamp (number of micro-seconds in the last connection event)
 * @param[in]       direction           Direction of the PDU (master -> slave / slave -> master)
 * @param[in]       processed           Set to true if PDU has been processed by the device, false otherwise
 * @param[in]       decrypted           Set to true if PDU has been decrypted, false otherwise
 **/

RawPdu::RawPdu(uint32_t channel, int32_t rssi, uint32_t conn_handle, uint32_t access_address,
                          PDU pdu, uint32_t crc, bool crc_validity, uint32_t timestamp,
                          uint32_t relative_timestamp, Direction direction, bool processed,
                          bool decrypted) : BleMsg()
{
    whad_ble_raw_pdu(this->getMessage(), channel, rssi, conn_handle, access_address, pdu.getBytes(), pdu.getSize(), crc, 
                     crc_validity, timestamp, relative_timestamp, (whad_ble_direction_t)direction, processed,
                     decrypted, true);
}

/**
 * @brief   Raw PDU constructor, no timestamp.
 * 
 * @param[in]       channel             Channel on which this PDU has been received
 * @param[in]       rssi                Received Signal Strength Indicator
 * @param[in]       conn_handle         Connection handle
 * @param[in]       access_address      Access Address of the connection
 * @param[in]       p_pdu               Pointer to a byte array containing the PDU
 * @param[in]       length              Length of the data PDU, in bytes
 * @param[in]       crc                 PDU CRC value
 * @param[in]       crc_validity        Set to true if CRC matches the expected value, false otherwise
 * @param[in]       direction           Direction of the PDU (master -> slave / slave -> master)
 * @param[in]       processed           Set to true if PDU has been processed by the device, false otherwise
 * @param[in]       decrypted           Set to true if PDU has been decrypted, false otherwise
 **/

RawPdu::RawPdu(uint32_t channel, int32_t rssi, uint32_t conn_handle, uint32_t access_address,
                           PDU pdu, uint32_t crc, bool crc_validity, Direction direction,
                           bool processed, bool decrypted) : BleMsg()
{
    whad_ble_raw_pdu(this->getMessage(), channel, rssi, conn_handle, access_address, pdu.getBytes(), pdu.getSize(),
                     crc, crc_validity, 0, 0, (whad_ble_direction_t)direction, processed, decrypted, false);
}