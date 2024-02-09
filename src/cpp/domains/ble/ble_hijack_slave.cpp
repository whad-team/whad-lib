#include <ble/hijack_slave.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as a HijackSlave message
 * 
 * @param[in]   message Message to parse
 */

HijackSlave::HijackSlave(BleMsg &message) : BleMsg(message), HijackBase()
{
    this->unpack();
}


/**
 * @brief       HijackSlave message constructor.
 * 
 * @param[in]   accessAddress   Target connection access address
 **/

HijackSlave::HijackSlave(uint32_t accessAddress) : BleMsg(), HijackBase(accessAddress)
{
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void HijackSlave::pack()
{
    whad_ble_hijack_slave(this->getMessage(), m_accessAddr);
}


/**
 * @brief   Extract parameters from a BleMsg
 */

void HijackSlave::unpack()
{
    whad_result_t result;

    result = whad_ble_hijack_slave_parse(this->getMessage(), &m_accessAddr);

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}