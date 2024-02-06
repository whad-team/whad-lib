#include <ble/central.hpp>

using namespace whad::ble;

/**
 * @brief       CentralMode message constructor.
 **/

CentralMode::CentralMode(void) : BleMsg()
{
    whad_ble_central_mode(this->getMessage());
}