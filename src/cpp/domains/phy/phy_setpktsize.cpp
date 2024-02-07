#include "phy/setpktsize.hpp"

using namespace whad::phy;


/** Set Packet size **/

/**
 * @brief       Create a SetPacketSize message based on raw PHY message.
 * 
 * @param[in]   message     Base PhyMsg message to use.
 **/

SetPacketSize::SetPacketSize(PhyMsg &message) : PhyMsg(message)
{
    this->unpack();
}


/**
 * @brief       Create a SetPacketSize message with a specific size
 * 
 * @param[in]   size     Packet size to use, in bytes
 **/

SetPacketSize::SetPacketSize(uint32_t size) : PhyMsg()
{
    m_size = size;
}


/**
 * @brief       Get the specified packet size
 * 
 * @retval      Packet size specified, in bytes
 **/

uint32_t SetPacketSize::getSize()
{
    uint32_t size = 0;

    whad_phy_set_packet_size_parse(
        this->getRaw(),
        &size
    );

    return size;
}


/**
 * @brief   Pack parameters into a PhyMsg.
 */

void SetPacketSize::pack()
{
    whad_phy_set_packet_size(
        this->getMessage(),
        m_size
    );   
}


/**
 * @brief   Extract parameters from PhyMsg.
 */

void SetPacketSize::unpack()
{
    if (whad_phy_set_packet_size_parse(this->getMessage(), &m_size) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}