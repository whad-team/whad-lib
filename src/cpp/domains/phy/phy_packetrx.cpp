#include "phy/packetrx.hpp"

using namespace whad::phy;

/** Received packet notification **/

/**
 * @brief       Create a PacketReceived message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

PacketReceived::PacketReceived(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a PacketReceived message with corresponding parameters.
 * 
 * @param[in]   frequency   Frequency on which this packet has been received
 * @param[in]   rssi        Received signal strength indicator
 * @param[in]   ts          Timestamp at which the packet has been received
 * @param[in]   packet      Packet received
 **/

PacketReceived::PacketReceived(uint32_t frequency, int32_t rssi, Timestamp &ts, Packet &packet)
{
    whad_phy_packet_received(
        this->getRaw(),
        frequency,
        rssi,
        ts.getSeconds(),
        ts.getMicroseconds(),
        packet.getBytes(),
        packet.getSize()
    );
}


/**
 * @brief       Parse the current message.
 * 
 * @retval      True if parsing is OK, false otherwise.
 **/

bool PacketReceived::parse()
{
    return (whad_phy_packet_received_parse(this->getRaw(), &this->m_packet) == WHAD_SUCCESS);
}


/**
 * @brief       Get the frequency parameter
 * 
 * @retval      Frequency in Hz
 **/

uint32_t PacketReceived::getFrequency()
{
    if (this->parse())
    {
        return this->m_packet.freq;
    }

    return 0;
}


/**
 * @brief       Get the RSSI parameter
 * 
 * @retval      Received signal strength indicator
 **/

int32_t PacketReceived::getRssi()
{
    if (this->parse())
    {
        return this->m_packet.rssi;
    }

    return 0;   
}


/**
 * @brief       Get the timetamp parameter
 * 
 * @retval      Timestamp at which the packet has been received
 **/

Timestamp PacketReceived::getTimestamp()
{
    if (this->parse())
    {
        return Timestamp(this->m_packet.ts.ts_sec, this->m_packet.ts.ts_usec);
    }

    return Timestamp(0,0);
}


/**
 * @brief       Get the received packet
 * 
 * @retval      Instance of Packet representing the received packet
 **/

Packet PacketReceived::getPacket()
{
    if (this->parse())
    {
        return Packet(this->m_packet.packet.payload, this->m_packet.packet.length);
    }
    else
    {
        /* Throw parsing error. */
        throw WhadMessageParsingError();
    }
}