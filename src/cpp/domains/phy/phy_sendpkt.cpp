#include "phy/sendpkt.hpp"

using namespace whad::phy;

/** Send Packet **/

/**
 * @brief       Create a SendPacket message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SendPacket::SendPacket(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SendPacket message from a packet
 * 
 * @param[in]   packet  Packet to send
 **/

SendPacket::SendPacket(Packet &packet) : PhyMsg()
{
    whad_phy_send(
        this->getRaw(),
        packet.getBytes(),
        packet.getSize()
    );
}


/**
 * @brief       Get the packet to send
 * 
 * @retval      Packet object to send
 **/

Packet SendPacket::getPacket()
{
    memset(this->m_packet.payload, 0, sizeof(this->m_packet.payload));

    whad_phy_send_parse(
        this->getRaw(),
        &this->m_packet
    );

    return Packet(this->m_packet.payload, this->m_packet.length);
}
