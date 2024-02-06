#include "phy/schedpkt.hpp"

using namespace whad::phy;

/** Schedule Packet **/

/**
 * @brief       Create a SchedulePacket message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SchedulePacket::SchedulePacket(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SchedulePacket message from timestamp and packet.
 * 
 * @param[in]   packet      Packet to schedule
 * @param[in]   timestamp   Timerstamp at which the provided packet must be sent
 **/

SchedulePacket::SchedulePacket(Packet &packet, Timestamp &timestamp) : PhyMsg()
{
    whad_phy_sched_packet(
        this->getRaw(),
        packet.getBytes(),
        packet.getSize(),
        timestamp.getSeconds(),
        timestamp.getMicroseconds()
    );
}


/**
 * @brief       Get the scheduled packet object
 * 
 * @retval      Scheduled packet
 **/

Packet SchedulePacket::getPacket()
{
    whad_phy_sched_packet_t sched_packet;

    whad_phy_sched_packet_parse(
        this->getRaw(),
        &sched_packet
    );

    return Packet(sched_packet.packet.payload, sched_packet.packet.length);
}


/**
 * @brief       Get the scheduled packet timestamp object
 * 
 * @retval      Scheduled packet timestamp
 **/

Timestamp SchedulePacket::getTimestamp()
{
    whad_phy_sched_packet_t sched_packet;

    whad_phy_sched_packet_parse(
        this->getRaw(),
        &sched_packet
    );

    return Timestamp(sched_packet.ts.ts_sec, sched_packet.ts.ts_usec);    
}

/** Scheduled packet notification **/

/**
 * @brief       Create a PacketScheduled message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

PacketScheduled::PacketScheduled(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a PacketScheduled message with specific packet ID.
 * 
 * @param[in]   packetId    Packet identifier
 * @param[in]   full        Set to true to indicate the scheduled packets list is full.
 **/

PacketScheduled::PacketScheduled(uint8_t packetId, bool full) : PhyMsg()
{
    whad_phy_packet_scheduled(
        this->getRaw(), packetId, full
    );
}


/**
 * @brief       Parse the current message.
 * 
 * @retval      True if parsing is OK, false otherwise.
 **/

bool PacketScheduled::parse()
{
    return (whad_phy_packet_scheduled_parse(this->getRaw(), &this->m_packet) == WHAD_SUCCESS);
}


/**
 * @brief       Get the packet identifier.
 * 
 * @retval      Packet identifier
 **/

uint8_t PacketScheduled::getPacketId()
{
    if (this->parse())
    {
        return this->m_packet.id;
    }

    return 0;
}


/**
 * @brief       Determine if the scheduled packets list is full.
 * 
 * @retval      True if list is full, false otherwise.
 **/

bool PacketScheduled::isFull()
{
    if (this->parse())
    {
        return this->m_packet.full;
    }

    return false;
}


/** Scheduled packet sent notification **/


/**
 * @brief       Create a ScheduledPacketSent message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

ScheduledPacketSent::ScheduledPacketSent(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a ScheduledPacketSent message with a specific packet ID.
 * 
 * @param[in]   packetId    Packet identifier.
 **/

ScheduledPacketSent::ScheduledPacketSent(uint32_t packetId) : PhyMsg()
{
    whad_phy_sched_packet_sent(this->getRaw(), packetId);
}


/**
 * @brief       Get message packet ID.
 * 
 * @retval      Packet ID
 **/

uint32_t ScheduledPacketSent::getPacketId()
{
    uint32_t packetId = 0;

    whad_phy_sched_packet_sent_parse(this->getRaw(), &packetId);

    return packetId;
}