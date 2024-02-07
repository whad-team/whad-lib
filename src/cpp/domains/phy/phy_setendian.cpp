#include "phy/setendian.hpp"

using namespace whad::phy;

/**
 * @brief       Create a SetEndianness message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetEndianness::SetEndianness(PhyMsg &message) : PhyMsg(message)
{
    this->unpack();
}


/**
 * @brief       Create a SetEndianness message with specific endianness
 * 
 * @param[in]   endian  Endianness to use
 **/

SetEndianness::SetEndianness(Endianness endian) : PhyMsg()
{
   m_endian = endian;
}


/**
 * @brief       Get the endianness specified in this message
 * 
 * @retval      Endianness to use
 **/

Endianness SetEndianness::getEndianness()
{
    return m_endian;
}


/**
 * @brief   Pack parameters into a PhyMsg.
 */

void SetEndianness::pack()
{
    whad_phy_set_endianness(
        this->getMessage(),
        (whad_phy_endian_t)m_endian
    );
}


/**
 * @brief   Extract parameters from PhyMsg.
 */

void SetEndianness::unpack()
{
    if (whad_phy_set_endianness_parse(this->getMessage(),
                                      (whad_phy_endian_t *)&m_endian) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}