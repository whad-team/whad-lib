#include <ble/hijack_master.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as a HijackMaster message.
 * 
 * @param[in]   message Message to parse
 */

HijackMaster::HijackMaster(BleMsg &message) : BleMsg(message), HijackBase()
{
    this->unpack();
}


/**
 * @brief       HijackMaster message constructor.
 * 
 * @param[in]   accessAddress   Target connection access address
 **/

HijackMaster::HijackMaster(uint32_t accessAddress) : BleMsg(), HijackBase(accessAddress)
{
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void HijackMaster::pack()
{
    whad_ble_hijack_master(this->getMessage(), m_accessAddr);
}


/**
 * @brief   Extract parameters from BleMsg.
 */

void HijackMaster::unpack()
{
    whad_result_t result;

    result = whad_ble_hijack_master_parse(
        this->getMessage(),
        &m_accessAddr
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}