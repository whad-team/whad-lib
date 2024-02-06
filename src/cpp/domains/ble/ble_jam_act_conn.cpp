#include <ble/jam_act_conn.hpp>

using namespace whad::ble;

/**
 * @brief       JamActiveConn message constructor.
 * 
 * @param[in]   accessAddress   Connection access address
 **/

JamActiveConn::JamActiveConn(uint32_t accessAddress) : BleMsg()
{
    whad_ble_jam_active_conn(this->getRaw(), accessAddress);
}