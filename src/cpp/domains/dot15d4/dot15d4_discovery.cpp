#include <dot15d4/discovery.hpp>

using namespace whad::dot15d4;

/**
 * @brief       Discovery message constructor.
 * 
 * @param[in]   pkt         the received pkt on the communication
 * @param[in]   size        the size of the discovered message
 * @param[in]   slot         Specify the slot of the discovered message
 * @param[in]   offset         Specify the offset of the discovered message
 **/

DiscoveredCommunication::DiscoveredCommunication(uint8_t* pkt, size_t size, uint16_t slot, uint16_t offset) : Dot15d4Msg()
{
    /* Save parameters. */
    m_pkt = pkt;
    m_size = size;
    m_slot = slot;
    m_offset = offset;
}

uint8_t* DiscoveredCommunication::getPkt(){
    return m_pkt;
}

size_t DiscoveredCommunication::getSize(){
    return m_size;
}

uint16_t DiscoveredCommunication::getSlot(){
    return m_slot;
}

uint16_t DiscoveredCommunication::getOffset(){
    return m_offset;
}

void DiscoveredCommunication::pack()
{
    whad_dot15d4_discovered_communication(
        this->getMessage(),
        m_pkt,
        m_size,
        m_slot,
        m_offset
    );
}