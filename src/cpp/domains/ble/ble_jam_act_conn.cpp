#include <ble/jam_act_conn.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as JamActiveConn message
 */

JamActiveConn::JamActiveConn(BleMsg &message) : BleMsg(message), HijackBase()
{
    /* Default PHY. */
    m_phy = Phy::LE1Mbit;
}


/**
 * @brief       JamActiveConn message constructor.
 * 
 * @param[in]   accessAddress   Connection access address
 **/

JamActiveConn::JamActiveConn(uint32_t accessAddress) : BleMsg(), HijackBase(accessAddress)
{
    /* Default PHY. */
    m_phy = Phy::LE1Mbit;
}


JamActiveConn::JamActiveConn(uint32_t accessAddress, Phy phy) : BleMsg(), HijackBase(accessAddress)
{
    m_phy = phy;
}

/**
 * @brief   Pack parameters into a BleMsg
 */

void JamActiveConn::pack()
{
    whad_ble_jam_active_conn(this->getMessage(), m_accessAddr, (whad_ble_phy_t)m_phy);
}


/**
 * @brief   Extract parameters from a BleMsg.
 */

void JamActiveConn::unpack()
{
    whad_result_t result;

    result = whad_ble_jam_active_conn_parse(
        this->getMessage(),
        &m_accessAddr,
        (whad_ble_phy_t *)&m_phy
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}


/**
 * @brief   Retrieve the PHY associated with this message.
 *
 * @retval  TX PHY
 */

Phy JamActiveConn::getPhy()
{
    return m_phy;
}
