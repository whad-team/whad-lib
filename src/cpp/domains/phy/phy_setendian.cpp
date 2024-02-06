#include "phy/setendian.hpp"

using namespace whad::phy;


/** Set endianness **/

/**
 * @brief       Create a SetEndianness message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetEndianness::SetEndianness(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetEndianness message with specific endianness
 * 
 * @param[in]   endian  Endianness to use
 **/

SetEndianness::SetEndianness(Endianness endian) : PhyMsg()
{
    whad_phy_set_endianness(
        this->getRaw(),
        (whad_phy_endian_t)endian
    );
}


/**
 * @brief       Get the endianness specified in this message
 * 
 * @retval      Endianness to use
 **/

Endianness SetEndianness::getEndianness()
{
    whad_phy_endian_t endian;

    whad_phy_set_endianness_parse(
        this->getRaw(),
        &endian
    );

    return (Endianness)endian;
}
