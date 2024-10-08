#include "phy/packetrx.hpp"

using namespace whad::phy;

/**
 * @brief       Create a PacketReceived message based on raw PHY message.
 *
 * @param[in]   message     Base NanoPb message to use.
 **/

PacketReceived::PacketReceived(NanoPbMsg &message) : PhyMsg(message)
{
    this->unpack();
}


/**
 * @brief       Create a PacketReceived message with corresponding parameters.
 *
 * @param[in]   frequency   Frequency on which this packet has been received
 * @param[in]   rssi        Received signal strength indicator
 * @param[in]   ts          Timestamp at which the packet has been received
 * @param[in]   packet      Packet received
 * @param[in]   syncword    Synchronization word
 * @param[in]   endian      Current packet endianness
 * @param[in]   datarate    Current datarate
 * @param[in]   deviation   Current frequency deviation
 * @param[in]   modulation  Current modulation type
 **/

PacketReceived::PacketReceived(uint32_t frequency, int32_t rssi, Timestamp &ts,
                               Packet &packet, SyncWord &syncword, Endianness endian,
                               uint32_t datarate, uint32_t deviation,
                               ModulationType modulation)
{
    m_frequency = frequency;
    m_rssi = rssi;
    m_timestamp = ts;
    m_packet = packet;
    m_syncword = syncword;
    m_endian = endian;
    m_datarate = datarate;
    m_deviation = deviation;
    m_modulation = modulation;
}


/**
 * @brief   Pack parameters into a NanoPb message.
 */

void PacketReceived::pack()
{
    whad_phy_packet_received(
        this->getMessage(),
        m_frequency,
        m_rssi,
        m_timestamp.getSeconds(),
        m_timestamp.getMicroseconds(),
        m_packet.getBytes(),
        m_packet.getSize(),
        m_syncword.get(),
        m_syncword.getSize(),
        m_deviation,
        m_datarate,
        (whad_phy_endian_t)m_endian,
        (whad_phy_modulation_t)m_modulation
    );
}


/**
 * @brief   Unpack a Phy message into a PacketReceived message.
 */

void PacketReceived::unpack()
{
    whad_phy_received_packet_t packet;
    if (whad_phy_packet_received_parse(this->getMessage(), &packet) == WHAD_SUCCESS)
    {
        m_frequency = packet.freq;
        m_rssi = packet.rssi;
        m_timestamp = Timestamp(packet.ts.ts_sec, packet.ts.ts_usec);
        m_packet.setBytes(packet.packet.payload, packet.packet.length);
    }
    else
    {
        throw WhadMessageParsingError();
    }
}


/**
 * @brief       Get the frequency parameter
 *
 * @retval      Frequency in Hz
 **/

uint32_t PacketReceived::getFrequency()
{
   return m_frequency;
}


/**
 * @brief       Get the RSSI parameter
 *
 * @retval      Received signal strength indicator
 **/

int32_t PacketReceived::getRssi()
{
   return m_rssi;
}


/**
 * @brief       Get the timetamp parameter
 *
 * @retval      Timestamp at which the packet has been received
 **/

Timestamp& PacketReceived::getTimestamp()
{
   return m_timestamp;
}


/**
 * @brief       Get the received packet
 *
 * @retval      Instance of Packet representing the received packet
 **/

Packet& PacketReceived::getPacket()
{
    return m_packet;
}
