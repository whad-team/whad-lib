#include "dot15d4/pdu.hpp"

using namespace whad::dot15d4;

/**
 * @brief   Create a PduReceived message from a Dot15d4Msg message.
 * 
 * @param[in]   message     Reference to a ZigbeeMessage
 */

PduReceived::PduReceived(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief   Create a PduReceived message from a dot15d4 packet
 * 
 * @param[in]   packet      Zigbee packet to include in the message
 */

PduReceived::PduReceived(Dot15d4Packet &packet)
{
    m_packet = packet;
}


/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void PduReceived::pack()
{
    whad_dot15d4_recvd_packet_t packet;

    /* Populate packet. */
    packet.channel = m_packet.getChannel();
    packet.fcs = m_packet.getFcs();

    /* Add optional RSSI. */
    if (m_packet.hasRssi())
    {
        packet.has_rssi = true;
        packet.rssi = m_packet.getRssi();
    }
    else
    {
        packet.has_rssi = false;
    }

    /* Add optional FCS validity. */
    if (m_packet.hasFcsValidity())
    {
        packet.has_fcs_validity = true;
        packet.fcs_validity = m_packet.isFcsValid();
    }
    else
    {
        packet.has_fcs_validity = false;
    }

    /* Add optional LQI. */
    if (m_packet.hasLqi())
    {
        packet.has_lqi = true;
        packet.lqi = m_packet.getLqi();
    }
    else
    {
        packet.has_lqi = false;
    }

    /* Add optional timestamp. */
    if (m_packet.hasTimestamp())
    {
        packet.has_timestamp = true;
        packet.timestamp = m_packet.getTimestamp();
    }
    else
    {
        packet.has_timestamp = false;
    }
    

    /* Add optional ASN. */
    if (m_packet.hasAsn())
    {
        packet.has_asn = true;
        packet.asn = m_packet.getAsn();
    }
    else
    {
        packet.has_asn = false;
    }
    

    /* Add optional Start of Slot Timestamp. */
    if (m_packet.hasStartOfSlotTimestamp())
    {
        packet.has_start_of_slot_timestamp = true;
        packet.start_of_slot_timestamp = m_packet.getStartOfSlotTimestamp();
    }
    else
    {
        packet.has_start_of_slot_timestamp = false;
    }

    /* Add optional Time slot. */
    if (m_packet.hasTimeSlot())
    {
        packet.has_time_slot = true;
        packet.time_slot = m_packet.getTimeSlot();
    }
    else
    {
        packet.has_time_slot = false;
    }
    
    /* Add optional Base Channel Frequency. */
    if (m_packet.hasBaseChannelFrequency())
    {
        packet.has_base_channel_frequency = true;
        packet.base_channel_frequency = m_packet.getBaseChannelFrequency();
    }
    else
    {
        packet.has_base_channel_frequency = false;
    }

    /* Add optional number of channels. */
    if (m_packet.hasNumberOfChannels())
    {
        packet.has_number_of_channels = true;
        packet.number_of_channels = m_packet.getNumberOfChannels();
    }
    else
    {
        packet.has_number_of_channels = false;
    }
    
    /* Add optional Channel spacing. */
    if (m_packet.hasChannelSpacing())
    {
        packet.has_channel_spacing = true;
        packet.channel_spacing = m_packet.getChannelSpacing();
    }
    else
    {
        packet.has_channel_spacing = false;
    }
    
    
    /* Copy packet bytes. */
    packet.packet.length = m_packet.getPdu().getSize();
    if ((packet.packet.length > 0) && (packet.packet.length <= 255))
    {
        memcpy(packet.packet.bytes, m_packet.getPdu().getBytes(), packet.packet.length);
    }

    /* Craft message with packet info. */
    whad_dot15d4_pdu_received(
        this->getMessage(),
        &packet
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg object
 */

void PduReceived::unpack()
{
    PDU pdu;
    whad_result_t result;
    whad_dot15d4_recvd_packet_t packet;

    result = whad_dot15d4_pdu_received_parse(
        this->getMessage(),
        &packet
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
    else
    {
        /* Populate our Zigbee packet. */
        m_packet.setChannel(packet.channel);
        m_packet.setFcs(packet.fcs);
        pdu.setBytes(packet.packet.bytes, packet.packet.length);
        m_packet.setPdu(pdu);

        /* Set optional RSSI. */
        if (packet.has_rssi)
        {
            m_packet.addRssi(packet.rssi);
        }

        /* Set optional FCS validity. */
        if (packet.has_fcs_validity)
        {
            m_packet.addFcsValidity(packet.fcs_validity);
        }

        /* Set optional LQI. */
        if (packet.has_lqi)
        {
            m_packet.addLqi(packet.lqi);
        }

        /* Set optional timestamp. */
        if (packet.has_timestamp)
        {
            m_packet.addTimestamp(packet.timestamp);
        }

        /* Set optional ASN */
        if (packet.has_asn)
        {
            m_packet.addAsn(packet.asn);
        }

        /* Set optional Start of Slot Timestamp */
        if (packet.has_start_of_slot_timestamp)
        {
            m_packet.addStartOfSlotTimestamp(packet.start_of_slot_timestamp);
        }

        /* Set optional time slot */
        if (packet.has_time_slot)
        {
            m_packet.addTimeSlot(packet.time_slot);
        }

        /* Set optional base channel frequency */
        if (packet.has_base_channel_frequency)
        {
            m_packet.addBaseChannelFrequency(packet.base_channel_frequency);
        }

        /* Set optional number of channels  */
        if (packet.has_number_of_channels)
        {
            m_packet.addNumberOfChannels(packet.number_of_channels);
        }

        /* Set optional channel spacing */
        if (packet.has_channel_spacing)
        {
            m_packet.addChannelSpacing(packet.channel_spacing);
        }

    }
}


/**
 * @brief   Retrieve the Zigbee packet
 * 
 * @retval  Reference to a dot15d4 packet, including PDU and metadata
 */

Dot15d4Packet& PduReceived::getPacket()
{
    return m_packet;
}