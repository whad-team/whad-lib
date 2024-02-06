#include "phy/setaskmod.hpp"

using namespace whad::phy;

/** ASK modulation **/

/**
 * @brief       Create a SetAskMod message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetAskMod::SetAskMod(whad::NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetAskMod message.
 * 
 * @param[in]   ook     On/Off keying is enabled if set to true, disabled otherwise.
 **/

SetAskMod::SetAskMod(bool ook) : PhyMsg()
{
    whad_phy_set_ask_mod(
        this->getRaw(),
        ook
    );
}


/**
 * @brief       Determine if OnOff keying is enabled or not.
 * 
 * @retval      OOK is enabled if true, disabled otherwise.
 **/

bool SetAskMod::isOok()
{
    bool bIsOok = false;

    /* Parse message and extract OOK parameter. */
    whad_phy_set_ask_mod_parse(this->getRaw(), &bIsOok);
    return bIsOok;
}