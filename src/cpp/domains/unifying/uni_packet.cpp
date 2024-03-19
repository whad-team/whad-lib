#include "unifying/packet.hpp"

using namespace whad::unifying;

UnifyingPacket::UnifyingPacket()
{
    /* No channel defined, empty PDU, no FCS. */
    m_channel = 0;
    m_pdu = PDU();
    m_crc = 0;

    /* We don't have any timestamp, rssi, FCS validity nor LQI. */
    m_hasTimestamp = false;
    m_timestamp = 0;
    m_hasRssi = false;
    m_rssi = 0;
    m_hasCrcValidity = false;
    m_crcValidity = false;
}

/**
 * @brief   Create a UnifyingPacket object with the given channel, PDU and FCS values
 * 
 * @param[in]   channel     ZigBee channel on which the PDU has been received
 * @param[in]   pPdu        Pointer to a buffer containing the PDU bytes
 * @param[in]   length      PDU length in bytes
 * @param[in]   crc         Frame Check Sequence value
 */

UnifyingPacket::UnifyingPacket(uint32_t channel, uint8_t *pPdu, int length, uint32_t crc)
{
    /* Set mandatory values. */
    m_channel = channel;
    m_pdu = PDU(pPdu, length);
    m_crc = crc;

    /* We don't have any timestamp, rssi, FCS validity nor LQI. */
    m_hasTimestamp = false;
    m_timestamp = 0;
    m_hasRssi = false;
    m_rssi = 0;
    m_hasCrcValidity = false;
    m_crcValidity = false;
}


/**
 * @brief   Create a UnifyingPacket object with the given channel, PDU and FCS values
 * 
 * @param[in]   channel     ZigBee channel on which the PDU has been received
 * @param[in]   pPdu        Pointer to a buffer containing the PDU bytes
 * @param[in]   length      PDU length in bytes
 * @param[in]   crc         Frame Check Sequence value
 * @param[in]   rssi        Received Signal Strength Indicator value (in dBm)
 */

UnifyingPacket::UnifyingPacket(uint32_t channel, uint8_t *pPdu, int length, uint32_t crc,
        int32_t rssi) : UnifyingPacket(channel, pPdu, length, crc)
{
    /* Add RSSI. */
    addRssi(rssi);
}


/**
 * @brief   Create a UnifyingPacket object with the given channel, PDU and FCS values
 * 
 * @param[in]   channel     ZigBee channel on which the PDU has been received
 * @param[in]   pPdu        Pointer to a buffer containing the PDU bytes
 * @param[in]   length      PDU length in bytes
 * @param[in]   crc         Frame Check Sequence value
 * @param[in]   rssi        Received Signal Strength Indicator value (in dBm)
 * @param[in]   timestamp   Timestamp (in seconds) at which the PDU has been received
 */

UnifyingPacket::UnifyingPacket(uint32_t channel, uint8_t *pPdu, int length, uint32_t crc,
        int32_t rssi, uint32_t timestamp) : UnifyingPacket(channel, pPdu, length, crc,
        rssi)
{
    /* Add timestamp. */
    addTimestamp(timestamp);
}


/* Setters. */

/**
 * @brief   Set zigbee packet channel value
 * 
 * @param[in]   channel     Zigbee channel this packet has been received on
 */

void UnifyingPacket::setChannel(uint32_t channel)
{
    m_channel = channel;
}

/**
 * @brief   Set zigbee packet channel FCS value
 * 
 * @param[in]   crc         Frame Check Sequence value for this packet
 */

void UnifyingPacket::setCrc(uint32_t crc)
{
    m_crc = crc;
}


/**
 * @brief   Set zigbee packet PDU
 * 
 * @param[in]   pdu         packet PDU
 */

void UnifyingPacket::setPdu(PDU& pdu)
{
    m_pdu.setBytes(pdu.getBytes(), pdu.getSize());
}


/**
 * @brief   Add RSSI to the received PDU
 * 
 * @param[in]   rssi    Received Signal Strength Indicator in dBm
 */

void UnifyingPacket::addRssi(int32_t rssi)
{
    /* Add an RSSI value. */
    m_hasRssi = true;
    m_rssi = rssi;
}


/**
 * @brief   Add Timestamp to the received PDU
 * 
 * @param[in]   timestamp   Timestamp in seconds
 */

void UnifyingPacket::addTimestamp(uint32_t timestamp)
{
    /* Add timestamp value. */
    m_hasTimestamp = true;
    m_timestamp = timestamp;
}


/**
 * @brief   Add FCS validity to the received PDU
 * 
 * @param[in]   valid   FCS validity
 */

void UnifyingPacket::addCrcValidity(bool valid)
{
    /* Add FCS validity. */
    m_hasCrcValidity = true;
    m_crcValidity = valid;
}


/* Getters. */

/**
 * @brief   Retrieve the channel on which the PDU has been received
 * 
 * @retval  Channel number
 */

uint32_t UnifyingPacket::getChannel()
{
    return m_channel;
}


/**
 * @brief   Retrieve the received PDU
 * 
 * @retval  Received PDU
 */

PDU& UnifyingPacket::getPdu()
{
    return m_pdu;
}


/**
 * @brief   Retrieve the Frame Check Sequence value
 * 
 * @retval  FCS value
 * @retval  0 if not available
 */

uint32_t UnifyingPacket::getCrc()
{
    return m_crc;
}


/**
 * @brief   Determine if the PDU has RSSI information available
 * 
 * @return  True if RSSI is available, false otherwise
 */

bool UnifyingPacket::hasRssi()
{
    return m_hasRssi;
}


/**
 * @brief   Retrieve the PDU RSSI value
 * 
 * @retval  RSSI value
 */

int32_t UnifyingPacket::getRssi()
{
    if (m_hasRssi)
    {
        return m_rssi;
    }

    return 0;
}


/**
 * @brief   Determine if the PDU has FCS validity information available
 * 
 * @retval  FCS validity presence
 */

bool UnifyingPacket::hasCrcValidity()
{
    return m_hasCrcValidity;
}


/**
 * @brief   Determine if the PDU FCS value is valid
 * 
 * @retval  FCS validity
 */

bool UnifyingPacket::isCrcValid()
{
    if (m_hasCrcValidity)
    {
        return m_crcValidity;
    }

    /* By default, consider FCS validity false. */
    return false;
}


/**
 * @brief   Determine if the packet timestamp is available
 * 
 * @retval  True if available, false otherwise.
 */

bool UnifyingPacket::hasTimestamp()
{
    return m_hasTimestamp;
}


/**
 * @brief   Retrieve the timestamp value
 * 
 * @retval  Timestamp value
 */

uint32_t UnifyingPacket::getTimestamp()
{
    if (hasTimestamp())
    {
        return m_timestamp;
    }

    return 0;
}