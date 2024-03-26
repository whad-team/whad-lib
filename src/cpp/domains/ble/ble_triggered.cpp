#include <ble/triggered.hpp>

using namespace whad::ble;

Triggered::Triggered(BleMsg &message) : BleMsg(message)
{
}

/**
 * @brief       Connection notification constructor. 
 * 
 * @param[in]   id          Prepared sequence id that has been triggered
 **/

Triggered::Triggered(uint8_t id)  : BleMsg()
{
    m_id = id;
}


/**
 * @brief   Pack parameters into a BleMsg.
 */

void Triggered::pack()
{
    whad_ble_triggered(
        this->getMessage(),
        m_id
    );
}


/**
 * @brief   Get sequence ID.
 * 
 * @retval  Prepared sequence ID.
 */

uint8_t Triggered::getId()
{
    return m_id;
}