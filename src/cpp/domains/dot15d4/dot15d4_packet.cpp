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


    /* We don't have any TSCH-related metadata. */
    m_hasAsn = false;
    m_hasStartOfSlotTimestamp = false;
    m_hasTimeSlot = false;
    m_hasBaseChannelFrequency = false;
    m_hasNumberOfChannels = false;
    m_hasChannelSpacing = false;


    m_asn = 0;
    m_startOfSlotTimestamp = 0;
    m_timeSlot = 0;
    m_baseChannelFrequency = 0;
    m_numberOfChannels = 0;
    m_channelSpacing = 0;
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

    /* We don't have any TSCH-related metadata. */
    m_hasAsn = false;
    m_hasStartOfSlotTimestamp = false;
    m_hasTimeSlot = false;
    m_hasBaseChannelFrequency = false;
    m_hasNumberOfChannels = false;
    m_hasChannelSpacing = false;


    m_asn = 0;
    m_startOfSlotTimestamp = 0;
    m_timeSlot = 0;
    m_baseChannelFrequency = 0;
    m_numberOfChannels = 0;
    m_channelSpacing = 0;
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
 * @param[in]   channel                         ZigBee channel on which the PDU has been received
 * @param[in]   pPdu                            Pointer to a buffer containing the PDU bytes
 * @param[in]   length                          PDU length in bytes
 * @param[in]   fcs                             Frame Check Sequence value
 * @param[in]   rssi                            Received Signal Strength Indicator value (in dBm)
 * @param[in]   timestamp                       Timestamp (in seconds) at which the PDU has been received
 * @param[in]   asn                             Absolute Slot Number
 * @param[in]   start_of_slot_timestamp         Timestamp (in seconds) at which the last slot has been started
 * @param[in]   time_slot                       Number of the last slot

 */

Dot15d4Packet::Dot15d4Packet(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs,
                int32_t rssi, uint32_t timestamp, uint64_t asn, uint32_t start_of_slot_timestamp, 
                uint64_t time_slot) : Dot15d4Packet(channel, pPdu, length, fcs, rssi, timestamp)
{
    /* Add ASN. */
    addAsn(asn);
    /* Add Start of Slot Timestamp. */
    addStartOfSlotTimestamp(asn);
    /* Add Time Slot. */
    addTimeSlot(time_slot);
}


/**
 * @brief   Create a Dot15d4Packet object with the given channel, PDU and FCS values
 * 
 * @param[in]   channel                         ZigBee channel on which the PDU has been received
 * @param[in]   pPdu                            Pointer to a buffer containing the PDU bytes
 * @param[in]   length                          PDU length in bytes
 * @param[in]   fcs                             Frame Check Sequence value
 * @param[in]   rssi                            Received Signal Strength Indicator value (in dBm)
 * @param[in]   timestamp                       Timestamp (in seconds) at which the PDU has been received
 * @param[in]   asn                             Absolute Slot Number
 * @param[in]   start_of_slot_timestamp         Timestamp (in seconds) at which the last slot has been started
 * @param[in]   time_slot                       Number of the last slot

 */

Dot15d4Packet::Dot15d4Packet(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs,
                int32_t rssi, uint32_t timestamp, uint64_t asn, uint32_t start_of_slot_timestamp, 
                uint64_t time_slot, uint32_t base_channel_frequency, uint32_t number_of_channels, 
                uint32_t channel_spacing) : Dot15d4Packet(channel, pPdu, length, fcs, rssi, timestamp, 
                asn, start_of_slot_timestamp, time_slot)
{
    /* Add Base Channel Frequency. */
    addBaseChannelFrequency(base_channel_frequency);
    /* Add Number of Channels. */
    addNumberOfChannels(number_of_channels);
    /* Add Channel Spacing. */
    addChannelSpacing(channel_spacing);
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
 * @brief   Set dot15d4 packet channel value
 * 
 * @param[in]   channel     Zigbee channel this packet has been received on
 */

void Dot15d4Packet::setChannel(uint32_t channel)
{
    m_channel = channel;
}

/**
 * @brief   Set dot15d4 packet channel FCS value
 * 
 * @param[in]   fcs         Frame Check Sequence value for this packet
 */

void Dot15d4Packet::setFcs(uint32_t fcs)
{
    m_fcs = fcs;
}


/**
 * @brief   Set dot15d4 packet PDU
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



/**
 * @brief Add Absolute Slot Number (ASN) to the received PDU
 *
 * @param[in]   asn    Absolute Slot Number
*/
void Dot15d4Packet::addAsn(uint64_t asn)
{
    /* Add ASN.*/
    m_hasAsn = true;
    m_asn = asn;
}
/**
 * @brief Add Start of Slot Timestamp to the received PDU
 *
 * @param[in]   start_of_slot_timestamp    Start of Slot timestamp (in seconds)
*/
void Dot15d4Packet::addStartOfSlotTimestamp(uint32_t start_of_slot_timestamp)
{
    /* Add Start of slot timestamp.*/
    m_hasStartOfSlotTimestamp = true;
    m_startOfSlotTimestamp = start_of_slot_timestamp;
}
/**
 * @brief Add time slot to the received PDU
 *
 * @param[in]   time_slot    Time Slot
*/
void Dot15d4Packet::addTimeSlot(uint64_t time_slot)
{
    /* Add time slot.*/
    m_hasTimeSlot = true;
    m_timeSlot = time_slot;

}
/**
 * @brief Add base channel frequency to the received PDU
 *
 * @param[in]   base_channel_frequency    Frequency associated with the base channel (in Hz)
*/
void Dot15d4Packet::addBaseChannelFrequency(uint32_t base_channel_frequency)
{
    /* Add base channel frequency.*/
    m_hasBaseChannelFrequency = true;
    m_baseChannelFrequency = base_channel_frequency;
}
/**
 * @brief Add number of channels to the received PDU
 *
 * @param[in]   number_of_channels  Number of channels in the channel map
*/
void Dot15d4Packet::addNumberOfChannels(uint32_t number_of_channels)
{
    /* Add number of channels.*/
    m_hasNumberOfChannels = true;
    m_numberOfChannels = number_of_channels;

}
/**
 * @brief Add channel spacing (in Hz) to the received PDU
 *
 * @param[in]   channel_spacing    Channel Spacing (in Hz)
*/
void Dot15d4Packet::addChannelSpacing(uint32_t channel_spacing)
{
    /* Add Channel Spacing.*/
    m_hasChannelSpacing = true;
    m_channelSpacing = channel_spacing;
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


/**
 * @brief   Retrieve the Absolute Slot Number
 * 
 * @retval  Absolute Slot Number (ASN)
 */
uint64_t Dot15d4Packet::getAsn() {
    if (hasAsn()) {
        return m_asn ;
    }
    return 0;
}

/**
 * @brief   Retrieve the timestamp associated with the start of slot
 * 
 * @retval Start of slot Timestamp value
 */
uint32_t Dot15d4Packet::getStartOfSlotTimestamp() {
    if (hasStartOfSlotTimestamp()) {
        return m_startOfSlotTimestamp ;
    }
    return 0;
}


/**
 * @brief   Retrieve the current timeslot
 * 
 * @retval  Time slot
 */
uint64_t Dot15d4Packet::getTimeSlot() {
    if (hasTimeSlot()) {
        return m_timeSlot ;
    }
    return 0;
}


/**
 * @brief   Retrieve the base channel frequency
 * 
 * @retval  Base Channel Frequency (in Hz)
 */
uint32_t Dot15d4Packet::getBaseChannelFrequency() {
    if (hasBaseChannelFrequency()) {
        return m_baseChannelFrequency ;
    }
    return 0;
}

/**
 * @brief   Retrieve the number of channels
 * 
 * @retval  Number of channels
*/
uint32_t Dot15d4Packet::getNumberOfChannels() {
    if (hasNumberOfChannels()) {
        return m_numberOfChannels ;
    }
    return 0;
}


/**
 * @brief   Retrieve the channel spacing
 * 
 * @retval  Channel spacing
 */
uint32_t Dot15d4Packet::getChannelSpacing() {
    if (hasChannelSpacing()) {
        return m_channelSpacing ;
    }
    return 0;
}


/**
 * @brief   Determine if the Absolute Slot Number (ASN) is available
 * 
 * @retval  True if available, false otherwise.
 */
bool Dot15d4Packet::hasAsn() {
    return m_hasAsn ;
}

/**
 * @brief   Determine if the Start of slot Timestamp is available
 * 
 * @retval  True if available, false otherwise.
 */
bool Dot15d4Packet::hasStartOfSlotTimestamp() {
    return m_hasStartOfSlotTimestamp ;
}

/**
 * @brief   Determine if the Time Slot is available
 * 
 * @retval  True if available, false otherwise.
 */
bool Dot15d4Packet::hasTimeSlot() {
    return m_hasTimeSlot ;
}

/**
 * @brief   Determine if the Base Channel Frequency is available
 * 
 * @retval  True if available, false otherwise.
 */
bool Dot15d4Packet::hasBaseChannelFrequency() {
    return m_hasBaseChannelFrequency ;
}

/**
 * @brief   Determine if the Number of channels is available
 * 
 * @retval  True if available, false otherwise.
 */
bool Dot15d4Packet::hasNumberOfChannels() {
    return m_hasNumberOfChannels;
}

/**
 * @brief   Determine if the Channel spacing is available
 * 
 * @retval  True if available, false otherwise.
 */
bool Dot15d4Packet::hasChannelSpacing() {
    return m_hasChannelSpacing;
}