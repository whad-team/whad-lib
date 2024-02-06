#include <ble/jam_adv.hpp>

using namespace whad::ble;

/**
 * @brief       JamAdv message constructor.
 * 
 **/

JamAdv::JamAdv(void) : BleMsg()
{
    whad_ble_jam_adv(this->getRaw());
}


/**
 * @brief       JamAdv message constructor.
 * 
 * @param[in]   channel     Channel to jam.
 **/

JamAdv::JamAdv(uint32_t channel) : BleMsg()
{
    whad_ble_jam_adv_channel(this->getRaw(), channel);
}