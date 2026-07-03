#include <ble/connected.hpp>

using namespace whad::ble;

Connected::Connected(BleMsg &message) : BleMsg(message)
{
    /* TODO: Unpack in C and C++ */
}

/**
 * @brief       Connection notification constructor. 
 * 
 * @param[in]   connHandle  Connection handle assigned to this connection
 * @param[in]   advAddr     Advertiser BD address
 * @param[in]   initAddr    Initiator BD address
 * @param[in]   phy         PHY configured when connection request has been received
 **/

Connected::Connected(uint32_t connHandle, BDAddress advAddr, BDAddress initAddr, Phy phy)  : BleMsg()
{
    m_connHandle = connHandle;
    m_advAddr = advAddr;
    m_initAddr = initAddr;
    m_phy = phy;
}


/**
 * @brief   Pack parameters into a BleMsg.
 */

void Connected::pack()
{
    whad_ble_notify_connected(
        this->getMessage(),
        
        /* Specify advertiser BD address */
        (whad_ble_addrtype_t)m_advAddr.getType(), m_advAddr.getAddressBuf(),

        /* Specify initiator BD address */
        (whad_ble_addrtype_t)m_initAddr.getType(), m_initAddr.getAddressBuf(),

        /* Connection handle */
        m_connHandle,

        /* PHY */
        (whad_ble_phy_t)m_phy
    );
}


/**
 * @brief   Get advertiser BD address.
 * 
 * @retval  Advertiser BD address.
 */

BDAddress& Connected::getAdvertiserAddr()
{
    return m_advAddr;
}


/**
 * @brief   Get initiator BD address.
 * 
 * @retval  Initiator BD address.
 */

BDAddress& Connected::getInitiatorAddr()
{
    return m_initAddr;
}


/**
 * @brief   Get connection handle
 * 
 * @retval  Connection handle value
 */

uint32_t Connected::getConnHandle()
{
    return m_connHandle;
}


/**
 * @brief   Get PHY
 * 
 * @retval  RX PHY
 */

Phy Connected::getPhy()
{
    return m_phy;
}

