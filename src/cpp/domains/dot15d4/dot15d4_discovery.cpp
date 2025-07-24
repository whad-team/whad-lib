#include <dot15d4/discovery.hpp>

using namespace whad::dot15d4;

/**
 * @brief       Discovery message constructor.
 * 
 * @param[in]   src         Specify the source of the discovered message
 * @param[in]   dst         Specify the destination of the discovered message
 * @param[in]   slot         Specify the slot of the discovered message
 * @param[in]   offset         Specify the offset of the discovered message
 **/

Discovery::Discovery(uint16_t src, uint16_t dst, uint16_t slot, uint16_t offset) : Dot15d4Msg()
{
    /* Save parameters. */
    m_src = src;
    m_dst = dst;
    m_slot = slot;
    m_offset = offset;
}

uint16_t Discovery::getSrc(){
    return m_src;
}

uint16_t Discovery::getDst(){
    return m_dst;
}

uint16_t Discovery::getSlot(){
    return m_slot;
}

uint16_t Discovery::getOffset(){
    return m_offset;
}

void Discovery::pack()
{
    whad_dot15d4_discovery(
        this->getMessage(),
        m_src,
        m_dst,
        m_slot,
        m_offset
    );
}