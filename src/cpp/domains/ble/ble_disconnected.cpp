#include <ble/disconnected.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as a Disconnected message.
 * 
 * @param[in]   message Message to parse
 */

Disconnected::Disconnected(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief       Disconnection notification constructor. 
 * 
 * @param[in]   connHandle  Connection handle assigned to this connection
 * @param[in]   reason      Disconnection reason (see BLE specs.)
 **/

Disconnected::Disconnected(uint32_t connHandle, uint32_t reason) : BleMsg()
{
    m_connHandle = connHandle;
    m_reasonCode = reason;
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void Disconnected::pack()
{
    whad_ble_notify_disconnected(this->getMessage(), m_connHandle, m_reasonCode);
}


/**
 * @brief   Extract parameters from a BleMsg
 */

void Disconnected::unpack()
{
    whad_result_t result;
    whad_ble_disconnected_params_t params;

    result = whad_ble_notify_disconnected_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}


/**
 * @brief   Retrieve the connection handle
 * 
 * @retval  Connection handle value
 */

uint32_t Disconnected::getConnHandle()
{
    return m_connHandle;
}


/**
 * @brief   Retrieve the reason code
 * 
 * @retval  Reason code
 */

uint32_t Disconnected::getReasonCode()
{
    return m_reasonCode;
}