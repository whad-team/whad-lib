#include "phy/schedpkt.hpp"

using namespace whad::phy;

/** Schedule Packet **/

/**
 * @brief       Create a SchedulePacket message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SchedulePacket::SchedulePacket(PhyMsg &message) : PhyMsg(message)
{
    this->unpack();
}


/**
 * @brief       Create a SchedulePacket message from timestamp and packet.
 * 
 * @param[in]   packet      Packet to schedule
 * @param[in]   timestamp   Timerstamp at which the provided packet must be sent
 **/

SchedulePacket::SchedulePacket(Packet &packet, Timestamp &timestamp) : PhyMsg()
{
    m_packet = packet;
    m_timestamp = timestamp;
}


/**
 * @brief       Get the scheduled packet object
 * 
 * @retval      Scheduled packet
 **/

Packet& SchedulePacket::getPacket()
{
   return m_packet;
}


/**
 * @brief       Get the scheduled packet timestamp object
 * 
 * @retval      Scheduled packet timestamp
 **/

Timestamp& SchedulePacket::getTimestamp()
{
    return m_timestamp;    
}

void SchedulePacket::pack()
{
    whad_phy_sched_packet(
        this->getMessage(),
        m_packet.getBytes(),
        m_packet.getSize(),
        m_timestamp.getSeconds(),
        m_timestamp.getMicroseconds()
    );
}

void SchedulePacket::unpack()
{
    whad_phy_sched_packet_t sched_packet;

    if (whad_phy_sched_packet_parse(
        this->getMessage(),
        &sched_packet
    ) == WHAD_SUCCESS)
    {
        m_packet.setBytes(sched_packet.packet.payload, sched_packet.packet.length);
        m_timestamp.set(sched_packet.ts.ts_sec, sched_packet.ts.ts_usec);
    }
    else
    {
        throw WhadMessageParsingError();
    }
}

/** Scheduled packet notification **/

/**
 * @brief       Create a PacketScheduled message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

PacketScheduled::PacketScheduled(PhyMsg &message) : PhyMsg(message)
{
    this->unpack();
}


/**
 * @brief       Create a PacketScheduled message with specific packet ID.
 * 
 * @param[in]   packetId    Packet identifier
 * @param[in]   full        Set to true to indicate the scheduled packets list is full.
 **/

PacketScheduled::PacketScheduled(uint8_t packetId, bool full) : PhyMsg()
{
    m_pktId = packetId;
    m_full = full;
}


/**
 * @brief       Parse the current message.
 **/

void PacketScheduled::unpack()
{
    whad_phy_scheduled_packet_t packet;

    if (whad_phy_packet_scheduled_parse(this->getMessage(), &packet) == WHAD_SUCCESS)
    {
        m_pktId = packet.id;
        m_full = packet.full;
    }
    else
    {
        throw WhadMessageParsingError();
    }
}

void PacketScheduled::pack()
{
    whad_phy_packet_scheduled(
        this->getMessage(), m_pktId, m_full
    );
}

/**
 * @brief       Get the packet identifier.
 * 
 * @retval      Packet identifier
 **/

uint8_t PacketScheduled::getPacketId()
{
    return m_pktId;
}


/**
 * @brief       Determine if the scheduled packets list is full.
 * 
 * @retval      True if list is full, false otherwise.
 **/

bool PacketScheduled::isFull()
{
    return m_full;
}


/** Scheduled packet sent notification **/


/**
 * @brief       Create a ScheduledPacketSent message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

ScheduledPacketSent::ScheduledPacketSent(PhyMsg &message) : PhyMsg(message)
{
    this->unpack();
}


/**
 * @brief       Create a ScheduledPacketSent message with a specific packet ID.
 * 
 * @param[in]   packetId    Packet identifier.
 **/

ScheduledPacketSent::ScheduledPacketSent(uint32_t packetId) : PhyMsg()
{
    m_pktId = packetId;
}


/**
 * @brief       Get message packet ID.
 * 
 * @retval      Packet ID
 **/

uint32_t ScheduledPacketSent::getPacketId()
{
    return m_pktId;
}


/**
 * @brief   Extract parameters from underlying PhyMsg.
 */

void ScheduledPacketSent::unpack()
{
    if (whad_phy_sched_packet_sent_parse(this->getMessage(), &m_pktId) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}


/**
 * @brief   Pack parameters in the corresponding PhyMsg.
 */

void ScheduledPacketSent::pack()
{
    whad_phy_sched_packet_sent(this->getMessage(), m_pktId);
}