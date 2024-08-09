#include <esb/sendpkt.hpp>

using namespace whad::esb;

/**
 * @brief   Constructor, parse an EsbMsg as a SendPacket message.
 */

SendPacket::SendPacket(EsbMsg &message) : EsbMsg(message)
{
    this->unpack();
}


/**
 * @brief   Constructor, create a SendPacket message.
 * 
 * @param[in]   channel     Channel on which the packet has to be sent
 * @param[in]   retries     Number of max retransmission retries
 * @param[in]   packet      Packet to send
 */

SendPacket::SendPacket(uint32_t channel, uint32_t retries, Packet &packet)
{
    /* Save properties. */
    this->m_channel = channel;
    this->m_retries = retries;
    this->m_packet.set(packet);
}


/**
 * @brief   Pack parameters into an EsbMsg.
 */

void SendPacket::pack()
{
    /* Craft message. */
    whad_esb_send(
        this->getMessage(),
        m_channel,
        m_retries,
        m_packet.getBytes(),
        m_packet.getSize()
    );
}


/**
 * @brief   Extract parameters from EsbMsg.
 */

void SendPacket::unpack()
{
    whad_result_t res;
    whad_esb_send_params_t params;
    Packet pkt;

    res = whad_esb_send_parse(
        this->getRaw(),
        &params
    );

    if (res == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }

    /* Set properties accordingly. */
    m_channel = params.channel;
    m_retries = params.retr_count;
    pkt = Packet(params.packet.bytes, params.packet.length);
    m_packet.set(pkt);
}


/**
 * @brief   Get the channel number
 * 
 * @retval  Channel number
 */

uint32_t SendPacket::getChannel()
{
    return m_channel;
}


/**
 * @brief   Get the maximum retransmission count
 * 
 * @retval  Maximum number of retransmissions
 */

uint32_t SendPacket::getRetrCount()
{
    return m_retries;
}


/**
 * @brief   Get the packet to send
 * 
 * @retval  Packet to send
 */

Packet& SendPacket::getPacket()
{
    return m_packet;
}


/**
 * @brief   Constructor, parse an EsbMsg into a SendPacketRaw message.
 * 
 * @param[in]   message     Message to parse
 */

SendPacketRaw::SendPacketRaw(EsbMsg &message) : EsbMsg(message)
{
    this->unpack();
}


/**
 * @brief   Constructor, create a SendPacketRaw message.
 * 
 * @param[in]   channel     Channel on which the packet has to be sent
 * @param[in]   retries     Number of max retransmission retries
 * @param[in]   packet      Packet to send
 */

SendPacketRaw::SendPacketRaw(uint32_t channel, uint32_t retries, Packet &packet)
{ 
    m_channel = channel;
    m_retries = retries;
    m_packet.set(packet);
}


/**
 * @brief   Extract parameters from an EsbMsg.
 */

void SendPacketRaw::unpack()
{
    whad_result_t res;
    whad_esb_send_params_t params;

    res = whad_esb_send_raw_parse(
        this->getMessage(),
        &params
    );

    if (res == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }

    /* Set properties accordingly. */
    m_channel = params.channel;
    m_retries = params.retr_count;
    m_packet.setBytes(params.packet.bytes, params.packet.length);
}


/**
 * @brief   Pack parameters into an EsbMsg.
 */

void SendPacketRaw::pack()
{
    /* Craft message. */
    whad_esb_send_raw(
        this->getMessage(),
        m_channel,
        m_retries,
        m_packet.getBytes(),
        m_packet.getSize()
    );
}

/**
 * @brief   Get the channel number
 * 
 * @retval  Channel number
 */

uint32_t SendPacketRaw::getChannel()
{
    return m_channel;
}


/**
 * @brief   Get the maximum retransmission count
 * 
 * @retval  Maximum number of retransmissions
 */

uint32_t SendPacketRaw::getRetrCount()
{
    return m_retries;
}


/**
 * @brief   Get the packet to send
 * 
 * @retval  Packet to send
 */

Packet& SendPacketRaw::getPacket()
{
    return m_packet;
}