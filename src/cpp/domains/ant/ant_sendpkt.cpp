#include <ant/sendpkt.hpp>

using namespace whad::ant;

/**
 * @brief   Constructor, parse an AntMsg as a SendPacket message.
 */

SendPacket::SendPacket(AntMsg &message) : AntMsg(message)
{
    this->unpack();
}


/**
 * @brief   Constructor, create a SendPacket message.
 * 
 * @param[in]   rf_channel              Channel on which the packet has to be sent
 * @param[in]   channel_number          Channel number on which the packet has to be sent
 * @param[in]   packet                  Packet to send
 */

SendPacket::SendPacket(uint32_t rf_channel, uint32_t channel_number, Packet &packet)
{
    /* Save properties. */
    this->m_rf_channel = rf_channel;
    this->m_channel_number = channel_number;
    this->m_packet.set(packet);
}


/**
 * @brief   Pack parameters into an AntMsg.
 */

void SendPacket::pack()
{
    /* Craft message. */
    whad_ant_send(
        this->getMessage(),
        this->m_rf_channel,
        this->m_channel_number,
        this->m_packet.getBytes(),
        this->m_packet.getSize()
    );
}


/**
 * @brief   Extract parameters from AntMsg.
 */

void SendPacket::unpack()
{
    whad_result_t res;
    whad_ant_send_params_t params;
    Packet pkt;

    res = whad_ant_send_parse(
        this->getRaw(),
        &params
    );

    if (res == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }

    /* Set properties accordingly. */
    this->m_rf_channel = params.rf_channel;
    this->m_channel_number = params.channel_number;
    pkt = Packet(params.packet.bytes, params.packet.length);
    m_packet.set(pkt);
}


/**
 * @brief   Get the channel number
 * 
 * @retval  Channel number
 */

uint32_t SendPacket::getChannelNumber()
{
    return this->m_channel_number;
}


/**
 * @brief   Get the RF Channel
 * 
 * @retval  RF channel
 */

uint32_t SendPacket::getRFChannel()
{
    return this->m_rf_channel;
}


/**
 * @brief   Get the packet to send
 * 
 * @retval  Packet to send
 */

Packet& SendPacket::getPacket()
{
    return this->m_packet;
}


/**
 * @brief   Constructor, parse an AntMsg into a SendPacketRaw message.
 * 
 * @param[in]   message     Message to parse
 */

SendPacketRaw::SendPacketRaw(AntMsg &message) : AntMsg(message)
{
    this->unpack();
}


/**
 * @brief   Constructor, create a SendPacketRaw message.
 * 
 * @param[in]   rf_channel           RF Channel on which the packet has to be sent
 * @param[in]   channel_number       Channel Number to use 
 * @param[in]   packet               Packet to send
 */

SendPacketRaw::SendPacketRaw(uint32_t rf_channel, uint32_t channel_number, Packet &packet)
{ 
    this->m_rf_channel = rf_channel;
    this->m_channel_number = channel_number;
    this->m_packet.set(packet);
}


/**
 * @brief   Extract parameters from an AntMsg.
 */

void SendPacketRaw::unpack()
{
    whad_result_t res;
    whad_ant_send_params_t params;

    res = whad_ant_send_raw_parse(
        this->getMessage(),
        &params
    );

    if (res == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }

    /* Set properties accordingly. */
    this->m_rf_channel = params.rf_channel;
    this->m_channel_number = params.channel_number;
    this->m_packet.setBytes(params.packet.bytes, params.packet.length);
}


/**
 * @brief   Pack parameters into an AntMsg.
 */

void SendPacketRaw::pack()
{
    /* Craft message. */
    whad_ant_send_raw(
        this->getMessage(),
        this->m_rf_channel,
        this->m_channel_number,
        this->m_packet.getBytes(),
        this->m_packet.getSize()
    );
}

/**
 * @brief   Get the RF channel
 * 
 * @retval  RF Channel
 */

uint32_t SendPacketRaw::getRFChannel()
{
    return this->m_rf_channel;
}

/**
 * @brief   Get the channel number
 * 
 * @retval  Channel number
 */

uint32_t SendPacketRaw::getChannelNumber()
{
    return this->m_channel_number;
}

 
/**
 * @brief   Get the packet to send
 * 
 * @retval  Packet to send
 */

Packet& SendPacketRaw::getPacket()
{
    return this->m_packet;
}
