#include <ble/hijack_master.hpp>

using namespace whad::ble;

/**
 * @brief       HijackMaster message constructor.
 * 
 * @param[in]   accessAddress   Target connection access address
 **/

HijackMaster::HijackMaster(uint32_t accessAddress) : BleMsg()
{
    whad_ble_hijack_master(this->getMessage(), accessAddress);
}