#include <esb/pktrecv.hpp>

using namespace whad::esb;

/******************************************
 * 
 * RawPacketReceived notification class
 * 
 *****************************************/

/**
 * @brief   Constructor, parses an EsbMsg object as a RawPacketReceived message.
 * 
 * @param[in]   message Message to parse
 */

RawPacketReceived::RawPacketReceived(EsbMsg &message) : EsbMsg(message)
{
    /* Parse message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a RawPacketReceived message.
 * 
 * @param[in]   channel     ESB channel on which the packet has been captured
 * @param[in]   packet      Received packet
 */

RawPacketReceived::RawPacketReceived(uint32_t channel, Packet &packet) : EsbMsg()
{
    /* Save properties. */
    m_channel = channel;
    m_packet.set(packet);
}


/**
 * @brief   Set channel
 * 
 * @param[in]   channel     ESB channel
 */

void RawPacketReceived::setChannel(uint32_t channel)
{
    m_channel = channel;
}


/**
 * @brief   Set packet
 * 
 * @param[in]   packet      Received packet
 */

void RawPacketReceived::setPacket(Packet &packet)
{
    m_packet.set(packet);
}


/**
 * @brief   Set RSSI
 * 
 * @param[in]   rssi        Received Signal Strength Indicator
 */

void RawPacketReceived::setRssi(int32_t rssi)
{
    m_rssi = rssi;
    m_hasRssi = true;
}


/**
 * @brief   Set packet reception timestamp
 * 
 * @param[in]   timestamp   Timestamp (milliseconds)
 */

void RawPacketReceived::setTimestamp(uint32_t timestamp)
{
    m_timestamp = timestamp;
    m_hasTimestamp = true;
}


/**
 * @brief   Set destination address
 * 
 * @param[in]   address     ESB address
 */

void RawPacketReceived::setAddress(EsbAddress &address)
{
    m_hasAddress = true;
    m_address = address;
}


/**
 * @brief   Set CRC validity
 * 
 * @param[in]   validity    True if CRC is valid, false otherwise
 */

void RawPacketReceived::setCrcValidity(bool validity)
{
    m_hasCrcValidity = true;
    m_crcValidity = validity;
}


/**
 * @brief   Get the channel number this packet has been captured on
 * 
 * @retval  Channel number
 */

uint32_t RawPacketReceived::getChannel()
{
    return m_channel;
}


/**
 * @brief   Determine if RSSI is available
 * 
 * @retval  True if available, false otherwise.
 */

bool RawPacketReceived::hasRssi()
{
    return m_hasRssi;
}


/**
 * @brief   Retrieve the RSSI level
 * 
 * @retval  RSSI
 */

int32_t RawPacketReceived::getRssi()
{
    return m_rssi;
}


/**
 * @brief   Determine if a timestamp is available
 * 
 * @retval  True if available, false otherwise
 */

bool RawPacketReceived::hasTimestamp()
{
    return m_timestamp;
}


/**
 * @brief   Retrieve the associated timestamp
 * 
 * @retval  Timestamp in milliseconds
 */

uint32_t RawPacketReceived::getTimestamp()
{
    return m_timestamp;
}


/**
 * @brief   Determine if CRC validity is available
 * 
 * @retval  True if available, false otherwise
 */

bool RawPacketReceived::hasCrcValidity()
{
    return m_hasCrcValidity;
}


/**
 * @brief   Check if CRC is valid (provided if CRC validity is true)
 * 
 * @retval  True if CRC is valid, false otherwise
 */

bool RawPacketReceived::isCrcValid()
{
    return m_crcValidity;
}


/**
 * @brief   Determine if the destination address is available
 * 
 * @retval  True if available, false otherwise
 */

bool RawPacketReceived::hasAddress()
{
    return m_hasAddress;
}


/**
 * @brief   Retrieve the destination address
 * 
 * @retval  Destination address
 */

EsbAddress& RawPacketReceived::getAddress()
{
    return m_address;
}


/**
 * @brief   Retrieve the captured packet bytes
 * 
 * @retval  Captured packet
 */

Packet& RawPacketReceived::getPacket()
{
    return m_packet;
}


/**
 * @brief   Pack parameters into an EsbMsg.
 */

void RawPacketReceived::pack()
{
    whad_esb_recvd_packet_t params;

    /* Set mandatory parameters. */
    params.channel = m_channel;
    params.packet.length = m_packet.getSize();
    memcpy(params.packet.bytes, m_packet.getBytes(), m_packet.getSize());

    /* Set optional parameters. */
    if (m_hasRssi)
    {
        params.has_rssi = true;
        params.rssi = m_rssi;
    }
    else
    {
        params.has_rssi = false;
    }

    if (m_hasTimestamp)
    {
        params.has_timestamp = true;
        params.timestamp = m_timestamp;
    }
    else
    {
        params.has_timestamp = false;
    }

    if (m_hasCrcValidity)
    {
        params.has_crc_validity = true;
        params.crc_validity = m_crcValidity;
    }
    else
    {
        params.has_crc_validity = false;
    }

    if (m_hasAddress)
    {
        params.has_address = true;
        params.address.size = m_address.getLength();
        memcpy(params.address.address, m_address.getAddressBuf(), m_address.getLength());
    }
    else
    {
        params.has_address = false;
    }

    whad_esb_raw_pdu_received(
        this->getMessage(),
        &params
    );
}


/**
 * Extract parameters from an EsbMsg.
 */

void RawPacketReceived::unpack()
{
    whad_result_t res;
    whad_esb_recvd_packet_t params;

    res = whad_esb_raw_pdu_received_parse(
        this->getMessage(),
        &params
    );

    if (res == WHAD_SUCCESS)
    {
        /* Extract mandatory parameters. */
        m_channel = params.channel;
        m_packet.setBytes(params.packet.bytes, params.packet.length);

        /* Extract optional parameters. */
        if (params.has_rssi)
        {
            m_hasRssi = true;
            m_rssi = params.rssi;
        }
        else
            m_hasRssi = false;

        if (params.has_timestamp)
        {
            m_hasTimestamp = true;
            m_timestamp = params.timestamp;
        }
        else
            m_hasTimestamp = false;

        if (params.has_crc_validity)
        {
            m_hasCrcValidity = true;
            m_crcValidity = params.crc_validity;
        }
        else
            m_hasCrcValidity = false;

        if (params.has_address)
        {
            m_hasAddress = true;
            m_address.setAddress(params.address.address, params.address.size);
        }
        else
            m_hasAddress = false;
    }
    else
    {
        throw WhadMessageParsingError();
    }
}

/******************************************
 * 
 * PacketReceived notification class
 * 
 *****************************************/

/**
 * @brief   Constructor, parse a message as a PacketReceived message
 */

PacketReceived::PacketReceived(EsbMsg &message) : RawPacketReceived(message)
{
    /* Parse message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a new PacketReceived message
 * 
 * @param[in]   channel ESB channel the packet has been captured on
 * @param[in]   packet  Captured packet
 */

PacketReceived::PacketReceived(uint32_t channel, Packet &packet) : RawPacketReceived(channel, packet)
{
}


/**
 * @brief   Pack parameters into an EsbMsg.
 */

void PacketReceived::pack()
{
    whad_esb_recvd_packet_t params;

    /* Set mandatory parameters. */
    params.channel = m_channel;
    params.packet.length = m_packet.getSize();
    memcpy(params.packet.bytes, m_packet.getBytes(), m_packet.getSize());

    /* Set optional parameters. */
    if (m_hasRssi)
    {
        params.has_rssi = true;
        params.rssi = m_rssi;
    }
    else
    {
        params.has_rssi = false;
    }

    if (m_hasTimestamp)
    {
        params.has_timestamp = true;
        params.timestamp = m_timestamp;
    }
    else
    {
        params.has_timestamp = false;
    }

    if (m_hasCrcValidity)
    {
        params.has_crc_validity = true;
        params.crc_validity = m_crcValidity;
    }
    else
    {
        params.has_crc_validity = false;
    }

    if (m_hasAddress)
    {
        params.has_address = true;
        params.address.size = m_address.getLength();
        memcpy(params.address.address, m_address.getAddressBuf(), m_address.getLength());
    }
    else
    {
        params.has_address = false;
    }

    whad_esb_pdu_received(
        this->getMessage(),
        &params
    );
}


/**
 * @brief   Extract parameters from EsbMsg.
 */

void PacketReceived::unpack()
{
    whad_result_t res;
    whad_esb_recvd_packet_t params;

    res = whad_esb_pdu_received_parse(
        this->getRaw(),
        &params
    );

    if (res == WHAD_SUCCESS)
    {
        /* Extract mandatory parameters. */
        m_channel = params.channel;
        m_packet.setBytes(params.packet.bytes, params.packet.length);

        /* Extract optional parameters. */
        if (params.has_rssi)
        {
            m_hasRssi = true;
            m_rssi = params.rssi;
        }
        else
            m_hasRssi = false;

        if (params.has_timestamp)
        {
            m_hasTimestamp = true;
            m_timestamp = params.timestamp;
        }
        else
            m_hasTimestamp = false;

        if (params.has_crc_validity)
        {
            m_hasCrcValidity = true;
            m_crcValidity = params.crc_validity;
        }
        else
            m_hasCrcValidity = false;

        if (params.has_address)
        {
            m_hasAddress = true;
            m_address.setAddress(params.address.address, params.address.size);
        }
        else
            m_hasAddress = false;
    }
    else
    {
        throw WhadMessageParsingError();
    }
}