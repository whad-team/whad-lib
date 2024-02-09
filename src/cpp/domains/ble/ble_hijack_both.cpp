#include <ble/hijack_both.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg message as a HijackBoth message
 */

HijackBoth::HijackBoth(BleMsg &message) : BleMsg(message), HijackBase()
{
    this->unpack();
}


/**
 * @brief       HijackBoth message constructor.
 * 
 * @param[in]   accessAddress   Target connection access address
 **/

HijackBoth::HijackBoth(uint32_t accessAddress) : BleMsg(), HijackBase(accessAddress)
{
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void HijackBoth::pack()
{
    whad_ble_hijack_both(this->getMessage(), m_accessAddr);
}


/**
 * @brief   Extract parameters from a BleMsg
 */

void HijackBoth::unpack()
{
    whad_result_t result;

    result = whad_ble_hijack_both_parse(
        this->getMessage(),
        &m_accessAddr
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}