#include "dot15d4/packet.hpp"

using namespace whad::dot15d4;

Dot15d4Packet::Dot15d4Packet()
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
 * @brief   Create a Dot15d4Packet object with the given channel, PDU and FCS values
 * 
 * @param[in]   channel     ZigBee channel on which the PDU has been received
 * @param[in]   pPdu        Pointer to a buffer containing the PDU bytes
 * @param[in]   length      PDU length in bytes
 * @param[in]   fcs         Frame Check Sequence value
 */

Dot15d4Packet::Dot15d4Packet(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs)
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
 * @brief   Create a Dot15d4Packet object with the given channel, PDU and FCS values
 * 
 * @param[in]   channel     ZigBee channel on which the PDU has been received
 * @param[in]   pPdu        Pointer to a buffer containing the PDU bytes
 * @param[in]   length      PDU length in bytes
 * @param[in]   fcs         Frame Check Sequence value
 * @param[in]   rssi        Received Signal Strength Indicator value (in dBm)
 */

Dot15d4Packet::Dot15d4Packet(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs,
        int32_t rssi) : Dot15d4Packet(channel, pPdu, length, fcs)
{
    /* Add RSSI. */
    addRssi(rssi);
}


/**
 * @brief   Create a Dot15d4Packet object with the given channel, PDU and FCS values
 * 
 * @param[in]   channel     ZigBee channel on which the PDU has been received
 * @param[in]   pPdu        Pointer to a buffer containing the PDU bytes
 * @param[in]   length      PDU length in bytes
 * @param[in]   fcs         Frame Check Sequence value
 * @param[in]   rssi        Received Signal Strength Indicator value (in dBm)
 * @param[in]   timestamp   Timestamp (in seconds) at which the PDU has been received
 */

Dot15d4Packet::Dot15d4Packet(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs,
        int32_t rssi, uint32_t timestamp) : Dot15d4Packet(channel, pPdu, length, fcs,
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

void Dot15d4Packet::setChannel(uint32_t channel)
{
    m_channel = channel;
}

/**
 * @brief   Set zigbee packet channel FCS value
 * 
 * @param[in]   fcs         Frame Check Sequence value for this packet
 */

void Dot15d4Packet::setFcs(uint32_t fcs)
{
    m_fcs = fcs;
}


/**
 * @brief   Set zigbee packet PDU
 * 
 * @param[in]   pdu         packet PDU
 */

void Dot15d4Packet::setPdu(PDU& pdu)
{
    m_pdu.setBytes(pdu.getBytes(), pdu.getSize());
}


/**
 * @brief   Add RSSI to the received PDU
 * 
 * @param[in]   rssi    Received Signal Strength Indicator in dBm
 */

void Dot15d4Packet::addRssi(int32_t rssi)
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

void Dot15d4Packet::addTimestamp(uint32_t timestamp)
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

void Dot15d4Packet::addFcsValidity(bool valid)
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

void Dot15d4Packet::addLqi(uint32_t lqi)
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

uint32_t Dot15d4Packet::getChannel()
{
    return m_channel;
}


/**
 * @brief   Retrieve the received PDU
 * 
 * @retval  Received PDU
 */

PDU& Dot15d4Packet::getPdu()
{
    return m_pdu;
}


/**
 * @brief   Retrieve the Frame Check Sequence value
 * 
 * @retval  FCS value
 * @retval  0 if not available
 */

uint32_t Dot15d4Packet::getFcs()
{
    return m_fcs;
}


/**
 * @brief   Determine if the PDU has RSSI information available
 * 
 * @return  True if RSSI is available, false otherwise
 */

bool Dot15d4Packet::hasRssi()
{
    return m_hasRssi;
}


/**
 * @brief   Retrieve the PDU RSSI value
 * 
 * @retval  RSSI value
 */

int32_t Dot15d4Packet::getRssi()
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

bool Dot15d4Packet::hasFcsValidity()
{
    return m_hasFcsValidity;
}


/**
 * @brief   Determine if the PDU FCS value is valid
 * 
 * @retval  FCS validity
 */

bool Dot15d4Packet::isFcsValid()
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

bool Dot15d4Packet::hasLqi()
{
    return m_hasLqi;
}


/**
 * @brief   Retrieve the LQI value
 * 
 * @retval  LQI value
 */

uint32_t Dot15d4Packet::getLqi()
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

bool Dot15d4Packet::hasTimestamp()
{
    return m_hasTimestamp;
}


/**
 * @brief   Retrieve the timestamp value
 * 
 * @retval  Timestamp value
 */

uint32_t Dot15d4Packet::getTimestamp()
{
    if (hasTimestamp())
    {
        return m_timestamp;
    }

    return 0;
}