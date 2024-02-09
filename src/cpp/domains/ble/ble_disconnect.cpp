#include <ble/disconnect.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as a Disconnect message.
 */

Disconnect::Disconnect(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief       Disconnect message constructor.
 * 
 * @param[in]   connHandle      Connection handle
 **/

Disconnect::Disconnect(uint32_t connHandle) : BleMsg()
{
    m_connHandle = connHandle;
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void Disconnect::pack()
{
    whad_ble_disconnect(this->getMessage(), m_connHandle);
}


/**
 * @brief   Extract parameters fron a BleMsg
 */

void Disconnect::unpack()
{
    whad_result_t result;

    result = whad_ble_disconnect_parse(
        this->getMessage(),
        &m_connHandle
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}