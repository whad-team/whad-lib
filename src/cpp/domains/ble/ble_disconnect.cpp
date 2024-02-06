#include <ble/disconnect.hpp>

using namespace whad::ble;

/**
 * @brief       Disconnect message constructor.
 * 
 * @param[in]   connHandle      Connection handle
 **/

Disconnect::Disconnect(uint32_t connHandle) : BleMsg()
{
    whad_ble_disconnect(this->getRaw(), connHandle);
}
