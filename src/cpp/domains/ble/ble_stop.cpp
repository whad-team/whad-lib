#include <ble/stop.hpp>

using namespace whad::ble;

/**
 * @brief       Stop message constructor.
 **/

Stop::Stop(void) : BleMsg()
{
    whad_ble_stop(this->getMessage());
}