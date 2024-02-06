#include "phy/setpktsize.hpp"

using namespace whad::phy;


/** Set Packet size **/

/**
 * @brief       Create a SetPacketSize message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetPacketSize::SetPacketSize(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetPacketSize message with a specific size
 * 
 * @param[in]   size     Packet size to use, in bytes
 **/

SetPacketSize::SetPacketSize(uint32_t size) : PhyMsg()
{
    whad_phy_set_packet_size(
        this->getRaw(),
        size
    );
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