#include <ble/start.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as a Start message.
 * 
 * @param[in]   message     Message to parse
 */

Start::Start(BleMsg &message) : BleMsg(message)
{
}


/**
 * @brief       Start message constructor.
 **/

Start::Start(void) : BleMsg()
{
    whad_ble_start(this->getMessage());
}


/**
 * @brief   Create a Start message.
 */

void Start::pack()
{
    whad_ble_start(this->getMessage());
}