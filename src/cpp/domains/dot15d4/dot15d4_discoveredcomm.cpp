#include <dot15d4/discoveredcomm.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a DiscoveredCommunication message.
 */

DiscoveredCommunication::DiscoveredCommunication(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       DiscoveredCommunication message constructor.
 * 
 * @param[in]   slot            Specify the slot of the discovered communication
 * @param[in]   offset          Specify the offset associated with the communication
 * @param[in]   pPdu            Pointer to a byte buffer representing the received packet
 * @param[in]   length          PDU length in bytes
 **/

DiscoveredCommunication::DiscoveredCommunication(uint64_t slot, uint32_t offset, uint8_t *pPdu, uint32_t length) : Dot15d4Msg()
{
    /* Save slot. */
    m_slot = slot;

    /* Save offset*/
    m_offset = offset;

    /* Save PDU. */
    m_pdu = PDU(pPdu, length);
}




/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void DiscoveredCommunication::pack()
{
    whad_dot15d4_packet_t pdu;
    memcpy(pdu.bytes, m_pdu.getBytes(), m_pdu.getSize());
    pdu.length = m_pdu.getSize();


    whad_dot15d4_discovered_comm(
        this->getMessage(),
        m_slot,
        m_offset,
        m_pdu.getBytes(),
        m_pdu.getSize()
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void DiscoveredCommunication::unpack()
{
    whad_result_t result;

    uint64_t slot;
    uint32_t offset;

    whad_dot15d4_packet_t pdu;
    
    result = whad_dot15d4_discovered_comm_parse(
        this->getMessage(),
        &slot, 
        &offset, 
        pdu.bytes, 
        (uint32_t*)(&(pdu.length))
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_slot = slot;
        m_offset = offset;
        m_pdu.setBytes(pdu.bytes, pdu.length);
    }
}


/**
 * @brief   Retrieve the dot15d4 slot used
 * 
 * @retval  absolute slot number
 */

uint64_t DiscoveredCommunication::getSlot()
{
    return m_slot;
}


/**
 * @brief   Retrieve the offset of the communication
 * 
 * @retval  offset
 */

uint32_t DiscoveredCommunication::getOffset()
{
    return m_offset;
}

/**
 * @brief   Retrieve the PDU to send
 * 
 * @retval  Reference to the PDU object containing the bytes to send
 */

PDU& DiscoveredCommunication::getPdu()
{
    return m_pdu;
}