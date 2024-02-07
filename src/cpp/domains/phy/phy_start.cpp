#include "phy/start.hpp"

using namespace whad::phy;

/**
 * @brief       Create a Start message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

Start::Start(PhyMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Default constructor.
 **/

Start::Start() : PhyMsg()
{
}


/**
 * @brief   Create a Start message.
 */

void Start::pack()
{
    whad_phy_start(this->getMessage());
}