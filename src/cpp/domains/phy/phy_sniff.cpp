#include "phy/sniff.hpp"

using namespace whad::phy;

/** Sniff mode **/

/**
 * @brief       Create a SniffMode message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SniffMode::SniffMode(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SniffMode message.
 * 
 * @param[in]   iqMode  If set to true, will sniff IQ samples otherwise will sniff packets.
 **/

SniffMode::SniffMode(bool iqMode) : PhyMsg()
{
    whad_phy_sniff_mode(
        this->getRaw(),
        iqMode
    );
}

/**
 * @brief       Determine if IQ sniffing mode is enabled.
 * 
 * @retval      True if IQ sniffing is enabled, false otherwise.
 **/

bool SniffMode::isIqModeEnabled()
{
    bool enabled = false;

    whad_phy_sniff_mode_parse(
        this->getRaw(),
        &enabled
    );

    return enabled;
}