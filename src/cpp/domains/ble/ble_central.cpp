#include <ble/central.hpp>

using namespace whad::ble;


/**
 * @brief   Parse a CentralMode message.
 */

CentralMode::CentralMode(BleMsg &message) : BleMsg(message)
{
}

/**
 * @brief       CentralMode message constructor.
 **/

CentralMode::CentralMode(void) : BleMsg()
{
}


/**
 * @brief   Create a CentralMode message.
 */

void CentralMode::pack()
{
    whad_ble_central_mode(this->getMessage());
}