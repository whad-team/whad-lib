#include "phy/sendpkt.hpp"

using namespace whad::phy;

/** Send Packet **/

/**
 * @brief       Create a SendPacket message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SendPacket::SendPacket(PhyMsg &message) : PhyMsg(message)
{
    this->unpack();
}


/**
 * @brief       Create a SendPacket message from a packet
 * 
 * @param[in]   packet  Packet to send
 **/

SendPacket::SendPacket(Packet &packet) : PhyMsg()
{
    m_packet = packet;
}


/**
 * @brief       Get the packet to send
 * 
 * @retval      Packet object to send
 **/

Packet& SendPacket::getPacket()
{
    return m_packet;
}


/**
 * @brief   Pack parameters into a PhyMsg.
 */

void SendPacket::pack()
{
    whad_phy_send(
        this->getMessage(),
        m_packet.getBytes(),
        m_packet.getSize()
    );   
}


/**
 * @brief   Extract parameters from a PhyMsg.
 */

void SendPacket::unpack()
{
    whad_phy_packet_t packet;

    if (whad_phy_send_parse(this->getMessage(), &packet) == WHAD_SUCCESS)
    {
        /* Copy packet bytes. */
        m_packet.setBytes(packet.payload, packet.length);
    }
    else
    {
        throw WhadMessageParsingError();
    }
}