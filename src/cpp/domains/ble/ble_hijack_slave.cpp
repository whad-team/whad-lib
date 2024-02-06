#include <ble/hijack_slave.hpp>

using namespace whad::ble;

/**
 * @brief       HijackSlave message constructor.
 * 
 * @param[in]   accessAddress   Target connection access address
 **/

HijackSlave::HijackSlave(uint32_t accessAddress) : BleMsg()
{
    whad_ble_hijack_slave(this->getRaw(), accessAddress);
}