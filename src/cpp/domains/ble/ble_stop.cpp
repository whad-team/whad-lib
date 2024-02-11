#include <ble/stop.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as a Stop message
 * 
 * @param[in]   message     Message to parse
 */

Stop::Stop(BleMsg &message) : BleMsg(message)
{
}


/**
 * @brief       Stop message constructor.
 **/

Stop::Stop(void) : BleMsg()
{
}


/**
 * @brief   Pack a Stop message into a BleMsg
 */

void Stop::pack()
{
    whad_ble_stop(this->getMessage());
}