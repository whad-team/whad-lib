#include "phy/start.hpp"

using namespace whad::phy;

/** Start **/

/**
 * @brief       Create a Start message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

Start::Start(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a Start message.
 **/

Start::Start() : PhyMsg()
{
    whad_phy_start(this->getRaw());
}