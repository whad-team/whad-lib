#include <ble/rawpdu.hpp>

using namespace whad::ble;

/**
 * @brief       Raw PDU constructor from an existing BleMsg.
 *
 * @param[in]   message             BleMsg to build the RawPdu from
 **/

RawPdu::RawPdu(BleMsg &message) : BleMsg(message)
{
    //this->unpack();
}

/**
 * @brief       Raw PDU constructor, including timestamp.
 * 
 * @param[in]   channel             Channel on which this PDU has been received
 * @param[in]   rssi                Received Signal Strength Indicator
 * @param[in]   conn_handle         Connection handle
 * @param[in]   access_address      Access Address of the connection
 * @param[in]   pdu                 PDU received
 * @param[in]   crc                 PDU CRC value
 * @param[in]   crc_validity        Set to true if CRC matches the expected value, false otherwise
 * @param[in]   timestamp           PDU timestamp (in micro-seconds)
 * @param[in]   relative_timestamp  PDU relative timestamp (number of micro-seconds in the last connection event)
 * @param[in]   direction           Direction of the PDU (master -> slave / slave -> master)
 * @param[in]   processed           Set to true if PDU has been processed by the device, false otherwise
 * @param[in]   decrypted           Set to true if PDU has been decrypted, false otherwise
 * @param[in]   phy                 Current Phy
 **/

RawPdu::RawPdu(uint32_t channel, int32_t rssi, uint32_t conn_handle, uint32_t access_address,
                          PDU pdu, uint32_t crc, bool crc_validity, uint32_t timestamp,
                          uint32_t relative_timestamp, Direction direction, bool processed,
                          bool decrypted, Phy phy) : BleMsg()
{
    m_channel = channel;
    m_connHandle = conn_handle;
    m_accessAddress = access_address;
    m_pdu = pdu;
    m_crc = crc;
    m_rssi = rssi;
    m_crcValidity = crc_validity;
    m_timestamp = timestamp;
    m_relative_timestamp = relative_timestamp;
    m_direction = direction;
    m_processed = processed;
    m_decrypted = decrypted;
    m_hasTimestamp = true;
    m_phy = phy;

    /*
    whad_ble_raw_pdu(this->getMessage(), channel, rssi, conn_handle, access_address, pdu.getBytes(), pdu.getSize(), crc, 
                     crc_validity, timestamp, relative_timestamp, (whad_ble_direction_t)direction, processed,
                     decrypted, true);
    */
}

/**
 * @brief   Raw PDU constructor, no timestamp.
 * 
 * @param[in]       channel             Channel on which this PDU has been received
 * @param[in]       rssi                Received Signal Strength Indicator
 * @param[in]       conn_handle         Connection handle
 * @param[in]       access_address      Access Address of the connection
 * @param[in]       pdu                 Received PDU
 * @param[in]       crc                 PDU CRC value
 * @param[in]       crc_validity        Set to true if CRC matches the expected value, false otherwise
 * @param[in]       direction           Direction of the PDU (master -> slave / slave -> master)
 * @param[in]       processed           Set to true if PDU has been processed by the device, false otherwise
 * @param[in]       decrypted           Set to true if PDU has been decrypted, false otherwise
 * @param[in]       phy                 Current Phy
 **/

RawPdu::RawPdu(uint32_t channel, int32_t rssi, uint32_t conn_handle, uint32_t access_address,
                           PDU pdu, uint32_t crc, bool crc_validity, Direction direction,
                           bool processed, bool decrypted, Phy phy) : BleMsg()
{
    m_channel = channel;
    m_connHandle = conn_handle;
    m_accessAddress = access_address;
    m_pdu = pdu;
    m_crc = crc;
    m_rssi = rssi;
    m_crcValidity = crc_validity;
    m_direction = direction;
    m_processed = processed;
    m_decrypted = decrypted;
    m_hasTimestamp = false;
    m_phy = phy;
}

/**
 * @brief   Pack a RawPdu message into a BleMsg.
 **/

void RawPdu::pack(void)
{
    if (m_hasTimestamp)
    {
        whad_ble_raw_pdu(
            this->getMessage(),
            m_channel,
            m_rssi,
            m_connHandle,
            m_accessAddress,
            m_pdu.getBytes(),
            m_pdu.getSize(),
            m_crc, 
            m_crcValidity,
            m_timestamp,
            m_relative_timestamp,
            (whad_ble_direction_t)m_direction,
            m_processed,
            m_decrypted,
            true,
            (whad_ble_phy_t)m_phy
        );
    }
    else
    {
        whad_ble_raw_pdu(
            this->getMessage(),
            m_channel,
            m_rssi,
            m_connHandle,
            m_accessAddress,
            m_pdu.getBytes(),
            m_pdu.getSize(),
            m_crc, 
            m_crcValidity,
            0,
            0,
            (whad_ble_direction_t)m_direction,
            m_processed,
            m_decrypted,
            false,
            (whad_ble_phy_t)m_phy
        );        
    }
}


/**
 * @brief   Retrieve the channel on which this PDU has been received.
 *
 * @retval  Channel number.
 **/

uint32_t RawPdu::getChannel()
{
    return m_channel;
}


/**
 * @brief   Retrieve the Received Signal Strength Indicator of this PDU.
 *
 * @retval  RSSI level (dBm).
 **/

int32_t RawPdu::getRssi()
{
    return m_rssi;
}


/**
 * @brief   Retrieve the connection handle associated with this PDU.
 *
 * @retval  Connection handle.
 **/

uint32_t RawPdu::getConnHandle()
{
    return m_connHandle;
}


/**
 * @brief   Retrieve the Access Address of the connection this PDU belongs to.
 *
 * @retval  Access address.
 **/

uint32_t RawPdu::getAccessAddress()
{
    return m_accessAddress;
}


/**
 * @brief   Retrieve the raw PDU payload.
 *
 * @retval  Reference to the PDU object.
 **/

PDU& RawPdu::getPdu()
{
    return m_pdu;
}


/**
 * @brief   Retrieve the CRC value of this PDU.
 *
 * @retval  CRC value.
 **/

uint32_t RawPdu::getCrc()
{
    return m_crc;
}


/**
 * @brief   Determine whether the CRC of this PDU is valid.
 *
 * @retval  True if CRC matches the expected value, false otherwise.
 **/

bool RawPdu::isCrcValid()
{
    return m_crcValidity;
}


/**
 * @brief   Retrieve the timestamp of this PDU.
 *
 * @retval  Timestamp in micro-seconds.
 **/

uint32_t RawPdu::getTimestamp()
{
    return m_timestamp;
}


/**
 * @brief   Retrieve the relative timestamp of this PDU.
 *
 * @retval  Number of micro-seconds elapsed in the last connection event.
 **/

uint32_t RawPdu::getRelativeTimestamp()
{
    return m_relative_timestamp;
}


/**
 * @brief   Retrieve the direction of this PDU.
 *
 * @retval  Direction (master -> slave or slave -> master).
 **/

Direction RawPdu::getDirection()
{
    return m_direction;
}


/**
 * @brief   Determine whether this PDU has been processed by the device.
 *
 * @retval  True if the PDU has been processed, false otherwise.
 **/

bool RawPdu::isProcessed()
{
    return m_processed;
}


/**
 * @brief   Determine whether this PDU has been decrypted.
 *
 * @retval  True if the PDU has been decrypted, false otherwise.
 **/

bool RawPdu::isDecrypted()
{
    return m_decrypted;
}


/**
 * @brief   Determine whether this PDU carries a timestamp.
 *
 * @retval  True if a timestamp is available, false otherwise.
 **/

bool RawPdu::hasTimestamp()
{
    return m_hasTimestamp;
}


/**
 * @brief   Retrieve the PHY used to receive this PDU.
 *
 * @retval  Current Phy.
 **/

Phy RawPdu::getPhy()
{
    return m_phy;
}
