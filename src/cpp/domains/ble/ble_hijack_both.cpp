#include <ble/hijack_both.hpp>

using namespace whad::ble;

/**
 * @brief       HijackBoth message constructor.
 * 
 * @param[in]   accessAddress   Target connection access address
 **/

HijackBoth::HijackBoth(uint32_t accessAddress) : BleMsg()
{
    whad_ble_hijack_both(this->getRaw(), accessAddress);
}
