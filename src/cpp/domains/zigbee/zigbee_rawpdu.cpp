#include "zigbee/rawpdu.hpp"

using namespace whad::zigbee;

/**
 * @brief   Create a RawPduReceived message from a ZigbeeMsg message.
 * 
 * @param[in]   message     Reference to a ZigbeeMessage
 */

RawPduReceived::RawPduReceived(ZigbeeMsg &message) : ZigbeeMsg(message)
{
    this->unpack();
}


/**
 * @brief   Create a RawPduReceived message from a zigbee packet
 * 
 * @param[in]   packet      Zigbee packet to include in the message
 */

RawPduReceived::RawPduReceived(ZigbeePacket &packet)
{
    m_packet = packet;
}


/**
 * @brief   Pack parameters into a ZigbeeMsg object
 */

void RawPduReceived::pack()
{
    whad_zigbee_recvd_packet_t packet;

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
    
    /* Copy packet bytes. */
    packet.packet.length = m_packet.getPdu().getSize();
    if ((packet.packet.length > 0) && (packet.packet.length <= 255))
    {
        memcpy(packet.packet.bytes, m_packet.getPdu().getBytes(), packet.packet.length);
    }

    /* Craft message with packet info. */
    whad_zigbee_raw_pdu_received(
        this->getMessage(),
        &packet
    );
}


/**
 * @brief   Extract parameters from a ZigbeeMsg object
 */

void RawPduReceived::unpack()
{
    PDU pdu;
    whad_result_t result;
    whad_zigbee_recvd_packet_t packet;

    result = whad_zigbee_pdu_received_parse(
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
    }
}


/**
 * @brief   Retrieve the Zigbee packet
 * 
 * @retval  Reference to a zigbee packet, including PDU and metadata
 */

ZigbeePacket& RawPduReceived::getPacket()
{
    return m_packet;
}