#include <ant/pktrecv.hpp>

using namespace whad::ant;

/******************************************
 * 
 * RawPacketReceived notification class
 * 
 *****************************************/

/**
 * @brief   Constructor, parses an AntMsg object as a PacketReceived message.
 * 
 * @param[in]   message Message to parse
 */

PacketReceived::PacketReceived(AntMsg &message) : AntMsg(message)
{
    /* Parse message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a PacketReceived message.
 * 
 * @param[in]   rf_channel     ANT RF channel on which the packet has been captured
 * @param[in]   channel_number     ANT channel number on which the packet has been captured
 * @param[in]   packet         Received packet
 */

PacketReceived::PacketReceived(uint32_t rf_channel, uint32_t channel_number, Packet &packet) : AntMsg()
{
    /* Save properties. */
    m_rf_channel = rf_channel;
    m_channel_number = channel_number;
    m_packet.set(packet);
}


/**
 * @brief   Set RF channel
 * 
 * @param[in]   rf_channel     ANT RF channel
 */

void PacketReceived::setRFChannel(uint32_t rf_channel)
{
    m_rf_channel = rf_channel;
}
/**
 * @brief   Set channel number
 * 
 * @param[in]   channel_number     ANT channel number
 */

void PacketReceived::setChannelNumber(uint32_t channel_number)
{
    m_channel_number = channel_number;
}

/**
 * @brief   Set packet
 * 
 * @param[in]   packet      Received packet
 */

void PacketReceived::setPacket(Packet &packet)
{
    m_packet.set(packet);
}


/**
 * @brief   Set RSSI
 * 
 * @param[in]   rssi        Received Signal Strength Indicator
 */

void PacketReceived::setRssi(int32_t rssi)
{
    m_rssi = rssi;
    m_hasRssi = true;
}


/**
 * @brief   Set packet reception timestamp
 * 
 * @param[in]   timestamp   Timestamp (milliseconds)
 */

void PacketReceived::setTimestamp(uint32_t timestamp)
{
    m_timestamp = timestamp;
    m_hasTimestamp = true;
}


/**
 * @brief   Set CRC validity
 * 
 * @param[in]   validity    True if CRC is valid, false otherwise
 */

void PacketReceived::setCrcValidity(bool validity)
{
    m_hasCrcValidity = true;
    m_crcValidity = validity;
}


/**
 * @brief   Get the RF channel this packet has been captured on
 * 
 * @retval  RF Channel
 */

uint32_t PacketReceived::getRFChannel()
{
    return m_rf_channel;
}


/**
 * @brief   Get the channel number this packet has been captured on
 * 
 * @retval  Channel number
 */

uint32_t PacketReceived::getChannelNumber()
{
    return m_channel_number;
}

/**
 * @brief   Determine if RSSI is available
 * 
 * @retval  True if available, false otherwise.
 */

bool PacketReceived::hasRssi()
{
    return m_hasRssi;
}


/**
 * @brief   Retrieve the RSSI level
 * 
 * @retval  RSSI
 */

int32_t PacketReceived::getRssi()
{
    return m_rssi;
}


/**
 * @brief   Determine if a timestamp is available
 * 
 * @retval  True if available, false otherwise
 */

bool PacketReceived::hasTimestamp()
{
    return m_timestamp;
}


/**
 * @brief   Retrieve the associated timestamp
 * 
 * @retval  Timestamp in milliseconds
 */

uint32_t PacketReceived::getTimestamp()
{
    return m_timestamp;
}


/**
 * @brief   Determine if CRC validity is available
 * 
 * @retval  True if available, false otherwise
 */

bool PacketReceived::hasCrcValidity()
{
    return m_hasCrcValidity;
}


/**
 * @brief   Check if CRC is valid (provided if CRC validity is true)
 * 
 * @retval  True if CRC is valid, false otherwise
 */

bool PacketReceived::isCrcValid()
{
    return m_crcValidity;
}

/**
 * @brief   Retrieve the captured packet bytes
 * 
 * @retval  Captured packet
 */

Packet& PacketReceived::getPacket()
{
    return m_packet;
}


/**
 * @brief   Pack parameters into an EsbMsg.
 */

void PacketReceived::pack()
{
    whad_ant_recvd_packet_t params;

    /* Set mandatory parameters. */
    params.rf_channel = m_rf_channel;
    params.channel_number = m_channel_number;

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


    whad_ant_pdu_received(
        this->getMessage(),
        &params
    );
}


/**
 * Extract parameters from an AntMsg.
 */

void PacketReceived::unpack()
{
    whad_result_t res;
    whad_ant_recvd_packet_t params;

    res = whad_ant_pdu_received_parse(
        this->getMessage(),
        &params
    );

    if (res == WHAD_SUCCESS)
    {
        /* Extract mandatory parameters. */
        m_rf_channel = params.rf_channel;
        m_channel_number = params.channel_number;

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
 * @brief   Constructor, parse a message as a RawPacketReceived message
 */

RawPacketReceived::RawPacketReceived(AntMsg &message) : PacketReceived(message)
{
    /* Parse message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a new RawPacketReceived message
 * 
 * @param[in]   rf_channel      ANT RF channel the packet has been captured on
 * @param[in]   channel_number  ANT channel number the packet has been captured on
 * @param[in]   packet          Captured packet
 */

RawPacketReceived::RawPacketReceived(uint32_t rf_channel, uint32_t channel_number, Packet &packet) : PacketReceived(rf_channel, channel_number, packet)
{
}


/**
 * @brief   Set CRC value
 * 
 * @param[in]   channel_number     ANT packet CRC value
 */

void RawPacketReceived::setCrc(uint32_t crc) {
    this->m_crc = crc;
}


/**
 * @brief   Retrieve the captured CRC
 * 
 * @retval  Captured CRC
 */

uint32_t RawPacketReceived::getCrc() {
    return this->m_crc;
}

/**
 * @brief   Pack parameters into an AntMsg.
 */

void RawPacketReceived::pack()
{
    whad_ant_recvd_packet_t params;

    /* Set mandatory parameters. */
    params.rf_channel = m_rf_channel;
    params.channel_number = m_channel_number;

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


    whad_ant_raw_pdu_received(
        this->getMessage(),
        &params, 
        m_crc
    );
}


/**
 * @brief   Extract parameters from AntMsg.
 */

void RawPacketReceived::unpack()
{
    whad_result_t res;
    whad_ant_recvd_packet_t params;

    res = whad_ant_raw_pdu_received_parse(
        this->getRaw(),
        &params, 
        &m_crc
    );

    if (res == WHAD_SUCCESS)
    {
        /* Extract mandatory parameters. */
        m_rf_channel = params.rf_channel;
        m_channel_number = params.channel_number;

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
    }
    else
    {
        throw WhadMessageParsingError();
    }
}