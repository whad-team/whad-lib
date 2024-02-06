#include "phy/monitor.hpp"

using namespace whad::phy;

/** Monitor mode **/

/**
 * @brief       Create a MonitorMode message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

MonitorMode::MonitorMode(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a MonitorMode message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

MonitorMode::MonitorMode() : PhyMsg()
{
    whad_phy_monitor_mode(
        this->getRaw()
    );
}