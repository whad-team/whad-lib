#include <esb/pktrecv.hpp>

using namespace whad::esb;

/** RawPacketReceived **/

RawPacketReceived::RawPacketReceived(EsbMsg &message) : EsbMsg(message)
{
    /* Parse message. */
    this->parse();
}

RawPacketReceived::RawPacketReceived(uint32_t channel, Packet &packet) : EsbMsg()
{
    /* Save properties. */
    m_channel = channel;
    m_packet.set(packet);

    /* Save into message. */
    this->update();
}

void RawPacketReceived::setChannel(uint32_t channel)
{
    m_channel = channel;

    /* Save into message. */
    this->update();
}

void RawPacketReceived::setPacket(Packet &packet)
{
    m_packet.set(packet);

    /* Save into message. */
    this->update();
}

void RawPacketReceived::setRssi(int32_t rssi)
{
    m_rssi = rssi;
    m_hasRssi = true;

    /* Save into message. */
    this->update();
}

void RawPacketReceived::setTimestamp(uint32_t timestamp)
{
    m_timestamp = timestamp;
    m_hasTimestamp = true;

    /* Save into message. */
    this->update();
}

void RawPacketReceived::setAddress(EsbAddress &address)
{
    m_hasAddress = true;
    m_address = address;

    /* Save into message. */
    this->update();
}

void RawPacketReceived::setCrcValidity(bool validity)
{
    m_hasCrcValidity = true;
    m_crcValidity = validity;

    /* Save into message. */
    this->update();
}

uint32_t RawPacketReceived::getChannel()
{
    return m_channel;
}

bool RawPacketReceived::hasRssi()
{
    return m_hasRssi;
}

int32_t RawPacketReceived::getRssi()
{
    return m_rssi;
}

bool RawPacketReceived::hasTimestamp()
{
    return m_timestamp;
}

uint32_t RawPacketReceived::getTimestamp()
{
    return m_timestamp;
}

bool RawPacketReceived::hasCrcValidity()
{
    return m_hasCrcValidity;
}

bool RawPacketReceived::isCrcValid()
{
    return m_crcValidity;
}

bool RawPacketReceived::hasAddress()
{
    return m_hasAddress;
}

EsbAddress& RawPacketReceived::getAddress()
{
    return m_address;
}

Packet& RawPacketReceived::getPacket()
{
    return m_packet;
}



void RawPacketReceived::update()
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
        this->getRaw(),
        &params
    );
}

void RawPacketReceived::parse()
{
    whad_result_t res;
    whad_esb_recvd_packet_t params;

    res = whad_esb_raw_pdu_received_parse(
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


/** PacketReceived **/

PacketReceived::PacketReceived(EsbMsg &message) : RawPacketReceived(message)
{
    /* Parse message. */
    this->parse();
}

PacketReceived::PacketReceived(uint32_t channel, Packet &packet) : RawPacketReceived(channel, packet)
{
    /* Save into message. */
    this->update();
}

void PacketReceived::update()
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
        this->getRaw(),
        &params
    );
}

void PacketReceived::parse()
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