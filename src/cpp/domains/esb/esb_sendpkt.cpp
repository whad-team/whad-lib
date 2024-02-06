#include <esb/sendpkt.hpp>

using namespace whad::esb;

/** PacketSend **/

SendPacket::SendPacket(EsbMsg &message) : EsbMsg(message)
{
}

SendPacket::SendPacket(uint32_t channel, uint32_t retries, Packet &packet)
{
    /* Save properties. */
    this->m_channel = channel;
    this->m_retries = retries;
    this->m_packet.set(packet);

    /* Craft message. */
    whad_esb_send(
        this->getRaw(),
        channel,
        retries,
        packet.getBytes(),
        packet.getSize()
    );
}

bool SendPacket::parse()
{
    whad_result_t res;
    whad_esb_send_params_t params;
    Packet pkt;

    res = whad_esb_send_parse(
        this->getRaw(),
        &params
    );

    if (res == WHAD_ERROR)
        return WHAD_ERROR;

    /* Set properties accordingly. */
    m_channel = params.channel;
    m_retries = params.retr_count;
    pkt = Packet(params.packet.bytes, params.packet.length);
    m_packet.set(pkt);

    /* Success. */
    return true;
}

uint32_t SendPacket::getChannel()
{
    if (this->parse())
    {
        return m_channel;
    }
    else
    {
        throw whad::WhadMessageParsingError();
    }
}

uint32_t SendPacket::getRetrCount()
{
    if (this->parse())
    {
        return m_retries;
    }
    else
    {
        throw whad::WhadMessageParsingError();
    }
}

Packet& SendPacket::getPacket()
{
    if (this->parse())
    {
        return m_packet;
    }
    else
    {
        throw whad::WhadMessageParsingError();
    }
}

SendPacketRaw::SendPacketRaw(EsbMsg &message) : SendPacket(message)
{
}

SendPacketRaw::SendPacketRaw(uint32_t channel, uint32_t retries, Packet &packet): SendPacket(channel, retries, packet)
{
    /* Save properties. */
    this->m_channel = channel;
    this->m_retries = retries;
    this->m_packet.set(packet);

    /* Craft message. */
    whad_esb_send_raw(
        this->getRaw(),
        channel,
        retries,
        packet.getBytes(),
        packet.getSize()
    );   
}

bool SendPacketRaw::parse()
{
    whad_result_t res;
    whad_esb_send_params_t params;
    Packet pkt;

    res = whad_esb_send_raw_parse(
        this->getRaw(),
        &params
    );

    if (res == WHAD_ERROR)
        return WHAD_ERROR;

    /* Set properties accordingly. */
    m_channel = params.channel;
    m_retries = params.retr_count;
    pkt = Packet(params.packet.bytes, params.packet.length);
    m_packet.set(pkt);

    /* Success. */
    return true;
}