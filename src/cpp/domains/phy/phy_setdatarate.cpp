#include "phy/setdatarate.hpp"

using namespace whad::phy;

/** Set datarate **/

/**
 * @brief       Create a SetDatarate message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetDatarate::SetDatarate(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetDatarate message with specific data rate
 * 
 * @param[in]   datarate    Data rate to use in bits/second
 **/

SetDatarate::SetDatarate(uint32_t datarate)
{
    whad_phy_set_datarate(
        this->getRaw(),
        datarate
    );
}


/**
 * @brief       Get the data rate specified in this message
 * 
 * @retval      Datarate in bits/second
 **/

uint32_t SetDatarate::getDatarate()
{
    uint32_t datarate = 0;

    whad_phy_set_datarate_parse(
        this->getRaw(),
        &datarate
    );

    return datarate;
}
