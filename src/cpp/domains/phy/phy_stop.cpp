#include "phy/stop.hpp"

using namespace whad::phy;

/** Stop **/

/**
 * @brief       Create a Stop message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

Stop::Stop(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a Stop message.
 **/

Stop::Stop() : PhyMsg()
{
    whad_phy_stop(this->getRaw());
}
