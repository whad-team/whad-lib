#include "phy/setdatarate.hpp"

using namespace whad::phy;

/**
 * @brief       Create a SetDatarate message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetDatarate::SetDatarate(PhyMsg &message) : PhyMsg(message)
{
    this->unpack();
}


/**
 * @brief       Create a SetDatarate message with specific data rate
 * 
 * @param[in]   datarate    Data rate to use in bits/second
 **/

SetDatarate::SetDatarate(uint32_t datarate)
{
    m_datarate = datarate;
}


/**
 * @brief       Get the data rate specified in this message
 * 
 * @retval      Datarate in bits/second
 **/

uint32_t SetDatarate::getDatarate()
{
    return m_datarate;
}


/**
 * @brief   Pack parameters into a PhyMsg.
 */

void SetDatarate::pack()
{
    whad_phy_set_datarate(
        this->getMessage(),
        m_datarate
    );   
}


/**
 * @brief   Extract parameters fron a PhyMsg.
 */

void SetDatarate::unpack()
{
    if (whad_phy_set_datarate_parse(this->getMessage(), &m_datarate) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}