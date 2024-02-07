#include "phy/stop.hpp"

using namespace whad::phy;

/**
 * @brief       Create a Stop message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

Stop::Stop(PhyMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a Stop message.
 **/

Stop::Stop() : PhyMsg()
{
}


/**
 * @brief   Create a Stop message.
 */

void Stop::pack()
{
    whad_phy_stop(this->getMessage());
}
