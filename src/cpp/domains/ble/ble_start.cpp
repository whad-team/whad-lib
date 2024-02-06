#include <ble/start.hpp>

using namespace whad::ble;

/**
 * @brief       Start message constructor.
 **/

Start::Start(void) : BleMsg()
{
    whad_ble_start(this->getMessage());
}