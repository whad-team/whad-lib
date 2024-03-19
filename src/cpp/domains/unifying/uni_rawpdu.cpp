#include <unifying/rawpdu.hpp>

using namespace whad::unifying;

/**
 * @brief   Parse a message as a RawPduReceived message.
 */

RawPduReceived::RawPduReceived(UnifyingMsg &message) : UnifyingMsg(message)
{
    this->unpack();
}


/**
 * @brief       RawPduReceived message constructor.
 * 
 * @param[in]   AddressType     Unifying device address
 * @param[in]   address         Specify the device address to use
 **/

RawPduReceived::RawPduReceived(UnifyingPacket& packet) : UnifyingMsg()
{
    /* Save parameters. */
    m_packet = packet;
    m_hasAddress = false;
}


/**
 * @brief   Set optional address field.
 * 
 * @param[in]   address     Unifying node address
 */

void RawPduReceived::addAddress(UnifyingAddress& address)
{
    m_hasAddress = true;
    m_address = address;
}


/**
 * @brief   Pack parameters into a UnifyingMsg object
 */

void RawPduReceived::pack()
{
    whad_unifying_recvd_packet_t packet;

    /* Fill packet. */
    packet.channel = m_packet.getChannel();

    if (m_hasAddress)
    {
        packet.has_address = true;
        packet.address.size = m_address.getLength();
        if ((packet.address.size > 0) && (packet.address.size <= 5))
        {
            memcpy(packet.address.address, m_address.getBytes(), packet.address.size);
        }
    }
    else
    {
        packet.has_address = false;
    }

    /* Optional fields. */
    if (m_packet.hasRssi())
    {
        packet.has_rssi = true;
        packet.rssi = m_packet.getRssi();
    }
    else
    {
        packet.has_rssi = false;
    }
    
    if (m_packet.hasCrcValidity())
    {
        packet.has_crc_validity = true;
        packet.crc_validity = m_packet.isCrcValid();
    }
    else
    {
        packet.has_crc_validity = false;
    }

    if (m_packet.hasTimestamp())
    {
        packet.has_timestamp = true;
        packet.timestamp = m_packet.getTimestamp();
    }
    else
    {
        packet.has_timestamp = false;
    }

    /* Copy packet PDU. */
    packet.packet.length = m_packet.getPdu().getSize();
    if ((packet.packet.length > 0) && (packet.packet.length <= 255))
    {
        memcpy(packet.packet.bytes, m_packet.getPdu().getBytes(), packet.packet.length);
    }

    whad_unifying_raw_pdu_received(
        this->getMessage(),
        &packet
    );
}


/**
 * @brief   Extract parameters from a UnifyingMsg
 */

void RawPduReceived::unpack()
{
    PDU pdu;
    whad_result_t result;
    whad_unifying_recvd_packet_t packet;

    result = whad_unifying_raw_pdu_received_parse(
        this->getMessage(),
        &packet
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_packet.setChannel(packet.channel);

        if (packet.has_address)
        {
            m_address.set(packet.address.address, packet.address.size);
        }

        if (packet.has_rssi)
        {
            m_packet.addRssi(packet.rssi);
        }

        if (packet.has_crc_validity)
        {
            m_packet.addCrcValidity(packet.crc_validity);
        }

        if (packet.has_timestamp)
        {
            m_packet.addTimestamp(packet.timestamp);
        }

        /* Copy PDU bytes. */
        pdu.setBytes(packet.packet.bytes, packet.packet.length);
        m_packet.setPdu(pdu);
    }
}


/**
 * @brief   Retrieve the received packet and its metadata
 * 
 * @retval  Reference to a UnifyingPacket
 */

UnifyingPacket& RawPduReceived::getPacket()
{
    return m_packet;
}


/**
 * @brief   Retrieve the retry counter
 * 
 * @retval  Number of retransmission counter
 */

UnifyingAddress& RawPduReceived::getAddress()
{
    return m_address;
}


/**
 * @brief   Determine if the address field has been set
 * 
 * @retval  True if set, false otherwise
 */

bool RawPduReceived::hasAddress()
{
    return m_hasAddress;
}