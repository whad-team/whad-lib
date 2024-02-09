#include <ble/hijacked.hpp>

using namespace whad::ble;


/**
 * @brief   Parse a BleMsg as an Hijacked message
 * 
 * @param[in]   message Message to parse
 */

Hijacked::Hijacked(BleMsg &message) : BleMsg(message), HijackBase()
{
}

/**
 * @brief       Notify a successful/unsuccessful connection hijacking
 * 
 * @param[in]   accessAddress       Connection access address
 * @param[in]   success             If true hijacking was successful, unsuccessful otherwise 
 **/

Hijacked::Hijacked(uint32_t accessAddress, bool success) : BleMsg(), HijackBase(accessAddress)
{
    m_success = success;
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void Hijacked::pack()
{
    whad_ble_hijacked(
        this->getMessage(),
        m_accessAddr,
        m_success
    );
}


/**
 * @brief   Extract parameters from BleMsg
 */

void Hijacked::unpack()
{
    whad_result_t result;
    whad_ble_hijacked_params_t params;

    result = whad_ble_hijacked_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
    else
    {
        m_accessAddr = params.access_address;
        m_success = params.success;
    }
}
