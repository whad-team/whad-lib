#include <ble/jam_act_conn.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as JamActiveConn message
 */

JamActiveConn::JamActiveConn(BleMsg &message) : BleMsg(message), HijackBase()
{
}


/**
 * @brief       JamActiveConn message constructor.
 * 
 * @param[in]   accessAddress   Connection access address
 **/

JamActiveConn::JamActiveConn(uint32_t accessAddress) : BleMsg(), HijackBase(accessAddress)
{
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void JamActiveConn::pack()
{
    whad_ble_jam_active_conn(this->getMessage(), m_accessAddr);
}


/**
 * @brief   Extract parameters from a BleMsg.
 */

void JamActiveConn::unpack()
{
    whad_result_t result;

    result = whad_ble_jam_active_conn_parse(
        this->getMessage(),
        &m_accessAddr
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}