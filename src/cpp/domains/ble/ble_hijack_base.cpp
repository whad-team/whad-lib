#include <ble/hijack_base.hpp>

using namespace whad::ble;

/**
 * @brief   Default constructor
 */

HijackBase::HijackBase()
{
    m_accessAddr = 0;
}


/**
 * @brief   Constructor, specifies the access address to use
 * 
 * @param[in]   accessAddress   Access address to use
 */

HijackBase::HijackBase(uint32_t accessAddress)
{
    m_accessAddr = accessAddress;
}


/**
 * @brief   Retrieve the access address
 * 
 * @retval  Access Address value
 */

uint32_t HijackBase::getAccessAddress()
{
    return m_accessAddr;
}