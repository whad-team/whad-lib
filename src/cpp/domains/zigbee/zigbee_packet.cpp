#include "zigbee/packet.hpp"

using namespace whad::zigbee;

ZigbeePacket::ZigbeePacket()
{
    /* No channel defined, empty PDU, no FCS. */
    m_channel = 0;
    m_pdu = PDU();
    m_fcs = 0;

    /* We don't have any timestamp, rssi, FCS validity nor LQI. */
    m_hasTimestamp = false;
    m_timestamp = 0;
    m_hasRssi = false;
    m_rssi = 0;
    m_hasLqi = false;
    m_lqi = 0;
    m_hasFcsValidity = false;
    m_fcsValidity = false;
}

/**
 * @brief   Create a ZigbeePacket object with the given channel, PDU and FCS values
 * 
 * @param[in]   channel     ZigBee channel on which the PDU has been received
 * @param[in]   pPdu        Pointer to a buffer containing the PDU bytes
 * @param[in]   length      PDU length in bytes
 * @param[in]   fcs         Frame Check Sequence value
 */

ZigbeePacket::ZigbeePacket(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs)
{
    /* Set mandatory values. */
    m_channel = channel;
    m_pdu = PDU(pPdu, length);
    m_fcs = fcs;

    /* We don't have any timestamp, rssi, FCS validity nor LQI. */
    m_hasTimestamp = false;
    m_timestamp = 0;
    m_hasRssi = false;
    m_rssi = 0;
    m_hasLqi = false;
    m_lqi = 0;
    m_hasFcsValidity = false;
    m_fcsValidity = false;
}


/**
 * @brief   Create a ZigbeePacket object with the given channel, PDU and FCS values
 * 
 * @param[in]   channel     ZigBee channel on which the PDU has been received
 * @param[in]   pPdu        Pointer to a buffer containing the PDU bytes
 * @param[in]   length      PDU length in bytes
 * @param[in]   fcs         Frame Check Sequence value
 * @param[in]   rssi        Received Signal Strength Indicator value (in dBm)
 */

ZigbeePacket::ZigbeePacket(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs,
        int32_t rssi) : ZigbeePacket(channel, pPdu, length, fcs)
{
    /* Add RSSI. */
    addRssi(rssi);
}


/**
 * @brief   Create a ZigbeePacket object with the given channel, PDU and FCS values
 * 
 * @param[in]   channel     ZigBee channel on which the PDU has been received
 * @param[in]   pPdu        Pointer to a buffer containing the PDU bytes
 * @param[in]   length      PDU length in bytes
 * @param[in]   fcs         Frame Check Sequence value
 * @param[in]   rssi        Received Signal Strength Indicator value (in dBm)
 * @param[in]   timestamp   Timestamp (in seconds) at which the PDU has been received
 */

ZigbeePacket::ZigbeePacket(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs,
        int32_t rssi, uint32_t timestamp) : ZigbeePacket(channel, pPdu, length, fcs,
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

void ZigbeePacket::setChannel(uint32_t channel)
{
    m_channel = channel;
}

/**
 * @brief   Set zigbee packet channel FCS value
 * 
 * @param[in]   fcs         Frame Check Sequence value for this packet
 */

void ZigbeePacket::setFcs(uint32_t fcs)
{
    m_fcs = fcs;
}


/**
 * @brief   Set zigbee packet PDU
 * 
 * @param[in]   pdu         packet PDU
 */

void ZigbeePacket::setPdu(PDU& pdu)
{
    m_pdu.setBytes(pdu.getBytes(), pdu.getSize());
}


/**
 * @brief   Add RSSI to the received PDU
 * 
 * @param[in]   rssi    Received Signal Strength Indicator in dBm
 */

void ZigbeePacket::addRssi(int32_t rssi)
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

void ZigbeePacket::addTimestamp(uint32_t timestamp)
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

void ZigbeePacket::addFcsValidity(bool valid)
{
    /* Add FCS validity. */
    m_hasFcsValidity = true;
    m_fcsValidity = valid;
}


/**
 * @brief   Add LQI to the received PDU
 * 
 * @param[in]   lqi     Link Quality Indication
 */

void ZigbeePacket::addLqi(uint32_t lqi)
{
    /* Add LQI. */
    m_hasLqi = true;
    m_lqi = lqi;
}



/* Getters. */

/**
 * @brief   Retrieve the channel on which the PDU has been received
 * 
 * @retval  Channel number
 */

uint32_t ZigbeePacket::getChannel()
{
    return m_channel;
}


/**
 * @brief   Retrieve the received PDU
 * 
 * @retval  Received PDU
 */

PDU& ZigbeePacket::getPdu()
{
    return m_pdu;
}


/**
 * @brief   Retrieve the Frame Check Sequence value
 * 
 * @retval  FCS value
 * @retval  0 if not available
 */

uint32_t ZigbeePacket::getFcs()
{
    return m_fcs;
}


/**
 * @brief   Determine if the PDU has RSSI information available
 * 
 * @return  True if RSSI is available, false otherwise
 */

bool ZigbeePacket::hasRssi()
{
    return m_hasRssi;
}


/**
 * @brief   Retrieve the PDU RSSI value
 * 
 * @retval  RSSI value
 */

int32_t ZigbeePacket::getRssi()
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

bool ZigbeePacket::hasFcsValidity()
{
    return m_hasFcsValidity;
}


/**
 * @brief   Determine if the PDU FCS value is valid
 * 
 * @retval  FCS validity
 */

bool ZigbeePacket::isFcsValid()
{
    if (m_hasFcsValidity)
    {
        return m_fcsValidity;
    }

    /* By default, consider FCS validity false. */
    return false;
}


/**
 * @brief   Determine if the PDU Link Quality Indication is available
 * 
 * @retval  True if available, false otherwise.
 */

bool ZigbeePacket::hasLqi()
{
    return m_hasLqi;
}


/**
 * @brief   Retrieve the LQI value
 * 
 * @retval  LQI value
 */

uint32_t ZigbeePacket::getLqi()
{
    if (m_hasLqi)
    {
        return m_lqi;
    }

    return 0;
}


/**
 * @brief   Determine if the packet timestamp is available
 * 
 * @retval  True if available, false otherwise.
 */

bool ZigbeePacket::hasTimestamp()
{
    return m_hasTimestamp;
}


/**
 * @brief   Retrieve the timestamp value
 * 
 * @retval  Timestamp value
 */

uint32_t ZigbeePacket::getTimestamp()
{
    if (hasTimestamp())
    {
        return m_timestamp;
    }

    return 0;
}