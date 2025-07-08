#include <ant/pktrecv.hpp>

using namespace whad::ant;

/******************************************
 * 
 * RawPacketReceived notification class
 * 
 *****************************************/

/**
 * @brief   Constructor, parses an AntMsg object as a RawPacketReceived message.
 * 
 * @param[in]   message Message to parse
 */

RawPacketReceived::RawPacketReceived(AntMsg &message) : AntMsg(message)
{
    /* Parse message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a RawPacketReceived message.
 * 
 * @param[in]   rf_channel     ANT RF channel on which the packet has been captured
 * @param[in]   channel_number     ANT channel number on which the packet has been captured
 * @param[in]   packet         Received packet
 */

RawPacketReceived::RawPacketReceived(uint32_t rf_channel, uint32_t channel_number, Packet &packet) : AntMsg()
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

void RawPacketReceived::setRFChannel(uint32_t rf_channel)
{
    m_rf_channel = rf_channel;
}
/**
 * @brief   Set channel number
 * 
 * @param[in]   channel_number     ANT channel number
 */

void RawPacketReceived::setChannelNumber(uint32_t channel_number)
{
    m_channel_number = channel_number;
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
 * @brief   Get the RF channel this packet has been captured on
 * 
 * @retval  RF Channel
 */

uint32_t RawPacketReceived::getRFChannel()
{
    return m_rf_channel;
}


/**
 * @brief   Get the channel number this packet has been captured on
 * 
 * @retval  Channel number
 */

uint32_t RawPacketReceived::getChannelNumber()
{
    return m_channel_number;
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
        &params
    );
}


/**
 * Extract parameters from an EsbMsg.
 */

void RawPacketReceived::unpack()
{
    whad_result_t res;
    whad_ant_recvd_packet_t params;

    res = whad_ant_raw_pdu_received_parse(
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
 * @brief   Constructor, parse a message as a PacketReceived message
 */

PacketReceived::PacketReceived(AntMsg &message) : RawPacketReceived(message)
{
    /* Parse message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a new PacketReceived message
 * 
 * @param[in]   rf_channel      ANT RF channel the packet has been captured on
 * @param[in]   channel_number  ANT channel number the packet has been captured on
 * @param[in]   packet          Captured packet
 */

PacketReceived::PacketReceived(uint32_t rf_channel, uint32_t channel_number, Packet &packet) : RawPacketReceived(rf_channel, channel_number, packet)
{
}


/**
 * @brief   Pack parameters into an AntMsg.
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
 * @brief   Extract parameters from AntMsg.
 */

void PacketReceived::unpack()
{
    whad_result_t res;
    whad_ant_recvd_packet_t params;

    res = whad_ant_pdu_received_parse(
        this->getRaw(),
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