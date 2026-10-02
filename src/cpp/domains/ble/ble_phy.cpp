#include <ble/phy.hpp>

using namespace whad::ble;

/**
 * @brief       SetPhy message constructor, parsing an existing message.
 *
 * @param[in]   message     Message to parse.
 */

SetPhy::SetPhy(BleMsg &message) : BleMsg(message)
{
    unpack();
}


/**
 * @brief       SetPhy message constructor.
 *
 * @param[in]   tx  TX PHY to use
 * @param[in]   rx  RX PHY to use
 */

SetPhy::SetPhy(Phy tx, Phy rx) : BleMsg()
{
    m_tx = tx;
    m_rx = rx;
}


/**
 * @brief   Pack parameters into a BleMsg object.
 */

void SetPhy::pack()
{
    whad_ble_set_phy(getMessage(), (whad_ble_phy_t)m_tx, (whad_ble_phy_t)m_rx);
    
}


/**
 * @brief   Extract parameters from a BleMsg object.
 */

void SetPhy::unpack()
{
    whad_ble_phy_t tx,rx;
    whad_result_t result;

    result = whad_ble_set_phy_parse(
        this->getMessage(),
        &tx,
        &rx);

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
    else
    {
        m_rx = (Phy)rx;
        m_tx = (Phy)tx;
    }
}


/**
 * @brief   Get TX PHY
 *
 * @retval  Selected TX PHY
 */

Phy SetPhy::getTx()
{
    return m_tx;
}


/**
 * @brief   Get RX PHY
 *
 * @retval  Selected RX PHY
 */

Phy SetPhy::getRx()
{
    return m_rx;
}


/**
 * PhyUpdated
 **/

/**
 * @brief       PhyUpdated notification message constructor, parsing an existing message.
 *
 * @param[in]   message     Message to parse.
 */

PhyUpdated::PhyUpdated(BleMsg &message) : BleMsg(message)
{
    unpack();
}


/**
 * @brief       PhyUpdated message constructor.
 *
 * @param[in]   tx  TX PHY to use
 * @param[in]   rx  RX PHY to use
 */

PhyUpdated::PhyUpdated(Phy tx, Phy rx) : BleMsg()
{
    m_tx = tx;
    m_rx = rx;
}


/**
 * @brief   Pack parameters into a BleMsg object.
 */

void PhyUpdated::pack()
{
    whad_ble_phy_updated(getMessage(), (whad_ble_phy_t)m_tx, (whad_ble_phy_t)m_rx);
}


/**
 * @brief   Extract parameters from a BleMsg object.
 */

void PhyUpdated::unpack()
{
    whad_ble_phy_t tx,rx;
    whad_result_t result;

    result = whad_ble_phy_updated_parse(
        this->getMessage(),
        &tx,
        &rx);

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
    else
    {
        m_rx = (Phy)rx;
        m_tx = (Phy)tx;
    }
}


/**
 * @brief   Get TX PHY
 *
 * @retval  Selected TX PHY
 */

Phy PhyUpdated::getTx()
{
    return m_tx;
}


/**
 * @brief   Get RX PHY
 *
 * @retval  Selected RX PHY
 */

Phy PhyUpdated::getRx()
{
    return m_rx;
}

/**
 * SetSupportedPhys
 **/

/**
 * @brief       SetSupportedPhys message constructor, parsing an existing message.
 *
 * @param[in]   message    Message to parse.
 */

SetSupportedPhys::SetSupportedPhys(BleMsg &message) : BleMsg(message)
{
    unpack();
}


/**
 * @brief       SetSupportedPhys message constructor.
 */

SetSupportedPhys::SetSupportedPhys() : BleMsg()
{
    m_tx_count = 0;
    m_rx_count = 0;
}


/**
 * @brief       Pack parameters into a BleMsg object.
 */

void SetSupportedPhys::pack()
{
    size_t i;
    whad_ble_phys_t phys;

    phys.tx_count = m_tx_count;
    for (i=0; i<m_tx_count; i++)
    {
        phys.tx[i] = (whad_ble_phy_t)m_tx[i];
    }
    phys.rx_count = m_rx_count;
    for (i=0; i<m_rx_count; i++)
    {
        phys.rx[i] = (whad_ble_phy_t)m_rx[i];
    }

    whad_ble_set_supp_phys(
        getMessage(),
        phys);
}


/**
 * @brief       Extract parameters from a BleMsg object.
 */

void SetSupportedPhys::unpack()
{
    size_t i;
    whad_result_t result;
    whad_ble_phys_t phys;

    result = whad_ble_set_supp_phys_parse(
        getMessage(), &phys
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
    else
    {
        for (i=0; i<phys.tx_count; i++)
        {
            m_tx[i] = (Phy)phys.tx[i];
        }
        for (i=0; i<phys.rx_count; i++)
        {
            m_rx[i] = (Phy)phys.rx[i];
        }
    }
}


/**
 * @brief       Add a TX PHY to the list of supported PHYs
 *
 * @param[in]   phy     TX PHY to add to supported PHYs
 *
 * @retval      true on success, false if the list is full.
 */

bool SetSupportedPhys::addTxPhy(Phy phy)
{
    if (m_tx_count < 4)
    {
        m_tx[m_tx_count++] = phy;
        return true;
    }
    else
    {
        return false;
    }
}


/**
 * @brief       Add a RX PHY to the list of supported PHYs
 *
 * @param[in]   phy     RX PHY to add to supported PHYs
 *
 * @retval      true on success, false if the list is full.
 */

bool SetSupportedPhys::addRxPhy(Phy phy)
{
    if (m_rx_count < 4)
    {
        m_rx[m_rx_count++] = phy;
        return true;
    }
    else
    {
        return false;
    }
}


/**
 * @brief       Get the number of TX PHYs already added.
 *
 * @retval      Number of TX PHYs already present in the list of supported PHYs.
 */

size_t SetSupportedPhys::countTxPhy()
{
    return m_tx_count;
}


/**
 * @brief       Get the number of RX PHYs already added.
 *
 * @retval      Number of RX PHYs already present in the list of supported PHYs.
 */

size_t SetSupportedPhys::countRxPhy()
{
    return m_rx_count;
}


/**
 * @brief       Get the index-th TX PHY from the list of supported PHYs.
 *
 * @retval      TX PHY
 */

Phy SetSupportedPhys::getTxPhy(unsigned int index)
{
    if (index < m_tx_count)
    {
        return m_tx[index];
    }
    else
    {
        return Phy::Undefined;
    }
}


/**
 * @brief       Get the index-th RX PHY from the list of supported PHYs.
 *
 * @retval      RX PHY
 */

Phy SetSupportedPhys::getRxPhy(unsigned int index)
{
    if (index < m_rx_count)
    {
        return m_rx[index];
    }
    else
    {
        return Phy::Undefined;
    }
}

