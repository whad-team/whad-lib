#include <ble/disconnected.hpp>

using namespace whad::ble;

/**
 * @brief       Disconnection notification constructor. 
 * 
 * @param[in]   connHandle  Connection handle assigned to this connection
 * @param[in]   reason      Disconnection reason (see BLE specs.)
 **/

Disconnected::Disconnected(uint32_t connHandle, uint32_t reason) : BleMsg()
{
    whad_ble_notify_disconnected(this->getRaw(), connHandle, reason);
}
